#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "regexp.h"

/* START TEMPORARY: REMOVE ME */
int main()
{
	const char *expression = "^(abc[def])\\b .*samsung$";
	const char *flags = "gi";
	regexp_mv regexp;
	int error;

	printf( "Expression %s\n", expression );
	printf( "Flags %s\n", flags );

	error = mv_regexp_compile( expression, flags, &regexp );
	printf( "Error code: %i\n", error );
}
/* END TEMPORARY: REMOVE ME */

int mv_regexp_compile( const char * expression, const char * flags, regexp_mv * regexp )
{
	struct regexp_internals_mv internals;
	int i, i_len;
	struct regexp_state_mv state;
	size_t state_length, state_index;
	struct regexp_state_mv *regexp_statelist;
	size_t regexp_statelist_length, regexp_statelist_index;
	size_t expression_index;

	internals.flags			= 0;
	regexp_statelist_length = 0;
	regexp_statelist_index	= 0;
	expression_index		= 0;

	state.type				= MIVA_REGEXP_START;
	state.condition			= NULL;
	state.nest				= NULL;
	state_length			= 0;
	state_index				= 0;

	for ( i = 0, i_len = strlen( flags ); i < i_len; i++ )
	{
		switch ( flags[ i ] )
		{
			case 'g':	internals.flags |= MIVA_REGEXP_FLAG_G;		break;
			case 'i':	internals.flags |= MIVA_REGEXP_FLAG_I;		break;
			case 'm':	internals.flags |= MIVA_REGEXP_FLAG_M;		break;
		}
	}

	strcpy( ( char * ) internals.regexp, expression );

	mv_regexp_compile_state_start( expression, &expression_index, &state, &state_length, &state_index );
	mv_regexp_compile_statelist_append( &regexp_statelist, &regexp_statelist_length, &regexp_statelist_index, &state );

	printf( "internals.flags: %lu\n", internals.flags );

	return 0;
}

int mv_regexp_execute( regexp_mv * regexp, const char * source, int start )
{

	return MIVA_REGEXP_EXECUTE_ERROR_NOMATCH;
}

int mv_regexp_compile_state_start( const char * expression, size_t * expression_index, regexp_state_mv * parent_state, size_t * parent_state_length, size_t * parent_index )
{
	struct regexp_state_mv state;
	size_t state_length, state_index;
	char c = expression[ *expression_index ];

	if ( c == '\0' )
	{
		// if out parent is not the root level state, return error (means we didn't close a '(' or something similar)
		return 0;
	}

	*expression_index = *expression_index + 1;
	printf( "regexp char: %c\n", c );

	switch ( c )
	{
		case '\\' :
			mv_regex_compile_state_escape( expression, expression_index, parent_state, parent_state_length, parent_index );
			break;

		case '^' :
			state.type		= MIVA_REGEXP_BOL;
			state.condition	= NULL;
			state.nest		= NULL;

			mv_regexp_compile_statelist_append( &(parent_state->nest), parent_state_length, parent_index, &state );
			mv_regexp_compile_state_start( expression, expression_index, parent_state, parent_state_length, parent_index );
			break;

		case '$' :
			state.type		= MIVA_REGEXP_EOL;
			state.condition	= NULL;
			state.nest		= NULL;

			mv_regexp_compile_statelist_append( &(parent_state->nest), parent_state_length, parent_index, &state );
			mv_regexp_compile_state_start( expression, expression_index, parent_state, parent_state_length, parent_index );
			break;

		case '*' :
			state.type		= MIVA_REGEXP_STAR;
			state.condition	= NULL;
			state.nest		= NULL;

			break;

		case '+' :
			state.type		= MIVA_REGEXP_PLUS;
			state.condition	= NULL;
			state.nest		= NULL;

			break;

		case '?' :
			state.type		= MIVA_REGEXP_QUEST;
			state.condition	= NULL;
			state.nest		= NULL;

			break;

		case '(' :
			state.type		= MIVA_REGEXP_CAPTURE;
			state.condition	= NULL;
			state.nest		= NULL;
			state_length	= 0;
			state_index		= 0;

			// append
			// capture - will contain everything in between
			// capture end append

			mv_regexp_compile_statelist_append( &(parent_state->nest), parent_state_length, parent_index, &state );
			mv_regexp_compile_state_start( expression, expression_index, &state, &state_length, &state_index );

			break;

		case ')' :
			/* End capture, let everything bubble up */
			break;

		default :
			state.type		= MIVA_REGEXP_EXACT;
			state.condition	= &c;
			state.nest		= NULL;

			mv_regexp_compile_statelist_append( &(parent_state->nest), parent_state_length, parent_index, &state );
			mv_regexp_compile_state_start( expression, expression_index, parent_state, parent_state_length, parent_index );
	}

	return 0;
}

int mv_regex_compile_state_escape( const char * expression, size_t * expression_index, regexp_state_mv * parent_state, size_t * parent_state_length, size_t * parent_index )
{
	struct regexp_state_mv state;
	size_t state_length, state_index;
	char h1, h2, h3, h4;
	char c = expression[ *expression_index ];

	if ( c == '\0' )
	{
		// The only time we want to return normal on '\0' is when we're in state start and our parent is the root level
		// ie... this should return an error
		return 0;
	}

	*expression_index = *expression_index + 1;
	printf( "escaped char: %c\n", c );

	switch ( c )
	{
		case 'b' :
			break;

		case 'B' :
			break;

		case 'c' :
			// For the time being, return error "CONTROL CHARACTERS NOT CURRENTLY SUPPORTED"
			return MIVA_REGEXP_COMPILE_ERROR_CONTROLCHARSNOTSUPPORTED;

			// Check to make sure next char is A-Z and insert exact match as control character, otherwise return invalid regexp error
			char c2 = expression[ *expression_index + 1 ];

			if ( !isupper( c2 ) )
			{
				// return invalid regexp error
			}

			state.type		= MIVA_REGEXP_EXACT;
			state.condition	= &c2;
			state.nest		= NULL;

			mv_regexp_compile_statelist_append( &(parent_state->nest), parent_state_length, parent_index, &state );
			return mv_regexp_compile_state_start( expression, expression_index, parent_state, parent_state_length, parent_index );

		case 'd' :
			break;

		case 'D' :
			break;

		case 'f' :
			break;

		case 'n' :
			break;

		case 'r' :
			break;

		case 's' :
			break;

		case 'S' :
			break;

		case 't' :
			break;

		case 'v' :
			break;

		case 'w' :
			break;

		case 'W' :
			break;

		case '0' :
			state.type		= MIVA_REGEXP_EXACT;
			state.condition	= NULL;
			state.nest		= NULL;

			mv_regexp_compile_statelist_append( &(parent_state->nest), parent_state_length, parent_index, &state );
			return mv_regexp_compile_state_start( expression, expression_index, parent_state, parent_state_length, parent_index );

		case 'x' :
			h1 = expression[ *expression_index ];
			h2 = expression[ *expression_index + 1 ];

			if ( !isxdigit( h1 ) || !isxdigit( h2 ) )
			{
				return MIVA_REGEXP_COMPILE_ERROR_INVALID_UNICODE;
			}
			// Next two chars must be hex
			break;

		case 'u' :
			// Test
			h1 = expression[ *expression_index ];
			h2 = expression[ *expression_index + 1 ];
			h3 = expression[ *expression_index + 2 ];
			h4 = expression[ *expression_index + 3 ];

			if ( !isxdigit( h1 ) || !isxdigit( h2 ) || !isxdigit( h3 ) || !isxdigit( h4 ) )
			{
				return MIVA_REGEXP_COMPILE_ERROR_INVALID_UNICODE;
			}
			// Next four chars must be hex
			break;

		default :
			if ( isdigit( c ) )
			{
				// BACKREFERENCE
			}
			else
			{
				state.type		= MIVA_REGEXP_EXACT;
				state.condition	= &c;
				state.nest		= NULL;

				mv_regexp_compile_statelist_append( &(parent_state->nest), parent_state_length, parent_index, &state );
				return mv_regexp_compile_state_start( expression, expression_index, parent_state, parent_state_length, parent_index );
			}

			break;
// MIVA_REGEXP_BACKSPACE,		/* [\b]		: Matches a backspace (U+0008). You need to use square brackets if you want to match a literal backspace character. */
// MIVA_REGEXP_WORD,			/* \b		: Matches a word boundary. A word boundary matches the position where a word character is not followed or preceeded by another word-character. Note that a matched word boundary is not included in the match. */
// MIVA_REGEXP_NWORD,			/* \B		: Matches a non-word boundary. This matches a position where the previous and next character are of the same type: Either both must be words, or both must be non-words. The beginning and end of a string are considered non-words. */
// MIVA_REGEXP_CHAR,			/* \cX		: Where X is a character ranging from A to Z. Matches a control character in a string. Example: \cM matches control-M (U+000D) */
// MIVA_REGEXP_DIG,			/* \d		: Matches a digit character. Equivalent to [0-9] */
// MIVA_REGEXP_NDIG,			/* \D 		: Matches any non-digit character. Equivalent to [^0-9] */
// MIVA_REGEXP_FF,				/* \f 		: Matches a form feed (U+000C) */
// MIVA_REGEXP_LF,				/* \n 		: Matches a line feed (U+000A) */
// MIVA_REGEXP_CR,				/* \r 		: Matches a carriage return (U+000D) */
// MIVA_REGEXP_WHITESPACE,		/* \s 		: Matches a single white space character. Equivalent to [ \f\n\r\t\v\u00a0\u1680\u180e\u2000\u2001\u2002\u2003\u2004\u2005\u2006\u2007\u2008\u2009\u200a\u2028\u2029\u202f\u205f\u3000] */
// MIVA_REGEXP_NWHITESPACE,	/* \s 		: Matches a single character other than white space. Equivalent to [^ \f\n\r\t\v\u00a0\u1680\u180e\u2000\u2001\u2002\u2003\u2004\u2005\u2006\u2007\u2008\u2009\u200a\u2028\u2029\u202f\u205f\u3000] */
// MIVA_REGEXP_TAB,			/* \t 		: Matches a tab (U+0009) */
// MIVA_REGEXP_VTAB,			/* \v 		: Matches a vertical tab (U+000B) */
// MIVA_REGEXP_ALNUM,			/* \w 		: Matches any alphanumeric character including underscore. Equivalent to [A-Za-z0-9_] */
// MIVA_REGEXP_NALNUM,			/* \W 		: Matches any non-word character. Equivalent to [^A-Za-z0-9_] */
// MIVA_REGEXP_BACKREF,		/* \n 		: Where n is a positive integer, a back reference to the last substring matching the n parenthetical in the regular expression (counting left parentheses) */
// MIVA_REGEXP_NULL,			/* \0 		: Matches a NULL (U+0000) character. Do not follow this with another digit, because \0<digits> is an octal escape sequence */
// MIVA_REGEXP_HEXTWO,			/* \xhh		: Matches the character with the code hh (two hexadecimal digits) */
// MIVA_REGEXP_HEXFOUR,		/* \uhhhh	: Matches the character with the code hhhh (four hexadecimal digits) */
	}

	return 0;
}

void mv_regexp_compile_statelist_append( regexp_state_mv **list, size_t *list_length, size_t *index, regexp_state_mv *state )
{
	regexp_state_mv *tmp_list;
	int orig_list_length;

	if ( *index >= *list_length )
	{
		orig_list_length		= *list_length;
		*list_length			= *list_length + ( *list_length + 512 );
		tmp_list				= ( regexp_state_mv * ) malloc( sizeof( regexp_state_mv ) * ( *list_length + 1 ) );

		memcpy( tmp_list, list, orig_list_length );

		*list					= tmp_list;
	}

	(*list)[ *index ]			= *state;
	*index						= *index + 1;
}

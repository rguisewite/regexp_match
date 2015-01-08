/* Structure Definitions */
#ifndef MIVA_REGEXP_STRUCT_DEFS
#define MIVA_REGEXP_STRUCT_DEFS

#define MIVA_REGEXP_COMPILE_ERROR_INVALID_FLAG 0x0001
#define MIVA_REGEXP_COMPILE_ERROR_INVALID_BACKSLASH 0x0002
#define MIVA_REGEXP_COMPILE_ERROR_CONTROLCHARSNOTSUPPORTED 0x0003
#define MIVA_REGEXP_COMPILE_ERROR_INVALID_UNICODE 0x0004

#define MIVA_REGEXP_EXECUTE_ERROR_NOMATCH 0x0001
#define MIVA_REGEXP_EXECUTE_ERROR_INVALID_REGEXP 0x0002

#define MIVA_REGEXP_FLAG_G 0x0001		/* Global match */
#define MIVA_REGEXP_FLAG_I 0x0002		/* Ignore case */
#define MIVA_REGEXP_FLAG_M 0x0004		/* Multi-line */

enum
{
	MIVA_REGEXP_COMPILE_STATE_START,
	MIVA_REGEXP_COMPILE_STATE_BACKSLASH
};

enum
{
	MIVA_REGEXP_START,
	MIVA_REGEXP_EXACT,			/*			: Any string value that is not a special character. Example, xyz will return match for xyz. */
	MIVA_REGEXP_BACKSLASH,		/* \		: A backslash that precedes a non-special character indicates that the next character is special and is not to be interpreted literally. 
											  A backslash that precedes a special character indicates that the next character is not special and should be interpreted literally.*/
	MIVA_REGEXP_BOL,			/* ^		: Matches beginning of input. If the multiline flag is set to true, also matches immediately after a line break character.*/
	MIVA_REGEXP_EOL,			/* $		: Matches end of input. If the multiline flag is set to true, also matches immediately before a line break character. */
	MIVA_REGEXP_STAR,			/* *		: Matches the preceding character 0 or more times. Equivalent to {0,}. */
	MIVA_REGEXP_PLUS,			/* +		: Matches the preceding character 1 or more times. Equivalent to {1,}. */
	MIVA_REGEXP_QUEST,			/* ?		: Matches the preceding character 0 or 1 time. Equivalent to {0,1}. If used immediately after any of the quantifiers *, +, ?, or {}, makes the quantifier non-greedy */
	MIVA_REGEXP_ANY,			/* .		: (The decimal point) matches any single character except the newline character. */
	MIVA_REGEXP_OR,				/* |		: Matches x OR y*/
	MIVA_REGEXP_CAPTURE,		/* (x)		: Matches 'x' and remembers the match, as the following example shows. The parentheses are called capturing parentheses. */
	MIVA_REGEXP_NOCAPTURE,		/* (?:x)	: Matches 'x' but does not remember the match. The parentheses are called non-capturing parentheses, and let you define subexpressions for regular expression operators to work with. */
	MIVA_REGEXP_LCAPTURE,		/* x(?=y)	: Matches 'x' only if 'x' is followed by 'y'. This is called a lookahead. */
	MIVA_REGEXP_NLCAPTURE,		/* x(?!y)	: Matches 'x' only if 'x' is not followed by 'y'. This is called a negated lookahead. */
	MIVA_REGEXP_OCCURRENCES,	/* {n}		: Matches exactly n occurrences of the preceding character. N must be a positive integer. */
	MIVA_REGEXP_RANGEOCCURS,	/* {n.m}	: Where n and m are positive integers and n <= m. Matches at least n and at most m occurrences of the preceding character. When m is omitted, it's treated as ∞ */
	MIVA_REGEXP_ANYOF,			/* []		: Character set. This pattern type matches any one of the characters in the brackets, including escape sequences. Special characters like the dot(.) and asterisk (*)
											  are not special inside a character set, so they don't need to be escaped. You can specify a range of characters by using a hyphen, as the following examples illustrate.*/
	MIVA_REGEXP_ANYBUT,			/* [^]		: A negated or complemented character set. That is, it matches anything that is not enclosed in the brackets. You can specify a range of characters by using a hyphen. */
	MIVA_REGEXP_BACKSPACE,		/* [\b]		: Matches a backspace (U+0008). You need to use square brackets if you want to match a literal backspace character. */
	MIVA_REGEXP_WORD,			/* \b		: Matches a word boundary. A word boundary matches the position where a word character is not followed or preceeded by another word-character. Note that a matched word boundary is not included in the match. */
	MIVA_REGEXP_NWORD,			/* \B		: Matches a non-word boundary. This matches a position where the previous and next character are of the same type: Either both must be words, or both must be non-words. The beginning and end of a string are considered non-words. */
	MIVA_REGEXP_CHAR,			/* \cX		: Where X is a character ranging from A to Z. Matches a control character in a string. Example: \cM matches control-M (U+000D) */
	MIVA_REGEXP_DIG,			/* \d		: Matches a digit character. Equivalent to [0-9] */
	MIVA_REGEXP_NDIG,			/* \D 		: Matches any non-digit character. Equivalent to [^0-9] */
	MIVA_REGEXP_FF,				/* \f 		: Matches a form feed (U+000C) */
	MIVA_REGEXP_LF,				/* \n 		: Matches a line feed (U+000A) */
	MIVA_REGEXP_CR,				/* \r 		: Matches a carriage return (U+000D) */
	MIVA_REGEXP_WHITESPACE,		/* \s 		: Matches a single white space character. Equivalent to [ \f\n\r\t\v\u00a0\u1680\u180e\u2000\u2001\u2002\u2003\u2004\u2005\u2006\u2007\u2008\u2009\u200a\u2028\u2029\u202f\u205f\u3000] */
	MIVA_REGEXP_NWHITESPACE,	/* \S 		: Matches a single character other than white space. Equivalent to [^ \f\n\r\t\v\u00a0\u1680\u180e\u2000\u2001\u2002\u2003\u2004\u2005\u2006\u2007\u2008\u2009\u200a\u2028\u2029\u202f\u205f\u3000] */
	MIVA_REGEXP_TAB,			/* \t 		: Matches a tab (U+0009) */
	MIVA_REGEXP_VTAB,			/* \v 		: Matches a vertical tab (U+000B) */
	MIVA_REGEXP_ALNUM,			/* \w 		: Matches any alphanumeric character including underscore. Equivalent to [A-Za-z0-9_] */
	MIVA_REGEXP_NALNUM,			/* \W 		: Matches any non-word character. Equivalent to [^A-Za-z0-9_] */
	MIVA_REGEXP_BACKREF,		/* \n 		: Where n is a positive integer, a back reference to the last substring matching the n parenthetical in the regular expression (counting left parentheses) */
	MIVA_REGEXP_NULL,			/* \0 		: Matches a NULL (U+0000) character. Do not follow this with another digit, because \0<digits> is an octal escape sequence */
	MIVA_REGEXP_HEXTWO,			/* \xhh		: Matches the character with the code hh (two hexadecimal digits) */
	MIVA_REGEXP_HEXFOUR,		/* \uhhhh	: Matches the character with the code hhhh (four hexadecimal digits) */
};

/* During compile, compress everything down to as few things as possible. IE, MIVA_REGEXP_WHITESPACE would actually become a MIVA_REGEXP_ANYOF 
 * with the list of characters as an array. The unicode characters would be converted into actual characters


/(abc[ab\u1680\s])/g
type: CAPTURE
condition: NULL
nest: 
[
	{
		type: EXACT
		condition: [ "a", "b", "c" ]
		nest: NULL
	},
	{
		type: ANYOF
		condition: NULL
		nest: 
		[
			{
				type: EXACT
				condition: "a"
				nest: NULL
			},
			{
				type: EXACT
				condition: "b"
				nest: NULL
			},
			{
				type: EXACT
				condition: "\u1680"
				nest: NULL
			},
			{
				type: ANYOF
				condition: NULL
				nest: [ { any of the white space characters as an array of "exact" matches
			}
		]
	}
]
*/

typedef struct regexp_state_mv
{
	int type;
	const char *condition;
	struct regexp_state_mv *nest;
} regexp_state_mv;

typedef struct
{
	int start;
	int end;
	char *match;
} regexp_match_mv;

struct regexp_internals_mv
{
	unsigned long int flags;			/* Bits for which flags are set */
	const char *regexp;					/* Copy of regexp string argument */
	int *statelist;						/* Used to keep track of the current state */
	int *positionlist;					/* Used to keep track of the current position */
	regexp_state_mv *regexp_statelist;	/* The compiled regular expression */
};

typedef struct
{
	struct regexp_internals_mv *internals;
	regexp_match_mv *matchlist;				/* List of matches */
	int num_subexpr;						/* Number of sub expressions */
	int	error;								/* Error number, if present */
} regexp_mv;

#endif

/* Function Definitions */

int mv_regexp_compile( const char * expression, const char * options, regexp_mv * regexp );
int mv_regexp_execute( regexp_mv * regexp, const char * source, int start );
void mv_regexp_compile_statelist_append( regexp_state_mv **list, size_t *list_length, size_t *index, regexp_state_mv *state );
int mv_regexp_compile_state_start( const char * expression, size_t * expression_index, regexp_state_mv * parent_state, size_t * parent_state_length, size_t * parent_index );
int mv_regex_compile_state_escape( const char * expression, size_t * expression_index, regexp_state_mv * parent_state, size_t * parent_state_length, size_t * parent_index );

/* misc utilities */
#define	OUT	(UCHAR_MAX+1)	/* a non-character value */
#define	ISWORD(c)	(isalnum(c) || (c) == '_')

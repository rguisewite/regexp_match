#include <stdio.h>
#include <string.h>
#include <regexp.h>
#include "regexp_match.h"

MV_EL_FunctionParameter regexp_match_parameters[] = {
	{ "expression",	10,		EPF_NORMAL },
	{ "source",		6,		EPF_NORMAL },
	{ "flags",		5,		EPF_NORMAL },
	{ "start",		5,		EPF_NORMAL },
	{ "match",		5,		EPF_REFERENCE },
};

MV_EL_FunctionParameter regexp_match_parameters_var[] = {
	{ "expression",	10,		EPF_NORMAL },
	{ "source",		6,		EPF_REFERENCE },
	{ "flags",		5,		EPF_NORMAL },
	{ "start",		5,		EPF_NORMAL },
	{ "match",		5,		EPF_REFERENCE },
};

void mv_regexp_match( mvProgram prog, mvVariableHash parameters, mvVariable returnvalue, void ** data )
{
	int start, expression_length, source_length, flags_length, match_length;
	const char *expression, *source, *flags, *match;

	expression	= mvVariable_Value( mvVariableHash_Index( parameters, 0 ), &expression_length );
	source		= mvVariable_Value( mvVariableHash_Index( parameters, 1 ), &source_length );
	flags		= mvVariable_Value( mvVariableHash_Index( parameters, 2 ), &flags_length );
	start		= mvVariable_Value_Integer( mvVariableHash_Index( parameters, 3 ) );
	match		= mvVariable_Value( mvVariableHash_Index( parameters, 4 ), &match_length );

	mvVariable_SetValue_Integer( returnvalue, mv_regexp_match_lowlevel( &expression, expression_length, &source, source_length, &flags, flags_length, start, &matchlist ) );
}

void mv_regexp_match_var( mvProgram prog, mvVariableHash parameters, mvVariable returnvalue, void ** data )
{
	int start, expression_length, source_length, flags_length, match_length;
	const char *expression, *source, *flags, *match;

	expression	= mvVariable_Value( mvVariableHash_Index( parameters, 0 ), &expression_length );
	source		= mvVariable_Value( mvVariableHash_Index( parameters, 1 ), &source_length );
	flags		= mvVariable_Value( mvVariableHash_Index( parameters, 2 ), &flags_length );
	start		= mvVariable_Value_Integer( mvVariableHash_Index( parameters, 3 ) );
	match		= mvVariable_Value( mvVariableHash_Index( parameters, 4 ), &match_length );

	mvVariable_SetValue_Integer( returnvalue, mv_regexp_match_lowlevel( &expression, expression_length, &source, source_length, &flags, flags_length, start, &matchlist ) );
}

int mv_regexp_match_lowlevel( char **expression, int expression_length, char **source, int source_length, char **flags, int flags_length, int start, struct match_item *matchlist )
{
	regexp_mv regexp;
	int error, options, flag_index, matchlist_count;

	options				= 0;
	matchlist_count		= 0;

	if ( flags_length > 0 )
	{
		for ( flag_index = 0; flag_index < flags_length; flag_index++ )
		{
			switch ( flags[ flag_index ] )
			{
				case 'g':	options |= REGEXP_MATCH_FLAG_G;		break;
				case 'i':	options |= REGEXP_MATCH_FLAG_I;		break;
				case 'm':	options |= REGEXP_MATCH_FLAG_M;		break;
			}
		}
	}

	/* mv_regexp_compile is part of the RegExp (regexp.h) library and will validate the regular expression */
	error = mv_regexp_compile( *expression, options, &regexp );
	if ( error )
	{
		printf( 'Error compiling!' ); // eventually use error codes to produce an error code-error message definition
		return -1;
	}

	while ( !( error = mv_regexp_execute( &regexp, *source, source_length, start ) ) )
	{
		/* Add the match to the match list and continue on */
	}

	if ( error == REGEXP_ERROR_NOMATCH )				;
	else if ( error == REGEXP_ERROR_INVALID_REGEXP )	;

	return matchlist_count;
}



/**
* Hook the functions into Miva
*/ 
EXPORT MV_EL_Function_List *miva_function_table()
{
	static MV_EL_Function exported_functions[] = {
		{ "regexp_match", 12, 5, regexp_match_parameters, mv_regexp_match },
		{ "regexp_match_var", 12, 5, regexp_match_parameters_var, mv_regexp_match_var },
		{ 0 , 0 , 0, 0 , 0 }
	};

	static MV_EL_Function_List list = { MV_EL_FUNCTION_VERSION, exported_functions };

	return &list;
}

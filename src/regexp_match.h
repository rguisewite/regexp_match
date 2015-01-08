#include "mivapi.h"

/* Structure Definitions */
#ifndef MIVA_REGEXP_MATCH_STRUCT_DEFS
#define MIVA_REGEXP_MATCH_STRUCT_DEFS

#define REGEXP_MATCH_FLAG_G 0x0001
#define REGEXP_MATCH_FLAG_I 0x0002
#define REGEXP_MATCH_FLAG_M 0x0004

struct match_item
{
	int start_index;
	int end_index;
	char *match;
};


#endif

/* Function Definitions */

void mv_regexp_match(mvProgram prog, mvVariableHash parameters, mvVariable returnvalue, void ** data);
void mv_regexp_match_var( mvProgram prog, mvVariableHash parameters, mvVariable returnvalue, void ** data );
int mv_regexp_match_lowlevel( char **expression, int expression_length, char **source, int source_length, char **flags, int flags_length, int start, struct match_item *matchlist, int *matchlist_length );

EXPORT MV_EL_Function_List *miva_function_table();

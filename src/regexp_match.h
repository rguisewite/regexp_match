#include "mivapi.h"

#define REGEXP_FLAG_G = 0x0001
#define REGEXP_FLAG_I = 0x0002
#define REGEXP_FLAG_M = 0x0004

/**
* Forward Declarations
*/
void mv_regexp_match(mvProgram prog, mvVariableHash parameters, mvVariable returnvalue, void ** data);
void mv_regexp_match_var( mvProgram prog, mvVariableHash parameters, mvVariable returnvalue, void ** data );
void mv_regexp_match_lowlevel( char **expression, int expression_length, char **source, int source_length, char **flags, int flags_length, int start, struct match_item *matchlist, int *matchlist_length );

EXPORT MV_EL_Function_List *miva_function_table();

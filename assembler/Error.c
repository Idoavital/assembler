
#include <stdio.h> /* printf */
#include "Error.h"


/*	  EXAMLE TODO: delete this commit
	 case NAME:
		printf(P_ERROR"MSG\n");
		break;
*/

int print_err(enum eERROR err_type)
{
	switch (err_type)
	{
	case ERR_COMMA_AFTER_CMD:
		printf(P_ERROR"a comma should not be after instruction name \n");
		break;

	case ERR_COMMA_NOT_INPLACE:
		printf(P_ERROR" comma is not in the right palce\n");
		break;

	case ERR_TWO_COMMA:
		printf(P_ERROR" two comma in a row\n");
		break;

	case ERR_COMMA_END_LINE:
		printf(P_ERROR"line ends with a comma\n");
		break;

	case ERR_MISSING_COMMA:
		printf(P_ERROR"missing comma\n");
		break;

	case ERR_ILLIGL_LABEL:
		printf(P_ERROR"illigal label name\n");
		break;

	default:
		printf(P_ERROR"UNDEFINE ERROR\n");
		break;
	}

	printf(RESET"\n");
	return 0;
}

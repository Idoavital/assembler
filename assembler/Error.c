
#include <stdio.h> /* printf */
#include "Error.h"


/*	  EXAMLE TODO: delete this commit
	 case NAME:
		printf(P_ERROR"MSG\n");
		break;
*/

int print_err(enum eERROR err_type)
{
	printf(P_ERROR"In line number [%d] ", Line_number);
	switch (err_type)
	{
	case ERR_COMMA_AFTER_CMD:
		printf("a comma should not be after instruction name \n");
		break;

	case ERR_COMMA_NOT_INPLACE:
		printf("comma is not in the right palce\n");
		break;

	case ERR_TWO_COMMA:
		printf("two comma in a row\n");
		break;

	case ERR_COMMA_END_LINE:
		printf("line ends with a comma\n");
		break;

	case ERR_MISSING_COMMA:
		printf("missing comma\n");
		break;

	case ERR_ILLIGL_LABEL:
		printf("illigal label name\n");
		break;

	default:
		printf("UNDEFINE ERROR\n");
		break;
	}

	printf(RESET"\n");
	return 0;
}

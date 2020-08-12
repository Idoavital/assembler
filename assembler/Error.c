
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
		printf("the comma should not be after instruction or a data name \n");
		break;

	case ERR_COMMA_NOT_INPLACE:
		printf("the comma is not in the right place\n");
		break;

	case ERR_TWO_COMMA:
		printf("two comma in a row\n"); /*this error refering to a comma that comes after a comma? example: mov r3,,r3*/
		break;

	case ERR_COMMA_END_LINE:
		printf("the sentence shouldn't end with a comma\n");
		break;

	case ERR_MISSING_COMMA:
		printf("there is a missing comma in the sentence\n");
		break;

	case ERR_ILLEGAL_DEF_LABEL:
		printf("the label definition is incorrect.\n");
		break;
	case ERR_COMMAND_NAME:
		printf("the command name is incorrect");
		break;
	case ERR_REGISTER_SOURCE:
		printf("the command cannot accept a register as a source operator.");
		break;
	case ERR_REGISTER_TARGET:
		printf("the command cannot accept a register as a target operator.");
		break;
	case ERR_ADDRESS_LABEL_SOURCE:
		printf("the command cannot accept an address label as a source operator.");
		break;
	case ERR_ADDRESS_LABEL_TARGET:
		printf("the command cannot accept an address label as a target operator.");
		break;
	case ERR_LABEL_SOURCE:
		printf("the command cannot accept a label as a source operator.");
		break;
	case ERR_LBAEL_TARGET:
		printf("the command cannot accept a label as a target operator.");
		break;
	case ERR_NUMBER_SOURCE:
		printf("the command cannot accept a number as a source operator.");
		break;
	case ERR_NUMBER_TARGET:
		printf("the command cannot accept a number as a target operator.");
		break;
	case ERR_OPERATOR_UNDEFINED_SOURCE:
		printf("the source operator is undefined.");
		break;
	case ERR_OPERATOR_UNDEFINED_TARGET:
		printf("the target operator is undefined");
		break;
	case ERR_EXTRA_TEXT:
		printf("there is unnecessary text after the command is completed.");
		break;
	case ERR_MISSING_SOURCE:
		printf("the source operator is missing.");
		break;
	case ERR_MISSING_TARGET:
		printf("the target operator is missing.");
		break;
	case ERR_NUMBER_DATA:
		printf("one of the numbers that was entered is incorrect.");
		break;
	case ERR_STRING:
		printf("the string that was entered is incorrect.");
		break;
	case ERR_ILLEGAL_LABEL:
		printf("the label that was entered is incorrect.");
		break;
	case ERR_MIISING_LABEL:
		printf("the commands .entry and .extern should have a label after the command.");
		break;
	default:
		printf("UNDEFINE ERROR\n");
		break;
	}

	printf(RESET"\n");
	return 0;
}

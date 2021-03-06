
#include <stdio.h> /* printf */
#include "Error.h"
#include "Data_structures.h"



int print_err(enum eERROR err_type)
{
	err_num = err_type;
	printf(P_ERROR"In file %s In line number [%d] ",file_name, Line_number);
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
	case ERR_PUSH_TABLE:
		printf("can't push symbol to table, becuase the symbol is already in the table or the symbol is illegal.");
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
	case ERR_FIRST_PASS_FIALED:
		printf("Can't complete the first pass.");
		break;
	case ERR_SECOND_PASS_FIALED:
		printf("Can't complete the second pass.");
		break;
	case ERR_WRITE_FILES_FIALED:
		printf("Can't write assembly files.");
		break;
	case ERR_SYMBOL_NOT_FOUND:
		printf("the label is incorrect because it was not set during the program.");
		break;
	case ERR_ADDRESS_EXTREN_LABEL:
		printf("in instruction command: jmp, jsr and bne. you cant use an extern label.");
		break;
	case ERR_EMPTY_LABEL:
		printf("empty label.");
	case ERR_LABEL_EXTERN:
		printf("you cannot define a label when declaring an entry or extern label.");
		break;
	default:
		printf("UNDEFINE ERROR\n");
		break;

	}

		
	printf(RESET"\n");
	return 0;
}

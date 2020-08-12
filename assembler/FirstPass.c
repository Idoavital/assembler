#include <string.h>
#include <stdlib.h>

#include "FirstPass.h"
#include "Defines.h"
#include "Error.h"
#include "parse.h"
#include "parseLine.h"
#include "Data_structures.h"

int firstPass(FILE* pfile)
{
	char name[MAX_LABEL_LEN];
	char line[MAX_LINE_LEN];
	int  index = START_LINE;

	enum Esymbole_type type;
	int address				= 0;

	pSymbole new_symbol     = NULL;

	int index_command = 0;
    int outcome =  0;
    int flag_label = FALSE;
	/*TODO: need to change the function for the data check, after i write them.*/
	int (*checkFunc[])(char line[MAX_LINE_LEN][MAX_LINE_LEN], int indexR, int indexC) =
	{ template0,  template0,  template0, template0, template2, template2, template2, template2, template2, template1, template1,
	template1, template1, template1, template1, template1, template1, template1, template0, template0};
	
	init_globals();
	initialize_address_mathod_table();

	for (Line_number = 1; fgets(line, MAX_LINE_LEN, pfile); Line_number++) /* Scanning through each line of the file */
	{
		int index = 0;
		
		index_command,outcome = 0;
		flag_label = FALSE;
		
		/* check is a comment or blank line*/
		if(is_comment_or_blank_line(line, START_LINE))
			continue;
		
		/*TODO: check comma error in line*/
		if (check_legal_comma(line, START_LINE) == COMMA_ERROR)
		{
			printf(P_DEBUG"comma problem !!!\n");
		}
		printf(P_DEBUG"%s", line);;

		/*check line error*/

		split_line(line,START_LINE, index_command == STRING? STRING: NOT_STRING);

		if (is_label_definition(splitLine[START_LINE],START_LINE))
    	{
        	if (!is_legal_label_definition(splitLine[START_LINE],START_LINE))
        	{
        	    print_err(ERR_ILLEGAL_DEF_LABEL);
				break;
        	}	 
        	else
        	{
            	flag_label = TRUE;
        	}
    	}
		
    	if ( (index_command = is_keyword(splitLine[flag_label],START_LINE,CHECK_COMMAND_NAME)) == FALSE)
    	{
      	  	print_err(ERR_COMMAND_NAME);
		  	break;
    	}

		if (  (outcome = (checkFunc[index_command])(splitLine,flag_label,START_LINE)) < 0 ) /*the flag indicate if it will send a pointer.*/
    	{                                                                                   /*to the first row in spiltLine or the second.*/
      		print_err(outcome);                                                             /*that depends if there is a definition of a label.*/
        	break;
    	}



		/*TODO: count ic and dc */

		if (is_label_definition(line, START_LINE))
		{
			if (is_legal_label_definition(line, START_LINE) == FALSE)
			{
				/*TODO:  print error and jump to the next line - flag dont do second pass*/
				continue;
			}
			type = get_type(line, START_LINE);
			address = (type == ST_EXTERN ? 0 : (type == ST_DATA ? DC : IC));
			get_label_name(line, name);

			/*TODO: add to symbloe table*/
			new_symbol = create_symbol(name, address, type);
			if (new_symbol == NULL)
			{
				/*TODO: ERROR*/
			}
			push_symbol(new_symbol);
		}

		calc_dc_counter(line, index);
		

	}
	return 0;
}

void init_globals()
{
	pSymbole_Head = NULL;
	IC			  = IC_BEGIN;
	DC			  = DC_BEGIN;
}

int get_type(char* str, int index)
{
	int i = 0;  /*loop index (also type index)*/

	char label_type[MAX_LINE_LEN];
	/*Read label*/
	index = label_position(str ,index);
	/*Read the type of the word*/
	sscanf(&str[index], "%s", label_type);
	
	for (i = 0; i < MAX_LABEL_TYPE; i++)
	{
		if (strcmp(label_type, g_keywords[i]) == 0)
		{
			return i; /* return the type number */
		}
	}

	/*else return CODE TYPE*/
	return i;
}

void get_label_name(__IN char* str_in, __OUT char* name)
{
	
	sscanf(str_in, "%s", name);
	while (*name != ':')
		name++;
	*name = '\0';
}

void calc_dc_counter(char* str, int index)
{
	int count_data = 0;
	char cmd[MAX_COMMAND_NAME];

	index = label_position(str, index);
	
	sscanf(&str[index], "%s", cmd);
	index = clear_white_space(str, index);
	/*If is a .data*/
	if (strcmp(".data", cmd) == 0)
	{
		index += strlen(".data");
		while (index >= 0)
		{
			count_data++;
			index = get_next_comma_pos(str, index);
		}	

	}
	else if (strcmp(".string", cmd) == 0)
	{

		index += strlen(".string");
		index = clear_white_space(str, index);
		index++; /*the string start with char ["] */
		while (str[index++] != '"')
			count_data++;
	}

	DC += count_data;

}

pSymbole create_symbol(char* pName, int address, int type)
{
	pSymbole psym = malloc(sizeof(*psym));

	if (psym == NULL)
	{
		printf(P_ERROR"Can't allocate memory for symbol\n"); /*TODO: FINISH PRINT ERR*/
		return NULL;
	}
	strcpy(psym->name, pName);
	psym->address = address;
	psym->type = type;

	return psym;
}

int push_symbol(pSymbole pSymbole_node)
{
	pSymbole pCurrent_symbol = pSymbole_Head;
	/*If is the first symbol*/
	if (pSymbole_Head == NULL)
	{
		pSymbole_Head = pSymbole_node;
		return PUSH_OK;
	}
	
	/*check if the symbol is already in the table */
	while (pCurrent_symbol != NULL)
	{
		if (strcmp(pCurrent_symbol->name, pSymbole_node->name) == 0)
			return PUSH_ERROR;

		/*if is the last symbol in the list, add the new symbol*/
		if (pCurrent_symbol->next == NULL)
		{
			pCurrent_symbol->next = pSymbole_node;
			return PUSH_OK;
		}
			
		pCurrent_symbol = pCurrent_symbol->next;
	}

	return PUSH_ERROR;
}

int free_symbol(pSymbole pSymbole_node)
{
	free (pSymbole_node);
	return 0;
}

int clear_list()
{
	pSymbole pCurrent_symbol = pSymbole_Head;
	pSymbole pSymTemp = NULL;

	while (pCurrent_symbol != NULL)
	{
		pSymTemp = pCurrent_symbol;
		pCurrent_symbol = pCurrent_symbol->next;
		
		free_symbol(pSymTemp);
	}
	return 0;
}


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
	enum Esymbole_type type;
	int address				= 0;
	pSymbole new_symbol     = NULL;

	int index_command = 0;
    int outcome =  0;
    int flag_label = FALSE;

	/*TODO: need to change the function for the data check, after i write them.*/
	int (*checkFunc[])(char line[MAX_LINE_LEN][MAX_LINE_LEN], int indexR, int indexC) =
	{ template_entry_extern,  template_entry_extern,  template_data, template_string , template2, template2,
	  template2, template2, template2, template1, template1, template1, template1, template1, template1,
	  template1, template1, template1, template0, template0};
	
	init_globals();
	initialize_address_mathod_table();

	for (Line_number = 1; fgets(line, MAX_LINE_LEN, pfile); Line_number++) /* Scanning through each line of the file */
	{
		index_command = 0;
	    outcome = 0;
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

		/*Check line error*/

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
			if (strcmp(&splitLine[flag_label][START_LINE],".extern") != 0)
			{
				print_err(ERR_COMMAND_NAME);
		  		break;
			}
      	  	
    	}

		if (  (outcome = (checkFunc[index_command])(splitLine,flag_label,START_LINE)) < 0 ) /*the flag indicate if it will send a pointer.*/
    	{                                                                                   /*to the first row in spiltLine or the second.*/
      		print_err(outcome);                                                             /*that depends if there is a definition of a label.*/
        	break;
    	}


		
		/*  if we a label in the table we push the label to symbol table */
		if (flag_label || is_extern(line, START_LINE))
		{

			type		= get_type(line, START_LINE);
			address		= (type == ST_EXTERN ? 0 : (type == ST_DATA ? DC : IC));
			get_label_name(line, name, type);

			new_symbol = create_symbol(name, address, type);
			if (new_symbol == NULL)
			{
				print_err(ERR_SYMBOL_ALLOCATION);
			}

			if (push_symbol(new_symbol) == PUSH_ERROR)
			{
				print_err(ERR_PUSH_TABLE);
				free(new_symbol);
			}
		}

		/*Update ic and dc */
		IC += outcome;
		calc_dc_counter(line, START_LINE);
		

	}
	return err_num;
}

void init_globals()
{
	pSymbole_Head = NULL;
	IC			  = IC_BEGIN;
	DC			  = DC_BEGIN;
}
/*TODO: need to add explanation*/
void initialize_splitLine ()
{
	int i,j;
	for ( i = 0; i < MAX_LINE_LEN; i++)
	{
		for (j = 0; i < MAX_LINE_LEN; j++)
		{
			splitLine[i][j] = '\0';
		}	
	}
}


int get_type(char* str, int index)
{

	char label_type[MAX_LINE_LEN];
	/*Read label*/
	index = label_position(str ,index);
	/*Read the type of the word*/
	sscanf(&str[index], "%s", label_type);

	if (strcmp(label_type, ".extern") == 0)
		return ST_EXTERN;

	else if (strcmp(label_type, ".data") == 0)
		return ST_DATA;

	else if (strcmp(label_type, ".string") == 0)
		return ST_DATA;

	else if (strcmp(label_type, ".string") == 0)
		return ST_DATA;


	/*else return CODE TYPE*/
	return ST_CODE;
}

void get_label_name(__IN char* str_in, __OUT char* name, int type)
{
	if (type == ST_EXTERN) /*take the second word , the label name is after the type*/
	{
		int index = 0;
		index = clear_white_space(str_in,START_LINE);
		index = clear_word(str_in, index);
		sscanf(str_in, "%s", name);
		
	}
	else /* the label name is before the type*/
	{
		sscanf(str_in, "%s", name);
		while (*name != ':')
			name++;
		*name = '\0';  /*delet the ':' colon sign */
	}

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

		/*check if it's not a empty string*/
		if (is_end_of_line(str[index]))
			return;

		index++; /*the string start with char ["] */
		while (str[index++] != '"')
			count_data++;

		count_data++; /*For the last char '\0' */
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
	psym->address	= address;
	psym->type		= type;
	psym->isEntry   = FALSE;
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

int get_symbol_address(char* name)
{

	pSymbole pCurrent_symbol = pSymbole_Head;

	while (pCurrent_symbol != NULL)
	{
		if (strcmp(name, pCurrent_symbol->name) == 0)
		{
			return pCurrent_symbol->address;
		}
		pCurrent_symbol = pCurrent_symbol->next;

	}

	return NO_SYMBOL;
}

int get_symbol_type(char* name)
{

	pSymbole pCurrent_symbol = pSymbole_Head;

	while (pCurrent_symbol != NULL)
	{
		if (strcmp(name, pCurrent_symbol->name) == 0)
		{
			return pCurrent_symbol->type;
		}
		pCurrent_symbol = pCurrent_symbol->next;

	}

	return NO_SYMBOL;
}

int set_symbol_to_entry(char* name)
{

	pSymbole pCurrent_symbol = pSymbole_Head;

	while (pCurrent_symbol != NULL)
	{
		if (strcmp(name, pCurrent_symbol->name) == 0)
		{
			pCurrent_symbol->isEntry = TRUE;
			return TRUE;
		}
		pCurrent_symbol = pCurrent_symbol->next;

	}

	return NO_SYMBOL;
}


pSymbole get_symbol(char* name)
{
	pSymbole pCurrent_symbol = pSymbole_Head;

	while (pCurrent_symbol != NULL)
	{
		if (strcmp(name, pCurrent_symbol->name) == 0)
		{
			return pCurrent_symbol;
		}
		pCurrent_symbol = pCurrent_symbol->next;

	}

	return NULL;
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


#include <string.h>
#include <stdlib.h>

#include "FirstPass.h"
#include "Defines.h"
#include "Error.h"
#include "parse.h"

int firstPass(FILE* pfile)
{
	char name[MAX_WORD_LEN];
	char line[MAX_LINE_LEN];

	enum Esymbole_type type;
	int address				= 0;
	pSymbole new_symbol     = NULL;

	init_globals();

	for (Line_number = 1; fgets(line, MAX_LINE_LEN, pfile); Line_number++) /* Scanning through each line of the file */
	{
		/* check is a comment or blank line*/
		if(is_comment_or_blank_line(line, START_LINE))
			continue;
		
		/*TODO: check comma error in line*/
		if (check_legal_comma(line, START_LINE) == COMMA_ERROR)
		{
			printf(P_DEBUG"comma problem !!!\n");
		}
		printf(P_DEBUG"%s", line);;
		/*TODO: check line error*/
		/*TODO: count ic and dc */

		address = (type == ST_DATA ? DC : IC);
		/*TODO: add to symbloe table*/
		new_symbol = create_symbol(name, address, type);
		if (new_symbol == NULL)
		{
			/*TODO: ERROR*/
		}
		push_symbol(new_symbol);
		

	}
	return 0;
}

void init_globals()
{
	pSymbole_Head = NULL;
	IC			  = IC_BEGIN;
	DC			  = DC_BEGIN;
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


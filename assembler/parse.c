#include <ctype.h>  /* isspace */
#include <stdio.h>	/* sscanf */
#include <string.h> /* strlen */

#include "parse.h"

int check_legal_comma(char* str, int index)
{
	int comma_flag = OFF;

	/* move to the first word (instruction name)*/
	while (is_space(str[index++]));

	/* after the first word there is only space without comma */
	/* check if there is no comma */
	while (!isspace(str[index]) && str[index] != '\0' && str[index] != EOF)
	{

		if (str[index] == COMMA)
		{
			/*TODO: print ERR_COMMA_AFTER_CMD*/
			return ERROR; /*TODO: RETURN ERR*/;
		}

		index++;
	}

	if (str[index] != '\n' && str[index] != '\0' && str[index] != EOF)
		return OK;

	/* move to the second word*/
	while (is_space(str[index]))
		index++;
	/* if there is a comma in the begining of the second word (first operand)*/
	if (str[index] == COMMA)
	{
		/*TODO: print ERR_COMMA_AFTER_CMD*/
		return ERROR; /*TODO: RETURN ERR*/;
	}

	for ( ; str[index] != '\n' && str[index] != '\0' && str[index] != EOF; index++)
	{
		if (is_space(str[index]))
			continue;

		/*Check if two comma in a row */
		if (str[index] == COMMA)
		{
			if (comma_flag == ON)
			{
				
				/*Print error two comma*/
				return ERROR; /*TODO: RETURN ERR*/;
			}
			comma_flag = ON;
		}		
		else
		{
			comma_flag = OFF;
		}

	}

	/*Check if the last char is a comma*/
	if (comma_flag == ON)
	{
		/*Print error comma_end_line*/
		return ERROR;/*TODO: RETURN ERR*/;
	}

	return OK;
}

int is_comma(char* str, int index)
{
	while (is_space(str[index]))
		index++;
	
	return (str[index] == ',');
}

int is_space(char c)
{
	return (isspace(c) && c != '\n');
}

int label_position(char* str, int index)
{

	if (is_label(str, index))
		while (':' != str[index++]);

	return index;
}

int is_label(char* str, int index)
{
	char word[MAX_WORD_LEN];
	int  endIndex = 0;

	sscanf(str, "%s", word);  /*Read the first word*/
	endIndex = strlen(word);

	/*Check for error*/
	if (endIndex == 0 || endIndex >= MAX_WORD_LEN) 
		return FALSE;

	return (':' == word[endIndex -1]);
}

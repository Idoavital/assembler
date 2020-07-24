#include <ctype.h>  /* isspace */
#include <stdio.h>	/* sscanf */
#include <string.h> /* strlen, strcmp */

#include "parse.h"
#include "Error.h"
#include "Data_structures.h"


int check_legal_comma(char* str, int index)
{
	int comma_flag = OFF;
	

	/* move to the first word (instruction name)*/
	index = clear_white_space(str, index);

	/* if there is a comma in the begining of the sentence*/
	if (str[index] == COMMA)
	{
		print_err(ERR_COMMA_NOT_INPLACE);
		return COMMA_ERROR;
	}

	/* Read instruction word */
	index = clear_word(str, index);
	/*TODO: ask Shachar if it better to check here if the word is insturction word */

	/* if line ends after the instruction (first word ) */
	if (is_end_of_line(str[index]))
		return COMMA_OK;

	/* move to the second word*/
	index = clear_white_space(str, index);

	/* if there is a comma in the begining of the second word (first operand)*/
	if (str[index] == COMMA)
	{
		print_err(ERR_COMMA_AFTER_CMD);
		return COMMA_ERROR; 
	}

	for ( ; !is_end_of_line(str[index]) ; index++)
	{
		index = clear_word(str, index);
		if (is_space(str[index]))
		{
			index = clear_white_space(str, index);
		}
	
		/*Check if two comma in a row */
		if (str[index] == COMMA)
		{
			if (comma_flag == ON)
			{
				print_err(ERR_TWO_COMMA);
				return COMMA_ERROR; 
			}
			comma_flag = ON;
		}		
		else 
		{
			/* check if comma missing */
			if (comma_flag == ON)
			{
				print_err(ERR_MISSING_COMMA);
				return COMMA_ERROR;
			}
			comma_flag = OFF;
		}

	}

	/*Check if the last char is a comma*/
	if (comma_flag == ON)
	{
		print_err(ERR_COMMA_END_LINE);
		return COMMA_ERROR;
	}

	return COMMA_OK;
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

int is_legal_label(char* str, int index)
{
	int label_flag = FALSE;

	index = clear_white_space(str, index);

	if (is_label(str, index))
	{
		/* Check if the name start in a number or a keyword (reserved word) */
		if (isdigit(str[index]) || is_keyword(str, index))
			label_flag = FALSE;
		else
			label_flag = TRUE;
	}

	if (label_flag == FALSE)
		print_err(ERR_ILLIGL_LABEL);

	return label_flag;
}

int clear_white_space(char* str, int index)
{
	while (is_space(str[index++]));
	
	return index;
}

int clear_word(char* str, int index)
{
	while (str[index] != COMMA && !(is_space(str[index])))
		index++;

	return index;
}

int is_end_of_line(char c)
{
	return (c == '\n' || c == '\0' || c == EOF);
}

int is_keyword(char* str, int index)
{
	int i = 0;
	for (i = 0; i < MAX_KEYWORDS; i++)
	{
		if (strcmp(&str[index], g_keywords[i]))
		{
			return TRUE;
		}
	}

	return FALSE;
}

void print_hex(st_mem_word word)
{
	printf("%06x", *((unsigned int*)&word));
}

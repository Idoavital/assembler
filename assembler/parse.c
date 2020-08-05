#include <ctype.h>  /* isspace */
#include <stdio.h>	/* sscanf */
#include <string.h> /* strlen, strcmp */

#include "parse.h"
#include "Error.h"
#include "Data_structures.h"


int check_legal_comma(char* str, int index)
{
	int comma_flag = OFF;
	int first_word = TRUE;
	int first_op   = TRUE;

	index = label_position(str, index);


	while ( !is_end_of_line(str[index]) )
	{
		if (is_space(str[index]))
		{
			index = clear_white_space(str, index);
			if (is_end_of_line(str[index]))
				break;
		}
				

		if (str[index] == COMMA )
		{

			/* if there is a comma in the begining of the sentence*/
			if (first_word == TRUE || first_op ==TRUE)
			{
				print_err(ERR_COMMA_NOT_INPLACE);
				return COMMA_ERROR;
			}

			/*Check if there is a two comma in a row */
			if (comma_flag == ON)
			{
				print_err(ERR_TWO_COMMA);
				return COMMA_ERROR;
			}
			comma_flag = ON;
		}
		
		if (str[index] != COMMA )
		{

			/*TODO: ask Shachar if it better to check here if the word is insturction word */
			if (first_word == TRUE)
				first_word = FALSE;
				
			else if (first_op == TRUE)
				first_op = FALSE;
				
			else if (comma_flag == OFF)
			{
				print_err(ERR_MISSING_COMMA);
				return COMMA_ERROR;
			}

			comma_flag = OFF;

			index = clear_word(str, index);
			continue;   /* no need to increase index */
		}

		index++;
	}


	/*Check if the last char is a comma*/
	if (comma_flag == ON)
	{
		print_err(ERR_COMMA_END_LINE);
		return COMMA_ERROR;
	}
	
	return COMMA_OK;
}


void split_line(char* str, int index)
{
    int splitPlace = 0;
    
    while (!is_end_of_line(str[index]))
    {
        if (is_space(str[index]))
		{
	    index = clear_white_space(str, index);
        if (is_end_of_line(str[index]))
		break;
		}
        if (str[index] == ',')
        {
           index++;
        }
            
        splitLine[splitPlace] = &str[index]; /*points to the start of a word*/

        while ( (!is_space(str[index])) && (str[index] != ',') && (!is_end_of_line(str[index]))) /*skip to the end of the word */
        {
            index++;
        }
        str[index] = '\0'; /*add \0 so the pointer of each cell in splitLine will point only on a one word*/
        index++; /*skip \0*/
        splitPlace++;  /*move to the next cell that will point on the next word*/
        
    }
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
		if (isdigit(str[index]) || is_keyword(str, index,CHECK_LABLE))
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
	while (is_space(str[index]))
		index++;
	
	return index;
}

int clear_word(char* str, int index)
{
	while (str[index] != COMMA && !isspace(str[index]) && (str[index] != '\0'))
		index++;

	return index;
}

int is_end_of_line(char c)
{
	return (c == '\n' || c == '\0' || c == EOF);
}
/*function that checks if the label or the command name is legal, that depends on the flag info.*/
int is_keyword(char* str, int index, int flag)
{
	int max =0;
	int i = 0;
	if (flag == CHECK_COMMAND_NAME)
	{
		max = MAX_COMMAND_NAME;
	}
	else
	{
		max = MAX_KEYWORDS;
	}
	
	
	for (i = 0; i <= max; i++)
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

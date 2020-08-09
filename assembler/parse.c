#include <ctype.h>  /* isspace */
#include <stdio.h>	/* sscanf */
#include <string.h> /* strlen, strcmp */

#include "parse.h"
#include "Error.h"
#include "Data_structures.h"
#include "parseLine.h"


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
    int row_index = 0;
    int column_index = 0;
    int start_word;
    int last_word = FALSE;
    
      while (last_word == FALSE)
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

        start_word = index;
        index = clear_word(str,index);
        last_word = is_end_of_line(str[index]) ? TRUE: FALSE;
        str[index] = '\0';
        strcpy(&splitLine[row_index++][column_index], &str[start_word]);    
        index++;
      
        
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

int is_comment_or_blank_line(char* str, int index)
{
	index = clear_white_space( str, index);

	return (str[index] == ';' || is_end_of_line(str[index]));
}

int get_next_comma_pos(char* str, int index)
{
	while (str[index] != COMMA && !is_end_of_line(str[index]))
		index++;

	if (is_end_of_line(str[index]))
		return REACH_END_LINE;

	return ++index;
}

int is_end_of_line(char c)
{
	return (c == '\n' || c == '\0' || c == EOF);
}

void print_hex(st_mem_word word)
{
	printf("%06x", *((unsigned int*)&word));
}

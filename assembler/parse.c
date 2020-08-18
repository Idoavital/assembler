#include <ctype.h>  /* isspace */
#include <stdio.h>	/* sscanf */
#include <string.h> /* strlen, strcmp */

#include "parse.h"
#include "Error.h"
#include "Data_structures.h"
#include "parseLine.h"


int check_legal_comma(char* str, int index)
{
	char cmd[MAX_COMMAND];
	int comma_flag = OFF;
	int first_word = TRUE;
	int first_op   = TRUE;

	index = label_position(str, index);


	sscanf(str,"%s", cmd);

	if (strcmp(cmd,".string") ==0 )
	{
		index = clear_white_space(str, index);
		index = clear_word(str, index);
		index = clear_white_space(str, index);

		if (str[index] != '"')
		{
			print_err(ERR_STRING);
			return  COMMA_ERROR;
		}
			
		index++;   /*increase after " sign*/

		while (!is_end_of_line(str[index]) && str[index] != '"')
		{
			index++;
		}

		if (is_end_of_line(str[index]))
		{
			print_err(ERR_EXTRA_TEXT);
			return  COMMA_ERROR;
		}

		index++;
		index = clear_white_space(str, index);
		/*check if there is extra text after string */
		if (!is_end_of_line(str[index]))
		{
			print_err(ERR_EXTRA_TEXT);
			return  COMMA_ERROR;
		}

		return COMMA_OK;
	}

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


void split_line(char* str, int index,int flag)
{
    char temp_str[MAX_LINE_LEN];
    int row_index = 0;
    int column_index = 0;
    int start_word;
    int last_word = FALSE;
    strcpy(&temp_str[index],&str[index]); 

    if (flag == STRING)
    {
		while (!is_end_of_line(str[index]))
		{
			sscanf(&str[index],"%s",&splitLine[row_index++][column_index]);
			index = clear_word(str,index);
			index = clear_white_space(str, index);
		}
		

       /*if (!is_end_of_line(str[index]))
            sscanf(&str[index],"%s",&splitLine[row_index++][column_index]);
        index = clear_word(str,index);
        index = clear_white_space(str, index);
        if (!is_end_of_line(str[index]))
            strcpy(&splitLine[row_index][column_index],&str[index]); */   
    }
    else
    {
        while (last_word == FALSE)
        {
        if (is_space(temp_str[index]))
		{
	        index = clear_white_space(temp_str, index);
            if (is_end_of_line(temp_str[index]))
		        break;
		}
        if (temp_str[index] == ',')
        {
           index++;
        }

		 if (is_space(temp_str[index]))
		{
	        index = clear_white_space(temp_str, index);
            if (is_end_of_line(temp_str[index]))
		        break;
		}

        start_word = index;
        index = clear_word(temp_str,index);
        last_word = is_end_of_line(temp_str[index]) ? TRUE: FALSE;
        temp_str[index] = '\0';
        strcpy(&splitLine[row_index++][column_index], &temp_str[start_word]);    
        index++;

        }
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

	if (is_label_definition(str, index))
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

int is_extern(char* str, int index)
{
	char word[MAX_LABEL_LEN];
	sscanf(&str[index], "%s", word);

	if (strcmp(word, ".extern") == 0)
		return TRUE;

	return FALSE;
}

int is_entry(char* str, int index)
{
	char word[MAX_LABEL_LEN];
	sscanf(&str[index], "%s", word);

	if (strcmp(word, ".entry") == 0)
		return TRUE;

	return FALSE;
}

int is_data(char* str, int index)
{
	char cmd[MAX_COMMAND_NAME];

	index = label_position(str, index);

	sscanf(&str[index], "%s", cmd);

	if (strcmp(cmd, ".data") == 0 || strcmp(cmd, ".string") == 0)
		return TRUE;

	return 0;
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

int is_one_word(char* str, int index)
{
	index = clear_white_space(str, START_LINE);
	index = clear_word(str, index);
	index = clear_white_space(str, START_LINE);

	if (is_end_of_line(str[index]))
		return TRUE;

	return FALSE;
}

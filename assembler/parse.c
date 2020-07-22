#include <ctype.h>  /* isspace */
#include <stdio.h>	/* sscanf */
#include <string.h> /* strlen */

#include "parse.h"

int check_legal_comma(char* str, int index)
{
	while (isspace(str[index]))
	{
		/*check if the last char is a comma*/
	}
	return 0;
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

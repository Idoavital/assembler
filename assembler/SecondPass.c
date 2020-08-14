
#include <string.h>
#include <stdlib.h>

#include "SecondPass.h"
#include "FirstPass.h"
#include "parse.h"
#include "parseLine.h"
#include "Error.h"

int SecondPass(FILE* pfile)
{
	char line[MAX_LINE_LEN];

	init_counter();

	for (Line_number = 1; fgets(line, MAX_LINE_LEN, pfile); Line_number++) /* Scanning through each line of the file */
	{
		/* check is a comment or blank line*/
		if (is_comment_or_blank_line(line, START_LINE))
			continue;

		/* if is entry : set the symbol and jump to the next line*/
		if (check_and_set_entry(line, START_LINE) == TRUE)
			continue;
		
		if (is_data(line, START_LINE))
		{
			read_data(line, START_LINE);
		}
	}


	return err_num;
}

int check_and_set_entry(char* line, int index)
{
	char def[MAX_COMMAND_NAME];
	char label[MAX_LABEL_LEN];

	sscanf(line,"%s %s", def, label);

	if (strcmp(".entry", def) == 0)
	{
		if (set_symbol_to_entry(label) == NO_SYMBOL)
			err_num = ERR_SYMBOL_NOT_FOUND;

		return TRUE;
	}

	return FALSE;
}

void init_counter()
{
	DC = START_DC;
	IC = START_IC;
}

int read_data(char* str, int index)
{

	char data[MAX_COMMAND_NAME];
	
	/*no need to read label if exisiting*/
	index = label_position(str, index);
	index = clear_white_space(str, index);

	sscanf(&str[index], "%s", data);

	index = clear_word(str, index);
	index = clear_white_space(str, index);

	if (strcmp(".data", data) == 0)
	{
		
		while (index >= 0)
		{
			data_table[DC].address   = DC;
			data_table[DC].word.data = atoi(&str[index]);
			index = get_next_comma_pos(str, index);
			DC++;
		}

	}
	else if (strcmp(".string", data) == 0)
	{

		/*check if it's not a empty string*/
		if (is_end_of_line(str[index]))
			return 0;

	}


	return 0;
}

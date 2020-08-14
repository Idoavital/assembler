
#include <string.h>

#include "SecondPass.h"
#include "FirstPass.h"
#include "parse.h"
#include "parseLine.h"
#include "Error.h"

int SecondPass(FILE* pfile)
{
	char line[MAX_LINE_LEN];


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


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

		if (str[index] == '"') /* data string start with " (qoute char)*/
			index++;

		while (str[index] != '"')
		{
			data_table[DC].address   = DC;
			data_table[DC].word.data = str[index];
			DC++;
			index++;
		}
		data_table[DC].address   = DC;  /* End of string add null terminator*/
		data_table[DC].word.data ='\0';
		DC++;
;
	}


	return 0;
}

int write_files(char* fName)
{
	char objFilesName[MAX_FILE_NAME];
	char entryFileName[MAX_FILE_NAME];
	char externFileName[MAX_FILE_NAME];

	/*Crate the assembly files names*/
	sprintf(objFilesName,	"%s.ob", fName);
	sprintf(entryFileName,	"%s.ent", fName);
	sprintf(externFileName, "%s.ext", fName);


	if (write_obj_file(objFilesName) == FALSE)
	{
		/*TODO: ERROR*/
		return FILE_ERR;
	}

	if (write_entry_file(entryFileName) == FALSE)
	{
		/*TODO: ERROR*/
		return FILE_ERR;
	}

	if (write_exteren_file(externFileName) == FALSE)
	{
		/*TODO: ERROR*/
		return FILE_ERR;
	}
	return NO_ERROR;
}

int write_obj_file(char* fName)
{
	FILE* pObjFile;
	int i = 0;

	pObjFile = fopen(fName, "w");
	if (pObjFile == NULL)
	{
		printf(P_ERROR"Can't open %s file\n", fName);
		return FILE_ERR;
	}

     /*In the first of the file, print the number instruction and data numbers*/
	fprintf(pObjFile, "\t%d %d\n", IC, DC); 

	for (i=START_IC ; i < IC; i++)  /*Print instructions address and machie code (in hex)*/
		fprintf(pObjFile, "%06d %06x\n", code_table[i].address , code_to_unsigned(code_table[i].word.b_code)); /* prints instruction macine code */

	for (i = 0; i < DC; i++)		/*Print data address and data machie code (in hex)*/
		fprintf(pObjFile, "%06d %06x\n", IC + data_table[i].address , data_table[i].word.data);


	fclose(pObjFile);
	return 0;
}

int write_entry_file(char* fName)
{

	FILE*    pEntryFile;
	pSymbole current_sym = pSymbole_Head;

	pEntryFile = fopen(fName, "w");
	if (pEntryFile == NULL)
	{
		printf(P_ERROR"Can't open %s file\n", fName);
		return FILE_ERR;
	}

	while (current_sym != NULL)
	{
		
		if(current_sym->isEntry)
			fprintf(pEntryFile, "%s %d\n",current_sym->name ,current_sym->address );

		current_sym = current_sym->next;
	}


	fclose(pEntryFile);
	return 0;
}

int write_exteren_file(char* fName)
{
	FILE* pExternFile;
	

	pExternFile = fopen(fName, "w");
	if (pExternFile == NULL)
	{
		printf(P_ERROR"Can't open %s file\n", fName);
		return FILE_ERR;
	}

	/* TODO: print the extern list - shachar format.
	*/
	fclose(pExternFile);
	return 0;
}

unsigned int code_to_unsigned(st_machine_word word)
{
	return (*((unsigned int*)&word));

}

void clean(FILE* pFile)
{

	clear_list();   /*delet the symbol table and clean the memory of all the symbol*/
	IC = START_IC;  /* set counter to next files*/
	DC = START_DC;  /* set counter to next files*/
	fclose(pFile);  /* free the assembly code file*/
}


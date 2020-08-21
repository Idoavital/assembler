
#include <string.h>
#include <stdlib.h>

#include "SecondPass.h"
#include "FirstPass.h"
#include "syntaxLine.h"
#include "parseLine.h"
#include "Error.h"
#include "Data_structures.h"
#include "Defines.h"

void bin(int n)
{
	unsigned i;
	for (i = 1 << 31; i > 0; i = i / 2)
		(n & i) ? printf("1") : printf("0");
}

int SecondPass(FILE* pfile)
{
	char line[MAX_LINE_LEN];
	int outcome = 0;
	initialize_opcode_funct_table();

	init_counter();

	for (Line_number = 1; fgets(line, MAX_LINE_LEN, pfile); Line_number++) /* Scanning through each line of the file */
	{
		/* check is a comment or blank line*/
		if (is_comment_or_blank_line(line, START_LINE))
			continue;

		if (is_extern(line, START_LINE))
		{
			continue;
		}
		/* if is entry : set the symbol and jump to the next line*/
		if (check_and_set_entry(line, START_LINE) == TRUE)
			continue;
		
		if (is_data(line, START_LINE))
		{
			read_data(line, START_LINE);
			continue;
		}
		initialize_splitLine();
		split_line(line,START_LINE, NOT_STRING,NOT_LABEL);
		if ((outcome = read_code (splitLine, START_LINE, START_LINE)) != OK)
		{
			print_err(outcome);
			continue;
		}
	}


	return err_num;
}



int read_code (char line[MAX_LINE_LEN][MAX_LINE_LEN], int indexR, int indexC)
{
	int first_memory  = IC-START_IC;
	int second_memory = 0;	
	int third_memory  = 0;
	int outcome       = 0;
	int i;

	int method_address = 0;;
	if (is_label_definition(line[START_LINE],START_LINE))
	{
		indexR ++; /*if the line had a definition of a label. we will skip to the next row in splitLine where the command name is written. */
	}
	/*update information in the first memory word.*/
	code_table[first_memory].address = IC;

	for (i = 0; i < MAX_COMMAND; i++)
	{
		if (!strcmp (opcode_funct_table[i].command_name,line[indexR]))
		{
			code_table[first_memory].word.b_code.opcode = opcode_funct_table[i].opcode;
			code_table[first_memory].word.b_code.funct  = opcode_funct_table[i].funct;
			break;
		}
	}
	code_table[first_memory].word.b_code.A = 1;
	
	/*checks if we got to the end of the line*/
	if (line[++indexR][indexC] == '\0')
	{
		IC++;
		return OK;
	}
		
	/*update info for the first operator*/
	method_address = which_type(line[indexR], indexC);
	code_table[first_memory].word.b_code.adrs_source = method_address;
	outcome = read_operator(line,indexR,indexC,method_address,first_memory,second_memory,third_memory,SOURCE);
	if (outcome != OK)
	{
		IC++;
		return outcome;
	}
		
	
	/*checks if we got to the end of the line*/
	if (splitLine[++indexR][indexC] == '\0')
	{	
		IC++;
		return OK;
	}
		
	
	/*update info for the second operator*/
	method_address = which_type(line[indexR], indexC);
	code_table[first_memory].word.b_code.adrs_dest = method_address;	
	outcome = read_operator(line,indexR,indexC,method_address,first_memory,second_memory,third_memory,TARGET);
	if (outcome != OK)
	{
		IC++;
		return outcome;
	}
		
	IC++;
	return OK;
}



int read_operator(char line[MAX_LINE_LEN][MAX_LINE_LEN], int indexR, int indexC, int method_address,int first_memory, int second_memory,int third_memory, int flag)
{
	int i             = 0;
	int num           = 0;
	int label_address = 0;

	if (method_address == METHOD_ADDRESS3)/*register*/
	{	for ( i = 0; i < MAX_REGISTER; i++)
		{	
			num = atoi(&splitLine[indexR][indexC+1]);
			if ( num == i)
			{
				if (flag == SOURCE)
					code_table[first_memory].word.b_code.reg_source = i;
				else
					code_table[first_memory].word.b_code.reg_dest = i;
				
				break;
			}
		}
	}/*if it isnt a register, we need to add anoter memory word*/
	else
	{
		second_memory = (++IC)-START_IC;
		code_table[second_memory].address = IC;
		if (method_address == METHOD_ADDRESS0)/*number*/
		{	
			num = atoi(&splitLine[indexR][indexC+1]);
			code_table[second_memory].word.b_address.address = num;
			code_table[second_memory].word.b_address.A = 1;
		}
		else if (method_address == METHOD_ADDRESS2)/*address label*/
		{
			if((label_address = get_symbol_address(&splitLine[indexR][indexC+1])) == NO_SYMBOL)
				return ERR_SYMBOL_NOT_FOUND;
			if (get_symbol_type(&splitLine[indexR][indexC+1]) == ST_EXTERN)
				return ERR_ADDRESS_EXTREN_LABEL;
			code_table[second_memory].word.b_address.address = label_address;
			code_table[second_memory].word.b_address.R = 1;
			third_memory = (++IC)-START_IC;
			code_table[third_memory].address = IC;
			code_table[third_memory].word.b_address.address = (label_address - second_memory)-START_IC; /*jumping distance*/
			code_table[third_memory].word.b_address.A = 1;
		}
		else /*the method address is equal to method_adress1, a label.*/
		{
			if((label_address = get_symbol_address(&splitLine[indexR][indexC])) == NO_SYMBOL)
				return ERR_SYMBOL_NOT_FOUND;

			code_table[second_memory].word.b_address.address = label_address;

			/*if the label is an extern we will add the label to the extern table.*/
			if (get_symbol_type(&splitLine[indexR][indexC]) == ST_EXTERN)
			{
				extern_label[index_extern].addrerss = IC;
				strcpy(extern_label[index_extern].name, &splitLine[indexR][indexC]);
				index_extern++;
				code_table[second_memory].word.b_address.E = 1;

			}
			else
			code_table[second_memory].word.b_address.R = 1;
			
		}
	}
	return OK;	
}


int which_type (char* line, int index)
{
	int outcome;

	if ((outcome = is_register(line,index)))
		return outcome;
	if ((outcome = is_number(line, index, INS_NUMBER)) != NOT_NUM)
		return outcome;
	if ((outcome = is_address_method_for_jump_command(line,index)))
		return outcome;
 
	return METHOD_ADDRESS1;
}


int check_and_set_entry(char* line, int index)
{
	char def[MAX_COMMAND_NAME];
	char label[MAX_LABEL_LEN];

	sscanf(line,"%s %s", def, label);

	if (strcmp(".entry", def) == 0)
	{
		if (set_symbol_to_entry(label) == NO_SYMBOL)
		{
			printf(P_ERROR"In file %s the symbol %s is not found \n", file_name, label);
			err_num = ERR_SYMBOL_NOT_FOUND;
		}
			

		return TRUE;
	}

	return FALSE;
}

void init_counter()
{
	DC = START_DC;
	IC = START_IC;
	index_extern = 0;
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
		err_num = ERR_WRITE_FILE;
		printf(P_ERROR" fiald to write obj file");

		return FILE_ERR;
	}

	if (write_entry_file(entryFileName) == FALSE)
	{
		err_num = ERR_WRITE_FILE;
		printf(P_ERROR" fiald to write entry file");

		return FILE_ERR;
	}

	if (write_exteren_file(externFileName) == FALSE)
	{
		err_num = ERR_WRITE_FILE;
		printf(P_ERROR" fiald to write extern file");
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
	fprintf(pObjFile, "\t%d %d\n", IC-START_IC , DC);

	for (i = START_IC; i < IC; i++)  /*Print instructions address and machie code (in hex)*/
	{

		fprintf(pObjFile, "%07d %06x\n", code_table[i - START_IC].address, code_to_unsigned(code_table[i - START_IC].word.b_code)); /* prints instruction macine code */
	}


	for (i = 0; i < DC; i++)		/*Print data address and data machie code (in hex)*/
	{
		printf("%06d ", IC + data_table[i].address);
		bin(data_table[i].word.data);
		printf("\n");
		fprintf(pObjFile, "%07d %06x\n", IC + data_table[i].address, data_table[i].word.data);

	}
	


	fclose(pObjFile);
	return TRUE;
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
			fprintf(pEntryFile, "%s %07d\n",current_sym->name ,current_sym->address );

		current_sym = current_sym->next;
	}


	fclose(pEntryFile);
	return TRUE;
}

int write_exteren_file(char* fName)
{
	FILE* pExternFile;
	int i = 0;

	pExternFile = fopen(fName, "w");
	if (pExternFile == NULL)
	{
		printf(P_ERROR"Can't open %s file\n", fName);
		return FILE_ERR;
	}

	for (i = 0; i < index_extern; i++)
		fprintf(pExternFile, "%s  %07d\n", extern_label[i].name, extern_label[i].addrerss);

	fclose(pExternFile);
	return TRUE;
}

 int code_to_unsigned(st_machine_word word)
{
	return (*(( int*)&word));

}

void clean(FILE* pFile)
{

	clear_list();   /*delet the symbol table and clean the memory of all the symbol*/
	IC = START_IC;  /* set counter to next files*/
	DC = START_DC;  /* set counter to next files*/
	fclose(pFile);  /* free the assembly code file*/
}


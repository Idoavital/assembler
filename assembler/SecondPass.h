#ifndef __SECOND_PASS_H__
#define  __SECOND_PASS_H__

#include <stdio.h>
#include "Data_structures.h"



/***************************************************************************/
						/* Second pass functions */
/***************************************************************************/

/*
* the seconed pass in assembler process - create the machine code and print binary files,
* @pfile - file pointer to assembley code file.
  @return error if there is error in the file code.
*/
int SecondPass(FILE* pfile);


/**
* This function update the first memory code (opcode,func ..),  if there wasnt an error.
* @param line	-a matrix that contains the split sentence, in a way that in every row there is a word.
* @param indexR	-  index of a row that contains the command name.
* @param indexC -  the position of the command name.
* @return  the function returns the specific ERROR if there was any error, otherwise it will return OK.
*/
int read_code (char line[MAX_LINE_LEN][MAX_LINE_LEN], int indexR, int indexC);


/**
* This function update the memory word accroding to the operator, if there wasnt an error.
* @param line	-a matrix that contains the split sentence, in a way that in every row there is a word.
* @param indexR	-  index of a row that contains the operator.
* @param indexC -  the position of the operator.
* @return  the function returns the specific ERROR if there was any error, otherwise it will return OK.
*/
int read_operator(char line[MAX_LINE_LEN][MAX_LINE_LEN], int indexR, int indexC, int method_address,int first_memory, int second_memory,int third_memory,int flag);


/**
* This function checks the type of the operator.
* @param line	- a pointer to the operator.
* @param index - the position of the operator.
* @return  the function returns the method address of the operator.
*/
int which_type (char* line, int index);


/*
* The function check if the line is .entry definition , and if it's entry 
* the function set the symbol to emtry type.
* @param str	- a pointer to beginnig of the line.
* @param index	- the postion in the line.
* @return	    - return TRUE if line is entry definition and seccuss to set the symbol else return FALSE
*/
int check_and_set_entry(char* line, int index);

/*
* The function initialize the IC and DC contres to start position
*/
void init_counter();

/*
* The function read the the data from line and inset the data to data_table
* @param str	- a pointer to beginnig of the line.
* @param index	- the postion in the line.
* @return	    - return TRUE if seccuss read and push all data, else return FALSE
*/
int read_data(char* str, int index);

/*
* Create and write assembly machine code files.
* @param fName	- the file name.
* @return		- NO_ERROR if success to create and write to files else return error number.
*/
int write_files(char* fName);

/*
* The function write assembly object machine code file.
* @param fName	- the file name.
* @return		- true if write to files else return false.
*/
int write_obj_file(char* fName);

/*
* The function write assembly object machine code file.
* @param fName	- the file name.
* @return		- true if write to files else return false.
*/
int write_entry_file(char* fName);

/*
* The function write assembly object machine code file.
* @param fName	- the file name.
* @return		- true if write to files else return false.
*/
int write_exteren_file(char* fName);

/* The function convert st_machine_word to unsigned.
* @param word	-  the macine word to convert.
* @return		- return unsignd int that represent the binary code.
*/
 unsigned int code_to_unsigned(st_machine_word  word);

/* The function clean all memory , structures and globals 
* @param pFile	- pointer to assembler code file
*/
void clean(FILE* pFile);

#endif /* !_SECOND_PASS_H__*/

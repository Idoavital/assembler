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

#endif /* !_SECOND_PASS_H__*/

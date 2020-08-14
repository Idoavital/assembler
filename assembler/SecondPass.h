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

void init_counter();

#endif /* !_SECOND_PASS_H__*/

#ifndef __FIRST_PASS_H__
#define __FIRST_PASS_H__


#include <stdio.h>
#include "Data_structures.h"



/***************************************************************************/
						/* First pass functions */
/***************************************************************************/
/*
* the first pass in assembler process - check for error in string line,
* and build a symbole table
* @pfile - file pointer to assembley code file.
  @return error if there is error in the file code.
*/
int firstPass(FILE* pfile);


/*
* The function initialize of the global variable.
*/
void init_globals();

/*
* The function check the type of the label.
* @param str	- a pointer to beginnig of the line.
* @param index	- the postion of the line
* @return		- the type of the label. 
*/
int get_type(char* str, int index);

/*
* the function copy the label name to param name
* @param str_in	- the line with label name to copy from.
* @param name	- pointer to a place that the name will be copy. 
* 
*/
void get_label_name(__IN char* str_in, __OUT char* name);

/***************************************************************************/
						/* Link list functions */
/***************************************************************************/


/* The function allocate and create a new symbole line and  .
* @param name		- pointer to the symbole name.
* @param address	- the address counter (according to IC or DC) .
* @param type		- the type of the symbole (label).
* @return			- return pointer to the new symbol.
*/
pSymbole create_symbol(char *pName, int address, int type );

/*
* The functoin insert new symbol to the symbol table .
* @param pSymbol	- pointer to new symbol.
* @return			- True if success to insert new symbol .
*/
int push_symbol(pSymbole pSymbole_node);

/* the function free the memory of the symbol.
* @param pSymbol	- pointer to the symbol to be free.
* @return			- True if success to free the symbol .
*/
int free_symbol(pSymbole pSymbole_node);

/* the function free the memory of all the symbols in the table.
* @return			- True if success to free all the symbols .
*/
int clear_list();

#endif /* !__FIRST_PASS_H__ */
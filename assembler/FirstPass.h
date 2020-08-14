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
* @param type	- the label type (if it's extern type).
*/
void get_label_name(__IN char* str_in, __OUT char* name, int type);

/*
* This function update the dc counter.
* @param str	- a pointer to beginnig of the line.
* @param index	- the postion of the line
* 
*/
void calc_dc_counter(char* str, int index);

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


/* the function return the symbol address.
* @param name	- the symbol name. (NOTE: the name have to finish with null terminator '\0')
* @return		- return the symbol address, if the symbol is not in the table
*				  the function return NO_SYMBOL (number that is less then 0) .
*/
int get_symbol_address(char *name);

/* the function return the symbol type.
* @param name	- the symbol name. (NOTE: the name have to finish with null terminator '\0')
* @return		- return the symbol address, if the symbol is not in the table
*				  the function return NO_SYMBOL (number that is less then 0) .
*/
int get_symbol_type(char* name);
/* the function set the symbol to entry type.
* @param name	- the symbol name. (NOTE: the name have to finish with null terminator '\0')
* @return		- return true if seccuss to set the symbol, if the symbol not in the list return NO_SYMBOL  (number that is less then 0).
*				
*/
int set_symbol_to_entry(char* name);

/* the function return the symbol .
* @param name	- the symbol name. (NOTE: the name have to finish with null terminator '\0')
* @return		- return pointer to symbol
*				  the function return NULL  .
*/
pSymbole get_symbol(char* name);

/* the function free the memory of all the symbols in the table.
* @return			- True if success to free all the symbols .
*/
int clear_list();

#endif /* !__FIRST_PASS_H__ */
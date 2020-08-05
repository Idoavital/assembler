#ifndef __FIRST_PASS_H__
#define __FIRST_PASS_H__


#include <stdio.h>
#include "Data_structures.h"

/*
* the first pass in assembler process - check for error in string line,
* and build a symbole table
* @pfile - file pointer to assembley code file.
  @return error if there is error in the file code.
*/
int firstPass(FILE* pfile);

/***************************************************************************/
						/* Link list functions */
/***************************************************************************/

/* The function allocate and create a new symbole line and  .
* @param name		- pointer to the symbole name.
* @param address	- the address counter (according to IC or DC) .
* @param type		- the type of the symbole (label).
* @return			- return pointer to the new symbol.
*/
pSymbole create_symbole(char *pName, int address, int type );

int push_symbole(pSymbole pSymbole_head, pSymbole pSymbole_node);

#endif /* !__FIRST_PASS_H__ */
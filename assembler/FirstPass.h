#include <stdio.h>


/*
* the first pass in assembler process - check for error in string line,
* and build a symbole table
* @pfile - file pointer to assembley code file.
  @return error if there is error in the file code.
*/
int firstPass(FILE* pfile);
#ifndef __H_PARSE__
#define __H_PARSE__


#include "Definitions.h"

/**
* This function check if the postion and numbers that comma appear in the assembly code line
* is leagal.
* @param str	- a pointer to beginnig of the line
* @param index	- the postion of the line
*/

int check_legal_comma(char* str, int index);

/**
* This function chekc if the next char  is a comma (ignore white space).
* @param str	- a pointer to beginnig of the line
* @param index	- the postion of the line
* @return true if the next character is comma .
*/
int is_comma(char* str, int index);


/**
* This function chekc if char  is space (only  - ' ','\t','\r','\v', '\f','\r') 
* new line char '\n' -is not space.
* @param c	- char
* @return true if the next character is space .
*/
int is_space(char c);

/**
* This function return the position in the string of the ending Label .
* @param str	- a pointer to beginnig of the line
* @param index	- the postion of the line
* @return the position of  of the ending Label (the index of':' ) 
* in a case is no label the return value is the index param value without change.
*/
int label_position(char* str, int index);

/**
* This function chekc if the next word is a label (ignore white space).
* @param str	- a pointer to beginnig of the line
* @param index	- the postion of the line
* @return true if the next word is label .
*/
int is_label(char* str, int index);

#endif /* !_H_PARSE_ */

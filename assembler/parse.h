#ifndef __PARSE_H__
#define __PARSE_H__


#include "Defines.h"
#include "Data_structures.h"


/***************************************************************************/
					/*Founctoin Declaration*/
/***************************************************************************/

/**
* This function check if the postion and numbers that comma appear in the assembly code line
* is leagal.
* @param str	- a pointer to beginnig of the line
* @param index	- the postion of the line
*/

int check_legal_comma(char* str, int index);

/**
* This function devied the line an a way that each cell in the splitLine array points to a word in the orginal sentence.
* @param str	- a pointer to beginnig of the line.
* @param index	- the postion of the line
*/
void split_line(char* str, int index);


/**
* This function check if the next char  is a comma (ignore white space).
* @param str	- a pointer to beginnig of the line
* @param index	- the postion of the line
* @return true if the next character is comma .
*/
int is_comma(char* str, int index);


/**
* This function check if char  is space (only  - ' ','\t','\r','\v', '\f','\r') 
* new line char '\n' -is not space.
* @param c	- char
* @return true if the next character is space .
*/
int is_space(char c);

/**
* This function return the position in the string of the ending Label .
* @param str	- a pointer to beginnig of the line.
* @param index	- the postion of the line.
* @return the position of  of the ending Label (the index of':' ) 
* in a case is no label the return value is the index param value without change.
*/
int label_position(char* str, int index);

/**
* This function check if the next word is a label (ignore white space).
* @param str	- a pointer to beginnig of the line.
* @param index	- the postion of the line.
* @return true if the next word is label .
*/
int is_label(char* str, int index);

/**
* This function check if the next word is lagal label name.
* @param str	- a pointer to beginnig of the line.
* @param index	- the postion of the line.
* @return true if the word is leagal label.
*/
int is_legal_label(char* str, int index);

/**
* This function clear white space.
* @param str	- a pointer to beginnig of the line.
* @param index	- the postion of the line.
* @return the index of the first char that is not white space/
*/
int clear_white_space(char* str, int index);

/**
* This function clear word. (word end with white space or a comma)
* @param str	- a pointer to beginnig of the line.
* @param index	- the postion of the line.
* @return the index of after the word .
*/
int clear_word(char* str, int index);


/**
* This function check if a char is end of line 
* @param c	- char .
* @return true if the char is end of line.
*/
int is_end_of_line(char c) ;

/**
* This function check if a word is keyword(reserved word)
* @param str	- a pointer to beginnig of the line.
* @param index	- the postion of the line.
* @return true if the char is end of line.
*/
int is_keyword(char *str, int index, int flag);

/**
* This function print the 24 bit word in hex
* @word - 24bit word to print
*/
void print_hex(st_mem_word word);



#endif /* !__PARSE_H__ */

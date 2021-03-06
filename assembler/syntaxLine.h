#ifndef __SYNTAX_LINE_H__
#define __SYNTAX_LINE_H__


#include "Defines.h"
#include "Data_structures.h"


/***************************************************************************/
					/*Founctoin Declaration*/
/***************************************************************************/

/**
* This function check if the postion and numbers that comma appear in the assembly code line
* is leagal.
* @param str	- a pointer to beginnig of the line
* @param index	- the position in the line
* @return		- COMMA_OK if there is no error, else return COMMA_ERROR
*/

int check_legal_comma(char* str, int index);


/**
* This function devied the line an a way that each row in the matrix splitLine contains a word from the sentence. 
* @param str	- a pointer to beginnig of the line.
* @param index	- the postion in the line
* @param flag- this flag indicate whether the command is '.string' or the rest of the commands. if its a .string, we'll split
* @param flag_label - this flag indicate if there is a definition of a label.
*the line in a way that the '.string' will be in one row in the metrix, and the actual string will be in the next row. 8888NEED TO UPDTAE8888
*/
void split_line(char* str, int index,int flag,int flag_label);

/**
* This function check if the next char  is a comma (ignore white space).
* @param str	- a pointer to beginnig of the line
* @param index	- the position in the line
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
* @param index	- the position in the line.
* @return the position of  of the ending Label (the index of':' ) 
* in a case is no label the return value is the index param value without change.
*/
int label_position(char* str, int index);


/**
* This function clear white space.
* @param str	- a pointer to beginnig of the line.
* @param index	- the position in the line.
* @return the index of the first char that is not white space/
*/
int clear_white_space(char* str, int index);

/**
* This function clear word. (word end with white space or a comma)
* @param str	- a pointer to beginnig of the line.
* @param index	- the position in the line.
* @return the index of after the word .
*/
int clear_word(char* str, int index);

/**
* This function check if a addembly line is a comment
* @param str	- a pointer to beginnig of the line.
* @param index	- the position in the line.
* @return true if the line is comment or a blank line .
*/
int is_comment_or_blank_line(char* str, int index);

/**
* This function check if a the line is extern label.
* @param str	- a pointer to beginnig of the line.
* @param index	- the position in the line.
* @return true if the line is extern label.
*/
int is_extern(char* str, int index);

/**
* This function check if a the line is entry label.
* @param str	- a pointer to beginnig of the line.
* @param index	- the position in the line.
* @return true if the line is extern label.
*/
int is_entry(char* str, int index);

/**
* This function check if a the line is data (".string" || ".data").
* @param str	- a pointer to beginnig of the line.
* @param index	- the position in the line.
* @return true if the line is data.
*/
int is_data(char* str, int index);
/**
* This function return the index in line after the comma.
* @param str	- a pointer to beginnig of the line.
* @param index	- the position in the line.
* @return the index in line after comma. if the line end return a negtive number.
*/
int get_next_comma_pos(char* str, int index);

/**
* This function check if a char is end of line 
* @param c	- char .
* @return true if the char is end of line.
*/
int is_end_of_line(char c) ;

/**
* This function return TRUE if there is only one word in the line.
* @param str	- a pointer to beginnig of the line.
* @param index	- the position in the line.
* @return		-  return TRUE if there is only one word in the line..
*/
int is_one_word(char* str, int index);



#endif /* !__SYNTAX_LINE_H__ */

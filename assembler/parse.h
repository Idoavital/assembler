#ifndef __H_PARSE__
#define __H_PARSE__


/**
* This function check if the postion and numbers that comma appear in the assembly code line
* is leagal.
* @param str	- a pointer to beginnig of the line
* @param index	- the postion of the line
*/

int check_legal_comma(char* str, int index);

/**
* This function chekc if the next char is a comma.
* @param str	- a pointer to beginnig of the line
* @param index	- the postion of the line
*/
int is_comma(char* str, int index);


#endif // !_H_PARSE_

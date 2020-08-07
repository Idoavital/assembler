#ifndef __ERROR__H__
#define __ERROR__H__


extern int Line_number;
/***************************************************************************/
						/* COLORS */
/***************************************************************************/

/* If you don't want to print error with color, just commit or delet color definition (/ * #define COLOR * / ) */
/*#define COLOR  */

#ifdef COLOR

#define YELLOW "\033[0;33m"		/*Yellow color*/
#define GREEN  "\033[0;32m"		/*Green color*/
#define RED    "\033[0;31m"		/*Red color*/
#define RESET  "\033[0;0m"		/*Reset to defualt color*/

#else

#define YELLOW " "		/*Yellow color*/
#define GREEN  " "		/*Green color*/
#define RED    " "		/*Red color*/
#define RESET  " "		/*Reset to defualt color*/

#endif

/***************************************************************************/
						/* Define */
/***************************************************************************/

#define P_ERROR RED"[ERROR] "
#define P_DEBUG GREEN"[DEBUG] "

#define COMMA_OK		0
#define COMMA_ERROR		1

#define PUSH_OK			0
#define PUSH_ERROR		1

/***************************************************************************/
						/* ENUMS */
/***************************************************************************/
enum eERROR
{
	ERR_COMMA_AFTER_CMD = 1,
	ERR_COMMA_NOT_INPLACE,
	ERR_TWO_COMMA,
	ERR_COMMA_END_LINE,
	ERR_MISSING_COMMA,
	ERR_ILLIGL_LABEL,
	ERR_NO_MATCH,
	ERR_OPERATOR_TARGET,
	ERR_OPERATOR_SOURCE,
	ERR_EXTRA_TEXT


};


/***************************************************************************/
					/*Founctoin Declaration*/
/***************************************************************************/

/**
* This function check if the postion and numbers that comma appear in the assembly code line
* is leagal.
* @param str	- a pointer to beginnig of the line
* @param index	- the postion of the line
*/
int print_err(enum eERROR err_type);

#endif /* !__ERROR__H__ */


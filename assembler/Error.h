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
	ERR_MIISING_LABEL  = -18,
	ERR_ILLEGAL_LABEL,
	ERR_STRING,
	ERR_NUMBER_DATA,
	ERR_MISSING_TARGET,
   	ERR_MISSING_SOURCE,
   	ERR_MISSING_OPERATOR,
   	ERR_EXTRA_TEXT,
   	ERR_OPERATOR_UNDEFINED_TARGET,
   	ERR_OPERATOR_UNDEFINED_SOURCE,
   	ERR_NUMBER_TARGET,
  	ERR_NUMBER_SOURCE,
  	ERR_LBAEL_TARGET,
  	ERR_LABEL_SOURCE,
   	ERR_ADDRESS_LABEL_TARGET,
   	ERR_ADDRESS_LABEL_SOURCE,
   	ERR_REGISTER_TARGET,
   	ERR_REGISTER_SOURCE,

	ERR_COMMA_AFTER_CMD = 1,
	ERR_COMMA_NOT_INPLACE,
	ERR_TWO_COMMA,
	ERR_COMMA_END_LINE,
	ERR_MISSING_COMMA,
	ERR_ILLEGAL_DEF_LABEL,
	ERR_NO_MATCH,
	ERR_COMMAND_NAME,

	ERR_PUSH_TABLE,
	ERR_SYMBOL_ALLOCATION

};


/***************************************************************************/
						/* Define Macros */
/***************************************************************************/

#define ERR_REGISTER(flag) flag == SOURCE ? ERR_REGISTER_SOURCE : ERR_REGISTER_TARGET
#define ERR_ADDRESS_LABEL(flag) flag == SOURCE? ERR_ADDRESS_LABEL_SOURCE: ERR_ADDRESS_LABEL_TARGET
#define ERR_LABEL(flag) flag == SOURCE? ERR_LABEL_SOURCE: ERR_LBAEL_TARGET
#define ERR_NUMBER(flag) flag == SOURCE? ERR_NUMBER_SOURCE: ERR_NUMBER_TARGET
#define ERR_OPERATOR_UNDEFINED(flag) flag == SOURCE? ERR_OPERATOR_UNDEFINED_SOURCE: ERR_OPERATOR_UNDEFINED_TARGET


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


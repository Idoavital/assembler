#include <ctype.h>  /* isspace */
/*TODO: DELET THIS FILE BEFOR SENDIG THE PROJECT*/
/*ONLY FOR DEBUG PORPOSE*/
#include  "Error.h"
#include  "parse.h"

/***************************************************************************/
							/* Functions Definitions */
/***************************************************************************/

int test_comma();

/***************************************************************************/
							/* main function */
/***************************************************************************/
int Test()
{
	test_comma();

	return 0;
}

/***************************************************************************/
							/* Functions Declarations */
/***************************************************************************/
int test_comma()
{
	
	int error = 0;

	char line_ok[80] = "  LABEL: MOV R2,R2";
	char line_1[80] = "  LABEL MOV R2 , R2 ,";
	char line_2[80] = "  MOV R2, R2 \n";
	char line_3[80] = "  LABEL: MOV , R2 R2	";
	char line_4[80] = "  LABEL MOV R2 R2	";
	char line_5[80] = "  LABEL: MOV	 R2,R2  ,	";
	char line_6[80] = "  , MOV R2 , R2 , r3,r4 ,r5";
	char line_7[80] = ".data 3 , 4, -9 , 10 \n";
	char line_8[80] = "  .data 3, , 4, -9 , 10";

	error += check_legal_comma(line_ok,	START_LINE);
	error += check_legal_comma(line_1,	START_LINE);
	error += check_legal_comma(line_2,	START_LINE);
	error += check_legal_comma(line_3,	START_LINE);
	error += check_legal_comma(line_4,	START_LINE);
	error += check_legal_comma(line_5,	START_LINE);
	error += check_legal_comma(line_6,	START_LINE);
	error += check_legal_comma(line_7,	START_LINE);
	error += check_legal_comma(line_8,	START_LINE);

	return 0;
}

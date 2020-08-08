#include <ctype.h>  /* isspace */
#include <string.h>
/*TODO: DELET THIS FILE BEFOR SENDIG THE PROJECT*/
/*ONLY FOR DEBUG PORPOSE*/
#include  "Error.h"
#include  "parse.h"
#include  "FirstPass.h"
#include  "Data_structures.h"

/***************************************************************************/
							/* Functions Definitions */
/***************************************************************************/

int test_comma();
int test_symbol();
int test_comment();

/***************************************************************************/
							/* main function */
/***************************************************************************/
int Test()
{

	init_globals();
	test_comment();
	test_symbol();

	return 0;
}

/***************************************************************************/
							/* Functions Declarations */
/***************************************************************************/
int test_comma()
{
	char name[50];
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

	get_label_name(line_5, name);

	return 0;
}

int test_symbol()
{
	
	char name[10] = "LAB";
	int address = 100;
	enum Esymbole_type type = ST_STRING;

	pSymbole sym;
	pSymbole sym1;
	pSymbole sym2;
	pSymbole sym3;
	pSymbole sym4;


	sym = create_symbol(name, address, type);

	strcpy(name, "dodo");
	address = 120;
	type = ST_CODE;
	sym1 = create_symbol(name, address, type);

	strcpy(name, "bobo1");
	address = 122;
	type = ST_CODE;
	sym2 = create_symbol(name, address, type);

	strcpy(name, "wwwww");
	address = 122;
	type = ST_EXTERN;
	sym3 = create_symbol(name, address, type);

	strcpy(name, "dasaa");
	address = 130;
	type = ST_DATA;
	sym4 = create_symbol(name, address, type);

	push_symbol(sym);
	push_symbol(sym1);
	push_symbol(sym2);
	push_symbol(sym3);
	push_symbol(sym4);

	clear_list();




	printf("name: %s  address: %d, type: %d \n", sym->name, sym->address, sym->type);
	printf("name: %s  address: %d, type: %d \n", sym1->name, sym1->address, sym1->type);
	printf("name: %s  address: %d, type: %d \n", sym2->name, sym2->address, sym2->type);
	printf("name: %s  address: %d, type: %d \n", sym3->name, sym3->address, sym3->type);
	printf("name: %s  address: %d, type: %d \n", sym4->name, sym4->address, sym4->type);



	return 0;
}

int test_comment()
{
	int ret = 0;

	char line[]  = "     ; sadfsdaf ";
	char line2[] = "      ";
	char line3[] = ";     ; ";
	char line4[] = "    sdfsd  ";

	ret += is_comment_or_blank_line(line, 0);
	ret += is_comment_or_blank_line(line2, 0);
	ret += is_comment_or_blank_line(line3, 0);
	ret += is_comment_or_blank_line(line4, 0);

	return 0;
}

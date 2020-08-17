#include <ctype.h>  /* isspace */
#include <string.h>
#include <stdlib.h>
/*TODO: DELET THIS FILE BEFOR SENDIG THE PROJECT*/
/*ONLY FOR DEBUG PORPOSE*/
#include  "Error.h"
#include  "parse.h"
#include  "FirstPass.h"
#include  "Data_structures.h"
#include  "parseLine.h"
#include  "SecondPass.h"

/***************************************************************************/
							/* Functions Definitions */
/***************************************************************************/

int test_comma();
int test_symbol();
int test_comment();
int test_calc_dc();
int test_symbol_list();
int test_read_data();
int test_read_code();


void print_sym(pSymbole symbol);
/***************************************************************************/
							/* main function */
/***************************************************************************/

int Test()
{

	init_globals();

	test_read_data();

	test_symbol_list();

	test_calc_dc();
	test_comma();
	test_comment();
	test_symbol();

	return 0;
}

/***************************************************************************/
							/* Functions Declarations */
/***************************************************************************/
int test_read_code()
{	char* test1 = "mov r1,r2";
	char* test2 = "cmp #4,r1";
	char* test3 = "jmp &MAIN";
	char* test4 = "sub r1,Y";

	char name[10] = "W";
	int address = 100;
	enum Esymbole_type type = ST_STRING;

	pSymbole sym;
	pSymbole sym1;
	pSymbole sym2;
	pSymbole sym3;
	


	sym = create_symbol(name, address, type);

	strcpy(name, "Y");
	address = 120;
	type = ST_CODE;
	sym1 = create_symbol(name, address, type);

	strcpy(name, "LIST");
	address = 122;
	type = ST_CODE;
	sym2 = create_symbol(name, address, type);

	strcpy(name, "MAIN");
	address = 130;
	type = ST_CODE;
	sym3 = create_symbol(name, address, type);

	push_symbol(sym);
	push_symbol(sym1);
	push_symbol(sym2);
	push_symbol(sym3);

	

	
	IC = 100;
	initialize_opcode_funct_table();
	split_line(test1,0,NOT_STRING);
	read_code(splitLine,0,0);

	split_line(test2,0,NOT_STRING);
	read_code(splitLine,0,0);

	split_line(test3,0,NOT_STRING);
	read_code(splitLine,0,0);

	split_line(test4,0,NOT_STRING);
	read_code(splitLine,0,0);
	clear_list();

	return 0;
}	

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


	get_label_name(line_5, name ,0);

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

int test_calc_dc()
{
	int index = 0;
	char line_1[80] = "   LABEL: .data 10,-12  ,20,  +10";
	char line_2[80] = "  .string \"aswd   123\"  ";
	char line_3[80] = "  .string   \"1234567\"	";

	printf("dc = %d\n", DC);
	index = label_position(line_1, index);
	calc_dc_counter(line_1, index);
	printf("dc after line 1= %d\n", DC);

	calc_dc_counter(line_2, 0);
	printf("dc after line 3= %d\n", DC);

	calc_dc_counter(line_3, 0);
	printf("dc after line 3= %d\n", DC);

	return 0;
}

int test_symbol_list()
{
	pSymbole symbol = pSymbole_Head;
	int i ;
	char line_[10][80];

	strcpy(line_[0], "  LABEL:		DIR R2 , R2 ,");
	strcpy(line_[1], "  .data 10, 20, 30, -40");
	strcpy(line_[2], " LABEL: MOV R2, R2 \n");
	strcpy(line_[3], "  LABEL2: MOV  R2, R2	");
	strcpy(line_[4], "  .extern W 	");
	strcpy(line_[5], "  LABEL3: .data 3 , 4, -9 , 10 \n");
	strcpy(line_[6], "  .extern W ");
	strcpy(line_[7], " LABEL4 :   \n");
	strcpy(line_[8], ".string   \n");
	strcpy(line_[9], " LABEL5:	.string \"iGotThePower\"");



	for(i =0 ; i<=9; i++)
	{

		char name[MAX_LABEL_LEN];
		char line[MAX_LINE_LEN];
		enum Esymbole_type type;
		pSymbole new_symbol = NULL;
		int address = 0;

		strcpy(line, line_[i]);


		if (is_label_definition(line, START_LINE) || is_extern(line, START_LINE))
		{
			type = get_type(line, START_LINE);
			address = (type == ST_EXTERN ? 0 : (type == ST_DATA ? DC : IC));
			get_label_name(line, name, type);

			/*TODO: add to symbloe table*/
			new_symbol = create_symbol(name, address, type);
			if (new_symbol == NULL)
			{
				/*TODO: ERROR*/
			}
			push_symbol(new_symbol);/*TODO: GET ERROT ANSWER */
		}


		calc_dc_counter(line, START_LINE);
	}
	symbol = pSymbole_Head;
	printf("\n");
	while (symbol)
	{

		 print_sym(symbol);
		 symbol = symbol->next;

	}
	clear_list();
	return 0;
}
int test_read_data()
{
	int i;
	char line_[10][80];
	char str[100];
	int index = 0;

	strcpy(line_[0], "   .data 1, 2, 3, -4	");
	strcpy(line_[1], "  .data 21, -21, 22,27");
	strcpy(line_[2], " LABEL:   .data 310, 320, 330, -340");
	strcpy(line_[3], "  LABEL2:   .string  \"abcd\"	");
	strcpy(line_[4], "   .data 510, 520, 530, -540	");
	strcpy(line_[5], "  LABEL3: .data 63 , 64, -69 , 610 \n");
	strcpy(line_[6], "     .string  \"abcd\"	 ");
	strcpy(line_[7], "   .data 810, 820, 830, -840");
	strcpy(line_[8], ".data 910,920, 930, -940");
	strcpy(line_[9], ".data 1010, 1020, 1030, -1040");

	for (i = 0; i <= 9; i++)
	{
		
		char data[100];

		printf("DC = %d\n", DC);

		index = 0;
		strcpy(str, line_[i]);

		index = label_position(str, index);
		index = clear_white_space(str, index);

		sscanf(&str[index], "%s", data);

		index = clear_word(str, index);
		index = clear_white_space(str, index);
		if (strcmp(".data", data) == 0)
		{
			while (index >= 0)
			{
				data_table[DC].address   = DC;
				data_table[DC].word.data = atoi(&str[index]);
				index = get_next_comma_pos(str, index);
				DC++;
			}

		}
		else if (strcmp(".string", data) == 0)
		{

			/*check if it's not a empty string*/
			if (is_end_of_line(str[index]))
				return 0;

			if (str[index] == '"') /* data string start with " (qoute char)*/
				index++;

			while (str[index] != '"')
			{
				data_table[DC].address = DC;
				data_table[DC].word.data = str[index];
				DC++;
				index++;
			}
			data_table[DC].address = DC;
			data_table[DC].word.data = '\0';
			DC++;
			;
		}

		
	}

	for (i = 0 ;i < DC; i++)
	{
		printf("the data in place %d = %d \n",i , data_table[i].word.data);
	}

	printf("DC = %d\n",DC);
	DC = 0;

	return 0;
}
void print_sym(pSymbole symbol)
{
	printf("name: %s\ttype: %d,\taddress: %d\tIC:%d	DC:%d\n", symbol->name, symbol->type, symbol->address,IC, DC);
}

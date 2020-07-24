#include <stdio.h>
#include <ctype.h>

#include "parse.h"
#include "Data_structures.h"






void printBinary( unsigned int *pword) {

	
	unsigned int word = *pword;
	int i = 0;
	unsigned int mask = 1;
	
	mask <<= 23;

	for (i = 0; i < 24; i++)
	{
		if (word & mask)
			printf("1");
		else
			printf("0");
		mask >>= 1;
	}
	printf("\n");
}
int main(int argc, char* argv[])
{
	
	char line[80]			= "  LABEL: MOV R2,R2";
	char line_no_label[80]	= "  LABEL MOV R2,R2";
	char line_ins[80]		= "  MOV R2, R2";
	char line_ins_err[80]	= "  LABEL MOV R2,R2";
	st_mem_word word;

	word.E = 0;
	word.R = 0;
	word.A = 1;
	word.funct = 1;
	word.reg_dest = 0;
	word.adrs_dest = 1;
	word.reg_source = 3;
	word.adrs_source = 3;
	word.opcode = 2;

	print_hex(word);
	printf("\n");
	int x = label_position(line,0);
	x = label_position(line_no_label, 0);

	x = check_legal_comma(line_ins, 0);
	x = check_legal_comma(line_ins_err, 0);

	x = 0xffccbbaa;


	return 0;
}
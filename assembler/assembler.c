#include <stdio.h>
#include <ctype.h>

#include "parse.h"

typedef struct mm{
	unsigned int E			: 1;
	unsigned int R			: 1;
	unsigned int A			: 1;
	unsigned int funct		: 5;
	unsigned int reg_dest	: 3;
	unsigned int adrs_dest	: 2;
	unsigned int reg_source	: 3;
	unsigned int adrs_source : 2;
	unsigned int opcode		: 6;

}st_mem_word;

typedef union _memroy {
	int			 data;
	st_mem_word  bit_word;
}memory;


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
	char line[80] = "  LABEL: MOV R2,R2";
	char line_no_label[80] = "  LABEL MOV R2,R2";

	int x = label_position(line,0);
	int y = label_position(line_no_label, 0);

	return 0;
}
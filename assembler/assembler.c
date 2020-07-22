#include <stdio.h>

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

	int x = -9;
	st_mem_word word ;

	word.E			  = 0; 
	word.R			  = 0;
	word.A			  = 1;
	word.funct		  = 1;
	word.reg_dest	  = 0;
	word.adrs_dest	  = 1;
	word.reg_source   = 3;
	word.adrs_source  = 3;
	word.opcode	      = 2;

	printBinary((unsigned*)&word);

	return 0;
}
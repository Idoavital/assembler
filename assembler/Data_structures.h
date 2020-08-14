#ifndef __DATA_STRUCTURES_H__
#define __DATA_STRUCTURES_H__

#include "Defines.h"

/***************************************************************************/
							/* Defines */
/***************************************************************************/
#define JSR_METHOD_TABEL 11
#define DEC_METHOD_TABEL 8


/***************************************************************************/
							/* Enums */
/***************************************************************************/




enum Esymbole_type { ST_EXTERN, ST_ENTRY, ST_DATA, ST_STRING,  ST_CODE }; /* Symbols Types, for symbol table */

/***************************************************************************/
							/* Structures */
/***************************************************************************/

/*Represent the machine binary instruction word code*/
typedef struct st_machine_words {
	unsigned int E			: 1;
	unsigned int R			: 1;
	unsigned int A			: 1;
	unsigned int funct		: 5;
	unsigned int reg_dest	: 3;
	unsigned int adrs_dest	: 2;
	unsigned int reg_source : 3;
	unsigned int adrs_source: 2;
	unsigned int opcode		: 6;

}st_machine_word;

/*Represent the machine binary address code*/
typedef struct st_addresses {
	unsigned int are     : 3;
	unsigned int address : 21;
}st_address;

/*Struct for binary code, can Represent binary address or binary machine instruction code*/
typedef union un_words
{
	st_address       b_address;
	st_machine_word  b_code;
}un_word;

/*Struct for global binary word represent the binary machine code and the address(decimal) of the code*/
typedef struct memory
{
	int     address;
	un_word word;
}st_memory;

/*the address mathod table that contains the legal methods for each command*/
typedef struct address_method_table
{
	char command_name[4];
	int legal_source[NUM_METHOD];
	int legal_target[NUM_METHOD];

}address_method_table;


/* symbole node type for symbol table */
typedef struct _symbol *pSymbole;
typedef struct _symbol {
	char    name[MAX_LABEL_LEN]; 
	int     address;			/* The value of Instruction counter or Data counter*/
	int     type;               /* type can be : CODE ,DATA, STRING, EXTERN   */
	int		isEntry;			/*  if it's entry type */
	pSymbole next;              /* The pointer for link list  */
}symbol ;

/***************************************************************************/
							/* Gloabls */
/***************************************************************************/

/*Reserved words */
extern char* g_keywords[MAX_KEYWORDS];
/*contains the divided line. every row represent a word in the sentence. */
extern char splitLine[MAX_LINE_LEN][MAX_LINE_LEN];
/*The current line number that read in the assembly file (for print error) */
extern int Line_number;
/*The head of symbole table link list */
extern pSymbole pSymbole_Head;
/*The instruction counter*/
extern int IC;
/*The Data counter*/
extern int DC;
/*Flag for error*/
extern int err_num;

/*the address mathod table that contains the legal methods for each command*/
extern address_method_table method_table[16];

/***************************************************************************/
				/*/*Founctoin Declaration*/
/***************************************************************************/

/**
* this function updates data into the address method table.
*/
void initialize_address_mathod_table ();


#endif /* !__DATA_STRUCTURES_H__ */


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

typedef struct _st_mem_word {
	unsigned int E			: 1;
	unsigned int R			: 1;
	unsigned int A			: 1;
	unsigned int funct		: 5;
	unsigned int reg_dest	: 3;
	unsigned int adrs_dest	: 2;
	unsigned int reg_source : 3;
	unsigned int adrs_source: 2;
	unsigned int opcode		: 6;

}st_mem_word;

/*the address mathod table that contains the legal methods for each command*/
typedef struct address_method_table
{
	char command_name[4];
	int legal_source[NUM_METHOD];
	int legal_target[NUM_METHOD];

}address_method_table;

typedef union _memroy {
	int			 data;
	st_mem_word  bit_word;
}memory;


/* symbole node type for symbol table */
typedef struct _symbol *pSymbole;
typedef struct _symbol {
	char    name[MAX_LABEL_LEN]; 
	int     address;			/* The value of Instruction counter or Data counter*/
	int     type;               /* type can be : CODE ,DATA, STRING, EXTERN, ENTRY  */
	pSymbole next;              /* The pointer for link list  */
}symbol ;

/*the address mathod table that contains the legal methods for each command*/
typedef struct address_method_table
{
	char command_name[4];
	int legal_source[NUM_METHOD];
	int legal_target[NUM_METHOD];

}address_method_table;

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


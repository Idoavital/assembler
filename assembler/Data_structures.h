#ifndef __DATA_STRUCTURES_H__
#define __DATA_STRUCTURES_H__

#include "Defines.h"


/***************************************************************************/
							/* Enums */
/***************************************************************************/

enum Esymbole_type { ST_DATA, ST_STRING, ST_EXTERN, ST_ENTRY, ST_CODE }; /* Symbols Types, for symbol table */

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


typedef union _memroy {
	int			 data;
	st_mem_word  bit_word;
}memory;


/* symbole node type for symbol table */
typedef struct _symbol *pSymbole;
typedef struct _symbol {
	char    name[MAX_WORD_LEN]; 
	int     address;			/* The value of Instruction counter or Data counter*/
	int     type;               /* type can be : CODE ,DATA, STRING, EXTERN, ENTRY  */
	pSymbole next;              /* The pointer for link list  */
}symbol ;

/***************************************************************************/
							/* Gloabls */
/***************************************************************************/

/*Reserved words */
extern char* g_keywords[MAX_KEYWORDS];
/*contains the relevant row in the program, so that each cell in the array indicates a word in the line */
extern char* splitLine[MAX_LINE_LEN];
/*The current line number that read in the assembly file (for print error) */
extern int Line_number;
/*The head of symbole table link list */
extern pSymbole pSymbole_Head;
/*The instruction counter*/
extern int IC;
/*The Data counter*/
extern int DC;


/***************************************************************************/
				
/***************************************************************************/

#endif /* !__DATA_STRUCTURES_H__ */


#ifndef __DATA_STRUCTURES_H__
#define __DATA_STRUCTURES_H__

#include "Defines.h"


/***************************************************************************/
							/* Gloabls */
/***************************************************************************/

/*Reserved words */
extern char *g_keywords[MAX_KEYWORDS];
/*/*contains the relevant row in the program, so that each cell in the array indicates a word in the line */
extern char *splitLine [MAX_LINE_LEN];


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
typedef struct symbol {
	char    name[MAX_WORD_LEN];
	int     address;
	int     type;               /* type can be : CODE ,DATA, STRING, EXTERN, ENTRY  */
	pSymbole next;              /* The pointer for link list  */
}symbol, * pSymbole;

#endif /* !__DATA_STRUCTURES_H__ */


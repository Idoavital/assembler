#ifndef __DATA_STRUCTURES_H__
#define __DATA_STRUCTURES_H__

#include "Defines.h"


/***************************************************************************/
							/* Gloabls */
/***************************************************************************/

/*Reserved words */
extern char *g_keywords[MAX_KEYWORDS];

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

#endif /* !__DATA_STRUCTURES_H__ */


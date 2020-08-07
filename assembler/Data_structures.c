#include "Data_structures.h"

/***************************************************************************/
							/* Gloabls */
/***************************************************************************/

/*Reserved words */
char* g_keywords[MAX_KEYWORDS] = { ".extern", ".entry", ".data", ".string", "mov", "cmp", "add", "sub", "lea", "clr", "not",
					"inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop", "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7" };

/*contains the relevant row in the program, so that each cell in the array indicates a word in the line */
char* splitLine [MAX_LINE_LEN];
/*The current line number that read in the assembly file (for print error) */
int Line_number;
/*The instruction counter*/
int IC;
/*The Data counter*/
int DC;
/*The head of symbole table link list */
 pSymbole pSymbole_Head;
/***************************************************************************/
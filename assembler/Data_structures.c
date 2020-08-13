#include <string.h>
#include "Data_structures.h"
#include "Defines.h"


/***************************************************************************/
							/* Gloabls */
/***************************************************************************/

/*Reserved words */
char* g_keywords[MAX_KEYWORDS] = { ".extern", ".entry", ".data", ".string", "mov", "cmp", "add", "sub", "lea", "clr", "not",
					"inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop", "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7" };

/*contains the divided line. every row represent a word in the sentence. */
char splitLine [MAX_LINE_LEN][MAX_LINE_LEN];
/*The current line number that read in the assembly file (for print error) */
int Line_number;
/*The instruction counter*/
int IC;
/*The Data counter*/
int DC;
/*Global error number */
int err_num;
/*The head of symbole table link list */
 pSymbole pSymbole_Head;
 /*the address mathod table that contains the legal methods for each command*/
 address_method_table method_table[16];

/***************************************************************************/


/**
* this function updates data into the address method table.
*/
void initialize_address_mathod_table ()
{
    int i=0;
    int command_name = START_COMMAND_NAME;
    /*copying the name command to the table */
    for (i = 0 ; i < MAX_METHOD_TABLE; i++)
    {
       strcpy(method_table[i].command_name , g_keywords[command_name++] );
    }

    /*initialize source and target method for each commands, -1,-1,-1 mean that there isnt any legal target/source method*/ 
    for ( i = 0; i < MAX_METHOD_TABLE; i++)
    {
        method_table[i].legal_source[0] =-1;
        method_table[i].legal_source[1] =-1;
        method_table[i].legal_source[2] =-1;

        method_table[i].legal_target[0]=-1;
        method_table[i].legal_target[1]=-1;
        method_table[i].legal_target[2]=-1;
    }
    
    /*initialize source method for commands: mov, cmp, add, sub */
    for ( i = 0; i < 4; i++)
    {
       method_table[i].legal_source[0] =METHOD_ADDRESS0;
       method_table[i].legal_source[1] =METHOD_ADDRESS1;
       method_table[i].legal_source[2] =METHOD_ADDRESS3;   
    }

    /*initialize source method for command: lea*/
    method_table[4].legal_source[0]=METHOD_ADDRESS1;

    /*initialize target method for commands: mov, cmp, add, sub, lea, clr, not, inc, dec,red, prn*/
    for ( i = 0; i < 14; i++)
    {
        method_table[i].legal_target[0]=METHOD_ADDRESS1;
        method_table[i].legal_target[1]=METHOD_ADDRESS3;
        i = (i == DEC_METHOD_TABEL ? JSR_METHOD_TABEL : i); /*here we jump to commands red and prn*/
    }
    /*initialize target method for command: cmp*/
    method_table[1].legal_target[2]=METHOD_ADDRESS0;
    
    /*initialize target method for commands: jmp, bne, jsr*/
    for ( i = 9; i < 12; i++)
    {
        method_table[i].legal_target[0]=METHOD_ADDRESS1;
        method_table[i].legal_target[1]=METHOD_ADDRESS2;
    }

    /*initialize target method for command: prn*/
    method_table[13].legal_target[2]=METHOD_ADDRESS0;
      
}

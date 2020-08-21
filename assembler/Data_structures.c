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
/*The current file name*/
char  file_name[MAX_FILE_NAME];
/*The instruction counter*/
int IC;
/*The Data counter*/
int DC;
/*the extern label counter*/
int index_extern;
/*Global error number */
int err_num;
/*The head of symbole table link list */
 pSymbole pSymbole_Head;
 /*the address mathod table that contains the legal methods for each command*/
 address_method_table method_table[MAX_METHOD_TABLE];
 /*The Table code list of binary instructions code*/
 st_memory code_table[MAX_TABLE_SIZE];
 /*The Table data list of binary data code*/
 st_memory data_table[MAX_TABLE_SIZE];
 /*the opcode-funct table */
 opcode_table opcode_funct_table [MAX_COMMAND];
/*an array that contains all the extern labels*/
extern_table extern_label [MAX_TABLE_SIZE];
/***************************************************************************/


/**
* this function updates data into the address method table.
*/
void initialize_address_mathod_table ()
{
    int i            = 0;
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

        method_table[i].legal_target[0] =-1;
        method_table[i].legal_target[1] =-1;
        method_table[i].legal_target[2] =-1;
    }
    
    /*initialize source method for commands: mov, cmp, add, sub */
    for ( i = MOV; i < LEA; i++)
    {
       method_table[i].legal_source[0] =METHOD_ADDRESS0;
       method_table[i].legal_source[1] =METHOD_ADDRESS1;
       method_table[i].legal_source[2] =METHOD_ADDRESS3;   
    }

    /*initialize source method for command: lea*/
    method_table[LEA].legal_source[0]=METHOD_ADDRESS1;

    /*initialize target method for commands: mov, cmp, add, sub, lea, clr, not, inc, dec,red, prn*/
    for ( i = MOV; i < RTS; i++)
    {
        method_table[i].legal_target[0]=METHOD_ADDRESS1;
        method_table[i].legal_target[1]=METHOD_ADDRESS3;
        i = (i == DEC ? JSR : i); /*here we jump to commands red and prn*/
    }
    /*initialize target method for command: cmp*/
    method_table[CMP].legal_target[2]=METHOD_ADDRESS0;
    
    /*initialize target method for commands: jmp, bne, jsr*/
    for ( i = 9; i < 12; i++)
    {
        method_table[i].legal_target[0]=METHOD_ADDRESS1;
        method_table[i].legal_target[1]=METHOD_ADDRESS2;
    }

    /*initialize target method for command: prn*/
    method_table[PRN].legal_target[2]=METHOD_ADDRESS0;
      
}


/**
* this function updates data into the opcode-funct table. 
*/
void initialize_opcode_funct_table ()
{
    int i=0;
    int command_name = START_COMMAND_NAME;
    /*copying the name command to the table */
    for (i = 0 ; i < MAX_COMMAND; i++)
    {
       strcpy(opcode_funct_table[i].command_name , g_keywords[command_name++] );
    }

    /*initialize opcode for command: mov,cmp*/
    for ( i = MOV; i < ADD; i++)
    {
        opcode_funct_table[i].opcode = i;
    }
    
    /*initialize opcode for commands: add,sub*/
    for ( i = ADD; i < LEA; i++)
    {
       opcode_funct_table[i].opcode = 2;
    }
    /*initialize opcode for command: lea */
    opcode_funct_table[LEA].opcode = 4;
    /*initialize opcode for commands: clr, not, inc, dec  */
    for ( i = CLR; i < JMP; i++)
    {
        opcode_funct_table[i].opcode = 5;
    }
    /*initialize opcode for commands: jmp, bne, jsr*/
    for ( i = JMP; i < RED; i++)
    {
        opcode_funct_table[i].opcode = 9;
    }
    /*initialize opcode for command: red,prn,rts,stop*/
    for ( i = RED; i < MAX_COMMAND; i++)
    {
        opcode_funct_table[i].opcode = i;
    }
    /*initialize funct for commands: add, clr, jmp */
    for ( i = ADD; i < BNE; i++)
    {
        opcode_funct_table[i].funct = 1;
        i = i == ADD? LEA: i; /*here we jump to clr*/
        i = i == CLR? DEC: i; /*here we jump to jmp*/
    }
    /*initialize funct for commands: sub,not,bne */
    for ( i = SUB; i < JSR; i++)
    {
        opcode_funct_table[i].funct = 2;
        i = i == SUB? CLR: i; /*here we jump to not*/
        i = i == NOT? JMP: i; /*here we jump to bne*/
    }
    /*initialize funct for commands: inc,jsr */
    for ( i = INC; i < RED; i++)
    {
        opcode_funct_table[i].funct = 3;
        i = i == INC? BNE: i; /*here we jump to jsr*/
    }
    /*initialize funct for command: dec*/
    opcode_funct_table[DEC].funct = 4;
    
}

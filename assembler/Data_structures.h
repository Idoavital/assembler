#ifndef __DATA_STRUCTURES_H__
#define __DATA_STRUCTURES_H__

#include "Defines.h"

/***************************************************************************/
							/* Defines */
/***************************************************************************/


/***************************************************************************/
							/* Enums */
/***************************************************************************/


enum commands {MOV = 0,CMP ,ADD ,SUB ,LEA ,CLR ,NOT ,INC ,DEC ,JMP ,BNE ,JSR ,RED ,PRN ,RTS ,STOP };

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
	unsigned int E       : 1;
	unsigned int R       : 1;
	unsigned int A       : 1;
	unsigned int address : 21;
	
}st_address;

/*Struct for binary code, can Represent binary address or binary machine instruction code*/
typedef union un_words
{
	int				 data;
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
	int  legal_source[NUM_METHOD];
	int  legal_target[NUM_METHOD];

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


typedef struct opcode_table
{
    char command_name [5];
    int  opcode;
    int  funct;

}opcode_table;

typedef struct extern_table
{
	char name[MAX_LABEL_LEN];
	int  addrerss;
}extern_table;


/***************************************************************************/
							/* Gloabls */
/***************************************************************************/

/*Reserved words */
extern char* g_keywords[MAX_KEYWORDS];
/*contains the divided line. every row represent a word in the sentence. */
extern char splitLine[MAX_LINE_LEN][MAX_LINE_LEN];
/*The current line number that read in the assembly file (for print error) */
extern int Line_number;
/*The current file name*/
extern char  file_name[MAX_FILE_NAME];
/*The head of symbole table link list */
extern pSymbole pSymbole_Head;
/*The instruction counter*/
extern int IC;
/*The Data counter*/
extern int DC;
/*the extern label counter*/
extern int index_extern;
/*Flag for error*/
extern int err_num;
/*the address mathod table that contains the legal methods for each command*/
extern address_method_table method_table[MAX_METHOD_TABLE];
/*The Table code list of binary instructions code*/
extern st_memory code_table[MAX_TABLE_SIZE];
/*The Table data list of binary data code*/
extern st_memory data_table[MAX_TABLE_SIZE];
/*the opcode-funct table */
extern opcode_table opcode_funct_table [MAX_COMMAND];
/*an array that contains all the extern labels*/
extern extern_table extern_label [MAX_TABLE_SIZE];

/***************************************************************************/
				/*/*Founctoin Declaration*/
/***************************************************************************/

/**
* this function updates data into the address method table.
*/
void initialize_address_mathod_table ();
/**
* this function updates data into the opcode-funct table. 
*/
void initialize_opcode_funct_table ();


#endif /* !__DATA_STRUCTURES_H__ */


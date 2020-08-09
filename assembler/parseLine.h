#ifndef __PARSE_LINE_H__
#define __PARSE_LINE_H__



/***************************************************************************/
					/*Founctoin Declaration*/
/***************************************************************************/




/**
* This function check if the next word is a label.
* @param str	- a pointer to beginnig of the line.
* @param index	- the position of the line.
* @return true if the next word is label .
*/
int is_label_definition(char* label , int index);


/**
* This function check if the next word is lagal label name.
* @param str	- a pointer to beginnig of the line.
* @param index	- the position of the line.
* @return true if the word is leagal label.
*/
int is_legal_label_definition(char* label, int index);


/**
* this function checks if the label is valid.
* @param label	- a pointer to the row that contains the label.
* @param index -  the position of the label.
* @return - the function returns true if the label is valid, otherwise returns false.
*/
int is_label_valid(char* label, int index);


/**
* This function check if a word is keyword(reserved word)
* @param str	- a pointer to beginnig of the line.
* @param index	- the position of the line.
* @param flag	- If to check all Keyword or only instructions/data.
* @return the index of the command in the array g_keywords, otherwise if there wasnt a match returns false.
*/
int is_keyword(char *str, int index, int flag);


/**
* this function checks if the operator is a number in this tamplate #num
* @param op	- points to the operator that is tested as a number
* @param index	- the position of the operator
* @return the function returns the number of the method address of a number operator, if the operator is a number
          otherwise returns NO_NUM.
*/
int is_number (char* op, int index);


/**
* this function checks if the operator is a register 
* @param op - points to the operator that is tested as register
* @param index	- the position of the operator
* @return the function returns the number of the method address of a register operator, if the operator is a register
          otherwise returns false.
*/
int is_register (char* op, int index);


/**
* this function checks if the command line have unnecessary text.
* @param line	- end of of the line 
* @param index	- the position of the end of the line 
* @return the function returns FALSE if there isnt extra text otherwise returns TRUE.
*/
int is_there_extra_text (char* line, int index);


/**
* this function checks if the address method specified by the operator type is valid for the this command.
* @param label	- points to the operator that is tested as a label in template &label 
* @param index	-  the position of the operator
* @return the function returns the number of the method address of a &label operator, if the operator is a &label
          otherwise returns false.
*/
int is_address_method_for_jump_command (char* label, int index);

/**
* this function checks if the address method specified by the operator type is valid for the this command.
* @param command_name	- the name of the command
* @param index -  the position of the command name
* @param method_adress	- the method adress this operator needs
* @param source_or_target - this indicates for us if the operator is a target or a source and according to that info we will check the method.
* @return the function returns ok if the address method is legal, otherwise it will return that there isn't a match. 
*/
int match_address_method (char* command_name, int address_method, int source_or_target );








#endif /* !__PARSE_LINE_H__ */
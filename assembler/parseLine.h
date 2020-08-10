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
* this function checks if the operator is a number in this tamplate #num if the flag is ins_number. if the flag is 
* data_number it will just check if the number is an intger type.
* @param opertaor	- points to the operator that is tested as a number
* @param index	- the position of the operator
* @param flag - indicate if the check is for a number in an instruction command or a data command.
* @return the function returns the number of the method address of a number operator, if the operator is a number
          otherwise returns NO_NUM. 
*/
int is_number (char* op, int index, int flag);


/**
* this function checks if the operator is a valid number. 
* @param op	- points to the operator that is tested as a number
* @param index	- the position of the operator
* @return the function returns the number of the method address of a number operator, if the operator is a number
          otherwise returns NO_NUM. 
*/
int is_legal_number(char* op, int index);



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
int match_address_method (char* command_name,int index, int address_method, int source_or_target );


/**
* this function activate the function match address method table, to check if the address method is legal for the particular command. 
* @param line	- points to command name.
* @param index	- the position of the command name.
* @param address_method - the number that represnts the address method.
* @param flag_source_target - the flag indicates if the operator is a soutce or a target.
* @return the function returns OK if the address method is legal for the particular operator, otherwise return that no match was found.
*/
int active_search_address_method_table (char* line,int index, int address_method, int flag_source_target);


/**
* this function sees if the operator ia a register/number/adress_label. and then checks if the address method that this operator needs
 is legal for the particular command. 
* @param line	- matrix that contains the sentence in a way that in every row there is a word.
* @param indexR	- the index of the row of the matrix that contain the command name.
* @param indexC- the position of the relevant word.
* @param index_op - the index of the row of the matrix that contain the operator.
* @param flag_source_target -  indicates if the operator is a source or a target.
* @return the function returns a sign that indicates which type the operator is if the test was found successful, otherwise returns error.
*/
int which_operator_and_if_legal (char line[MAX_LINE_LEN][MAX_LINE_LEN], int indexR, int indexC, int index_op, int flag_source_target);


/**
* this function checks which operator was sent to her, and if the operator isnt a register it will send +1, its means to add more memory word.
* @param op	- type of the operator (register/label/adress_label/number)
* @return the function returns 1 if there needed to add more memory word based on the operator, otherwise the function returns 0.
*/
int is_more_memory_needed (int op);


/**
* this function checks if there is an operator that is missing.
* @param op	- a pointer to the row that contains the operator.
* @return the function returns ERROR if there is a missing operator, otherwise returns OK.
*/
int is_operator_missing (char* op, int index);


/**
* this function checks a command that receive 2 operators.
* @param line	- a matrix that contains the split sentence, in a way that in every row there is a word.
* @param indexR - index of a row that contains the command name.
* @param indexC - the position of the command name.
* @return the function returns the specific ERROR if there was any error, otherwise it will return the amount of memory that the command need.
*/
int template2 (char line[MAX_LINE_LEN][MAX_LINE_LEN], int indexR, int indexC);


/**
* this function checks a command that receive 1 operator.
* @param line	- a matrix that contains the split sentence, in a way that in every row there is a word.
* @param indexR - index of a row that contains the command name.
* @param indexC - the position of the command name.
* @return the function returns the specific ERROR if there was any error, otherwise it will return the amount of memory that the command need.
*/
int template1 (char line[MAX_LINE_LEN][MAX_LINE_LEN], int indexR ,int indexC);

/**
* this function checks a command that doesnt have any operators.
* @param line	- a matrix that contains the split sentence, in a way that in every row there is a word.
* @param indexR - index of a row that contains the command name.
* @param indexC - the position of the command name.
* @return the function returns the specific ERROR if there was any error, otherwise it will return the amount of memory that the command need.
*/
int template0 (char line[MAX_LINE_LEN][MAX_LINE_LEN], int indexR, int indexC);


#endif /* !__PARSE_LINE_H__ */
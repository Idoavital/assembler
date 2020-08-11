#include <stdio.h>
#include <string.h>
#include <ctype.h>  /* is_number */
#include <stdlib.h> /*extra_text*/

#include "Defines.h"
#include "Data_structures.h"
#include "Error.h"
#include "parseLine.h"



int is_label_definition(char* label , int index) /*here we check if this is a label that we want to define */
{
    char label_name[MAX_LABEL_LEN];
    int  endIndex = 0;
    sscanf(&label[index], "%s", label_name);
	endIndex = strlen(label_name);

	return (':' == (label_name[endIndex -1]));
}


int is_legal_label_definition(char* label, int index)  /*we check if the definition label is valid.*/
{
    int  endIndex,i = 0;
	int label_flag = FALSE;
    endIndex = strlen(&label[index]);

	if (is_label_definition(label, index)  && ':' != (label[endIndex-2]))
	{

        if (isdigit(label[index]) || is_keyword( label ,index, CHECK_LABLE) || (strlen(label) > MAX_LABEL_LEN))
        {
            return FALSE;
        }

        for ( i = 0; label[i] != ':'; i++)
        {
            if (isdigit(label[i]) == 0 && isalpha(label[i]) == 0 )
            return FALSE;
        }

        label_flag = TRUE;
		
    }

	if (label_flag == TRUE)
		return TRUE;

	return label_flag;
}


int is_label_valid(char* label, int index)
{
    int i;

    /* Check if the name start with a number, or the label is a keyword (reserved word), and if the label is more then 31 characters*/
    if (isdigit(label[index]) || is_keyword( label ,index, CHECK_LABLE) || (strlen(label) > MAX_LABEL_LEN))
    {
       return FALSE;
    }

    for ( i = index; label[i] != '\0'; i++)
    {
        if (isdigit(label[i]) == 0 && isalpha(label[i]) == 0 )
        return FALSE;
    }
    
    return TRUE;
}



/*function that checks if the label or the command name is legal, that depends on the flag info.*/
int is_keyword(char* str, int index, int flag)
{
	int max,i = 0;
    char temp_str[MAX_LABEL_LEN];
	int temp_index = 0;
    sscanf(str,"%s",temp_str);

    max = (flag == CHECK_COMMAND_NAME) ? MAX_COMMAND_NAME: MAX_KEYWORDS;

    if (flag == CHECK_LABLE) /*in order to compare between a keyword and the label, we need to remove the ':'*/
    {
        while (temp_str[temp_index] != ':')
            temp_index++;
        
        temp_str[temp_index] = '\0';      
    }
    
	for (i = 0; i < max; i++)
	{
		if (!strcmp(&temp_str[index], g_keywords[i]))
		{
			return i;
		}
	}

	return FALSE;
}



int is_number (char* op, int index, int flag)
{
    if (flag == INS_NUMBER)
    {
        if (op[index] == '#')
        {
            index++;
            if (is_legal_number(op,index) == METHOD_ADDRESS0)
                return METHOD_ADDRESS0;
            else
                return NOT_NUM; 
        }
        
    }
    else
    {
        if (is_legal_number(op,index) == METHOD_ADDRESS0)
            return METHOD_ADDRESS0;
        else
            return NOT_NUM;   
    }
    
}


int is_legal_number(char* op, int index) 
{
    int i;
    int temp_digit;
    char temp_str[1];
    int flag_after_dot = FALSE;
    int flag_num = TRUE;

       for ( i = index ; op[i] != '\0'; i++)
        {
            if (flag_after_dot == TRUE)
            {
                if (op[i] != '0')
                {   
                    flag_num = FALSE;
                    break;
                }
            
            }
            else if (op[i] == '.')
            {
                flag_after_dot = TRUE;
            }
            else
            {
                temp_str[0] = op[i];
                temp_digit = atoi(temp_str);
                if (strcmp(&temp_str[0],"0") != 0  && temp_digit == 0)
                {
                    flag_num = FALSE;
                    break;
                } 
            } 
        } 

    if (flag_num == FALSE)
    {
       return NOT_NUM;
    }
     
    return METHOD_ADDRESS0;

}


int is_register (char* op, int index)
{
    int i;
    for ( i = START_REGISTER; i < MAX_KEYWORDS; i++)
    {
        if (!strcmp(&op[index], g_keywords[i]))
		{
			return METHOD_ADDRESS3;
		}
    }

    return FALSE;
}


int is_there_extra_text (char* line, int index)
{
    if (line[index] == '\0')
    {
        return FALSE; 
    }
    
    return TRUE;
}

int is_address_method_for_jump_command (char* label, int index)
{
    if(label[index] == '&' && is_label_valid(label,index+1))
    return METHOD_ADDRESS2;

    else
    return FALSE;
}



int match_address_method (char* command_name,int index, int address_method, int source_or_target )
{
    int i,j;
    for ( i = 0; i < MAX_METHOD_TABLE; i++)
    {
        if (!strcmp(command_name, method_table[i].command_name))
        {
            if (source_or_target == SOURCE)
            {
                for ( j = 0; j < NUM_METHOD; j++)
                {
                    if (address_method == method_table[i].legal_source[j])
                    {
                        return OK;
                    }
                }
                
            }

            else
            {
                for ( j = 0; j < NUM_METHOD; j++)
                {
                    if (address_method == method_table[i].legal_target[j])
                    {
                        return OK;
                    }
                    
                }
                
            }

            return ERR_NO_MATCH; /*after we have found the correct command name and checked for a match between the methods. we can stop the search. */
            
        }
        
        
    }
    return OK;
}

int active_search_address_method_table (char* line,int index, int address_method, int flag_source_target)
{
    int flag;
    flag = flag_source_target == SOURCE ? SOURCE : TARGET;

    if(match_address_method(line ,index, address_method, flag) == OK) /*checks if the command can accept the address method that the opertaor needs */
    {
        return OK; 
    }
    else
    {
        return ERR_NO_MATCH;     
    }
  
}



int which_operator_and_if_legal (char line[MAX_LINE_LEN][MAX_LINE_LEN], int indexR, int indexC, int index_op, int flag_source_target)
{
    int op = 0;
    int flag = flag_source_target == SOURCE? SOURCE: TARGET;

    if ((op = is_register(line[index_op],indexC)))
    {
        if (active_search_address_method_table(line[indexR], indexC, op, flag) == OK)
        {
           return REGISTER;
        } 
        else
        {
            return ERR_REGISTER(flag);
        }
        
    }
    else if ( (op = is_number(line[index_op],indexC, INS_NUMBER)) != NOT_NUM )
    {
        if (active_search_address_method_table(line[indexR], indexC, op, flag) == OK)
        {
            return NUMBER;
        }
        else
        {
            return ERR_NUMBER(flag);
        }
    }
    else if ((op = is_address_method_for_jump_command(line[index_op], indexC)))
    {
        if (active_search_address_method_table(line[indexR], indexC, op, flag) == OK)
        {
            return ADDRESS_LABEL;
        }
        else
        {
            return ERR_ADDRESS_LABEL(flag);
        }
            
    }
    else if ((op = is_label_valid(line[index_op],indexC)))
    {
        if (active_search_address_method_table(line[indexR], indexC, op, flag) == OK)
        {
            return LABEL;
        }
        else
        {
            return ERR_LABEL(flag);
        }
        
    }
    else
    {
        return ERR_OPERATOR_UNDEFINED(flag);
    }   

}


int is_more_memory_needed (int op)
{
    int count = 0;

    if (op == NUMBER || op == ADDRESS_LABEL || op == LABEL)
    {
        count++;
    }
    
    return count;
}

int is_operator_missing (char* op, int index)
{
    if (op[index] == '\0')
    {
        return ERR_MISSING_OPERATOR;
    }

    return OK;  
}



int template2 (char line[MAX_LINE_LEN][MAX_LINE_LEN], int indexR, int indexC)
{
    int op = 0;
    int amount_memory = 1; /*at least one word of memory must be assigned to a line in the program*/
    int index_op1 = indexR+1;/*indexR points to the row that contains the command name, so if we move +1 we will point to the first operator.*/
    int index_op2 = indexR+2;/*like the explanation from above, but here if we move +2 we will point to the second operator.*/
    int index_exstra_text = indexR+3; /*in this row there should be no text, that mean that in this point the command need to end*/
    
    if (is_there_extra_text(line[index_exstra_text],indexC))
    {
        return ERR_EXTRA_TEXT;
    }

    if (is_operator_missing(line[index_op1],indexC) == ERR_MISSING_OPERATOR)
    {
        return ERR_MISSING_SOURCE;
    }

    if (is_operator_missing(line[index_op2],indexC) == ERR_MISSING_OPERATOR)
    {
        return ERR_MISSING_TARGET;
    }
    
    if( (op = which_operator_and_if_legal(line,indexR,indexC,index_op1,SOURCE) ) > 0) /*If the result is positive the check was successful*/
    {
        amount_memory += is_more_memory_needed(op);
    }
    else
    {
        return op; /*op represents the type of the error*/
    }
    if ( (op = which_operator_and_if_legal(line,indexR,indexC,index_op2,TARGET) ) > 0)
    {
        amount_memory += is_more_memory_needed(op);
    }
    else
    {
        return op;
    }
    
    return amount_memory;
  
}


int template1 (char line[MAX_LINE_LEN][MAX_LINE_LEN], int indexR ,int indexC)
{
    int op = 0;
    int amount_memory = 1;/*at least one word of memory must be assigned to a line in the program*/
    int index_op1 = indexR+1;/*indexR points to the row that contains the command name, so if we move +1 we will point to the first operator.*/
    int index_exstra_text = indexR+2;/*in this row there should be no text, that mean that in this point the command need to end*/

    if (is_there_extra_text(line[index_exstra_text],indexC))
    {
        return ERR_EXTRA_TEXT;
    }

    if (is_operator_missing(line[index_op1],indexC) == ERR_MISSING_OPERATOR)
    {
        return ERR_MISSING_TARGET; /*when the command have one operator we will see the operator as a target.*/
    }
    

    if( (op = which_operator_and_if_legal(line,indexR,indexC,index_op1,TARGET) ) > 0) /*If the result is positive the check was successful*/
    {
        amount_memory += is_more_memory_needed(op);
    }
    else
    {
        return op; /*op represents the type of the error*/
    }

      return amount_memory;    
}

int template0 (char line[MAX_LINE_LEN][MAX_LINE_LEN], int indexR, int indexC)
{
    int  amount_memory = 1;/*at least one word of memory must be assigned to a line in the program*/
    int index_exstra_text = indexR+1;/*in this row there should be no text, that mean that in this point the command need to end*/
    
    if (is_there_extra_text(line[index_exstra_text],indexC))
    {
        return ERR_EXTRA_TEXT;
    }

    return amount_memory;
}


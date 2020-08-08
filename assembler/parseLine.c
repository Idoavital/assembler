#include <stdio.h>
#include <string.h>
#include <ctype.h>  /* is_number */
#include <stdlib.h> /*extra_text*/

#include "Defines.h"
#include "Data_structures.h"
#include "Error.h"




int is_label(char* label , int index)
{
	int  endIndex = 0;
	endIndex = strlen(&label[index]);

	return (':' == (label[endIndex -1]));
}


int is_legal_label_definition(char* label, int index)  /*we check if the definition label is valid.*/
{
    int  endIndex,i = 0;
	endIndex = strlen(&label[index]);
	int label_flag = FALSE;

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




int is_number (char* op, int index)
{
    double number = 0;
    int num = 0;
    int check = 0; 
    int length = 0; /*the length of the string before converting to a number */
    int count = 0; /*the number of digits of the number, this will need to be equal to 'length'*/
    if (op[index] == '#')
    {
       index++;
       number = atof(&op[index]);
       check = (int)number; /*convert to int, and then check if the original number is equal to the convert number */
       length = strlen(&op[index]);
       num = number;
       while(num)
       {
           count++;
           num/=10;
       }
       if( isdigit(number) == 0 && check == number && length == count) /*we check that the operator is an integer number*/
       return METHOD_ADDRESS0;
    }

    return NOT_NUM;
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
    if(label[index] == '&')
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
    
}










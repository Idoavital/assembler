#ifndef __DEFINES_H__
#define __DEFINES_H__

#define OK 100
#define FALSE 0
#define TRUE  1

#define START_LINE	  0
#define MAX_LABEL_LEN 31
#define MAX_LINE_LEN 81
#define MAX_FILE_NAME 100

#define COMMA ','

#define ON	1
#define OFF 0

#define MAX_LABEL_TYPE 4
#define MAX_KEYWORDS  28  
#define MAX_COMMAND_NAME 20
#define MAX_METHOD_TABLE 16
#define START_COMMAND_NAME 4 

#define CHECK_LABLE -3
#define CHECK_COMMAND_NAME -4 


#define NUM_METHOD 3
#define METHOD_ADDRESS0 0
#define METHOD_ADDRESS1 1
#define METHOD_ADDRESS2 2
#define METHOD_ADDRESS3 3

#define START_REGISTER 21
#define SOURCE 1
#define TARGET 2
#define NOT_NUM 1

#define REACH_END_LINE	-1

#define REGISTER 1
#define NUMBER 2
#define ADDRESS_LABEL 3
#define LABEL 4
#define STRING 4 /*string is in index 4 in g_keybords*/
#define NOT_STRING 5 

#define INS_NUMBER 5/*ins: instruction*/
#define DATA_NUMBER 6

#define IC_BEGIN 100
#define DC_BEGIN 0


#define __IN
#define __OUT

#define NO_SYMBOL  -1

#define MAX_TABLE_SIZE 300
#endif /* !__DEFINES_H__*/


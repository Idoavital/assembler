#include <stdio.h>
#include <string.h>

#include "parse.h"
#include "Data_structures.h"
#include "FirstPass.h"


extern int Test();

int main(int argc, char* argv[])
{
	/*TODO: only for debug - delete leater*/
#define _DEBUG
#ifdef _DEBUG

	Test(); /*debug*/

#else
	
	char  file_name[MAX_FILE_NAME];
	FILE* pFile;
	int   i = 1;  

	for (i =1 ; i < argc; i++) /* Scanning argv from the second argument, the first file name to be checked */
	{

		strcpy(file_name, argv[i]);
		strcat(file_name, ".as");

		/* Opens the file, if it exists, for reading */
		pFile = fopen(file_name, "r");
		if (!pFile) /* If the file wasn't found, or it isn't allowed for reading, the file pointer is NULL */
		{
			printf( "Couldn't open file %s\n", file_name);
			continue;
		}

		firstPass(pFile);
		 /*second_pass*/
		fclose(pFile); /* closes the file */
	}

#endif /* DEBUG*/

	return 0;
}
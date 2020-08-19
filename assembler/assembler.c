#include <stdio.h>
#include <string.h>


#include "syntaxLine.h"
#include "Data_structures.h"
#include "FirstPass.h"
#include "SecondPass.h"


extern int Test();
extern void print_sym(pSymbole symbol);

int main(int argc, char* argv[])
{
	/*TODO: only for debug - delete leater*/
/*#define _DEBUG*/
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

		if (firstPass(pFile) != NO_ERROR) /*if there is error in first pass no need to pass to second pass*/
		{

			clean(pFile); /* closes the file */
			continue;
		}
		fseek(pFile,0,SEEK_SET);
			
		/*DEBUG*/
		{
			pSymbole symbol = pSymbole_Head;
			symbol = pSymbole_Head;
			printf("\n");
			while (symbol)
			{

				print_sym(symbol);
				symbol = symbol->next;

			}
		}
		/*END DEBUG*/
		if (SecondPass(pFile) != NO_ERROR) /*if there is error in second pass no need to print assembly files*/
		{
			clean(pFile); /* closes the file */
			continue;
		}

		if (write_files(argv[i]) != NO_ERROR)
		{
			clean(pFile); /* closes the file */
			continue;
		}

		/*Clean list and structures and set them to next file */
		clean(pFile);
	}

#endif /* DEBUG*/

	return 0;
}

#include <stdio.h>
#include <string.h>

#include "parse.h"
#include "Data_structures.h"
#include "FirstPass.h"
#include "SecondPass.h"


extern int Test();
extern int test_read_code();

int main(int argc, char* argv[])
{
	/*TODO: only for debug - delete leater*/
/*#define _DEBUG*/
#ifdef _DEBUG

	test_read_code();
	/* Test(); debug */

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

			fclose(pFile); /* closes the file */
			continue;
		}
			

		if (SecondPass(pFile) != NO_ERROR) /*if there is error in second pass no need to print assembly files*/
		{
			fclose(pFile); /* closes the file */
			continue;
		}

		if (write_files(argv[i]) != NO_ERROR)
		{
			fclose(pFile); /* closes the file */
			continue;
		}
		/*TODO: print files*/
		/*Clean list and structures and set them to next file */
		/* closes the file */
	}

#endif /* DEBUG*/

	return 0;
}
#include <string.h>
#include <stdlib.h>

#include "FirstPass.h"
#include "Defines.h"
#include "Error.h"

int firstPass(FILE* pfile)
{
	char line[MAX_LINE_LEN];
	int line_num = 0;

	for (line_num = 1; fgets(line, MAX_LINE_LEN, pfile); line_num++) /* Scanning through each line of the file */
	{
		/*TODO: check comma error in line*/
		/*TODO: check line error*/
		/*TODO: count ic and dc */
		/*TODO: add to symbloe table*/

	}
	return 0;
}

pSymbole create_symbole(char* pName, int address, int type)
{
	pSymbole psym = malloc(sizeof(*psym));

	if (psym == NULL)
	{
		printf(P_ERROR"\n"); /*TODO: FINISH PRINT ERR*/
	}
	strcpy(psym->name, pName);
	psym->address = address;
	psym->type = type;

	return psym;
}




#include "FirstPass.h"
#include "Defines.h"

int firstPass(FILE* pfile)
{
	char line[MAX_LINE_LEN];
	int line_num = 0;

	for (line_num = 1; fgets(line, MAX_LINE_LEN, pfile); line_num++) /* Scanning through each line of the file */
	{
		/*TODO: check comma error*/
		/*TODO: check line error*/
		/*TODO: count ic and dc */
		/*TODO: add to symbloe table*/

	}
	return 0;
}

assembler: assembler.o syntaxLine.o Error.o Data_structures.o FirstPass.o parseLine.o SecondPass.o 
	gcc -g -ansi -Wall -pedantic -std=c90 assembler.o syntaxLine.o Error.o Data_structures.o FirstPass.o parseLine.o SecondPass.o -o assembler 

assembler.o: assembler.c FirstPass.h Data_structures.h syntaxLine.h
	gcc -c -g -ansi -Wall -pedantic -std=c90 assembler.c -o assembler.o

syntaxLine.o: syntaxLine.c syntaxLine.h
	gcc -c -g -ansi -Wall -pedantic -std=c90 syntaxLine.c -o syntaxLine.o

parseLine.o: parseLine.c parseLine.h
	gcc -c -g -ansi -Wall -pedantic -std=c90  parseLine.c -o parseLine.o

FirstPass.o: FirstPass.c FirstPass.h
	gcc -c -g -ansi -Wall -pedantic -std=c90 FirstPass.c -o FirstPass.o

SecondPass.o: SecondPass.c SecondPass.h syntaxLine.h Data_structures.h FirstPass.h Error.h  parseLine.h
	gcc -c -g -ansi -Wall -pedantic -std=c90  SecondPass.c -o SecondPass.o

Error.o: Error.c Error.h Data_structures.h 
	gcc -c -g -ansi -Wall -pedantic -std=c90 Error.c -o Error.o

Data_structures.o: Data_structures.c Data_structures.h Defines.h
	gcc -c -g -ansi -Wall -pedantic -std=c90 Data_structures.c -o Data_structures.o

OBJ = assembler.o syntaxLine.o Error.o Data_structures.o FirstPass.o parseLine.o SecondPass.o syntaxLine.o
clean:
	rm -f $(OBJ)  assembler
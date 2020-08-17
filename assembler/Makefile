assembler: assembler.o parse.o Error.o Data_structures.o FirstPass.o parseLine.o SecondPass.o Test.o
	gcc -g -ansi -Wall -pedantic -std=c90 assembler.o parse.o Error.o Data_structures.o FirstPass.o parseLine.o SecondPass.o Test.o -o assembler 

assembler.o: assembler.c FirstPass.h Data_structures.h parse.h
	gcc -c -g -ansi -Wall -pedantic -std=c90 assembler.c -o assembler.o

parse.o: parse.c parse.h
	gcc -c -g -ansi -Wall -pedantic -std=c90 parse.c -o parse.o

parseLine.o: parseLine.c parseLine.h
	gcc -c -g -ansi -Wall -pedantic -std=c90  parseLine.c -o parseLine.o

FirstPass.o: FirstPass.c FirstPass.h
	gcc -c -g -ansi -Wall -pedantic -std=c90 FirstPass.c -o FirstPass.o

SecondPass.o: SecondPass.c SecondPass.h parse.h Data_structures.h FirstPass.h Error.h  parseLine.h
	gcc -c -g -ansi -Wall -pedantic -std=c90  SecondPass.c -o SecondPass.o

Error.o: Error.c Error.h Data_structures.h
	gcc -c -g -ansi -Wall -pedantic -std=c90 Error.c -o Error.o

Data_structures.o: Data_structures.c Data_structures.h Defines.h
	gcc -c -g -ansi -Wall -pedantic -std=c90 Data_structures.c -o Data_structures.o

Test.o: Test.c 
	gcc -c -g -ansi -Wall -pedantic -std=c90 Test.c  -o Test.o

OBJ = assembler.o parse.o Error.o Data_structures.o FirstPass.o parseLine.o SecondPass.o Test.o
clean:
	rm -f $(OBJ)  assembler
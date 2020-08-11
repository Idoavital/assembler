

TARGET  = assembler
CC      = gcc
CFALG   = -g -Wall -ansi -pedantic -std=c90 
LDFLAG  = -lm
INCLUDE = -I.

DEPS    = parse.h Definitions.h Error.h Data_structures.h FirstPass.h parseLine.h
OBJ     = assembler.o parse.o Error.o Data_structures.o FirstPass.o parseLine.o Test.o


#################################################
# Ruls
#################################################
%.o: %.c $(DEPS)
	$(CC) $(CFALG) -c -o $@ $< $(INCLUDE) 

$(TARGET): $(OBJ)
	$(CC) $(CFALG) $(INCLUDE) -o $@ $^  $(LDFLAG) 

.PHONY: clean

clean:
	rm -f $(OBJ)

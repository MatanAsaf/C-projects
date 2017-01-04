#This is a makefile for intToBinary API

FILE_NAME = intToBinary.out

IDIR = ./
IDIR_TEST = unitTest/


CFLAGS = -g -c -ansi -pedantic -Wconversion -Wall -Werror -I$(IDIR)

CC = gcc $(CFLAGS)

OBJ_LIST = intToBinary.o $(IDIR_TEST)tests.o

#defualt command for the makefile:
$(FILE_NAME): $(OBJ_LIST)
	gcc -o $(FILE_NAME) $(OBJ_LIST) -lm


#compile
intToBinary.o: intToBinary.c intToBinary.h
	$(CC) -o intToBinary.o intToBinary.c

$(IDIR_TEST)tests.o: $(IDIR_TEST)tests.c intToBinary.h
	$(CC) -o $(IDIR_TEST)tests.o $(IDIR_TEST)tests.c




#debug
debug:
	gdb $(FILE_NAME)

#run test
run:
	./$(FILE_NAME)
	
#clean .o files and executables (.out)
clean:
	find ./ -type f -name "*.o" -exec rm -fr "{}" \;
	find ./ -type f -name "*.ipc" -exec rm -fr "{}" \;
	find ./ -type f -name "*.out" -exec rm -fr "{}" \;

	

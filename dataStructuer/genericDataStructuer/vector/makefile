#This is a makefile for Generic Vector
FILE_NAME = vector.out


IDIR = ../include/
IDIR_TEST = unitTest/
IDIR_MATAN_TEST = ../

CFLAGS = -g -c -pedantic-errors -ansi -Wconversion -Werror -Wall -I$(IDIR) -I$(IDIR_MATAN_TEST)

CC = gcc $(CFLAGS)

OBJ_LIST = vector.o $(IDIR_TEST)tests.o
 
#defualt command for the makefile:
all: $(FILE_NAME) 

#Linking
$(FILE_NAME): $(OBJ_LIST)
	gcc -o $(FILE_NAME) $(OBJ_LIST)
	
	 

#compile
vector.o: vector.c $(IDIR)vector.h  
	$(CC) -o vector.o vector.c

#compile test file	
$(IDIR_TEST)tests.o: $(IDIR_TEST)tests.c $(IDIR)vector.h $(IDIR_MATAN_TEST)matan_test.h
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
	find ./ -type f -name "*.out" -exec rm -fr "{}" \;


#This is a makefile for Generic tree
FILE_NAME = binTree.out


IDIR = ../include/
IDIR_TEST = unitTest/
IDIR_MATAN_TEST = ../


CFLAGS = -g -c -pedantic -ansi -Wconversion -Werror -Wall -I$(IDIR) -I$(IDIR_MATAN_TEST)

CC = gcc $(CFLAGS)

OBJ_LIST = $(DIR_OBJ)binTree.o $(IDIR_TEST)tests.o


#defualt command for the makefile:
all: $(FILE_NAME) 
	
#Linking
$(FILE_NAME): $(OBJ_LIST)
	gcc -o $(FILE_NAME) $(OBJ_LIST)

#compile tree files:
$(IDIR_TEST)tests.o : $(IDIR_TEST)tests.c  $(IDIR)binTree.h $(IDIR_MATAN_TEST)matan_test.h
	$(CC) -o $(IDIR_TEST)tests.o $(IDIR_TEST)tests.c

binTree.o : $(IDIR)binTree.h binTree.c
	$(CC) -o binTree.o binTree.c


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

#This is a makefile for queue
FILE_NAME = queue.out

DIR = ../include/
DIR_TEST = unitTest/
IDIR_MATAN_TEST = ../


CFLAGS = -g -c -pedantic -Wconversion -ansi -Wall -Werror -I$(DIR) -I$(IDIR_MATAN_TEST)

CC = gcc $(CFLAGS)

OBJ_LIST = $(DIR_OBJ)queue.o $(DIR_TEST)tests.o

#defualt command for the makefile:
all: $(FILE_NAME) 

#Linking
$(FILE_NAME): $(OBJ_LIST)
	gcc -o $(FILE_NAME) $(OBJ_LIST)


#compile
queue.o: queue.c $(DIR)queue.h
	$(CC) -o queue.o queue.c

#compile
$(DIR_TEST)tests.o: $(DIR_TEST)tests.c $(DIR)queue.h $(IDIR_MATAN_TEST)matan_test.h
	$(CC) -o $(DIR_TEST)tests.o $(DIR_TEST)tests.c




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

	

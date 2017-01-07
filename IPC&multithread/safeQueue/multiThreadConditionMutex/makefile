#This is a makefile for safe queue
FILE_NAME = safeQueue.out

DIR = ./inc/
DIR_OBJ = bin/
DIR_SRC = src/
DIR_INC = inc/
DIR_TEST = unitTest/


CFLAGS = -g -c -pedantic -Wconversion -ansi -Wall -Werror -I$(DIR)


CC = gcc $(CFLAGS)

OBJ_LIST = $(DIR_OBJ)safeQueue.o $(DIR_TEST)tests.o

#defualt command for the makefile:
all: $(FILE_NAME) 

#Linking
$(FILE_NAME): $(OBJ_LIST)
	gcc -o $(FILE_NAME) $(OBJ_LIST) -pthread




#compile
$(DIR_OBJ)safeQueue.o: $(DIR_SRC)safeQueue.c $(DIR_INC)safeQueue.h
	$(CC) -o $(DIR_OBJ)safeQueue.o $(DIR_SRC)safeQueue.c

#compile
$(DIR_TEST)tests.o: $(DIR_TEST)tests.c $(DIR_INC)safeQueue.h $(DIR_TEST)matan_test.h
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
	find ./ -type f -name "*.ipc" -exec rm -fr "{}" \;
	find ./ -type f -name "*.out" -exec rm -fr "{}" \;

	

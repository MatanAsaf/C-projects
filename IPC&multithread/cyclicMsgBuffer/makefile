#This is a makefile for cyclieBuf
FILE_NAME = cyclieBuf.out

DIR = ./inc/
DIR_OBJ = obj/
DIR_SRC = src/
DIR_INC = inc/
DIR_TEST = unitTest/


CFLAGS = -g -c -pedantic -Wconversion -ansi -Wall -Werror -I$(DIR)

CC = gcc $(CFLAGS)

OBJ_LIST = $(DIR_OBJ)cyclieBuf.o $(DIR_TEST)cyclieBufTests.o

#defualt command for the makefile:
all: $(FILE_NAME) 

#Linking
$(FILE_NAME): $(OBJ_LIST)
	gcc -o $(FILE_NAME) $(OBJ_LIST)


#compile
$(DIR_OBJ)cyclieBuf.o: $(DIR_SRC)cyclieBuf.c $(DIR_INC)cyclieBuf.h
	$(CC) -o $(DIR_OBJ)cyclieBuf.o $(DIR_SRC)cyclieBuf.c

#compile
$(DIR_TEST)cyclieBufTests.o: $(DIR_TEST)cyclieBufTests.c $(DIR_INC)cyclieBuf.h $(DIR_TEST)matan_test.h
	$(CC) -o $(DIR_TEST)cyclieBufTests.o $(DIR_TEST)cyclieBufTests.c



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

	

#This is a makefile for policies
FILE_NAME = policies.out

DIR = ./inc/
DIR_OBJ = obj/
DIR_SRC = src/
DIR_INC = inc/
DIR_DS = ds/
DIR_HASH = HASH/
DIR_TEST = unitTest/


CFLAGS = -g -c -pedantic -Wconversion -ansi -Wall -Werror -I$(DIR)

CC = gcc $(CFLAGS)

OBJ_LIST = $(DIR_OBJ)policies.o $(DIR_TEST)tests.o $(DIR_OBJ)list.o $(DIR_OBJ)listItr.o $(DIR_OBJ)listFunctions.o $(DIR_OBJ)vector.o $(DIR_OBJ)hashMap.o

#defualt command for the makefile:
all: $(FILE_NAME) 

#Linking
$(FILE_NAME): $(OBJ_LIST)
	gcc -o $(FILE_NAME) $(OBJ_LIST) -lm



#compile
$(DIR_OBJ)policies.o: $(DIR_SRC)policies.c $(DIR_INC)policies.h
	$(CC) -o $(DIR_OBJ)policies.o $(DIR_SRC)policies.c

#compile
$(DIR_TEST)tests.o: $(DIR_TEST)tests.c $(DIR_INC)policies.h $(DIR_TEST)matan_test.h
	$(CC) -o $(DIR_TEST)tests.o $(DIR_TEST)tests.c

#compile
$(DIR_OBJ)list.o: $(DIR_DS)list.c $(DIR_INC)list.h $(DIR_DS)privateListStruct.h
	$(CC) -o $(DIR_OBJ)list.o $(DIR_DS)list.c

#compile
$(DIR_OBJ)listItr.o: $(DIR_DS)listItr.c $(DIR_INC)list.h $(DIR_INC)listItr.h $(DIR_DS)privateListStruct.h
	$(CC) -o $(DIR_OBJ)listItr.o $(DIR_DS)listItr.c

#compile
$(DIR_OBJ)listFunctions.o: $(DIR_DS)listFunctions.c $(DIR_INC)listFunctions.h $(DIR_INC)listItr.h
	$(CC) -o $(DIR_OBJ)listFunctions.o $(DIR_DS)listFunctions.c

#compile
$(DIR_OBJ)vector.o: $(DIR_DS)vector.c $(DIR_INC)vector.h
	$(CC) -o $(DIR_OBJ)vector.o $(DIR_DS)vector.c

#compile
$(DIR_OBJ)hashMap.o: $(DIR_DS)hashMap.c $(DIR_INC)hashMap.h
	$(CC) -o $(DIR_OBJ)hashMap.o $(DIR_DS)hashMap.c




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

	

#This is a makefile for Generic hashMap
FILE_NAME = hashMap.out

IDIR = ../include/
IDIR_LIST = ../list/list/
IDIR_LIST_ITR = ../list/listItr/
IDIR_LIST_FUNCTIONS = ../list/listFunctions/
IDIR_VECTOR = ../vector/
IDIR_TEST = unitTest/
IDIR_MATAN_TEST = ../

CFLAGS = -g -c -pedantic -ansi -Wconversion -Werror -Wall -I$(IDIR) -I$(IDIR_LIST) -I$(IDIR_MATAN_TEST)

CC = gcc $(CFLAGS)

OBJ_LIST = hashMap.o $(IDIR_LIST_FUNCTIONS)listFunctions.o $(IDIR_LIST_ITR)listItr.o $(IDIR_LIST)list.o $(IDIR_VECTOR)vector.o $(IDIR_TEST)tests.o
 
#defualt command for the makefile:
all: $(FILE_NAME) 


#Linking
$(FILE_NAME): $(OBJ_LIST)
	gcc -o $(FILE_NAME) $(OBJ_LIST) -lm

#compile list file
$(IDIR_LIST)list.o: 
		cd $(IDIR_LIST); make;
	
#compile listItr file
$(IDIR_LIST_ITR)listItr.o: 
		cd $(IDIR_LIST_ITR); make;

#compile listFunctions file
$(IDIR_LIST_FUNCTIONS)listFunctions.o:
		cd $(IDIR_LIST_FUNCTIONS); make;

#compile vector file
$(IDIR_VECTOR)vector.o:
		cd $(IDIR_VECTOR); make;

#compile listFunctions file
hashMap.o : hashMap.c $(IDIR)hashMap.h 
	$(CC) hashMap.c

#compile listFunctions test file
$(IDIR_TEST)test.o : $(IDIR_TEST)tests.c $(IDIR)hashMap.h $(IDIR_MATAN_TEST)matan_test.h
	$(CC) -o $(IDIR_TEST)tests.o $(IDIR_TEST)tests.c




#debug
debug:
	gdb $(FILE_NAME)

#run test
run:
	./$(FILE_NAME)
	
#clean .o files and executables (.out)
clean:
	find ../ -type f -name "*.o" -exec rm -fr "{}" \;
	find ../ -type f -name "*.out" -exec rm -fr "{}" \;


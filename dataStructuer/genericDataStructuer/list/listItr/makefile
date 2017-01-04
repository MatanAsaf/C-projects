#This is a makefile for Generic listItr
FILE_NAME = listItr.out

IDIR = ../../include/
IDIR_LIST = ../list/
IDIR_TEST = unitTest/
IDIR_MATAN_TEST = ../../

CFLAGS = -g -c -pedantic-errors -ansi -Wconversion -Werror -Wall -I$(IDIR) -I$(IDIR_LIST) -I$(IDIR_MATAN_TEST)

CC = gcc $(CFLAGS)

OBJ_LIST = listItr.o $(IDIR_LIST)list.o $(IDIR_TEST)tests.o
 
#defualt command for the makefile:
all: $(FILE_NAME) 


#Linking
$(FILE_NAME): $(OBJ_LIST)
	gcc -o $(FILE_NAME) $(OBJ_LIST)



#compile list file
$(IDIR_LIST)list.o : 
	cd ../list/ ; make ;
	
#compile listItr file
listItr.o : listItr.c $(IDIR)listItr.h $(IDIR)list.h $(IDIR_LIST)privateListStruct.h
	$(CC) -o listItr.o listItr.c

#compile test file	
$(IDIR_TEST)tests.o: $(IDIR_TEST)tests.c $(IDIR)listItr.h $(IDIR)list.h $(IDIR_MATAN_TEST)matan_test.h
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


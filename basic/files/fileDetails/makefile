#This is a makefile for fileDetails

FILE_NAME = fileDetails.out

IDIR = ./
IDIR_TEST = unitTest/

CFLAGS = -g -c -ansi -pedantic -Wconversion -I$(IDIR)

CC = gcc $(CFLAGS)

OBJ_LIST = fileDetails.o $(IDIR_TEST)tests.o

#defualt command for the makefile:
$(FILE_NAME): $(OBJ_LIST)
	gcc -o $(FILE_NAME) $(OBJ_LIST)


#compile
fileDetails.o: fileDetails.c fileDetails.h
	$(CC) -o fileDetails.o fileDetails.c

$(IDIR_TEST)tests.o: $(IDIR_TEST)tests.c fileDetails.h $(IDIR_TEST)matan_test.h
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
	find ./ -type f -name "*.txt" -exec rm -fr "{}" \;
	

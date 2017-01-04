#This is a makefile for swap

FILE_NAME = swap.out

IDIR = ./
IDIR_TEST = unitTest/

CFLAGS = -g -c -ansi -pedantic -Wconversion -Werror -Wall -I$(IDIR)

CC = gcc $(CFLAGS)

OBJ_LIST = swap.o $(IDIR_TEST)tests.o

#defualt command for the makefile:
$(FILE_NAME): $(OBJ_LIST)
	gcc -o $(FILE_NAME) $(OBJ_LIST)


#compile
swap.o: swap.c swap.h
	$(CC) -o swap.o swap.c

$(IDIR_TEST)tests.o: $(IDIR_TEST)tests.c swap.h $(IDIR_TEST)matan_test.h
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
	

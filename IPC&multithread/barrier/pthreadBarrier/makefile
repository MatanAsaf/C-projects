#This is a makefile for barrier
FILE_NAME = barrier.out

CFLAGS = -g -c -pedantic -Wconversion -Wall -Werror

CC = gcc $(CFLAGS)

OBJ_LIST = barrier.o 

#defualt command for the makefile:
$(FILE_NAME): $(OBJ_LIST)
	gcc -o $(FILE_NAME) $(OBJ_LIST) -pthread


#compile
barrier.o: barrier.c  matan_test.h
	$(CC) -o barrier.o barrier.c


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

	

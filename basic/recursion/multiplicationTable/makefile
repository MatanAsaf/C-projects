#This is a makefile for multiplicationTable

FILE_NAME = multiplicationTable.out


CFLAGS = -g -c -ansi -pedantic -Wconversion -Werror -Wall 

CC = gcc $(CFLAGS)

OBJ_LIST = multiplicationTable.o 

#defualt command for the makefile:
$(FILE_NAME): $(OBJ_LIST)
	gcc -o $(FILE_NAME) $(OBJ_LIST)


#compile
multiplicationTable.o: multiplicationTable.c
	$(CC) -o multiplicationTable.o multiplicationTable.c

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
	

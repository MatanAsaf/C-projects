#This is a makefile for triangle

FILE_NAME = triangle.out


CFLAGS = -g -c -ansi -pedantic -Wconversion -Werror -Wall 

CC = gcc $(CFLAGS)

OBJ_LIST = triangle.o 

#defualt command for the makefile:
$(FILE_NAME): $(OBJ_LIST)
	gcc -o $(FILE_NAME) $(OBJ_LIST)


#compile
triangle.o: triangle.c
	$(CC) -o triangle.o triangle.c

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
	

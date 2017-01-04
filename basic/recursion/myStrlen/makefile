#This is a makefile for myStrlen

FILE_NAME = myStrlen.out


CFLAGS = -g -c -ansi -pedantic -Wconversion -Werror -Wall 

CC = gcc $(CFLAGS)

OBJ_LIST = myStrlen.o 

#defualt command for the makefile:
$(FILE_NAME): $(OBJ_LIST)
	gcc -o $(FILE_NAME) $(OBJ_LIST)


#compile
myStrlen.o: myStrlen.c
	$(CC) -o myStrlen.o myStrlen.c

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
	

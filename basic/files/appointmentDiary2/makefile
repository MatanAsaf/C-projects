#This is a makefile for appointmentDiary API

FILE_NAME_USER = appointmentDiary.out
FILE_NAME_TEST = appointmentDiaryTest.out

IDIR = ./
IDIR_TEST = unitTest/


CFLAGS = -g -c -pedantic -Wconversion -Wall -Werror -I$(IDIR)

CC = gcc $(CFLAGS)

OBJ_LIST_USER = appointmentDiary.o userInterface.o
OBJ_LIST_TEST = appointmentDiary.o $(IDIR_TEST)tests.o

#defualt command for the makefile:
all: $(FILE_NAME_USER) $(FILE_NAME_TEST)


#link
$(FILE_NAME_USER): $(OBJ_LIST_USER)
	gcc -o $(FILE_NAME_USER) $(OBJ_LIST_USER)

$(FILE_NAME_TEST): $(OBJ_LIST_TEST)
	gcc -o $(FILE_NAME_TEST) $(OBJ_LIST_TEST)


#compile
appointmentDiary.o: appointmentDiary.c appointmentDiary.h
	$(CC) -o appointmentDiary.o appointmentDiary.c

userInterface.o: userInterface.c appointmentDiary.h
	$(CC) -o userInterface.o userInterface.c

$(IDIR_TEST)tests.o: $(IDIR_TEST)tests.c appointmentDiary.h
	$(CC) -o $(IDIR_TEST)tests.o $(IDIR_TEST)tests.c




#debug
debugUser:
	gdb $(FILE_NAME_USER)

debugTest:
	gdb $(FILE_NAME_TEST)

#run the program:
run:
	./$(FILE_NAME_USER)

test:
	./$(FILE_NAME_TEST)
	
#clean .o files and executables (.out)
clean:
	find ./ -type f -name "*.o" -exec rm -fr "{}" \;
	find ./ -type f -name "*.txt" -exec rm -fr "{}" \;
	find ./ -type f -name "*.out" -exec rm -fr "{}" \;

	

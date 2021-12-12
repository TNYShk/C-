#code
CC = gcc 
CFLAGS = -ansi -pedantic-errors -Wall -Wextra 
LDFLAGS = -g
DEBUG = -ansi -pedantic-errors -Wall -Wextra -g

OBJ = main.o foo.o
#target : prerequisits, files needed to make the target

fooer : $(OBJ)
	gcc main.o foo.o -o fooer

all : fooer.out
	

main.o : main.c
	gcc -c main.c


foo.o : foo.c foo.h 
	gcc -c foo.c


.PHONY : clean all

clean : 
		rm -rf *.o fooer.out


debug : $(OBJ)
	$(CC) $(DEBUG) -o debugged.out $(OBJ)
#code
CC = gcc 
CFLAGS = -ansi -pedantic-errors -Wall -Wextra 
LDFLAGS = -g
DEBUG = -ansi -pedantic-errors -Wall -Wextra -g

OBJ = main.o foo.o
#target : prerequisits, files needed to make the target


all : fooer.out
	./fooer.out	

fooer.out : $(OBJ)
	$(LINK.o) -o fooer.out $(OBJ) 

main.o : main.c foo.h
	$(COMPILE.c) main.c

foo.o : foo.c foo.h
	$(COMPILE.c) foo.c


.PHONY : clean all

clean : 
		rm -rf *.o fooer.out debugged.out


debug : $(OBJ)
	$(CC) $(DEBUG) -o debugged.out $(OBJ)
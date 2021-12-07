#code
GD = gcc -ansi -pedantic-errors -Wall -Wextra -g

OBJ = main.o foo.o
#target : prerequisits, files needed to make the target




fooer.out : $(OBJ)
		gcc -g -o fooer.out $(OBJ) 

main.o : main.c foo.h
		$(GD) -c main.c

foo.o : foo.c foo.h
		$(GD) -c $(CFLAGS) foo.c


.PHONY : clean all

clean : 
		rm -rf *.o fooer.out

all : fooer.out
	./fooer.out	
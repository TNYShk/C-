CC = gcc
.PHONY := clean

TARGET:= test

$(TARGET) : dll_test.c libdll.so
	gcc -L. -Wl,-rpath=. -Wall -o $@ dll_test.c -ldll

libdll.so : dll.o
	gcc -shared -o $@ dll.o 

dll.o : dll.c
	gcc -c -Wall -Werror -fpic $<


clean:
	rm -rf test *.o *.so
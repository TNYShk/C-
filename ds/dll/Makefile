
CC := gcc

.PHONY := clean test release debug all

RLS := -O3 -DNDBUG
CFLAGS := -ansi -pedantic-errors -Wall -Wextra -fPIC 
LINKN := -shared
TARGET:= a.out

DEBUG := -g

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)


$(TARGET) : $(filter *_test.c,$(SRCS)) ../libs/debug/libdll.so
	$(CC) -L../libs/debug -Wl,-rpath=../libs/debug -Wall -o $@ dll_test.c -ldll $(DEBUG)

../libs/debug/libdll.so : $(filter-out *_test.c,$(SRCS:.c=.o))
	$(CC) $(LINKN) $(DEBUG) -o $@ $< 

$(OBJS) : $(filter-out *_test.c,$(SRCS)) ../include/dll.h
	$(CC) -c $(CFLAGS) $<


release: ../libs/release/libdll.so

../libs/release/libdll.so : $(filter-out *_test.c,$(SRCS:.c=.o))
	$(CC) $(LINKN) $(RLS) -o $@ $<


debug: ../libs/debug/libdll.so

all: release debug

clean:
	rm -rf $(TARGET) *~ *.o *.d

test:
	./$(TARGET)
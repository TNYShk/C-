
CC := gcc

.PHONY := clean test release debug all

RLS := -O3 -DNDBUG
CFLAGS := -ansi -pedantic-errors -Wall -Wextra -fPIC 
LINKN := -shared
TARGET:= a.out
DEBUG := -g

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)
LIBS := $(addprefix lib,$(notdir $(CURDIR)))
DS := $(notdir $(CURDIR))

$(TARGET) : $(filter *_test.c,$(SRCS)) ../libs/debug/$(LIBS).so
	$(CC) -L../libs/debug -Wl,-rpath=../libs/debug -Wall -o $@ $(DS)_test.c -l$(DS) $(DEBUG)

../libs/debug/$(LIBS).so : $(filter-out *_test.c,$(SRCS:.c=.o))
	$(CC) $(LINKN) $(DEBUG) -o $@ $< 

$(OBJS) : $(filter-out *_test.c,$(SRCS)) 
	$(CC) -c $(CFLAGS) $<


release: ../libs/release/$(LIBS).so

../libs/release/$(LIBS).so : $(filter-out *_test.c,$(SRCS:.c=.o))
	$(CC) $(LINKN) $(RLS) -o $@ $<


debug: ../libs/debug/$(LIBS).so

all: release debug

clean:
	rm -rf $(TARGET) *~ *.o *.d

test:
	./$(TARGET)

CC := gcc

.PHONY := clean test release debug all

RLS := -O3 -DNDBUG
CFLAGS := -ansi -pedantic-errors -Wall -Wextra 
PIC := -fPIC
CPPFLAGS := -I ../include
LINKN := -shared
TARGET:= a.out
DEBUG := -g

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)
CLEAN_SRC := $(filter-out $(wildcard *_test.c), $(SRCS))
CLEAN_OBJ :=  $(CLEAN_SRC:.c=.o)

DEPS := dll
DEPLIST := $(addsuffix .so, $(addprefix lib,$(DEPS)))


LIBS := $(addsuffix .so, $(addprefix lib,$(notdir $(CURDIR))))
DS := $(notdir $(CURDIR))

$(TARGET) : $(filter *_test.c,$(SRCS)) ../libs/debug/$(LIBS) $(DEPLIST) 
	$(CC) $(CPPFLAGS) -L ../libs/debug -Wl,-rpath=../libs/debug $(CFLAGS) -o $@ $(DS)_test.c -l$(DS) $(addprefix -l,$(DEPS)) $(DEBUG)

$(DEPLIST) : lib%.so : 
	$(MAKE) -C ../$* all clean

../libs/debug/$(LIBS) : $(CLEAN_OBJ) 
	$(CC) $(LINKN) $(DEBUG) -o $@ $^ 

$(CLEAN_OBJ) : $(CLEAN_SRC) 
	$(CC) $(CPPFLAGS) -c $(CFLAGS) $(PIC) $^ $(DEBUG)


release: ../libs/release/$(LIBS)

../libs/release/$(LIBS): $(CLEAN_OBJ)
	$(CC) $(LINKN) $(RLS) -o $@ $^


debug: ../libs/debug/$(LIBS)

all: release debug

clean:
	rm -rf $(TARGET) *~ *.o

test: $(TARGET)
	./a.out


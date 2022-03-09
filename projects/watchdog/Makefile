NAME = $(notdir $(CURDIR))
MODE ?=debug

DS_LIB_LOC := ../../ds/libs/$(MODE)
DS_INC_LOC := ../../ds/include 


DS_DEPS := task uid schedule semaphore_sys_v 

CUR_LIB_NAME := lib$(NAME).so
CUR_LIB := $(DS_LIB_LOC)/$(CUR_LIB_NAME)
CUR_INC := $(DS_INC_LOC)
#NO_REBUILD_DEPS := pthread



CC = gcc
CFLAGS = -fpic -ansi -pedantic-errors -Wall -Wextra -pthread
CPPFLAGS = -I$(DS_INC_LOC) -I../include
LDFLAGS = -pthread -L$(DS_LIB_LOC) -Wl,-rpath='$(DS_LIB_LOC)'  -Wl,-rpath='$$ORIGIN'
LDLIBS =  $(addprefix -l,$(DS_DEPS)) 
VLG = valgrind --leak-check=yes --track-origins=yes

DEBUG = -g -DDEBUG
RELEASE =  -DNDBUG

SRCS := $(wildcard *.c)  
OBJS := $(filter-out %_guard.c,$(SRCS:.c=.o))

TRGT = $(filter %.out,$(SRCS:_test.c=_test.out))
GUARDIAN_TRGT = $(SRCS:_guard.c=_guard.out)
GD = $(CC)

ifeq ($(MODE), debug)
CFLAGS += $(DEBUG)
LDFLAGS += $(DEBUG)
else ifeq ($(MODE), release)
CFLAGS += $(RELEASE)
LDFLAGS += $(RELEASE)
endif

.PHONY: all run vlg debug clean release

all: run

run: test $(GUARDIAN_TRGT)
	./$(NAME)_test.out

vlg: debug
	$(VLG) ./$(TRGT)

debug: $(DS_DEPS) $(CUR_LIB) | $(DS_LIB_LOC) $(DS_INC_LOC)

release: 
	$(MAKE) MODE=release

test: debug $(TRGT)
	

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -c -o $@

%.out: %.o kickdog.o
	#link : 
	$(CC) $(LDFLAGS) $^ -o $@ $ -lwatchdog $(LDLIBS) 

$(CUR_LIB): $(NAME).o
	$(CC) -shared $(LDFLAGS) -o $@ $< $(LDLIBS) 

#$(GUARDIAN_TRGT): kickdog.o
#	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS) -lwatchdog

$(DS_DEPS) : 
	$(MAKE) -C../../ds/ $(MODE) target=$@

$(DS_LIB_LOC) $(DS_INC_LOC):
	@mkdir -p $@

clean:
	#cleaning!
	rm -rf $(TRGT) *~ *.o


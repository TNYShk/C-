CC := gcc
CFLAGS := -fPIC -ansi -pedantic-errors -Wall -Wextra
CPPFLAGS := -I../include -I../../ds/include -I../../system_programming/include
LDFLAGS = -shared -pthread
RELEASE = -O3 -DNDEBUG  
DEBUG = -g -DDEBUG
VLG = valgrind --leak-check=yes --track-origins=yes
DEPC1 = semaphore_sys_v
DEPC2 = schedule

DBG := debug
RLS := release

#shoshanas make
MKDIR = mkdir -p
OBJDIR := ../objects/

RLSDIR := ../../ds/libs/$(RLS)
DBGDIR := ../../ds/libs/$(DBG)

SRCS_TEST := $(wildcard *_test.c)
SRCS_LIB := $(filter-out $(SRCS_TEST),$(wildcard *.c))

OBJS_LIB := $(SRCS_LIB:.c=.o)
OBJS_TEST := $(SRCS_TEST:.c=.o)

SRC_EXE := kickdog.c
OBJS_EXE := ../../ds/libs/kickdog.o
EXE_EXE := kickdog

TEST := $(basename $(SRCS_TEST)) 
STEM := $(subst _test,,$(TEST))

SHLIB := $(patsubst %,lib%.so,$(STEM))
LDLIBS = -l$(STEM) -lm


.PHONY: all release debug test
all: release debug
	
release: $(RLSDIR)/$(SHLIB) | $(RLSDIR)

$(RLSDIR)/$(SHLIB): $(RLSDIR)/$(OBJS_LIB) | $(RLSDIR)
	$(CC) $(LDFLAGS) -o $@ $^
$(RLSDIR)/$(OBJS_LIB): $(SRCS_LIB) | $(RLSDIR)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $(RELEASE) $< -o $@


debug: LDFLAGS += -g
debug: $(DBGDIR)/$(SHLIB) | $(DBGDIR)

$(DBGDIR)/$(SHLIB): LDFLAGS := -shared
$(DBGDIR)/$(SHLIB): $(DBGDIR)/$(OBJS_LIB) | $(DBGDIR)
	$(CC) $(LDFLAGS) -o $@ ../../ds/libs/debug/watchdog.o
$(DBGDIR)/$(OBJS_LIB): $(SRCS_LIB) | $(DBGDIR)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $(DEBUG) $< -o $@

$(TEST): LDFLAGS := $(filter-out -shared,$(LDFLAGS))
$(TEST): LDFLAGS += -g -L $(DBGDIR) -Wl,-rpath=$(DBGDIR) 
																	
$(TEST): $(DBGDIR)/$(SHLIB) $(EXE_EXE) | $(DBGDIR)
	$(MAKE) -C ../../system_programming/$(DEPC1)
	$(MAKE) -C ../../ds/$(DEPC2)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $(SRCS_TEST) $(LDLIBS) $(DBGDIR)/libsemaphore_sys_v.so $(DBGDIR)/libschedule.so $(DBGDIR)/libpq.so $(DBGDIR)/libheap.so $(DBGDIR)/libdynamic_vector.so $(DBGDIR)/libtask.so $(DBGDIR)/libuid.so $(DBGDIR)/libsorted_list.so $(DBGDIR)/libdll.so

test: $(TEST)

$(EXE_EXE): $(OBJS_EXE) $(DBGDIR)/$(SHLIB)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $(SRC_EXE) $(LDLIBS) $(DBGDIR)/libsemaphore_sys_v.so $(DBGDIR)/libschedule.so $(DBGDIR)/libpq.so $(DBGDIR)/libheap.so $(DBGDIR)/libdynamic_vector.so $(DBGDIR)/libtask.so $(DBGDIR)/libuid.so $(DBGDIR)/libsorted_list.so $(DBGDIR)/libdll.so

$(OBJS_EXE): ../include/watchdog.h

$(RLSDIR) $(DBGDIR):
	$(MKDIR) $@

%.c: | ../include/%.h
	sed 's/^#.*//g ; 3i #include "$*.h"' $| > $@
	sed -i 's/^typedef.*//g ; s/);/)\n{\n    \n}/g' $@ 
	sed -i '/./{H;$!d} ; x ; s/\/\*.*\*\///g' $@


.PHONY := vlg git clean
vlg: test
	$(VLG) ./$(TEST)

git:
	git add ./
	git commit -m "$(m)"
	git push 

clean:
	rm -rf $(TARGET) *~ *.o
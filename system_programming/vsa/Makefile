CC := gcc
CFLAGS := -ansi -pedantic-errors -Wall -Wextra -g
LDFLAGS := -g

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

TARGET := a.out

.DEFAULT_GOAL := $(TARGET)
.PHONY := valg clean

%.c: | %.h
	sed 's/^#.*//g ; 3i #include "$|"' $| > $@
	sed -i 's/^typedef.*//g ; s/);/)\n{\n    \n}/g' $@ 
	sed -i '/./{H;$!d} ; x ; s/\/\*.*\*\///g' $@

%.d: %.c
	$(CC) -MM $< > $@~
	sed 's/\($*\.o\):/\1 $@:/g' $@~ > $@
	rm -f $@~


$(TARGET): $(OBJS)
	$(LINK.o) $^ -o $@

valg: $(TARGET)
	valgrind --leak-check=yes --track-origins=yes ./$<

clean:
	rm -rf $(TARGET) *~ *.o
	
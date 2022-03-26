CC := gcc
CFLAGS := -ansi -pedantic-errors -Wall -Wextra -g
LDFLAGS := -g

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o) stack.o sll.o bst.o avl.o hash.o dll.o
CPPFLAGS := -I ../../ds/include
TARGET := a.out

.DEFAULT_GOAL := $(TARGET)
.PHONY := valg push clean

%.c: | %.h
	sed 's/^#.*//g ; 3i #include "$|"' $| > $@
	sed -i 's/^typedef.*//g ; s/);/)\n{\n    \n}/g' $@ 
	sed -i '/./{H;$!d} ; x ; s/\/\*.*\*\///g' $@

stack.o: ../../ds/stack/stack.c ../../ds/include/stack.h | ../../ds/stack
	$(COMPILE.c) $< -o $@

bst.o: ../../ds/bst/bst.c ../../ds/include/bst.h | ../../ds/bst
	$(COMPILE.c) $< -o $@

dll.o: ../../ds/dll/dll.c ../../ds/include/dll.h | ../../ds/dll
	$(COMPILE.c) $< -o $@

sll.o: ../../ds/sll/sll.c ../../ds/include/sll.h | ../../ds/sll
	$(COMPILE.c) $< -o $@

hash.o: ../../ds/hash/hash.c ../../ds/include/hash.h | ../../ds/hash
	$(COMPILE.c) $< -o $@

avl.o: ../../ds/avl/avl.c ../../ds/include/avl.h | ../../ds/avl
	$(COMPILE.c) $< -o $@

$(TARGET): $(OBJS)
	$(LINK.o) $^ -o $@

valg: $(TARGET)
	valgrind --leak-check=yes --track-origins=yes ./$<

clean:
	rm -rf $(TARGET) *~ *.o
	
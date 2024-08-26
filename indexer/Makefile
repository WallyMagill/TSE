# Makefile for 'indexer'
# 
# Wally Magill, Febuary 2023

L = ../libcs50
P = ../common
CC = gcc
CFLAGS= -Wall -pedantic -std=c11 -ggdb -I$L -I$P

OBJS = indexer.o
OBJSTEST = indextest.o
LIBS = -lm
LLIBS = $P/common.a $L/libcs50-given.a

.PHONY: all test clean

# Builds program
indexer: $(OBJS) $(LLIBS)
	 $(CC) $(CFLAGS) $^ $(LIBS) -o $@

indextest: $(OBJSTEST) $(LLIBS)
	 $(CC) $(CFLAGS) $^ -o $@

# Object files
indexer.o: $L/webpage.h $L/counters.h $L/hashtable.h $L/file.h $L/mem.h $P/pagedir.h $P/word.h $P/index.h

indextest.o: $P/index.h

# Makes all files
all: indexer indextest

# Test using bash script
test:
	bash -v testing.sh

# Clean products
clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f indexer
	rm -f indextest
	rm -f *~ *.o
	rm -f core
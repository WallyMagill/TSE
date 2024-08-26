# Makefile for 'querier'
# 
# Wally Magill, Febuary 2023

L = ../libcs50
P = ../common
CC = gcc
CFLAGS= -Wall -pedantic -std=c11 -ggdb -I$L -I$P

OBJS = querier.o
LIBS = -lm
LLIBS = $P/common.a $L/libcs50-given.a

.PHONY: test clean

# Builds program
querier: $(OBJS) $(LLIBS)
	 $(CC) $(CFLAGS) $^ $(LIBS) -o $@

# Object files
indexer.o: $L/webpage.h $L/counters.h $L/hashtable.h $L/file.h $L/mem.h $P/pagedir.h $P/word.h $P/index.h

# Test using bash script
test:
	bash -v testing.sh

# Clean products
clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f querier
	rm -f *~ *.o
	rm -f core
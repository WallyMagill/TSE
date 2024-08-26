# Makefile for 'crawler'
# 
# Wally Magill, Febuary 2023

L = ../libcs50
P = ../common
CC = gcc
CFLAGS= -Wall -pedantic -std=c11 -ggdb -I$L -I$P -DAPPTEST

OBJS = crawler.o
LIBS = -lm
LLIBS = $L/libcs50-given.a $P/common.a

.PHONY: test clean

# Builds program
crawler: $(OBJS) $(LLIBS)
	 $(CC) $(CFLAGS) $^ $(LIBS) -o $@

# Object files
crawler.o: $L/webpage.h $L/bag.h $L/hashtable.h $P/pagedir.h

# Test using bash script
test:
	bash -v testing.sh

# Clean products
clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f crawler
	rm -f *~ *.o
	rm -f core

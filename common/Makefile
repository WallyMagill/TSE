# Makefile for 'common'
# 
# Wally Magill, Febuary 2023

L = ../libcs50
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$L

OBJS = pagedir.o index.o word.o
LIB = common.a
LIBS = -lm
LLIBS = $L/libcs50-given.a

.PHONY: clean

# Building common.a
$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS) $(LLIBS) $(LIBS)

# Object file
pagedir.o: $L/webpage.h pagedir.h
index.o: $L/hashtable.h $L/webpage.h $L/counters.h $L/file.h index.h
word.o: word.h

# Clean products
clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f common.a
	rm -f *~ *.o
	rm -f core

# Makefile for the creator module
#
# CS50 Final Project

# DEBUG = -D DEBUG

C = ../common

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$C $(DEBUG)
PROG = creator.o
OBJS = creator.c $C/common.h

# make the object file for creator
$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -c -o $@ creator.c

.PHONY: clean test valgrind

clean:
	rm -f $(PROG)
	rm -f *~ *.o
	rm -rf *.dSYM

test:

valgrind:

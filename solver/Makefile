# Makefile for 'solver' module 

DEBUG = -D DEBUG
C = ../common
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$C $(DEBUG)
CC = gcc

#rules
solver.o: solver.c $C/common.h
	$(CC) $(CFLAGS) -c -o $@ solver.c

clean:
	rm -f *~ *.o *.dSYM

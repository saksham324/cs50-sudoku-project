# Makefile for the creator module
# CS50 Final Project

C = common
R = creator
S = solver

# Comment or uncomment DEBUG flags within module makefiles to control DEBUG printing per module. This flag only for sudoku.c.
# DEBUG = -D DEBUG

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(DEBUG) -I$C -I$R -I$S
PROG = sudoku
OBJS = sudoku.o $S/solver.o $R/creator.o $C/common.o 

MAKE = make
.PHONY: all clean test valgrind

############## default: make all libs and programs ##########
all: 
	$(MAKE) -C $C
	$(MAKE) -C $R
	$(MAKE) -C $S
	$(MAKE) $(PROG)

# executable depends on object files
$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# object files depend on include files
sudoku.o: $C/common.h $R/creator.h $S/solver.h
	$(CC) $(CFLAGS) -c -o $@ sudoku.c 

############# Uncomment below rules if module makefiles are missing for whatever reason ########################
#$R/creator.o: $C/common.h $R/creator.h
#	$(CC) $(CFLAGS) -c -o $@ $R/creator.c 

#$S/solver.o: $C/common.h $S/solver.h
#	$(CC) $(CFLAGS) -c -o $@ $S/solver.c

#$C/common.o: $C/common.h
#	$(CC) $(CFLAGS) -c -o $@ $C/common.c

############## clean  ##########
clean:
	rm -f $(PROG)
	rm -f *~ *.o
	rm -rf *.dSYM
	$(MAKE) -C $C clean
	$(MAKE) -C $R clean
	$(MAKE) -C $S clean

test:
	./testing.sh 3

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROG) create
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROG) solve < tests/test2/test2
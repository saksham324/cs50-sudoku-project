/*
 * sudoku.c - CS50 Final Project, Main Function
 * This module is the main driver of the sudoku program. It parses command line
 * arguments and calls the appropriate modules to either create or solve a
 * 9x9 sudoku puzzle.
 * The creator outputs the puzzle with rows separated with newlines and columns
 * separated with spaces to stdout.
 * The solver accepts digits and whitespace from stdin, with each digit
 * separated by at least one whitespace character. Whitespace is ignored.
 * See docs for more info.
 */

#include <string.h>
#include "common.h"
#include "creator.h"
#include "solver.h"


int main(int argc, char *argv[])
{
    const char *USAGE = "Usage: sudoku [create|solve]\n";
    
    if (argc != 2) {
        fprintf(stderr, "Wrong number of arguments.\n%s", USAGE);
        return 1;
    }

    if (strcmp(argv[1], "create") == 0) {
        sudoku_create();
    } else if (strcmp(argv[1], "solve") == 0) {
        sudoku_solver();
    } else {
        fprintf(stderr, "Argument was not create or solve.\n%s", USAGE);
        return 2;
    }

    return 0;
}


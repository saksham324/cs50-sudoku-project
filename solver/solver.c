/*
 * solver.c - implements the solver module. Accepts a 9x9 sudoku puzzle from
 * stdin (digits separated by whitespace) and outputs the solved puzzle to
 * stdout. See docs for more info.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "common.h"

void sudoku_solver(void)
{
    int sudoku[9][9]= {0};
    int row = 0, col = 0;
    bool expect_digit = true;               // flag to keep track of if to expect digit (only after at least one whitespace)
    char c;

    // read chars from stdin until EOF or error
    while ((c = fgetc(stdin)) != EOF) {
        // ignore whitespace (' ', '\t', '\n', '\v', '\f', '\r')
        if (isspace(c)) {
            expect_digit = true;
            continue;
        }

        // if char is digit and we were expecting a digit (previous char was whitespace)
        if (isdigit(c) && expect_digit) {
            sudoku[row][col] = c - '0';         // converts digit from ASCII to int
            expect_digit = false;
            // increment [row, col] values accordingly
            if (++col >= 9) {
                col = 0;
                row += 1;
            }
            // break if we are done filling up the board
            if (row >= 9)
                break;
        } else {
            // invalid input: bad character or multiple digits at once.
            fprintf(stderr, "Invalid input: only digits and whitespace allowed. Each digit must be separated by at least one whitespace character.\n");
            return;
        }
    }

    // check if board has been filled
    if (row < 9) {
        fprintf(stderr, "Invalid input: not enough numbers.\n");
        return;
    }

    #ifdef DEBUG
        printf("Solver parsed sudoku puzzle:\n");
        print_sudoku(sudoku);
    #endif

    int solution[9][9] = {0};
    int ret = unique_solver(sudoku, solution);
    
    #ifdef DEBUG
        printf("\nSolved sudoku:\n");
    #endif

    if (ret == 0) {
        printf("No solutions found.\n");
    } else {
        print_sudoku(solution);
        if (ret == 2)
            printf("Multiple solutions found.\n");
        #ifdef DEBUG
            if(ret == 1)
                printf("Unique solution! Normally, nothing is printed when DEBUG flag turned off.\n");
        #endif
    } 
}


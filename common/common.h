/*
 * common.h - header file for common functions between
 * the solver and creator sudoku modules 
 * 
 * Pratinav Bagla, Wendell Wu, and Eyasu Fetene 
 */

#ifndef __COMMON_H
#define __COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

/**************** print_sudoku ****************/
/* print the sudoku puzzle
 * 
 * Caller provides:
 *  valid pointer to a 2D array
 * We return:
 *  the 2D array printed in a 9 by 9 grid
 */
void print_sudoku(int array[9][9]);

/**************** unique_solver ****************/
/*
 * Solve the sudoku puzzle. Put the first
 * solution found into firstSolution.
 * 
 * If firstSolution is NULL, nothing is returned except
 * the appropriate return code.
 * 
 * Caller provides:
 *  - memory (9x9 grid) for firstSolution to be stored at
 *  - the unsolved puzzle itself, left untouched
 * Returns:
 *  - the first solution found, if found, copied into firstSolution
 *  - an integer return code
 *    0. If no solutions found or puzzle is NULL.
 *       firstSolution remains untouched.
 *    1. a unique solution was found. it is written to
 *       firstSolution, if non-NULL.
 *    2. more than one solution was found for this board. the first
 *       solution found is placed in firstSolution, if non-NULL.
 */
int unique_solver(int puzzle[9][9], int firstSolution[9][9]);

/**************** mycalloc ****************/
/*
 * Behaves like calloc but prints an error message and exits when calloc fails.
 * Returns pointer returned by calloc.
 */
void * mycalloc(const size_t nmemb, const size_t size);

#endif


/*
 * solver.h - defines the exported functions of the solver module. Used to
 * accept a 9x9 sudoku puzzle from stdin (digits separated by whitespace) and
 * output the solved puzzle.
 * See docs for more info.
 */

#ifndef __SOLVER_H_
#define __SOLVER_H_

/**************** sudoku_solver ****************/
/*
 * Called by sudoku when solve is the argument passed.
 * It will parse the puzzle from stdin and print the
 * solution, if it finds one. Otherwise, an error
 * message will be printed to stderr instead.
 */
void sudoku_solver(void);

#endif


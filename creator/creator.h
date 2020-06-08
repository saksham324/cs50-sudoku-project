/*
 * creator.h - Header file that defines and exports functions for the creator
 * module. Creates a new 9x9 sudoku with a unique solution and at least 40 empty
 * slots, and outputs to stdout. See docs for more info.
 */

#ifndef __CREATOR_H_
#define __CREATOR_H_

/**
 * Called by sudoku when create is passed
 * as an argument to sudoku
 */
void sudoku_create();

#endif

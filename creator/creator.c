/*
 * creator.c - CS50 Final Project, Sudoku Creator Module
 * This module is responsible for creating a new randomized 9x9 sudoku puzzle
 * with a unique solution, and has a minimum of 40 numbers removed. The generated
 * sudoku is outputted to stdout. See docs for more info.
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "common.h"

static void shuffle(int puzzle[9][9]);
static void remove_nums(int puzzle[9][9]);
static void get_rand_orientation(int arr[3]);
static void copy_puzzle(int og[9][9], int copy[9][9]);

/**************** sudoku_create ****************/
/*
 * This function is called by program execution if "create" was called. It
 * takes in no parameters and does not return anything. It simply creates a
 * puzzle guaranteed to have a unique solution and prints it to stdout.
 */
void sudoku_create(void)
{
    // Hardcoded template to work off of, where [0][0] = top left and [8][0] is
    // bottom left. Essentially, [row][col].
    int puzzle[9][9] = {
        {4, 3, 5, 2, 6, 9, 7, 8, 1},
        {6, 8, 2, 5, 7, 1, 4, 9, 3},
        {1, 9, 7, 8, 3, 4, 5, 6, 2},
            
        {8, 2, 6, 1, 9, 5, 3, 4, 7},
        {3, 7, 4, 6, 8, 2, 9, 1, 5},
        {9, 5, 1, 7, 4, 3, 6, 2, 8},
            
        {5, 1, 9, 3, 2, 6, 8, 7, 4},
        {2, 4, 8, 9, 5, 7, 1, 3, 6},
        {7, 6, 3, 4, 1, 8, 2, 5, 9}
    };

    // Shuffle the template puzzle to get a new, valid puzzle.
    srand(time(0));     // seed RNG
    shuffle(puzzle); 

    #ifdef DEBUG
        printf("\nRandomly shuffled template board:\n");
        print_sudoku(puzzle);
    #endif

    // Remove min. 40 slots making sure there is a unique solution.
    remove_nums(puzzle);
    #ifdef DEBUG
        printf("\nBoard with nums removed:\n");
    #endif
    print_sudoku(puzzle);
}

/**************** shuffle ****************/
/*
 * Randomly shuffles the given sudoku puzzle while maintaing its validity.
 * Caller must provide a valid pointer to an int[9][9] containing the puzzle.
 * Directly edits the given puzzle.
 */

static void shuffle(int puzzle[9][9])
{
    int puzzle_copy[9][9]= {0};
    int pos_total[2][9] = {0};
    int pos_major[3]= {0};
    int pos_minor[3]= {0};

    // Randomly generate an int[] of shuffled column positions as well as row
    // positions. The sudoku's validity is maintained by first generating the
    // positions for each major 9x3/3x9 section, then the 9x1/1x9 rows/columns
    // within them.
    for (int i = 0; i < 2; i++) {
        get_rand_orientation(pos_major);
        for (int j = 0; j < 3; j++) {
            get_rand_orientation(pos_minor);
            for (int k = 0; k < 3; k++)
                pos_total[i][j * 3 + k] = pos_major[j] * 3 + pos_minor[k];
        }
    }

    // Re-orient the puzzle according to the newly generated int arrays of
    // shuffled col and row positions.
    copy_puzzle(puzzle, puzzle_copy);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            puzzle[i][j] = puzzle_copy[pos_total[0][i]][pos_total[1][j]];
        }
    }
}

/**************** remove_nums ****************/
/*
 * Takes in a solved (filled) puzzle and removes at least 40 random numbers so
 * that there is still only one solution to the puzzle.
 * After removing at least 40 nums, if it fails to remove a num three times
 * continuously, it stops removing numbers.
 * Caller provides a valid pointer to an int[9][9] containing the puzzle, that
 * will be edited directly by replacing nums with zeros.
 * Caller is responsible for seeding rand before calling the function.
 */
static void remove_nums(int puzzle[9][9])
{
    int removed_count = 0;
    int num_failed_tries = 0;               // records the num of continuously failed tries
    int row, col;
    while (removed_count <= 65) {           // 16 is the lowest number of starting clues to get a unique solution
        // get a num that has not yet been removed
        do {
            row = rand() % 9;
            col = rand() % 9;
        } while (puzzle[row][col] == 0);

        // remove num from puzzle.
        int temp = puzzle[row][col];
        puzzle[row][col] = 0;

        int num_solutions = unique_solver(puzzle, NULL);
        if (num_solutions != 1) {           // if non-unique solution or non-existent solution
            puzzle[row][col] = temp;        // put the number back
            num_failed_tries += 1;          // increment the num of continuous failed tries
            // if we have removed at least 40 nums and have failed to remove
            // nums at least 3 times continuously, break.
            if (removed_count >= 40 && num_failed_tries == 3) break;
        } else {
            removed_count++;                // keep the 0 and increment removed_count
            num_failed_tries = 0;           // reset the num of continuously failed tries
        }
    }
}

/**************** get_rand_orientation ****************/
/*
 * Generates an int array of random positions for shuffling the rows and cols in
 * the sudoku, setting it to the given int[]. There are 6 total possibilites:
 * {0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0}.
 * Caller must provide a valid pointer to an int[].
 * Caller is responsible for seeding srand before calling the function.
 */
static void get_rand_orientation(int arr[3])
{
    // generate a random int between 0 and 3 (excluding 3) for each array item.
    for (int i = 0; i < 3; i++) {
        arr[i] = rand() % 3;
        // if the generated int is already present in the array, repeat.
        for (int j = 0; j < i; j++) {
            if (arr[i] == arr[j]) {
                i -= 1;
                break;
            }
        }
    }
}

/**************** copy_puzzle ****************/
/*
 * Copies the given puzzle int[9][9] to the given int[9][9].
 * Caller provides valid pointers to the original and copy arrays.
 */
static void copy_puzzle(int og[9][9], int copy[9][9])
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            copy[i][j] = og[i][j];
}


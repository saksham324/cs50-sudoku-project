/*
 * common.c - module for solver and creator modules of 
 * sudoku puzzle
 * 
 * see common.h for more information 
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

/**************** LOCAL FUNCTION PROTOTYPES ****************/
static bool unique_solver_helper(int temp[9][9], int first_solution[9][9], int *num_solutions);
static bool is_puzzle_valid(int puzzle[9][9]);
static bool is_num_valid(int array[9][9], int row, int col, int val);

/**************** GLOBAL FUNCTIONS ****************/

/**************** print_sudoku ****************/
/* see common.h */
void print_sudoku(int array[9][9])
{
    for (int i = 0; i < 9; i++) {           // iterate through the 9 arrays in the pointer
        for (int j = 0; j < 9; j++) {       // iterate through the 9 elements in the current array
            printf("%d", array[i][j]);      // print out the number
            if (j != 8) printf(" ");
        }
        printf("\n");                       // start at a new line after printing first array 
    }
}

/**************** unique_solver ****************/
/* see common.h */
int unique_solver(int puzzle[9][9], int first_solution[9][9])
{
    // check if puzzle is valid
    if (!is_puzzle_valid(puzzle)) {
        fprintf(stderr, "Inputted sudoku is invalid!\n");
        return 0;
    }

    // copy puzzle to temp variable
    int temp[9][9] = {0};
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            temp[i][j] = puzzle[i][j];

    int num_solutions = 0;           // serve as an accumulator to detect non-unique solution
    unique_solver_helper(temp, first_solution, &num_solutions);
    return num_solutions;
}

/**************** mycalloc ****************/
/*
 * Behaves like calloc but exits when returns NULL.
 * See common.h.
 */
void * mycalloc(const size_t nmemb, const size_t size)
{
    void *ptr = calloc(nmemb, size);
    if (ptr == NULL) {
        fprintf(stderr, "ERROR: MALLOC FAILED\n");
        exit(99);
    }
    return ptr;
}

/**************** LOCAL FUNCTIONS ****************/

/**************** unique_solver_helper ****************/
/*
 * Recursive helper function for unique_solver.
 * Logic is documented in-line.
 */
static bool unique_solver_helper(int temp[9][9], int first_solution[9][9], int *num_solutions)
{
    int row = 9, col = 9;

    // find the next empty spot in the array;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (temp[i][j] == 0) {
                row = i;
                col = j;
                break;
            }
        }
    }

    // if no empty spots found, increment num_solutions and return appropriate bool
    if (row == 9) {
        (*num_solutions)++;
        if (*num_solutions == 1 && first_solution != NULL) {    // if this is the first solution, copy to first_solution
            for (int i = 0; i < 9; i++)
                for (int j = 0; j < 9; j++)
                    first_solution[i][j] = temp[i][j];
        } else if (*num_solutions > 1) {                        // if this is the second solution, don't do anything, return false to stop recursion.
            return false;
        }
        return true;
    }

    // empty spot was found
    for (int i = 1; i <= 9; i++) {
        // if the number 'i' satisfies the rules for its spot, 
        if (is_num_valid(temp, row, col, i)) {
            // set that spot to 'i'
            temp[row][col] = i;

            // if second solution found, stop recursing
            if (!unique_solver_helper(temp, first_solution, num_solutions))
                return false;
            else                                                // otherwise, reset to 0 and try more numbers
                temp[row][col] = 0;
        }
    }

    // no numbers worked for that spot, keep trying to look for more possibilities before
    return true;
}

/**************** is_puzzle_valid ****************/
/*
 * Checks if the given 9x9 sudoku puzzle is valid by checking each row, column,
 * and box for duplicate and invalid numbers (0 <= num <= 9).
 * Caller must provide a valid pointer to an int[9][9] containing the puzzle.
 * 0 indicate empty nums.
 * Returns true if puzzle is valid, else false.
 */
static bool is_puzzle_valid(int puzzle[9][9])
{
    // iterate over every num
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (puzzle[i][j] < 0 || puzzle[i][j] > 9) return false;             // check bounds
            if (puzzle[i][j] == 0) continue;                                    // skip if 0
            
            // check rows (starting from current index only)
            for (int ri = i + 1; ri < 9; ri++)
                if (puzzle[i][j] == puzzle[ri][j]) return false;

            // check cols (starting from current index only)
            for (int ci = j + 1; ci < 9; ci++)
                if (puzzle[i][j] == puzzle[i][ci]) return false;

            // check box (starting from current index only)
            int end_row = i - (i % 3) + 2;
            int end_col = j - (j % 3) + 2;
            for (int ri = i; ri <= end_row; ri++) {                             // start iterating from current row
                for (int ci = end_col - 2; ci <= end_col; ci++) {               // start iterating from first column of every box
                    if (ri == i && ci == end_col - 2) {                         // if at beginning of loop, set pos to num's curr index
                        ci = j;
                        continue;
                    }
                    if (puzzle[i][j] == puzzle[ri][ci]) return false;
                }
            }
        }
    }

    // return true if no duplicates/invalid nums found
    return true;
}

/**************** is_num_valid ****************/
/*
 * Checks if a given value would be valid at [row, col] in the given puzzle by
 * checking for duplicates in its row, column, and box.
 * Assumes the actual num at [row, col] is currently != val.
 * Caller provides a valid int[9][9] pointer containing the puzzle, the row and
 * column indices of the number, and the value itself.
 * Returns true if the num is valid, i.e. no duplicates, or if the num <= 0.
 * Returns false if the num is invalid, i.e. duplicates were found.
 */
static bool is_num_valid(int array[9][9], int row, int col, int val)
{
    // return true if num <= 0
    if (val <= 0) return true;

    // find the starting column and row of the box
    int start_row = row - (row % 3);
    int start_col = col - (col % 3);

    // iterate over every num in row, column, and box
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // return false if any num in row, col, or box matches val.
            if (array[i + start_row][j + start_col] == val ||   // if num in box matches val
                array[row][i * 3 + j] == val ||                 // if num in row matches val
                array[i * 3 + j][col] == val)                   // if num in col matches val
                return false;
        }
    }

    // return true if nothing matches, therefore num is valid.
    return true; 
}


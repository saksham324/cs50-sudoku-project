# Implementation Spec

## Data structures

Each 9x9 sudoku is represented with a "2 dimensional" 9x9 integer array:
`int puzzle[9][9]`. The first index represents the row, and the second represents the
column. Thus each number is contained in its respective
`puzzle[row_index][column_index]`.

All sudokus are always declared on the stack and not the heap. This is because
the size of the puzzle 2d array is relatively small, and should not cause a
stack overflow on most machines (excluding special cases like embedded systems),
even with multiple puzzle arrays being stored in memory. This seems to be the
simplest, safest, and most efficient choice.

## Main (`sudoku.c`)

`sudoku.c`, contained in the project's top-level directory, is the main driver
of the program that parses command line arguments and initializes other modules.

- Check number of command line arguments via the given argument `int argc`.
    - Exit if not == 2.
- Check argument given to `sudoku` contained in `char *argv[]` at index 1. Use
  `strcmp`.
    - If equals "create", initialize creator by calling `sudoku_create`.
    - Else if equals "solve", initialize solver by calling `sudoku_solve`.
    - Else, print error and exit.

## Creator

Create a random 9x9 sudoku puzzle with at least 40 missing numbers and a
unique solution. Each columnn is separated with a single space and each row with
a newline. Missing numbers are represented with '0'.

Implemented in `creator.c` contained in the `creator` directory. `creator.h`
exports the following function:

```C
/**************** sudoku_create ****************/
/*
 * This function is called by program execution if "create" was called. It
 * takes in no parameters and does not return anything. It simply creates a
 * puzzle guaranteed to have a unique solution and prints it to stdout.
 */
void sudoku_create(void);
```

### `sudoku_create`

Prototype: `void sudoku_create(void)`

Essentially the main function exposed to other programs. Initializes other
modules and facilitates control flow.

- Initial setup:
    - Define a 9x9 2d int array to store the sudoku puzzle and initialize it to
      a solved and valid template sudoku.
    - Seed `rand` by calling `srand` and passing in the current time
      (`time(0)`).
- Randomly shuffle the template puzzle while still maintaining the sudoku's
  validity by calling the `shuffle` function with the puzzle as an argument.
- Remove a minimum of 40 numbers from the puzzle while making sure that the
  sudoku has a unique solution by calling `remove_nums` with the puzzle as an
  argument.
- Print the sudoku in the correct format by calling `print_sudoku` in the common
  module with the puzzle as an argument.

### `shuffle`

Prototype: `static void shuffle(int puzzle[9][9])`

Randomly shuffles the given sudoku puzzle while maintaing its validity.
Caller must provide a valid pointer to an `int[9][9]` containing the puzzle.
Directly edits the given puzzle.

The basic idea behind the shuffling function so that it does not violate sudoku
rules is to shuffle rows and columns while maintaining the integrity for each
3x3 box. This is achieved by first shuffling the 3x3 boxes by treating the 9x9
grid as a 3x3 grid composed of sub-grids. Then, shuffling the actual rows and
columns for each 3x3 grid.

The function first computes the new position for each row and each column using
the algorithm described above, storing it in int arrays. Then, the function
re-orients the actual puzzle according to the new, shuffled row and column
indices.

The following pseudocode is followed for generating an int array storing the
new, shuffled indices of a row/column:

- Generate a random permutation of positions three objects (0, 1, 2) can be
  arranged in using `get_rand_orientation` and passing in an int array of length
  3, each int storing the respective object's position.
- Iterate over every int element in generated array:
    - Again call `get_rand_orientation` to generate a new array of randomized
      positions.
    - Iterate over every int element in generated array:
        - Set the new position of the row/column to `outer_arr[outer_iterator] *
          3 + inner_arr[inner_iterator]`.

Repeat the above psuedocode twice to obtain two int arrays containing shuffled
indices as desired. Then, re-orient the actual puzzle according the new
positions of rows and columns using the following pseudocode:

- Copy puzzle to a temporary puzzle 2d array using `copy_puzzle`.
- Iterate over every number in the puzzle:
    - Set the value of each number in the original puzzle according to the new
      positions for each row and col using the copied puzzle.

### `remove_nums`

Prototype: `static void remove_nums(int puzzle[9][9])`

Takes in a solved (filled) puzzle and removes at least 40 random numbers so
that there is still only one solution to the puzzle.

After removing at least 40 nums, if it fails to remove a num three times
continuously, it stops and returns.

Caller provides a valid pointer to an int[9][9] containing the puzzle, that
will be edited directly by replacing nums with zeros.

Caller is responsible for seeding rand before calling the function.

- Initial setup:
    - initialize an `int removed_count` to 0 to keep track of number of removed
      items.
    - `int num_failed_tries = 0` to keep track of number of continuously failed
      tries.
- Iterate while the `removed_count <= 65` as 16 is the smallest number of clues
  a sudoku puzzle can have while still having a unique solution.
    - Generate a random row and column index using `rand() % 9` until we find a
      non-empty spot in the puzzle.
    - Temporarily set the value of the number at [row, col] to 0, and store the
      original value in a temp int.
    - Call `unique_solver` with puzzle as an argument and NULL as the second
      argument to obtain then number of solutions returned by it.
    - If the return value is == 1, indicating that the puzzle has a unique
      solution, keep the change in the puzzle, increment `removed_count` and
      reset `num_failed_tries` to 0.
    - Else, the puzzle has no solutions or multiple solutions, thus the change
      must be reverted by setting `puzzle[row][col]` to `temp`.
      `num_failed_tries` is incremented, and if `num_failed_tries == 3 &&
      removed_count >= 40`, break the loop and return.

### `get_rand_orientation`

Prototype: `static void get_rand_orientation(int arr[3])`

Generates a random permutation of positions three objects (0, 1, 2) can be
arranged in. There are six possibilities: {0, 1, 2}, {0, 2, 1}, {1, 0, 2},
{1, 2, 0}, {2, 0, 1}, {2, 1, 0}. The results are stored in the given int array
of length 3.

- Iterate over each of the three int elements in the array using a for loop:
    - Set the element value to a randomly generated int greater equal to 0 and
      less than 3 obtained by `rand() % 3`.
    - Iterate over the previous elements in the array using a for loop:
        - If any of the previous elements match the newly generated int, repeat
          outer loop for the same iterator value by decrementing the iterator
          value by 1 in the inner loop.
        - Else, continue.

### `copy_puzzle`

Prototype: `static void copy_puzzle(int og[9][9], int copy[9][9])`

Copies the given puzzle `int[9][9]` to the second given `int[9][9]`.

Caller provides valid pointers to the original and copy arrays.

- Iterate over every element in the puzzle 2d array using a for loop, and set
  the copy 2d array's value to it.

## Solver

Parse and solve a random 9x9 sudoku puzzle from stdin, print the solved puzzle
to stdout, and notify the user if there were no solutions or multiple solutions.
The stdin must follow the format of the output of the Creator module exactly;
otherwise, parsing will fail and an error message will be printed.
(Each columnn is separated with a single space and each row with
a newline. Missing numbers are represented with '0'.)
If the puzzle is not valid before solving (i.e. the given numbers already break
one of the sudoku rules), an error message will be printed and "No solutions."
printed to stdout.

Implemented in `solver.c` contained in the `solver` directory. `solver.h`
exports the following function:

```C
/**************** sudoku_solver ****************/
/*
 * Called by sudoku when solve is the argument passed.
 * It will parse the puzzle from stdin and print the
 * solution, if it finds one. Otherwise, an error
 * message will be printed to stderr instead.
 */
void sudoku_solver(void);
```

### `sudoku_solver`

Prototype: `void sudoku_solver(void)`

Essentially the main function exposed to other programs. Initializes other
modules and facilitates control flow.

- Initial setup:
    - Initialize an empty 9x9 2D array to hold the parsed puzzle
    - Initialize row and col ints to keep track of where you are in the puzzle
    - Initialize an empty char and a bool (init true) to run the parse algorithm
- Begin a while loop which parses digit by digit.
    - If whitespace, ignore whitespace and set bool to true.
    - If char is digit and expect_digit,
        - Put the digit in its location and shift row/col appropriately, and
          break from the program as needed.
    - Else, print error message and stop program.
- If row was not nine,
    - Print an error message saying that not enough numbers were parsed.
- Create an empty 9x9 2D array to hold the solution.
- Call `unique_solver` to solve the puzzle and assign its return value to an
  integer.
- If the return value is 0
    - Print "No solutions found."
- Else,
    - Print the first solution found by `unique_solver`, stored in the solution.
    - If the return value was 2
        - Print "Multiple solutions found."

`unique_solver` is defined in the following module, common.

## Common

The common module holds two functions used by both solver and
creator--`print_sudoku` and `unique_solver`.

Implemented in `common.c` in the `common` directory. `common.h` exports the
following two functions:

```C
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
```

### `print_sudoku`

Prototype: `void print_sudoku(int array[9][9])`

This is literally just a nested for loop which prints the number at the
location with a space separating each number, and a newline following each row.

### `unique_solver`

Prototype: `int unique_solver(int puzzle[9][9], int firstSolution[9][9])`

This `unique_solver` as described in its header comment will solve the puzzle
(if solvable) and place the first solution it finds into the array passed to
it, firstSolution. Before running its algorithm, it will check whether the 
puzzle (as given) is valid or not using `is_puzzle_valid`. If not, it will
exit and print an error message without solving the puzzle.

If the puzzle is valid, it will begin its solving algorithm. The algorithm 
employs a recursive helper function, `unique_solver_helper` as well as a
pointer to an int acting as an accumulator to determine whether or not there
exist multiple solutions to the sudoku puzzle. The algorithm is non-exhaustive,
meaning that it will search for at most 2 possible solutions to the puzzle,
regardless of whether or not there are more. This is because the return code
need only know whether or not there are multiple solutions, not how many
there are. `unique_solver_helper` again employs a helper function,
`is_num_valid` to check whether a potential number would fit at a certain
square of the puzzle.

The algorithm is outlined below:

- Check whether or not the given puzzle is valid using `is_puzzle_valid`.
  If it isn't,
    - return 0 and print error message to stderr.
- If it passes the check, create a temporary 9x9 2D array and copy the original
  puzzle in order to not edit the original puzzle while the algorithm runs,
  since the puzzle may not be fully reverted to its original form while the
  algorithm is running.
- Create an integer to serve as an accumulator.
- Pass in the copy of the puzzle, the pointer to the array for the solution,
  and a reference to the integer accumulator to `unique_solver_helper`.
- Return the integer accumulator's value after running the helper function.

### `unique_solver_helper`

Prototype: `static bool unique_solver_helper(int temp[9][9], int first_solution[9][9], int *num_solutions)`

This is a simple recursive function employing the "_backtracing_" algorithm
described in DESIGN.md. The base case uses the accumulator to determine the next
logical step of the algorithm, and increments the accumulator every time the
base case is reached. The base case is reached when there are no empty spots
left in the sudoku puzzle.

- Initialize two integers, row and col, to 9, and whose vaue will hold the next 
  empty spot after the following for loops.
- Use a nested for loop to iterate over the puzzle, and if the value of the
  puzzle at any [i][j] is 0, then set the row and col to i and j and break
  from the loop.
- If no empty spots were found (row == 9), then increment the accumulator.
    - If the accumulator is == 1, copy the answer to the solution array,
      if possible.
    - If the accumulator is larger than 1, return false.
    - Return true (only reachable when accumulator is 1).
- For the empty spot that was found, iterate over 1-9.
    - Call `is_num_valid` given the puzzle, empty spot row/col, and the number
      to check (1-9).
    - If it's valid, set that spot to the number
        - Call `unique_solver_helper`. If it returns false,
            - return false
        - Otherwise, set the spot to 0 and try the next number in line (1-9).
- At the very end, return true.

This algorithm was largely implemented by Eyasu, and adapted later to find 
multiple solutions if possible.

### `is_puzzle_valid`

Prototype: `static bool is_puzzle_valid(int puzzle[9][9])`

Given a puzzle, check whether there are any repeating numbers in any single
column, row, or 3x3 grid (each 3x3 grid mutually exclusive). It's late and
I have to turn this in and the code is pretty self-explanatory so I'll skip
writing the algorithm out. Also, Pratinav wrote this function and it's super
concise and well-written and I don't understand the math behind it. Super
cool implementation though. Apparently it's super efficient too, only checks
numbers which haven't been checked before so we don't double-check (but
I wouldn't know, since Pratinav is asleep after pulling an all-nighter and I'd
rather defer to his wisdom on this function).

### `is_num_valid`

Prototype: `static bool is_num_valid(int array[9][9], int row, int col, int val)`

Checks whether the number given to it and the possible position for it would
produce any rule breaks in the sudoku puzzle. If not, return true. Otherwise,
the number was already found in the given row/column/grid, so return false.
Again, this is really self-explanatory code and Pratinav wrote this one as well
and it uses some wicked math-magic to check each square of the
row/column/grid simultaneously so you should definitely check out the source
code because it's there.

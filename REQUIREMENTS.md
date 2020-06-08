# Requirements

Source: https://www.cs.dartmouth.edu/~cs50/Project/

1. You will invoke your Sudoku program from the command line with one command
line argument and usage must be as follows:
    - `./sudoku create` to create a random Sudoku puzzle
    - `./sudoku solve` to solve a given Sudoku puzzle
2. Sudoku creator must satisfy the following requirements:
    - Create a puzzle that has a unique solution
    - There must be at least 40 missing numbers in the generated puzzle
    - The puzzle must be randomized
    - The puzzle is printed to `stdout`
3. Sudoku solver must satisfy the following requirements:
    - Be able to accept puzzles that have multiple solutions
    - Generate any one possible solution for the given puzzle
    - Must not change any given numbers in the puzzle
    - Should read the puzzle from `stdin` and print the solution to `stdout`.

## Rules

In a valid Sudoku grid every number from 1 to 9 must appear:

- Only once in every row
- Only once in every column
- Only once in every 3x3 squared region

The puzzle is presented as a 9x9 valid grid with some numbers missing. A person
or program solving the Sudoku puzzle should fill in the missing numbers without
violating above mentioned rules. In the above given picture the numbers in red
are filled by a solver.

## Textual representation of the grid

Here is a suggested textual representation for your Sudoku grid to read from
stdin and print to stdout.

- The grid is represented as 9 lines of text
- Each line contains 9 integers that range from 0 to 9, separated by a whitespace
- 0 represents a missing number in the grid

If you wish to use a different textual representation please clearly specify it in your README.md and make sure to use the same format for both creator and solver.

## Documentation

You need to provide the following documentation for your project:

- DESIGN.md: This document should contain an overview of the algorithms that
you use for your Sudoku creator and solver.
- IMPLEMENTATION.md: This document should contain the details of how you
implement the algorithms described in DESIGN.md.
- TESTING.md: This document should contain the details of testing plan to test
each module.
- README.md: This document should contain the details about on how to use the
solver and creator, and the format of their input and output.

## Testing

Having a good testing plan is a key to success of any project. For the Sudoku project you are expected to perform *fuzz testing* for Sudoku solver and *unittesting* for both the creator and solver modules. Regression testing is strongly recommended.

You must create a testing script for your project and also include the output of the testing script in your submission.

## Code organization

There are two modules in this project, Sudoku solver and Sudoku creator. Your code should be organised in such a way that each module specific code should be in the respective directories. If required you must build a separate library of functions that are required by both modules.

## Final presentation

Each team will make a 15 to 20 minute final presentation that is due on Wednesday, June 3rd at 11:59 pm. The team must present the algorithm that they use to create and solve Sudoku puzzles. They should also describe their testing strategy and code organization.

## Extra credit

A possible extra credit is to show the game progress using a graphics software. You are welcome to come up with your own interesting extra credit options.


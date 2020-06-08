# Dartmouth CS50 20Spring, Sudoku Project

Members: Pratinav Bagla, Wendell Wu, Eyasu Lemma

Project video:

https://dartmouth.zoom.us/rec/share/wOMoAanQ609LYafTyF_uWZEjBqTiaaa8hiAervQFmR1lL-aNeCr0IdiPRTDEcT0e?startTime=1591210300000

## Usage

`make` to compile.

`./sudoku [create|solve]` to run the sudoku creator or solver, depending on the argument passed in.

`make clean` to clean up output files.

`make test` to see the result of running our testing script with a default of 3 fuzzqueries.

Where create will create a sudoku puzzle guaranteed to have
 1. a unique solution
 2. 40 or more numbers removed from the puzzle

and solve will
 1. solve any sudoku puzzle passed in to stdin and let the user know whether
   - the input format was invalid
   - there's no solutions
   - there's a unique solution
   - there's multiple solutions
 2. print the solved puzzle (if available) to stdout

The format of the sudoku puzzle must be
 - 9 x 9 grid of singular digits separated by whitespace
 - 0's represent empty squares
 - non-zeroes represent filled squares
 - must already be valid (filled squares should not violate sudoku rules, outlined in REQUIREMENTS.md)

If the input doesn't follow this exact format, it will print an error message.

To enable/disable DEBUG prints, uncomment/comment the DEBUG variable in the each module's respective Makefile.

Please note: piping sudoku create to sudoku solve will not work with debug statements enabled from creator module. Please disable debug flag in the creator module makefile AND sudoku module makefile by commenting it out before attempting to pipe.

## Assumptions about Input

No assumptions about input. All input passed to stdin must follow the outlined format or it will be rejected.

The only argument allowed to the sudoku program are create and solve, all other arguments will be discarded.

## Project Structure

- README.md
- REQUIREMENTS.md
- DESIGN.md
- IMPLEMENTATION.md
- TESTING.md
- COLLABORATING.md (our collaboration and github workflow, for reference)
- STYLEGUIDE.md (how we styled our code, for reference)
- Makefile
- testing.sh
- testing.out
- creator/
- solver/
- common/
- tests/
- sudoku.c

## Dependencies

The sudoku.c main program depends on both creator and solver modules.

Both creator and solver modules rely on common code found in the common module.

Each module has its own Makefile, which is called by the top-level project Makefile. Compilation is handled by the top-level Makefile and so is the default testing script call.

## Error Codes
 1. Incorrect number of arguments
 2. Invalid argument (not create or solve)

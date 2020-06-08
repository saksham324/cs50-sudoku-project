# Design

## User interface

Command line:
```
sudoku [create|solve]
```

## Inputs and Outputs

### Inputs

- Create mode: command line argument.
- Solve mode: command line argument,  puzzle from `stdin`.

### Outputs

- Create mode: new puzzle to `stdout`.
- Solve mode: solved puzzle to `stdout`.

## Functional decomposition into modules

- Creator
- Solver

## Functional Decomposition into Modules
 
1. Main - validate arguments and call appropriate module (wendell)
2. Solver Module - (eyasu, pratinav)
3. Creator Module - (wendell)
    - *creator* - function which creates the 2d unsolved puzzle and uses *puzzlePrinter* to print the puzzle to stdout
4. Common
    - *puzzleLoader* - take a puzzle (solved or unsolved) in from stdin and put it into a 2D array. (0’s represent missing nums) (Eyasu)
    - *puzzlePrinter* take a 2D array and print the puzzle stored inside (wendell)
    -  *solver* - Function which returns true or false depending on if there is one or multiple/no solutions, takes a pointer to the 2d array, and directly edits the items inside(eyasu) (pratinav)
    - *rowCheck* Given a row num, int, and 2D array, check if the number is already on that row. (eyasu)
    - *colCheck* Given a col num, int, and 2D array, check if the number is already on that col. (pratinav)
    - *gridCheck* Given a grid region (1-9 labeled like below), int, and 27x27 2D array, check if the number is already within its 3x3 grid.(wendell)
        - 1 | 2 | 3
        - 4 | 5 | 6
        - 7 | 8 | 9
        - 
        - EACH OF THE ABOVE NUMS IS A 3x3 REGION, NOT A NUMBER ITSELF

The grid is organized into the 2D array like so

Each row is a pointer to an array

Each column is the array itself.

![Diagram](https://beginnersbook.com/wp-content/uploads/2014/01/2D-array-updated.png)

## Pseudocode for logic/algorithm flow

1. Solver
    - For each cell
    - If it is a 0
        - Place it on the stack to backtrace
        - For each num 1-9
            - Check the rules (grid, row, col) for the num.
            - If all 3 rules checks pass
                - Place the num in that spot
2. Creator
    - Start with a valid board
    - Shuffle using a valid shuffle https://stackoverflow.com/questions/6924216/how-to-generate-sudoku-boards-with-unique-solutions/7280517
    - Remove nums at random one by one until more than 1 solution
    - Go back a step and if # removed is < 50, keep removing random nums.
    - Once we hit 50 removed, this is the valid sudoku solution
## Testing

Test invalid parameters
Test creator
Test solver using non-unique solutions
Test solver using unique solutions


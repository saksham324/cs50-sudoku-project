# Style Guide

This document defines a common coding style for the project.

In addition to this, there are some useful tips in the [course style guide](https://www.cs.dartmouth.edu/~cs50/Resources/CodingStyle.html).
However, remember that this document will always supersede it.

In case of any ambiguity or confusion, please emulate the code snippets as
closely as possible.

## Indentation and spacing

- Indentation: four spaces.
- Maximum line length: 80 columns.

## Naming variables and functions

Use snake case.

```c
void example_function(int first_arg, int second_arg);
char this_is_a_var;
```

## Functions

- Opening curly brace on the next line of function signature.
- No space between function identifier and opening parenthesis.

```c
int main(int argc, char *argv[])
{
    ...
}
```

## Conditionals, Loops etc.

- Opening curly brace on the same line with a space preceding it.
- One space before opening parenthesis.

```c
if (condition) {
    ...
}
```

```c
for (int x = 0; x < 10; x++) {
    ...
}
```

## Comments

- Do not over or undercomment: comment when something needs to be explained or
  clarified, or when you think necessary.
- Have informative beginning-of-file and beginning-of-function comments.

```c
/*
 * solver.c - The solver module takes a...
 * and does...
 *
 * Author, 2020
 */
```

```c
/**************** example_function ****************/
/*
 * Does...
 * Returns x if successful.
 * Returns NULL if error.
 * Caller is responsible for freeing...
 * Does not work if...
 */
```

```c
/**************** another_function ****************/
/* See somefile.h for documentation. */
```

- There should always be a space after the beginning (`//` or `/*`) of a comment.
    ```
    /* example comment */
    // example comment
    ```
- **Paragraph comments:** a small comment at the beginning of a logical section
  describing what it does may be useful.
- **End-of-line comments:** a short comment to clarify unclear code or call
  attention to nuances in the code. As the course webpage recommends, do not
  overdo it. Align the comments within a function to begin in the same column.

```c
int example_function()
{
    for (int x = 0; x < 10; x++) {
        f += arr[x];            // Explain something unclear. Notice alignment.
    }
    return (f - 32) * 9/5;      // Convert fahrenheit to celsius using formula.
}
```


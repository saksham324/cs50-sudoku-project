# Collaborating

Project status, TODOs, and responsibilities are in `TODO.md`.

For code, please follow the style guide defined in `STYLEGUIDE.md`.

## Git

We will use git to manage our project. [This][1] is a great resource for
understanding git's underlying model.

We will use [GitHub Flow][2], a branch-based workflow. Basically, create a new
branch for each module/feature, and send in a pull request once you are done.
This will ensure that every change is discussed and reviewed before being
finalized.

Each commit should ideally
address a specific change and the commit message should be clear, concise, and
informative (should also include the names of the files/modules addressed). For
example, `creator.c: fix segmentation fault in main`. Commit messages are also
generally written in the imperative.

Please remember to `git pull` before starting work and `git push` after
you are done. In case of any conflicts or issues,
please send in a pull request so that the team can review.

## Data Files

If generating files for tests etc. please store them in a directory prefixed
with `data`. For example `data-tests-1`, `data-random`, `data3` etc. This will
be ignored by git as per the `.gitignore` and prevent it from being tracked and
uploaded to the remote.

[1]: https://missing.csail.mit.edu/2020/version-control/
[2]: https://guides.github.com/introduction/flow/


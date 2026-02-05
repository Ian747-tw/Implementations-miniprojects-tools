# Instructions

This repository is for the decision tree homework described in the user prompt.

## Goals
- Implement the decision tree learner that reads LIBSVM-format data and emits C/C++ code for `int tree_predict(double *attr);`.
- Support the `tree` executable interface: `./tree <data-file> <epsilon>`.
- Follow the assignment’s requirements on threshold selection, tree output, and evaluation tasks.

## Expected deliverables
- Source code for the learner (and any helpers) that builds a binary decision tree for numerical features.
- The generated C/C++ prediction function printed to stdout, matching the required signature and style.
- Any documentation or notes requested by the assignment (data structures, example dataset, etc.).

## Constraints and conventions
- Use ASCII in all files unless the existing file uses Unicode.
- Keep code simple and readable; add brief comments only for non-obvious logic.
- Avoid extra dependencies or build tools unless explicitly requested.
- Prefer `rg` for searching in the repo.

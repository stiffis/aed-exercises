# AED Exercises

![C++](https://img.shields.io/badge/language-C%2B%2B17-blue.svg)
![Status](https://img.shields.io/badge/status-learning-informational.svg)
![License](https://img.shields.io/badge/license-GPLv2-green.svg)

> Collection of algorithm and data structure exercises for the Algorithms and Data Structures (AED) course. Includes LeetCode style problems, class assignments, and multiple from-scratch implementations.

## Table of Contents

- [Overview](#overview)
- [Repository Structure](#repository-structure)
- [Requirements](#requirements)
- [Quick Start](#quick-start)
- [Topics Covered](#topics-covered)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

## Overview

This repository gathers C++ solutions used to practice algorithms and data structures. You will find worked examples, personal experiments, evaluation material, and reference implementations of classic structures.

## Repository Structure

| Path                                                                           | Description                                                           |
| ------------------------------------------------------------------------------ | --------------------------------------------------------------------- |
| `arrayExercises/`                                                              | Array-focused problems and warm-up algorithms (LeetCode inspired).    |
| `EC*/`                                                                         | Short evaluations from the course (for example `EC1`, `EC7`, `EC11`). |
| `REC/`, `Partial/`                                                             | Review sessions, partial exams, and complementary exercises.          |
| `LinkedListTask/`, `IteratorsQuest/`                                           | Linked list variants and custom iterator implementations.             |
| `bstImplementation/`, `btree/`, `bTreeImplementation/`, `proyectRedBlackTree/` | Binary search trees, B-Trees, and Red-Black Tree projects.            |
| `HashImplementation/`, `dictionariesTask/`                                     | Hash tables and dictionary-based structures.                          |
| `graphImplementation/`                                                         | Graph abstractions and traversal utilities.                           |
| `sparseMatrixImplementation/`                                                  | Sparse matrix algorithms and helpers.                                 |
| `TrainStringMatching/`, `stringMatching.md`                                    | String matching practice sets and notes.                              |
| Miscellaneous files (`backtracking.cpp`, `btree.md`, etc.)                     | One-off exercises or in-class guides.                                 |

> Several directories contain compiled binaries (`main`, `main.exe`). Remove them after compiling to keep the tree tidy.

## Requirements

- C++ compiler with C++17 support (GCC, Clang, or MSVC).
- C++ standard library.
- Optional: build tooling such as `cmake` or `make` if you prefer custom build scripts.

## Quick Start

1. Clone the repository:
   ```bash
   git clone https://github.com/stiffis/aed-exercises.git
   cd aed-exercises
   ```
2. Enter the folder that contains the exercise you want to run:
   ```bash
   cd arrayExercises
   ```
3. Compile and execute the desired source file:
   ```bash
   g++ containsDuplicate.cpp -std=c++17 -O2 -o containsDuplicate
   ./containsDuplicate
   ```
   > Adjust compiler flags or the C++ standard as required by each exercise.

## Topics Covered

- Arrays and strings
- Linked lists and dynamic structures
- Binary search trees, B-Trees, and Red-Black Trees
- Hash tables and dictionary ADTs
- Graphs, traversals, and shortest paths
- Recursion, backtracking, and dynamic programming
- String matching algorithms and advanced data structures (sparse matrices, disjoint sets, etc.)

## Contributing

Contributions are welcome! You can add new exercises, propose alternative solutions, or suggest documentation improvements.

Recommended workflow:

1. Fork this repository.
2. Create a feature branch: `git checkout -b feature/new-solution`.
3. Commit and push your changes: `git commit -m "Add new solution"` followed by `git push origin feature/new-solution`.
4. Open a pull request describing your changes, test results, and any relevant notes.

## License

This project is distributed under the **GNU GPL v2**. Refer to `LICENSE` for the full terms.

## Contact

Questions or suggestions? Open an issue or email [steve.ildefonso@utec.edu.pe](mailto:steve.ildefonso@utec.edu.pe).

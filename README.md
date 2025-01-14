# Computer Architecture Projects - C211

This repository contains a collection of programs written in C, showcasing concepts and implementations related to computer architecture. Each folder focuses on a distinct topic within the subject.

## Folder Structure

### 1. Data Structures Implementation
This folder contains programs that implement various data structures and algorithms in C:
- **`balance.c`**: Implements an algorithm to balance parentheses in a given expression.
- **`list.c`**: Demonstrates the use of linked lists, including basic operations such as insertion, deletion, and traversal.
- **`rot13.c`**: Encodes a given input string using the ROT13 cipher, commonly used for text obfuscation.
- **`sorta.c`**: Contains a sorting algorithm to organize data in ascending or descending order.

### 2. Logic Circuit
This folder focuses on simulating logic circuits:
- **`truthtable.c`**: Generates truth tables for given logical expressions or circuits, illustrating the behavior of combinational logic.

### 3. Manipulating Matrices
This folder includes programs related to matrix operations and applications:
- **`estimate.c`**: Implements a simple machine learning algorithm using "one-shot learning." This program estimates house prices based on attributes such as the number of rooms, bathrooms, and square footage. The algorithm learns from training data presented in matrix form.

## How to Use
To compile and run any of the programs:
1. Use the `gcc` compiler to compile the program:
   ```bash
   gcc -o program_name file_name.c

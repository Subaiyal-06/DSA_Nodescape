# DSA NodeScape

**CT-159 Data Structures and Algorithms** | BSCS (F), Fall 2026
NED University of Engineering & Technology, Karachi

A menu-driven console program in C++ that implements the main data structures of the course from scratch and shows the result of every operation on the screen.

## Group Members

| S.No | Name | Roll No | Modules |
|------|------|---------|---------|
| 1 | Syed Abdullah Hussain (Group Lead) | CT-25283 | Main menu, AVL Tree, Time Complexity |
| 2 | Muhammad Subaiyal | CT-25270 | Singly, Doubly and Circular Linked List |
| 3 | Muhammad Ali Ahad | CT-25269 | Stack, Queue, Array ADT |
| 4 | Muhammad Arib | CT-25273 | Binary Tree, Binary Search Tree |

**Repository link:** (https://github.com/Subaiyal-06/DSA_Nodescape)

## Features

1. Singly Linked List: insert (front, end, position), delete, search, reverse
2. Doubly Linked List: insert, delete, forward and backward display
3. Circular Linked List: insert, delete, search
4. Stack: array and linked version, bracket checker
5. Queue: circular array and linked version
6. Array ADT: insert, delete, update, linear search, binary search, bubble sort
7. Binary Tree: level-order insert, four traversals, height, node and leaf count
8. Binary Search Tree: insert, search, delete, min and max
9. AVL Tree: insert and delete with LL, RR, LR and RL rotations
10. Time Complexity: complexity table and a live step counter

## Rules followed

- One source file (`main.cpp`) and only the `<iostream>` header
- No STL containers (no vector, string or algorithm)
- Classes with constructors and destructors, no structs
- Inheritance and virtual functions for the tree family (`Tree` -> `BinaryTree`, `BST` -> `AVLTree`)

## How to compile and run

Requires g++ (MinGW / MSYS2 on Windows) with C++17.

```
g++ -std=c++17 main.cpp -o DSA_NodeScape.exe
.\DSA_NodeScape.exe
```

Type a number from 1 to 10 to open a module. Type 0 to go back or to exit.

## Sample output

```
DSA NodeScape
 1. Singly Linked List
 2. Doubly Linked List
 ...
10. Time Complexity
 0. Exit
Choice: 10
Time Complexity
1. Complexity table
2. Live demo
0. Back
Choice: 2
Enter n (1 to 2000): 1000

Worst case steps for n = 1000:
Linear search  O(n)     : 1000 comparisons
Binary search  O(log n) : 10 comparisons
Bubble sort    O(n^2)   : 499500 comparisons
```

## Time complexity summary

| Structure | Search | Insert | Delete |
|-----------|--------|--------|--------|
| Array | O(n) | O(n) | O(n) |
| Singly / Doubly / Circular list | O(n) | O(1) at front (ends for doubly) | O(1) at front (ends for doubly) |
| Stack, Queue | O(n) | O(1) | O(1) |
| BST (average / worst) | O(log n) / O(n) | O(log n) / O(n) | O(log n) / O(n) |
| AVL tree | O(log n) | O(log n) | O(log n) |

## Repository contents

- `main.cpp` - complete source code (the author of each part is written in the comments)
- `docs/` - project report (6 pages) and code explanation
- `README.md` - this file

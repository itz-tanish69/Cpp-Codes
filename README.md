# C++ Data Structures

Standalone C++ examples for learning and comparing binary trees, binary search trees, and AVL trees. Each program demonstrates common tree operations through a simple console interface.

## Implementations

| Structure | Insertion | Deletion | Duplicate values |
|---|---|---|---|
| [Binary Tree](DSA/Binary_Tree/binary_tree.cpp) | Fills the next open position in level order | Replaces the first level-order match with the deepest, rightmost node | Allowed |
| [Binary Search Tree](DSA/BST/bst.cpp) | Places values according to BST ordering | Uses standard BST deletion, including the inorder successor for a node with two children | Ignored |
| [AVL Tree](DSA/AVL/avl_tree.cpp) | Uses BST ordering and rotates to stay height-balanced | Deletes as a BST, then rebalances the affected path | Ignored |

## Operations

All three programs include:

- Insertion, search, and deletion
- Inorder, preorder, postorder, and level-order traversals
- Height, total node count, and leaf node count
- Minimum and maximum value lookup

The Binary Tree is not ordered, so its minimum and maximum are found by examining the whole tree. The BST and AVL Tree use their ordering to find them.

## Repository layout

```
DSA/
├── AVL/
│   └── avl_tree.cpp
├── Binary_Tree/
│   └── binary_tree.cpp
└── BST/
    └── bst.cpp
```

## Build and run

Use a GNU-compatible C++17 compiler such as `g++`. The examples use the GCC header `bits/stdc++.h`.

Compile and run one program at a time from the repository root:

```sh
# Binary Tree
g++ -std=c++17 DSA/Binary_Tree/binary_tree.cpp -o binary_tree
./binary_tree

# Binary Search Tree
g++ -std=c++17 DSA/BST/bst.cpp -o bst
./bst

# AVL Tree
g++ -std=c++17 DSA/AVL/avl_tree.cpp -o avl_tree
./avl_tree
```

On Windows, run the generated executable with its `.exe` name, for example `.\binary_tree.exe`.

Each program asks for the number of values, the values to insert, a search key, and a deletion key. For example:

```text
5
30 20 40 10 25
25
20
```

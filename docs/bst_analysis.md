# Binary Search Tree Analysis

## Core operations

Students should analyze the following BST operations:

- insertion;
- search;
- deletion;
- traversal;
- minimum/maximum lookup;
- subtree height.

## Required discussion

Provide a short analysis comparing the complexity of the following operations:

- best-case vs. worst-case behavior;
- average-case behavior for a balanced BST;
- worst-case behavior for a skewed tree;
- recursive vs. iterative implementations;
- how tree height affects search cost.

## Expected Big-O summary

Students should identify the Big-Oh complexity for:

- `insert`
- `search`
- `remove`
- `inorderTraversal`
- `height`

For a balanced binary search tree, expected operations are near O(log n), while a degenerate tree can degrade to O(n).

insertion is O(log n) in a balanced tree and O(n) in a skewed tree. Best case is O(1) when inserting at the root. Worst case is O(n) when tree is skewed.

search is O(log n) in a balanced tree and O(n) in a skewed tree. Best case is O(1) when tree == empty or the root is == value we are searching. Worst case is O(n) when tree is skewed.

remove is O(log n) in a balanced tree and O(n) in a skewed tree. Best case O(1) when removing root. Worst case is O(n) when tree is skewed.

Traversal is O(n) no matter which part of the Euler Tour we do (preorder, inorder, postorder).

Height is O(n) regardless of wheter its a skewed tree or a balanced tree.

minimum/maximum lookup is O(log n) in a balanced tree and O(n) in a skewed tree.

Recursion uses the call stack which saves some data like variables and the parameters passed through the function. This causes it to use O(h) auxillery space, while looking into the call stack, it seems that it uses Call stack-space which is a part of Auxillery space. The call stack is then 'unwound' till it reaches the original / first function call (through a process called "stack unwinding") where then it resumes the program.

Iterative functions in BST are generally O(1) auxillery space.

Tree height effects cost as in a heavily skewed BST, that only has increasing values, all the nodes as visited when finding the maximum as it has to keep going right until it gets to a leaf node / end of the tree. While is a balanced BST, only one 'path' is visited, meaning its O(log n).

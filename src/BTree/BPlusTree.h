#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include "TreeNode.h"  // Make sure TreeNode is defined in this file or included here.

/*
Template Parameters:
- T:     The key type (must support comparison operators)
- Data:  The value type associated with each key (stored in leaf nodes)
- CHILDREN: The maximum number of child pointers per internal node (defines the tree's order/degree)

Key Properties:
- All (key, value) pairs are stored in the leaf nodes
- Internal nodes contain only keys to guide search paths
- Supports logarithmic-time insertion and search

Public Interface:
- BPlusTree(): Constructor initializes an empty tree
- insert(T key, Data value): Inserts a key-value pair into the tree
    - Handles splitting of leaf and internal nodes as needed
- Data* search(T key): Searches for the given key
    - Returns a pointer to the associated value if found, otherwise nullptr
- void display(): Prints the structure of the tree using level-order (BFS) traversal
*/
template <typename T, typename Data, int CHILDREN>
class BPlusTree {
private:
    using Node = TreeNode<T, Data, CHILDREN>;
    Node* root;

public:
    BPlusTree();

    void insert(T key, Data value);
    Data* search(T key);
    void display();
};

#include "BPlusTree.tpp"

#endif
#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include "TreeNode.h"  // Make sure TreeNode is defined in this file or included here.

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
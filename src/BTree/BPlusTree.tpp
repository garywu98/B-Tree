#include <iostream>
#include <vector>
#include <queue>
#include "BPlusTree.h"

template <typename T, typename Data, int CHILDREN>
BPlusTree<T, Data, CHILDREN>::BPlusTree() {
    root = new Node(true);  // root is initially a leaf
}

template <typename T, typename Data, int CHILDREN>
void BPlusTree<T, Data, CHILDREN>::insert(T key, Data value) {
    std::cout << "INSERTING " << key << "\n";
    Node* node = root;
    std::vector<Node*> path;

    // Traverse to leaf
    while (!node->isLeaf) {
        path.push_back(node);
        int i = 0;
        while (i < node->numKeys && key >= node->keys[i]) {
            ++i;
        }
        node = node->children[i];
    }

    // Insert in leaf
    int i = node->numKeys - 1;
    while (i >= 0 && node->keys[i] > key) {
        node->keys[i + 1] = node->keys[i];
        node->values[i + 1] = node->values[i];
        --i;
    }
    node->keys[i + 1] = key;
    node->values[i + 1] = value;
    ++node->numKeys;

    // Split if needed
    if (node->numKeys == CHILDREN) {
        int mid = CHILDREN / 2;
        Node* newLeaf = new Node(true);

        newLeaf->numKeys = CHILDREN - mid;
        for (int j = 0; j < newLeaf->numKeys; ++j) {
            newLeaf->keys[j] = node->keys[mid + j];
            newLeaf->values[j] = node->values[mid + j];
        }

        node->numKeys = mid;
        newLeaf->nextLeaf = node->nextLeaf;
        node->nextLeaf = newLeaf;

        T splitKey = newLeaf->keys[0];

        // Create new root if needed
        if (node == root) {
            Node* newRoot = new Node(false);
            newRoot->keys[0] = splitKey;
            newRoot->children[0] = node;
            newRoot->children[1] = newLeaf;
            newRoot->numKeys = 1;
            root = newRoot;
        } else {
            // Propagate split up
            while (!path.empty()) {
                Node* parent = path.back();
                path.pop_back();

                int insertPos = parent->numKeys;
                while (insertPos > 0 && parent->keys[insertPos - 1] > splitKey) {
                    parent->keys[insertPos] = parent->keys[insertPos - 1];
                    parent->children[insertPos + 1] = parent->children[insertPos];
                    --insertPos;
                }
                parent->keys[insertPos] = splitKey;
                parent->children[insertPos + 1] = newLeaf;
                ++parent->numKeys;

                if (parent->numKeys < CHILDREN) {
                    return;
                }

                // If parent needs to split
                mid = CHILDREN / 2;
                Node* newInternal = new Node(false);
                newInternal->numKeys = CHILDREN - mid - 1;

                for (int j = 0; j < newInternal->numKeys; ++j) {
                    newInternal->keys[j] = parent->keys[mid + 1 + j];
                }
                for (int j = 0; j <= newInternal->numKeys; ++j) {
                    newInternal->children[j] = parent->children[mid + 1 + j];
                }

                splitKey = parent->keys[mid];
                parent->numKeys = mid;
                newLeaf = newInternal;

                if (parent == root) {
                    Node* newRoot = new Node(false);
                    newRoot->keys[0] = splitKey;
                    newRoot->children[0] = parent;
                    newRoot->children[1] = newLeaf;
                    newRoot->numKeys = 1;
                    root = newRoot;
                    return;
                }
            }
        }
    }

    std::cout << "INSERTED key = " << key << std::endl;
}

template <typename T, typename Data, int CHILDREN>
Data* BPlusTree<T, Data, CHILDREN>::search(T key) {
    Node* node = root;
    while (!node->isLeaf) 
    {
        int i = 0;
        while (i < node->numKeys && key >= node->keys[i]) 
        {   
            i++;
        }

        node = node->children[i];
    }

    for (int i = 0; i < node->numKeys; ++i) 
    {
        if (node->keys[i] == key)
        {
            return &node->values[i];
        }
    }
    return nullptr;
}

/*
Utilize BFS to display all nodes in tree
*/
template <typename T, typename Data, int CHILDREN>
void BPlusTree<T, Data, CHILDREN>::display() {
    std::cout << "Display" << "\n";
    std::queue<Node*> q;
    q.push(root);

    while (!q.empty()) 
    {
        int sz = q.size();
        
        for (int i = 0; i < sz; i++)
        {
            Node* currentNode = q.front(); q.pop();
            std::cout << "[";
            for (int j = 0; j < currentNode->numKeys; ++j) 
            {
                std::cout << currentNode->keys[j];
                if (j < currentNode->numKeys - 1) 
                {
                    std::cout << ",";
                }
            }
            std::cout << "]";
            if (!currentNode->isLeaf) 
            {
                for (int j = 0; j <= currentNode->numKeys; ++j) {
                    q.push(currentNode->children[j]);
                }
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

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
    Node* parent = nullptr;
    std::vector<Node*> path;

    // Traverse to leaf
    while (!node->isLeaf) 
    {
        path.push_back(node);
        int i = 0;
        while (i < node->numKeys && key >= node->keys[i]) 
        {
            i++;
        }

        parent = node;
        node = node->children[i];
    }


    // Find insert position
    int i = 0;
    while (i < node->numKeys && key > node->keys[i]) 
    {
        i++;
    }


    // Shift keys and values
    for (int j = node->numKeys; j > i; --j) 
    {
        if (j < CHILDREN - 1) {
            node->keys[j] = node->keys[j - 1];
            node->values[j] = node->values[j - 1];
        }
    }

    node->keys[i] = key;
    node->values[i] = value;
    node->numKeys++;

    // Split leaf if needed
    if (node->numKeys == CHILDREN) 
    {
        Node* newLeaf = new Node(true);
        int mid = (CHILDREN) / 2;

        newLeaf->numKeys = node->numKeys - mid;
        for (int k = 0; k < newLeaf->numKeys; ++k) 
        {
            newLeaf->keys[k] = node->keys[mid + k];
            newLeaf->values[k] = node->values[mid + k];
        }

        node->numKeys = mid;
        newLeaf->nextLeaf = node->nextLeaf;
        node->nextLeaf = newLeaf;

        T splitKey = newLeaf->keys[0];

        if (node == root) 
        {
            Node* newRoot = new Node(false);
            newRoot->keys[0] = splitKey;
            newRoot->children[0] = node;
            newRoot->children[1] = newLeaf;
            newRoot->numKeys = 1;
            root = newRoot;
        } 
        else 
        {
            Node* current = path.back(); path.pop_back();
            int idx = 0;
            while (idx < current->numKeys && splitKey > current->keys[idx]) 
            {
                idx++;
            }

            for (int j = current->numKeys; j > idx; --j) 
            {
                if (j < CHILDREN - 1) current->keys[j] = current->keys[j - 1];
                if (j + 1 < CHILDREN) current->children[j + 1] = current->children[j];
            }

            current->keys[idx] = splitKey;
            current->children[idx + 1] = newLeaf;
            current->numKeys++;
        }
    }

    std::cout << "INSERTED\n";
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
    std::queue<Node*> q;
    q.push(root);

    while (!q.empty()) 
    {
        for(int i = 0; i < q.size(); i++) 
        {
            Node* currentNode = q.front(); q.pop();
            std::cout << "[";
            for (int i = 0; i < currentNode->numKeys; ++i) 
            {
                std::cout << currentNode->keys[i];
                if (i < currentNode->numKeys - 1) 
                {
                    std::cout << ",";
                }
            }
            std::cout << "]";
            if (!currentNode->isLeaf) 
            {
                for (int i = 0; i <= currentNode->numKeys; ++i) 
                {
                    if (currentNode->children[i]) 
                    {
                        q.push(currentNode->children[i]);
                    }
                }
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

#include <iostream>
#include <vector>
#include <queue>
#include "BPlusTree.h"

template <typename T, typename Data, int CHILDREN>
BPlusTree<T, Data, CHILDREN>::BPlusTree() {
    root = new Node(true);  // root is initially a leaf
}

/*
1. Start at the root and traverse down to the appropriate leaf node:
    - At each internal node, choose the child pointer based on the key range
2. Insert the (key, value) pair into the leaf node in sorted order
3. If the leaf has room (less than max keys), insertion is complete
4. If the leaf overflows:
    - Split the leaf into two nodes:
        - Move half the keys to a new leaf node
        - Copy up the **smallest key in the new node** to the parent (not move)
        - Maintain linked leaf structure (next pointer)
5. If the parent node also overflows:
    - Recursively split the parent, pushing keys up the tree
    - This may continue all the way to the root
6. If the root splits:
    - A new root is created with two children, increasing tree height by 1

Note:
- Values are only stored in leaf nodes
- Internal nodes only store keys as separators to guide search
- Leaf splits **copy up**, not push up actual keys and values
*/
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

/*
1. Start at the root node
2. At each internal node, perform a search on keys:
     - If key < keys[i], follow child[i]
     - If key >= all keys, follow the rightmost child
3. Repeat until reaching a leaf node
4. In the leaf node, search for the exact key among its keys
     - If found, return node
     - If not found, return nullptr

Note: Only leaf nodes store actual values; internal nodes only guide the path
*/
template <typename T, typename Data, int CHILDREN>
Data* BPlusTree<T, Data, CHILDREN>::search(T key) {
    Node* node = root;
    while (!node->isLeaf) 
    {
        int i = 0;
        while (i < node->numKeys && key >= node->keys[i]) 
        {   
            ++i;
        }

        node = node->children[i];
    }

    for (int i = 0; i < node->numKeys; ++i) 
    {
        if (node->keys[i] == key)
        {
            std::cout << &node->values[i] << std::endl;
            return &node->values[i];
        }
    }
    return nullptr;
}

/*
Utilize BFS to display all nodes in tree
1. Start by pushing the root node into the queue
2. For each node in the queue (current size of queue = number of nodes in that level):
    - Print its keys (without values if internal)
    - Enqueue its children (if internal node)

Example Output:
[15]
[5,10] [15,20,25]
(Where first line is root, second line are its children)
*/
template <typename T, typename Data, int CHILDREN>
void BPlusTree<T, Data, CHILDREN>::display() {
    std::cout << "Displaying BTree" << std::endl;
    std::queue<Node*> queue;
    queue.push(root);

    while (!queue.empty()) 
    {
        int level = queue.size();
        
        for (int i = 0; i < level; i++)
        {
            Node* currentNode = queue.front(); queue.pop();
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
                for (int j = 0; j <= currentNode->numKeys; ++j) 
                {
                    queue.push(currentNode->children[j]);
                }
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

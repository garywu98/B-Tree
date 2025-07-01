#include <iostream>
#include <vector>
#include <queue>

/*
* Each node can have at most n children
* Each node can have at most n-1 keys
    EX: Keys: [10 | 20 | 30]
        Chilren: [<10 | 10-20 | 20-30 | >30]
* Each node is linked to the next leaf node for fast range queries.
* Keys is the key in which we search for, should be sorted, and determines where it is placed in the tree
*/

template <typename T, typename Data, int CHILDREN>
class TreeNode
{
private:
    T keys[CHILDREN - 1];
    TreeNode* children[CHILDREN];
    TreeNode* nextLeaf;
    Data values[CHILDREN - 1];
    int numKeys;
    bool isLeaf;


    TreeNode(bool isLeaf) : numKeys(0), isLeaf(isLeaf), nextLeaf(nullptr)
    {
        std::fill(children, children + CHILDREN, nullptr);
    }
};

template <typename T, typename Data, int CHILDREN>
class BPlusTree {
private:
    using Node = TreeNode<T, Data, CHILDREN>;
    Node* root;

public:
    BPlusTree() {
        root = new Node(true);
    }

    void insert(T key, Data value);
    Data* search(T key);
    void display();
};

template <typename T, typename Data, int CHILDREN>
void BPlusTree<T, Data, CHILDREN>::insert(T key, Data value) {
    Node* node = root;
    Node* parent = nullptr;
    vector<Node*> path;

    // Traverse to the appropriate leaf
    while (!node->isLeaf) {
        path.push_back(node);
        int i = 0;
        while (i < node->numKeys && key >= node->keys[i]) i++;
        parent = node;
        node = node->children[i];
    }

    // Insert in leaf
    int i = 0;
    while (i < node->numKeys && key > node->keys[i]) i++;

    for (int j = node->numKeys; j > i; --j) {
        node->keys[j] = node->keys[j - 1];
        node->values[j] = node->values[j - 1];
    }
    node->keys[i] = key;
    node->values[i] = value;
    node->numKeys++;

    // Split if needed
    if (node->numKeys == CHILDREN) {
        Node* newLeaf = new Node(true);
        int mid = (CHILDREN - 1) / 2;

        newLeaf->numKeys = node->numKeys - mid;
        for (int i = 0; i < newLeaf->numKeys; ++i) {
            newLeaf->keys[i] = node->keys[mid + i];
            newLeaf->values[i] = node->values[mid + i];
        }

        node->numKeys = mid;
        newLeaf->nextLeaf = node->nextLeaf;
        node->nextLeaf = newLeaf;

        // Propagate up
        T splitKey = newLeaf->keys[0];

        if (node == root) {
            Node* newRoot = new Node(false);
            newRoot->keys[0] = splitKey;
            newRoot->children[0] = node;
            newRoot->children[1] = newLeaf;
            newRoot->numKeys = 1;
            root = newRoot;
        } else {
            // Insertion to internal node (simplified 1-level up logic)
            Node* current = path.back(); path.pop_back();
            int idx = 0;
            while (idx < current->numKeys && splitKey > current->keys[idx]) idx++;

            for (int j = current->numKeys; j > idx; --j) {
                current->keys[j] = current->keys[j - 1];
                current->children[j + 1] = current->children[j];
            }
            current->keys[idx] = splitKey;
            current->children[idx + 1] = newLeaf;
            current->numKeys++;
        }
    }
}

template <typename T, typename Data, int CHILDREN>
Data* BPlusTree<T, Data, CHILDREN>::search(T key) {
    Node* node = root;
    while (!node->isLeaf) {
        int i = 0;
        while (i < node->numKeys && key >= node->keys[i]) i++;
        node = node->children[i];
    }

    for (int i = 0; i < node->numKeys; ++i) {
        if (node->keys[i] == key)
            return &node->values[i];
    }
    return nullptr;
}

template <typename T, typename Data, int CHILDREN>
void BPlusTree<T, Data, CHILDREN>::display() {
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int sz = q.size();
        while (sz--) {
            Node* node = q.front(); q.pop();
            std::cout << "[";
            for (int i = 0; i < node->numKeys; ++i) {
                std::cout << node->keys[i];
                if (i < node->numKeys - 1) std::cout << ",";
            }
            std::cout << "]";
            if (!node->isLeaf) {
                for (int i = 0; i <= node->numKeys; ++i) {
                    if (node->children[i]) q.push(node->children[i]);
                }
            }
            std::cout << " ";
        }
        std::cout << endl;
    }
}

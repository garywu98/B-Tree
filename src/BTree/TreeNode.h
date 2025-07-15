/*
Template Parameters:
- T:     The key type.
- Data:  The value type (only used in leaf nodes).
- CHILDREN: The maximum number of keys per node (defines node capacity).

Node Structure:
- keys[CHILDREN]:
    - Stores up to CHILDREN keys in sorted order.
    - Used for comparisons to guide search and insert logic.
- children[CHILDREN + 1]:
    - Array of pointers to child nodes (used only in internal nodes).
    - Up to CHILDREN + 1 children are needed to support splitting.
- values[CHILDREN]:
    - Stores associated values (used only in leaf nodes).
- nextLeaf:
    - Pointer to the next leaf node in the linked list of leaves.
    - Used to support range queries and fast ordered traversal.
- numKeys:
    - Current number of keys stored in this node.
- isLeaf:
    - True if this is a leaf node (contains values and no children).
    - False if internal node (contains child pointers only).

Constructor:
- TreeNode(bool isLeaf):
    - Initializes all keys and values to default T() and Data().
    - Sets all child pointers to nullptr.
    - Initializes numKeys to 0 and sets isLeaf accordingly.

Note:
Each node can have at most n children
Each node can have at most n-1 keys
    EX: Keys: [10 | 20 | 30]
        Chilren: [<10 | 10-20 | 20-30 | >30]
Each node is linked to the next leaf node for fast range queries.
Keys is the key in which we search for, should be sorted, and determines where it is placed in the tree
*/
template <typename T, typename Data, int CHILDREN>
class TreeNode
{
public:
    T keys[CHILDREN];
    TreeNode* children[CHILDREN + 1];
    TreeNode* nextLeaf;
    Data values[CHILDREN];
    int numKeys;
    bool isLeaf;

    TreeNode(bool isLeaf) : numKeys(0), isLeaf(isLeaf), nextLeaf(nullptr)
    {
        std::fill(keys, keys + CHILDREN, T());
        std::fill(values, values + CHILDREN, Data());
        std::fill(children, children + CHILDREN + 1, nullptr);
    }
};
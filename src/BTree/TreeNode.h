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
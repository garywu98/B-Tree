/*
* Each node can have at most n children
* Each node can have at most n-1 keys
    EX: Keys: [10 | 20 | 30]
        Chilren: [<10 | 10-20 | 20-30 | >30]
* Flag determining if node is a leaf node
* Each internal node has at least ceil(n/2) children
*/
template <typename T, int CHILDREN>
class TreeNode
{
private: 
    T keys[CHILDREN - 1];
    TreeNode* children[CHILDREN];
    int numKeys;
    bool isLeaf;

    TreeNode(bool isLeaf) : numKeys(0), isLeaf(isLeaf)
    {
        std::fill(children, children + CHILDREN, nullptr);
    }
};

class BMinusTree
{
    private:
    public:
};
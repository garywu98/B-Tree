# B-Tree
A B-tree is a self-balancing tree data structure that maintains sorted data and allows searches, sequential access, insertions, and deletions in logarithmic time. It is commonly used in databases and file systems to efficiently manage large blocks of data.

### Key Features
* Multi-way tree: Each node can have multiple children (more than two).
* Balanced: All leaf nodes are at the same depth
* Data in internal and leaf nodes: Keys and values are stored in every node
* Efficient operations: Supports O(log n) time complexity for search, insertion, and deletion
* Minimum and maximum keys per node: Each node (except root) must have at least ceil(m/2)-1 keys and at most m-1 keys, where m is the order of the tree.

### Use Cases
* Database indexing
* Filesystem directory organization
* Disk-based sorted data storage

# B+Tree
A B+ tree is an extension of the B-tree which stores data only at the leaf nodes. Internal nodes only store keys to guide the search. Leaf nodes are linked together, enabling efficient range queries.

### Key Features
* Data only in leaf nodes: Internal nodes store keys but no actual data.
* Linked leaf nodes: Leaf nodes are connected in a linked list for fast sequential access.
* Balanced: All leaves are at the same depth.
* Efficient range queries: The linked leaf nodes allow efficient traversal of ranges.
* Search always reaches a leaf: Ensures consistent data access patterns.

### Use Cases
* Database indexes (primary and secondary)
* Filesystems (e.g., NTFS, HFS+)
* Situations requiring efficient range queries

# Difference
* Historically, B-trees were introduced for database indexing and general balanced tree usage.
* Practically today, almost all modern databases and filesystems use B+ trees, not plain B-trees, because B+ trees are better optimized for disk and range queries.

| Feature            | B-tree                      | B+ tree                     |
| ------------------ | --------------------------- | --------------------------- |
| Data in nodes      | Internal & leaf nodes       | Only leaf nodes             |
| Leaf nodes linked? | No                          | Yes, linked list for leaves |
| Search ends at     | Internal or leaf node       | Always leaf node            |
| Range query speed  | Slower, more complex        | Fast and simple             |
| Usage              | General balanced tree needs | Databases, filesystems      |

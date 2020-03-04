#ifndef BST_CLASS
#define BST_CLASS

class Bst {
public:
    // constructors
    Bst();
    ~Bst();

    // member functions
    std::string insert(int i); // add to tree
    void printTree() const; // prints tree in 3 traversal types
    std::string deleteElem(int i); // delete i from tree
    std::string access(int i) const; // find i in tree, calls getNode

private:
    struct Node {
        Node(int v) : value(v), parent(0), left(0), right(0) {}

        Node* parent;
        int value;
        Node* left;
        Node* right;
    };

    // helper methods
    void clear(Node *n); // recursive helper for destructor
    Node* getNode(int value, Node* n) const; // return node corresponding to value
    std::string insert(int i, Node* n); // helper method for insert

    // printing
    void printPreOrder(Node* n) const;
    void printInOrder(Node* n) const;
    void printPostOrder(Node* n) const;

    // succ and pred for delete
    Node* getPredecessorNode(Node* n) const;
    Node* getSuccessorNode(Node* n) const;
    
    Node* root;
};
#ifndef BST_CLASS
#define BST_CLASS

#include <string>

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
    std::string deleteElem(Node* n);

    // printing
    std::string printPreOrder(Node* n) const;
    std::string printInOrder(Node* n) const;
    std::string printPostOrder(Node* n) const;

    // succ for delete
    Node* getSuccessorNode(Node* n) const;
    
    Node* root;
};

#endif
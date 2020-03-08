#ifndef AVL_CLASS
#define AVL_CLASS

#include <string>

class Avl {
public:
    // constructors
    Avl();
    ~Avl();

    // member functions
    std::string insert(int i); // add to tree
    void printTree() const; // prints tree in 3 traversal types
    void printBfs() const;
    std::string deleteElem(int i); // delete i from tree
    std::string access(int i) const; // find i in tree, calls getNode
    

private:
    struct Node {
        Node(int v) : value(v), parent(0), left(0), right(0), leftHeight(-1), rightHeight(-1) {}

        Node* parent;
        int value;
        int leftHeight;
        int rightHeight;
        Node* left;
        Node* right;
    };

    // helper methods
    void clear(Node *n); // recursive helper for destructor
    Node* getNode(int value, Node* n) const; // return node corresponding to value
    std::string insert(int i, Node* n); // helper method for insert
    std::string deleteElem(int i, Node* n); // helper method for delete

    int getBalance(Node* n) const; // return difference in height of subtrees

    // printing
    std::string printPreOrder(Node* n) const;
    std::string printInOrder(Node* n) const;
    std::string printPostOrder(Node* n) const;
    std::string bfsHelper(Node* n) const;

    // succ for delete
    Node* getSuccessorNode(Node* n) const;

    // rotations
    void leftLeft(Node* n, bool decrement=true);
    void rightRight(Node* n, bool decrement=true);
    void leftRight(Node* n);
    void rightLeft(Node* n);
    
    Node* root;

};

#endif
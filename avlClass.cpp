// avlClass.cpp
// Implements class AvlTree
// Author: Xinyi Zhang, 3/2/2020

#include "avlClass.h"
#include <iostream>
#include <string>
#include <stack>
#include <algorithm> // std::max

// constructors
Avl::Avl() : root(0) {}

Avl::~Avl() {
    clear(root);
}

// access element
std::string Avl::access(int i) const{
    Node* elem = getNode(i, root);

    if (elem == 0) {
        return "Element not found";
    }else {
        return "Element accessed";
    }
}

// print
void Avl::printTree() const {
    if (root == 0) {
        std::cout << "Empty tree" << std::endl;
        return;
    }

    std::cout << printPreOrder(root);
    std::cout << std::endl;
    std::cout << printInOrder(root);
    std::cout << std::endl;
    std::cout << printPostOrder(root);
    std::cout << std::endl;
}

// insert element
std::string Avl::insert(int i) {
    std::string output = "";
    if (root == 0) {
        root = new Node(i);
        output = "Element inserted";
        return output;
    }
    if (getNode(i, root) != 0) {
        return "Element already present";
    }
    return insert(i, root);
}

// delete element
std::string Avl::deleteElem(int i) {
    if (getNode(i, root) == 0) {
        return "Element not found";
    }else {
        return deleteElem(i, root);
    }
}

// HELPER METHODS
// helper for delete
std::string Avl::deleteElem(int i, Node* n) {
    if (i < n->value) {
        deleteElem(i, n->left);
    }else if (i > n->value) {
        deleteElem(i, n->right);
    }else {
        // Case #1: no children
        if (n->left == 0 && n->right == 0) {
            if (n == root) {
                root = 0;
            }else {
                if (n == n->parent->left) {
                    n->parent->left = 0;
                    n->parent->leftHeight--;
                }else {
                    n->parent->right = 0;
                    n->parent->rightHeight--;
                }
            }
            delete n;
        }else if (n->left && n->right == 0) { // Case #2: node has no right child
            if (n == root) {
                n = n->left;
                delete root;
                root = n;
                root->parent = 0;
            }else {
                if (n == n->parent->right) { // if n is parent's right subtree, parent's new right subtree is n's left subtree
                    n->parent->right = n->left;
                    n->parent->rightHeight--;
                }else { // if n is parent's left subtree, parent's new left subtree is n's left subtree
                    n->parent->left = n->left; 
                    n->parent->leftHeight--;
                }

                n->left->parent = n->parent; // either way, n's left subtree's parent becomes n's parent
                delete n;
            }
        }else if (n->left == 0 && n->right) { // Case #3: node has no left child
            if (n == root) {
                n = n->right;
                delete root;
                root = n;
                root->parent = 0;
            }else {
                if (n == n->parent->right) {
                    n->parent->right = n->right;
                    n->parent->rightHeight--;
                }else {
                    n->parent->left = n->right; 
                    n->parent->leftHeight--;
                }

                n->right->parent = n->parent;
                delete n;
            }
        }else { // Case #4: node has 2 children
            Node* successor = getSuccessorNode(n);
            n->value = successor->value;

            deleteElem(successor->value, n->right);
        }
        return "Element deleted";
    }

    // update height of current node
    if (n->parent && n->parent->right == n) {
        n->parent->rightHeight = std::max(n->leftHeight, n->rightHeight) + 1;
    }else if (n->parent && n->parent->left == n){
        n->parent->leftHeight = std::max(n->leftHeight, n->rightHeight) + 1;
    }

    // check unbalance
    if (getBalance(n) > 1) {
        // left-left
        if (getBalance(n->left) > 0) {
            // balance the tree
            leftLeft(n);
        }else if (getBalance(n->left) < 0) { // left-right
            leftRight(n);
        }
    }else if (getBalance(n) < -1) {
        // right-left
        if (getBalance(n->right) > 0) {
            rightLeft(n);
        }else if (getBalance(n->right) < 0) {
            rightRight(n);
        }
    }

    return "Element deleted";
}

// helper for insert, also update subtree height
std::string Avl::insert(int i, Node* n) {
    if (i < n->value) {
        n->leftHeight++; // update heights on way down
        if (n->left) {
            insert(i, n->left);
        }else {
            n->left = new Node(i);
            n->left->parent = n;
        } 
    }else {
        n->rightHeight++;
        if (n->right) {
            insert(i, n->right);
        }else {
            n->right = new Node(i);
            n->right->parent = n;
        }
    }

    // check unbalance
    if (getBalance(n) > 1) {
        // left-left
        if (getBalance(n->left) > 0) {
            // balance the tree
            leftLeft(n);
        }else if (getBalance(n->left) < 0) { // left-right
            leftRight(n);
        }
    }else if (getBalance(n) < -1) {
        // right-left
        if (getBalance(n->right) > 0) {
            rightLeft(n);
        }else if (getBalance(n->right) < 0) {
            rightRight(n);
        }
    }

    return "Element inserted";
}

// recursive helper for destructor
void Avl::clear(Node *n) {
    if (n) { // post-order traversal
	    clear(n->left);
	    clear(n->right);
	    delete n;
    }
}

// helper, returns Node for given value
Avl::Node* Avl::getNode(int value, Node* n) const{
    if (n == 0) {
        return 0;
    }else if (value == n->value) {
        return n;
    }else if (value < n->value) {
        return getNode(value, n->left);
    }else {
        return getNode(value, n->right);
    }
}

Avl::Node* Avl::getSuccessorNode(Node* n) const{
    if (n->right) { // find minimum of right subtree
        n = n->right;
        while (n->left) {
            n = n->left;
        }
    }else { // traverse up tree until node with value greater than target is found
        while (n->parent && n->parent->value < n->value) {
            n = n->parent;
        }

        if (n->parent) {
            n = n->parent;
        }else {
            n = 0;
        }
    }

    return n;
}

// print in order
std::string Avl::printInOrder(Node* n) const {
    std::string output = "";

    if (n == 0) {
        return "";
    }
    
    std::stack<Node*> AvlStack;

    while(!(n == 0 && AvlStack.empty())) {
        // left subtree
        if (n != 0) {
            AvlStack.push(n);
            n = n->left;
        }else {
            n = AvlStack.top();
            AvlStack.pop();

            int value = n->value; // prints root node
            // std::cout << value << " ";
            output = output + std::to_string(value) + " ";
            n = n->right;
        }
    }

    output = output.substr(0, output.length() - 1);
    return output;
}

std::string Avl::printPreOrder(Node* n) const {
    std::string output = "";

    if (n == 0) {
        return output;
    }
    
    std::stack<Node*> AvlStack;
    AvlStack.push(n);
    while(!AvlStack.empty()) {
        // print root node add right child, add left child
        n = AvlStack.top();
        AvlStack.pop();

        int value = n->value;
        output = output + std::to_string(value) + " ";
    
        // add right child to stack
        if (n->right) {
            AvlStack.push(n->right);
        }
        
        // add left child to stack
        if (n->left) {
            AvlStack.push(n->left);
        }
    }

    output = output.substr(0, output.length() - 1);
    return output;
}

std::string Avl::printPostOrder(Node* n) const{
    std::string output = "";
    if (n == 0) {
        return output;
    }
    
    std::stack<Node*> AvlStack;

    do {
        // add right child, add left child
        while (n) {
            if (n->right) {
                AvlStack.push(n->right);
            }
            AvlStack.push(n);

            n = n->left;
        }

        // if on right subtree continuous, go back up
        n = AvlStack.top();
        AvlStack.pop();

        // if popped has a right child and its next on stack
        if (!AvlStack.empty() && n->right && AvlStack.top() == n->right) {
            AvlStack.pop(); // pop right child
            AvlStack.push(n); // push n back on stack
            n = n->right; // set n to right child
        }else {
            output = output + std::to_string(n->value) + " ";
            n = 0;
        }
    } while (!AvlStack.empty());

    output = output.substr(0, output.length() - 1);
    return output;
}

// HELPERS for rebalancing
int Avl::getBalance(Node* n) const {
    return (n->leftHeight) - (n->rightHeight);
}

// right rotation
void Avl::leftLeft(Node* n, bool decrement) {
    Node* z = n;
    Node* y = z->left;

    y->parent = z->parent; // y's parent become z's parent

    // check if z is root node
    if (z->parent == 0) {
        root = y; // set new root to left child of z
    }else {
        Node* temp = z->parent;
        if (z == z->parent->left) { // if z is left child of parent, set left child of parent to y
            z->parent->left = y;
            if (decrement) {
                temp->leftHeight--;
            }

        }else {
            z->parent->right = y;
            if (decrement) {
                temp->rightHeight--;
            }
        }

        while(decrement && temp->parent) {
            if (temp == temp->parent->left) {
                temp->parent->leftHeight--;
            }else {
                temp->parent->rightHeight--;
            }
            temp = temp->parent;
        }
    }

    if (y->right) {
        z->left = y->right; // set z left point to right subtree of y
        z->left->parent = z;
        z->leftHeight = std::max(z->left->leftHeight, z->left->rightHeight) + 1;
    }else {
        z->left = 0;
        z->leftHeight = -1;
    }

    y->right = z; // right subtree of y is set to z
    z->parent = y;

    y->rightHeight = std::max(z->leftHeight, z->rightHeight) + 1;
}

// left rotation
void Avl::rightRight(Node* n, bool decrement) {
    Node* z = n;
    Node* y = z->right;

    y->parent = z->parent; // y's parent become z's parent

    // check if z is root node
    if (z->parent == 0) {
        root = y; // set new root to right child of z
    }else {
        Node* temp = z->parent;
        if (z == z->parent->left) { // if z is left child of parent, set left child of parent to y
            z->parent->left = y;
            if (decrement) {
                temp->leftHeight--;
            }

        }else {
            z->parent->right = y;
            if (decrement) {
                temp->rightHeight--;
            }
        }

        while(decrement && temp->parent) {
            if (temp == temp->parent->left) {
                temp->parent->leftHeight--;
            }else {
                temp->parent->rightHeight--;
            }
            temp = temp->parent;
        }
    }

    if (y->left) {
        z->right = y->left; // set z right point to left subtree of y
        z->right->parent = z;
        z->rightHeight = std::max(z->right->leftHeight, z->right->rightHeight) + 1;
    }else {
        z->right = 0;
        z->rightHeight = -1;
    }

    y->left = z; // right subtree of y is set to z
    z->parent = y;

    y->leftHeight = std::max(z->leftHeight, z->rightHeight) + 1;
}

// left-right rotation
void Avl::leftRight(Node* n) {
    Node* z = n;
    Node* y = z->left;
    rightRight(y);
    leftLeft(z, false);
}

// right-left rotation
void Avl::rightLeft(Node* n) {
    Node* z = n;
    Node* y = z->right;
    leftLeft(y);
    rightRight(z, false);
}


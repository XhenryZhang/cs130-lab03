// bstClass.cpp
// Implements class Bst
// Author: Xinyi Zhang, 3/2/2020

#include "bstClass.h"
#include <iostream>
#include <string>
#include <stack>

// constructors
Bst::Bst() : root(0) {}

Bst::~Bst() {
    clear(root);
}

// access element
std::string Bst::access(int i) const{
    Node* elem = getNode(i, root);

    if (elem == 0) {
        return "Element accessed";
    }else {
        return "Element not found";
    }
}

std::string Bst::insert(int i) {
    std::string output = "";
    if (root == 0) {
        root = new Node(i);
        output = "Element inserted";
        return output;
    }

    return insert(i, root);
}

std::string Bst::deleteElem(int i) {
    return deleteElem(getNode(i, root));
}

std::string Bst::deleteElem(Node* n) {
    if (n == 0) {
        return "Element not found";
    }else {
        // Case #1: no children
        if (n->left == 0 && n->right == 0) {
            if (n == root) {
                root = 0;
            }else {
                if (n == n->parent->left) {
                    n->parent->left = 0;
                }else {
                    n->parent->right = 0;
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
                }else { // if n is parent's left subtree, paren'ts new left subtree is n's left subtree
                    n->parent->left = n->left; 
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
                }else {
                    n->parent->left = n->right; 
                }
                    n->right->parent = n->parent;
                    delete n;
                }
            }

        }else { // Case #4: node has 2 children
            Node* successor = getSuccessorNode(n);
            n->value = successor->value;
            /*
            if (successor->parent->right == sucessor) {

            }
            successor->parent->left = sucessor->right;
            if (successor->right != 0) {
                successor->right->parent = successor->parent;
            }

            delete successor;*/
            deleteElem(successor);
        }

        return "Element deleted";
    }
}

// helper for insert
std::string Bst::insert(int i, Node* n) {
    if (i == n->value) {
        return "Element already present";
    }

    if (i < n->value) {
        if (n->left) {
            return insert(i, n->left);
        }else {
            n->left = new Node(i);
            n->left->parent = n;
            return "Element inserted";
        } 
    }else {
        if (n->right) {
            return insert(i, n->right);
        }else {
            n->right = new Node(i);
            n->right->parent = n;
            return "Element inserted";
        }
    }
}

// recursive helper for destructor
void Bst::clear(Node *n) {
    if (n) { // post-order traversal
	    clear(n->left);
	    clear(n->right);
	    delete n;
    }
}

Node* Bst::getNode(int value, Node* n) const{
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

Node* Bst::getPredecessorNode(Node* n) const{
    if (n->left) { // find maximum of left subtree
        n = n->left;
        while (n->right) {
            n = n->right;
        }
    }else { // traverse up tree until node with value less than target is found
        while (n->parent && n->parent->value > n->value) {
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

Node* Bst::getSuccessorNode(Node* n) const{
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
}

void Bst::printInOrder(Node* n) const {
    if (n == 0) {
        return;
    }
    
    std::stack<Node*> bstStack;

    while(!(n == 0 && bstStack.empty())) {
        // left subtree
        if (n != 0) {
            bstStack.push(n);
            n = n->left;
        }else {
            n = bstStack.pop();
            int value = n->value; // prints root node
            std::cout << value << " ";
            n = n->right;
        }
        // node

        // right subtree
    }
}

void Bst::printPreOrder(Node* n) const {
    if (n == 0) {
        return;
    }
    
    std::stack<Node*> bstStack;
    bstStack.push(n);
    while(!bstStack.empty()) {
        // print root node add right child, add left child
        n = bstStack.pop();
        int value = n->value;
        std::cout << value << " ";

        // add right child to stack
        if (n->right) {
            bstStack.push(n->right);
        }
        
        // add left child to stack
        if (n->left) {
            bstStack.push(n->left);
        }
    }
}

void Bst::printPostOrder(Node* n) const {
    if (n == 0) {
        return;
    }
    
    std::stack<Node*> bstStack;

    while(!bstStack.empty()) {
        // add right child, add left child
        while (n) {
            if (n->right) {
                bstStack.push(n->right);
            }
            bstStack.push(n);

            n = n->left;
        }

        // if on right subtree continuous, go back up
        n = bstStack.pop();

        // if popped has a right child and its next on stack
        if (n->right && bstStack.top() == n->right) {
            bstStack.pop(); // pop right child
            bstStack.push(n); // push n back on stack
            n = n->right; // set n to right child
        }else {
            std::cout << n->value << " ";
            n = 0;
        }
    }
}


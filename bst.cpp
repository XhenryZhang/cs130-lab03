// bst.cpp
// Driver class
// Author: Xinyi Zhang, 3/3/2020

#include "bstClass.h"
#include <iostream>
#include <string>
#include <sstream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: ./bst " << "<string representing sequence of insert, delete, access, print commands to the bst>" << std::endl;
        exit(1);
    }

    std::string input = argv[1];
    input += ",";
    std::string command = "";
    std::string med = "";
    std::string arr[2];
    Bst* myBst = new Bst();

    // parse user input
    for (int i = 0; i < input.size(); i++) {
        if (input[i] != ',') {
            command += input[i];
        }else {
            std::stringstream parser(command);
            int x = 0;
            while(getline(parser, med, ' ')) {
                arr[x] = med;
                x++;
            }

            i++; // skip the next space
            
            // execute command
            if (arr[0] == "insert") {
                std::cout << myBst->insert(std::stoi(arr[1])) << std::endl;
            }else if (arr[0] == "print" && arr[1] == "bfs") {
                myBst->printBfs();
            }else if (arr[0] == "print") {
                myBst->printTree();
            }else if (arr[0] == "access") {
                std::cout << myBst->access(std::stoi(arr[1])) << std::endl;
            }else if (arr[0] == "delete") {
                std::cout << myBst->deleteElem(std::stoi(arr[1])) << std::endl;
            }

            command = "";
            arr[0] = "";
            arr[1] = "";
        }

    }

    delete myBst;

    return 0;
}
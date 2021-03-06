# makefile
CXX=g++
AVL_BINARIES=avl.o avlClass.o
BST_BINARIES=bst.o bstClass.o

all: bst avl

avl: ${AVL_BINARIES}
	${CXX} $^ -o $@

bst: ${BST_BINARIES}
	${CXX} $^ -o $@

avl.o: avl.cpp
	${CXX} $^ -c

avlClass.o: avlClass.cpp
	${CXX} $^ -c

bst.o: bst.cpp
	${CXX} $^ -c

bstClass.o: bstClass.cpp
	${CXX} $^ -c

clean:
	rm -rf *.o avl bst

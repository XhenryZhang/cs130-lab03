# makefile
CXX=g++
AVL_BINARIES=avl.o avlClass.o
BST_BINARIES=bst.o bstClass.o

avl.out: ${AVL_BINARIES}
	${CXX} $^ -o $@

bst.out: ${BST_BINARIES}
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
	rm -rf *.o avl.out bst.out

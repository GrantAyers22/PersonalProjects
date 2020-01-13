//owner Grant Ayers
#ifndef INDEX_H
#define INDEX_H
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "filekey.h"
#include "avltree.h"

using namespace std;

class Index{
public:
    Index(){}
    Index(const Index& rhs) {}
        ~Index() {}
        virtual bool contains(FileKey x)= 0;
        virtual void insert(FileKey x) = 0;
        virtual FileKey find(FileKey & x) = 0;
        virtual void printTree()= 0;
        virtual void makeEmpty() = 0;
        virtual int getNumOfNodes() = 0;
};

class AVLTreeIndex : public Index {
    AVLTree<FileKey> tree = AVLTree<FileKey>();
    bool contains(FileKey x){return tree.contains(x, tree.getRoot());}
    void insert(FileKey x){tree.insert(x, tree.getRoot());}
    FileKey find(FileKey & x){return tree.find(x);}
    void makeEmpty(){tree.makeEmpty(tree.getRoot());}
    int getNumOfNodes(){return tree.getNumOfNodes();}
    void printTree(){tree.printTree();}
};


#endif // INDEX_H

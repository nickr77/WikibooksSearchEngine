#ifndef AVLTREEINTERFACE_H
#define AVLTREEINTERFACE_H
#include "indexinterface.h"
#include "avlnode.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;
class AVLTreeInterface : public IndexInterface
{
private:
    AVLNode* root;
    int heightCounter;

    void insert(string &val, int &num, AVLNode*& t);
    int height(AVLNode *t);
    void rotateWithLeftChild(AVLNode*& k1);
    void rotateWithRightChild(AVLNode*& k1);
    void doubleWithLeftChild(AVLNode*& k3);
    void doubleWithRightChild(AVLNode*& k3);
    void search(string &val, AVLNode *&t);
    void writeIndex(AVLNode *t, ofstream &outputFile);
    void clearIndex(AVLNode *t);

public:
    AVLTreeInterface();

    virtual void insert(std::string &word, int &page);
    virtual void getPages(std::string &entry, std::vector<int> &myList);
    virtual void writeIndex();
    virtual int indexSize();
    virtual void clearIndex();

};

#endif // AVLTREEINTERFACE_H

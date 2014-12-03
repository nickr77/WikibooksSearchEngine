#ifndef AVLNODE_H
#define AVLNODE_H
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;
class AVLNode
{
    friend class AVLTreeInterface;
private:
    std::vector<int> pages;
    std::string element;
    AVLNode *right;
    AVLNode *left;
    int height;
public:
    AVLNode(std::string theElem, AVLNode* L, AVLNode* R, int h);
    void addEntry(std::string &entry, int &id);
    std::string& getEntry();
    void setRight(AVLNode*);
    void setLeft(AVLNode*);
    AVLNode* getRight();
    AVLNode* getLeft();
    int &getHeight();
    void setHeight(int &h);
    void getPages();
};

#endif // AVLNODE_H

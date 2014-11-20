#ifndef AVLNODE_H
#define AVLNODE_H
#include <vector>
#include <string>

class AVLNode
{
private:
    std::vector<int> pages;
    std::string word;
    AVLNode *right;
    AVLNode *left;
    int height;
public:
    AVLNode();
    void addEntry(std::string &entry, int &id);
    std::string& getEntry();
    void setRight(AVLNode*);
    void setLeft(AVLNode*);
    AVLNode* getRight();
    AVLNode* getLeft();
    int &getHeight();
    void setHeight(int &h);
};

#endif // AVLNODE_H

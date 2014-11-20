#include "avlnode.h"
#include <string>
#include <vector>
using namespace std;

AVLNode::AVLNode()
{
    right = nullptr;
    left = nullptr;
    height = 0;
}

void AVLNode::addEntry(string &entry, int &id)
{
    word = entry;
    pages.push_back(id);
}

string& AVLNode::getEntry()
{
    return word;
}

void AVLNode::setLeft(AVLNode *x)
{
    left = x;
}

void AVLNode::setRight(AVLNode *x)
{
    right = x;
}
void AVLNode::setHeight(int &h)
{
    height = h;
}

int& AVLNode::getHeight()
{
    return height;
}

AVLNode* AVLNode::getLeft()
{
    return left;
}

AVLNode* AVLNode::getRight()
{
    return right;
}

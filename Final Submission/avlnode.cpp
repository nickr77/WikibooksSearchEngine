#include "avlnode.h"
#include <string>
#include <vector>
using namespace std;

AVLNode::AVLNode(string theElem, AVLNode* L, AVLNode* R, int h)
{
    element = theElem;
    right = R;
    left = L;
    height = h;
    //cout << "Balls" << endl;
}

void AVLNode::addEntry(string &entry, int &id)
{
    element = entry;
    pages.push_back(id);
    //cout << element << endl;
}

string& AVLNode::getEntry()
{
    return element;
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

void AVLNode::getPages()
{
    for(int i = 0; i < pages.size(); i++)
    {
        cout << pages[i] << endl;
    }
}

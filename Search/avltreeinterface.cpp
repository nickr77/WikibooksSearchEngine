#include "avltreeinterface.h"
#include <algorithm> //for max()
using namespace std;

AVLTreeInterface::AVLTreeInterface()
{
    root = nullptr;
    heightCounter = 0;
}

void AVLTreeInterface::insert(string &entry, int num)
{
    insert(entry, num, root);
}

int AVLTreeInterface::height(AVLNode *t)
{
    if(t == nullptr)
    {
        return -1;
    }
    else
        return t->height;
}

void AVLTreeInterface::insert(string val, int num, AVLNode* &t)
{
    if(t == nullptr)
    {
        t = new AVLNode(val, nullptr,nullptr, heightCounter);
    }
    else if(val < t->element)
    {
        insert(val, num, t->left);
        if(height(t->left) - height(t->right) == 2)
        {
            if(val < t->left->element)
            {
                rotateWithLeftChild(t);
            }
            else
            {
                doubleWithLeftChild(t);
            }
        }
    }
    else if (t->element < val)
    {
        insert(val, num, t->right);
        if(height(t->right) - height(t->left) == 2)
        {
            if(val < t->right->element)
            {
                rotateWithRightChild(t);
            }
            else
            {
                doubleWithRightChild(t);
            }
        }
    }
    t->height = max(height(t->left), height(t->right)) + 1;
}

void AVLTreeInterface::rotateWithLeftChild(AVLNode*& k1)
{
AVLNode* k2 = k1->left;
k1->left = k2->right;
k2->right = k1;
k1->height = max(height(k1->left), height(k1->right)) +1;
k2->height = max(height(k2->left), height(k2->right)) +1;
k1 = k2;
}

void AVLTreeInterface::rotateWithRightChild(AVLNode*& k1)
{
AVLNode* k2 = k1->right;
k1->right = k2->left;
k2->left = k1;
k1->height = max(height(k1->left), height(k1->right)) +1;
k2->height = max(height(k2->left), height(k2->right)) +1;
k1 = k2;
}

void AVLTreeInterface::doubleWithLeftChild(AVLNode*& k3)
{
rotateWithRightChild(k3->left);
rotateWithLeftChild(k3);
}

void AVLTreeInterface::doubleWithRightChild(AVLNode*& k3)
{
rotateWithLeftChild(k3->right);
rotateWithRightChild(k3);
}

void AVLTreeInterface::getPages(string &entry)
{

}

int AVLTreeInterface::indexSize()
{

}

void AVLTreeInterface::writeIndex()
{

}


#include "avltreeinterface.h"
#include <algorithm> //for max()
using namespace std;

AVLTreeInterface::AVLTreeInterface()
{
    root = nullptr;
    heightCounter = 0;
}

void AVLTreeInterface::insert(string &word, int &page)
{
    //cout << "Balls" << endl;
    insert(word, page, root);
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

void AVLTreeInterface::insert(string &val, int &num, AVLNode* &t)
{

    if(t == nullptr)
    {
        t = new AVLNode(val, nullptr,nullptr, heightCounter);
        t->addEntry(val, num);
    }
    else if (t->element == val)
    {
        t->addEntry(val, num);
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
                //cout << "D3" << endl;
                doubleWithRightChild(t);
            }
            else
            {
                //cout << "D4" << endl;
                rotateWithRightChild(t);
            }
        }
    }
    t->height = max(height(t->left), height(t->right)) + 1;
}

void AVLTreeInterface::rotateWithLeftChild(AVLNode*& k1)
{
AVLNode* k2 = k1->left;
//cout << "Debug 3" << endl;
k1->left = k2->right;
//cout << "Debug 5" << endl;
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

void AVLTreeInterface::getPages(string &entry, std::vector<int> &myList)
{
    search(entry, root, myList);
}

int AVLTreeInterface::indexSize()
{
    cout << "Sorry, I don't know what to tell you" << endl;
}

void AVLTreeInterface::writeIndex()
{
    ofstream outputFile;
    outputFile.open("index.txt");
    if (outputFile.is_open())
    {
        writeIndex(root, outputFile);
        outputFile << "c." << endl;
        outputFile << "1" ;
    }
    else
        cout << "Could not write to index" << endl;

    outputFile.close();

}

void AVLTreeInterface::writeIndex(AVLNode *t, ofstream &outputFile)
{
    if (t == nullptr)
    {
        return;
    }
    writeIndex(t->left, outputFile);
    writeIndex(t->right, outputFile);
    outputFile << t->element << endl;
    for (int i = 0; i < t->pages.size(); i++)
    {
        outputFile << t->pages[i] << " ";
    }
    outputFile << endl;
}

void AVLTreeInterface::search(string &val, AVLNode* &t, std::vector<int> &myList)
{
    if(t == nullptr)
    {
        return;
    }
    else if (t->getEntry() == val)
    {
        myList = t->pages;
    }

    else if(val < t->element)
    {
        search(val, t->left, myList);
    }
    else if (t->element < val)
    {
        search(val, t->right, myList);
    }

}

void AVLTreeInterface::clearIndex() //public interface function
{
    clearIndex(root);
    remove("index.txt");
}

void AVLTreeInterface::clearIndex(AVLNode *t) //private function
{
    if (t == nullptr)
    {
        return;
    }
    clearIndex(t->left);
    clearIndex(t->right);
    free(t);

}

void AVLTreeInterface::partialClear()
{
    clearIndex(root);
}



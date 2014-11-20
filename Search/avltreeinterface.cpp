#include "avltreeinterface.h"
#include <algorithm> //for max()
AVLTreeInterface::AVLTreeInterface()
{
    root = nullptr;
    heightCounter = 0;
}

void AVLTreeInterface::addToIndex(std::string &entry, int &entryID)
{
    insert(root, entry, entryID);
}

void AVLTreeInterface::insert(AVLNode *cur, std::string &entry, int &entryID)
{

    if (cur == nullptr)
    {
        cur = new AVLNode;
        cur->addEntry(entry, entryID);
        cur->setHeight(heightCounter);
    }

    else if(entry < cur->getEntry())
    {
        heightCounter++;
        insert(cur->getLeft(), entry, entryID);
        heightCounter--;
    }

    else if(entry > cur->getEntry())
    {
        heightCounter++;
        insert(cur->getRight(), entry, entryID);
        heightCounter--;
    }
}

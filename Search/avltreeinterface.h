#ifndef AVLTREEINTERFACE_H
#define AVLTREEINTERFACE_H
#include "indexinterface.h"
#include "avlnode.h"
class AVLTreeInterface : public IndexInterface
{
private:
    AVLNode *root;
    void insert(AVLNode *cur, std::string &entry, int &entryID);
    int heightCounter;


public:
    AVLTreeInterface();
    virtual void addToIndex(std::string &entry, int &entryID);


};

#endif // AVLTREEINTERFACE_H

#ifndef AVLTREEINTERFACE_H
#define AVLTREEINTERFACE_H
#include "indexinterface.h"
#include "avlnode.h"
#include <string>
class AVLTreeInterface : public IndexInterface
{
private:
    AVLNode* root;
    int heightCounter;

    void insert(std::string val, int num, AVLNode*& t);
    int height(AVLNode *t);
    void rotateWithLeftChild(AVLNode*& k1);
    void rotateWithRightChild(AVLNode*& k1);
    void doubleWithLeftChild(AVLNode*& k3);
    void doubleWithRightChild(AVLNode*& k3);

public:
    AVLTreeInterface();

    virtual void insert(std::string &entry, int num);
    virtual void getPages(std::string &entry);
    virtual void writeIndex();
    virtual int indexSize();

};

#endif // AVLTREEINTERFACE_H

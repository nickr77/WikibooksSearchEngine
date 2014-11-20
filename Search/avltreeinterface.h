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
    void addToIndex(std::string &entry, int &entryID);
    AVLNode* rr_rotation(AVLNode*);
    AVLNode* ll_rotation(AVLNode*);
    AVLNode* lr_rotation(AVLNode*);
    AVLNode* rl_rotation(AVLNode*);
    AVLNode* balance(AVLNode*);

};

#endif // AVLTREEINTERFACE_H

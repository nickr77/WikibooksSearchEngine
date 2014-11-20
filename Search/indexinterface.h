#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H
#include <string>

class IndexInterface
{
public:
    IndexInterface();
    virtual void addToIndex(std::string &entry, int &entryID);
};

#endif // INDEXINTERFACE_H

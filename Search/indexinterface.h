#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H
#include <string>

class IndexInterface
{
public:
    IndexInterface();
    virtual void insert(std::string &entry, int &entryID);
    virtual void getPages(std::string &entry);
    virtual void writeIndex();
    virtual int indexSize();
};

#endif // INDEXINTERFACE_H

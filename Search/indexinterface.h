#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;
class IndexInterface
{
public:
    IndexInterface();
    virtual void insert(std::string &word, int &page);
    virtual void getPages(std::string &query, std::vector<int> &pageList);
    virtual void writeIndex();
    virtual int indexSize();
    virtual void clearIndex();
};

#endif // INDEXINTERFACE_H

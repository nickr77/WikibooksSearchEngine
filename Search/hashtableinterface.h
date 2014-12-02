#ifndef HASHTABLEINTERFACE_H
#define HASHTABLEINTERFACE_H
#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>
#include "indexinterface.h"
class HashTableInterface : public IndexInterface
{
private:
    std::unordered_map<std::string, std::vector<int>> mapIndex;
    std::unordered_map<std::string, std::vector<int>>::const_iterator found;
    std::unordered_map<std::string, std::vector<int>>::const_iterator printer;
public:
    HashTableInterface();
    virtual void insert(std::string &word, int &page);
    virtual void getPages(std::string &query);
    virtual int indexSize() {return mapIndex.size();}
    virtual void writeIndex();
};

#endif // HASHTABLEINTERFACE_H

//
//  HashTableInterface Class
//  Search
//
//  Created by Nick Roberts.
//  Copyright (c) 2014 Nick Roberts. All rights reserved.
//

#ifndef HASHTABLEINTERFACE_H
#define HASHTABLEINTERFACE_H
#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "indexinterface.h"
using namespace std;
class HashTableInterface : public IndexInterface
{
private:
    std::unordered_map<std::string, std::vector<int>> mapIndex;
    std::unordered_map<std::string, std::vector<int>>::const_iterator found;
    std::unordered_map<std::string, std::vector<int>>::const_iterator printer;
public:
    HashTableInterface();
    virtual void insert(std::string &word, int &page);
    virtual void getPages(std::string &query, std::vector<int> &pageList);
    virtual int indexSize() {return mapIndex.size();}
    virtual void writeIndex();
    virtual void clearIndex();
    virtual void partialClear();
};

#endif // HASHTABLEINTERFACE_H

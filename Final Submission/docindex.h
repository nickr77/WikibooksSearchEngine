//
//  DocIndex Class
//  Search
//
//  Created by Nick Roberts.
//  Copyright (c) 2014 Nick Roberts. All rights reserved.
//

#ifndef DOCINDEX_H
#define DOCINDEX_H
#include <unordered_map>
#include <pageinfo.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;
class DocIndex
{
private:
    std::unordered_map<int, PageInfo> dIndex;
    std::unordered_map<int, PageInfo>::const_iterator found;
    std::unordered_map<int, PageInfo>::const_iterator printer;
    std::vector<int> pageStart;
    std::vector<std::string> docName;
public:
    DocIndex();
    void insert(int &id, std::string&title, std::string &author, std::string &time);
    void insertTitle(int&id, std::string&title);
    void insertAuthor(int &id, std::string &author);
    void insertTime(int &id, std::string &time);
    void writeIndex();
    void clearIndex();
    void partialClear();
    int getSize();
    void addDocInfo(int &page, std::string &dName);
    void whereToLook(int &page, int &pageST, std::string &dName);
    void getPageInfo(int &id, std::string &title, std::string &author, std::string &date);

};

#endif // DOCINDEX_H

#ifndef DOCINDEX_H
#define DOCINDEX_H
#include <unordered_map>
#include <pageinfo.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;
class DocIndex
{
private:
    std::unordered_map<int, PageInfo> dIndex;
    std::unordered_map<int, PageInfo>::const_iterator found;
    std::unordered_map<int, PageInfo>::const_iterator printer;
public:
    DocIndex();
    void insert(int &id, std::string&title, std::string &author, std::string &time);
    void insertTitle(int&id, std::string&title);
    void insertAuthor(int &id, std::string &author);
    void insertTime(int &id, std::string &time);
    void writeIndex();
    void clearIndex();
    int getSize();
};

#endif // DOCINDEX_H

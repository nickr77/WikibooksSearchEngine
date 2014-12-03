#ifndef WORDDATA_H
#define WORDDATA_H
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;
class WordData
{
private:
    std::string word;
    std::vector<int> pages;
    std::vector<int> pageCount;

public:
    WordData();
    void insert(std::string&, int&);
    void upPageCount(int&);

};

#endif // WORDDATA_H

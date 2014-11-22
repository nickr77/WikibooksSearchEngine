#ifndef HASHTABLEINTERFACE_H
#define HASHTABLEINTERFACE_H
#include <unordered_map>
#include <vector>
#include <iostream>
class HashTableInterface
{
private:
    std::unordered_map<std::string, std::vector<int>> mapIndex;
    std::unordered_map<std::string, std::vector<int>>::const_iterator found;
public:
    HashTableInterface();
    void insert(std::string &word, int &page);
    void getPages(std::string &query);
};

#endif // HASHTABLEINTERFACE_H

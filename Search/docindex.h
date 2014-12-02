#ifndef DOCINDEX_H
#define DOCINDEX_H
#include <unordered_map>
#include <pageinfo.h>
class DocIndex
{
private:
    std::unordered_map<int, PageInfo> dIndex;
    std::unordered_map<int, PageInfo>::const_iterator found;
public:
    DocIndex();
    void insert(int&id, std::string&title, std::string&author, std::string&date);
};

#endif // DOCINDEX_H

#ifndef FASTSTEM_H
#define FASTSTEM_H
#include <unordered_map>

class FastStem
{
private:
    std::unordered_map<std::string, std::string> stemMap;
    std::unordered_map<std::string, std::string>::const_iterator found;
public:
    FastStem();
    bool isStem(std::string &word);
    void insert(std::string&, std::string&);
};

#endif // FASTSTEM_H

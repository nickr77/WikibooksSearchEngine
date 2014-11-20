#ifndef DOCPARSE_H
#define DOCPARSE_H
#include <string>
#include "porter2_stemmer.h"
#include "tagstack.h"
#include "stopremover.h"
#include <vector>
class DocParse
{
private:
    StopRemover sRemove;
    //TagStack tagStack;
    std::vector<std::string> strVec;
    std::string line;
    int tagStart;
    int tagEnd;
    int counter;
    int totalCounter;
    std::string curTag;
    int titleStart;
    int titleEnd;
    std::string title;
    int idStart;
    int idEnd;
    std::string idString;
    int id;
    int textStart;
    int textEnd;
    std::string text;
    std::string individualWord;
    bool idFound;


public:
    DocParse();
    void parse();
};

#endif // DOCPARSE_H

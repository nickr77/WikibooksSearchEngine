#ifndef DOCPARSE_H
#define DOCPARSE_H
#include <string>
#include "porter2_stemmer.h"
#include "stopremover.h"
#include "faststem.h"
#include "hashtableinterface.h"
#include "avltreeinterface.h"
#include "indexinterface.h"
#include "docindex.h"
#include <vector>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iostream>
using namespace std;

class DocParse
{
private:
    StopRemover sRemove;

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
    int timestampStart;
    int timestampEnd;
    std::string timestamp;
    int usernameStart;
    int usernameEnd;
    std::string username;
    int idStart;
    int idEnd;
    std::string idString;
    int id;
    int textStart;
    int textEnd;
    std::string text;
    std::string individualWord;
    bool idFound;
    FastStem fStem;


public:
    DocParse();
    void parse(IndexInterface* &myIndex, DocIndex &dIndex);
    void readIndex(IndexInterface* &myIndex, DocIndex &dIndex);
};

#endif // DOCPARSE_H




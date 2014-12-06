#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H
#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
#include "tagstack.h"
#include "indexinterface.h"
#include "hashtableinterface.h"
#include "avltreeinterface.h"
#include "porter2_stemmer.h"
#include "docindex.h"
#include "stopremover.h"
#include "docparse.h"
#include <math.h>
using namespace std;
using namespace Porter2Stemmer;
class QueryProcessor
{
private:
    //IndexInterface* myIndex = new HashTableInterface();
    TagStack myStack;
    StopRemover stopRemove;
    std::string word;
    std::string singleSearchWord;
    std::string firstBoolean;
    std::string secondBoolean;
    std::string queryString;
    int wordStart;
    int wordEnd;
    std::string andWord1;
    std::string andWord2;
    std::string orWord1;
    std::string orWord2;
    std::string notWord;
    std::vector<int> andWord1List;
    std::vector<int> andWord2List;
    std::vector<int> orWord1List;
    std::vector<int> orWord2List;
    std::vector<int> notWordList;
    std::vector<int> singleSearchWordList;
    int counter;
    std::vector<int> andWordIntersection;
    std::vector<int> orWordIntersection;
    std::vector<int> notWordIntersection;
    std::vector<int> finalPageList;
    std::vector<int> frequency;
    int firstIndex;
    int lastIndex;
    std::string title;
    std::string author;
    std::string date;

    int newCounter;
    int andTracker;
    int orTracker;
    int notTracker;
    std::vector<std::string> andWordVector;
    std::vector<std::string> orWordVector;
    std::vector<std::string> notWordVector;

    void intersection(std::vector<int> &list1, std::vector<int> &list2, std::vector<int> &list3);
    void disjunction(std::vector<int> &list1, std::vector<int> &list2, std::vector<int> &list3);
    void remove(std::vector<int> & list, const int & item);
    void frequencySort(vector<int> &pageList, vector<int> &freq, int &firstIndex, int &lastIndex);
    string search(IndexInterface *&myIndex, std::vector<int> &finalList, std::vector<int> &freq);
    void frequencyTracker(vector<int> &originalPageList, vector<int> &finalList, vector<int> &freq);
    void first();
public:
    QueryProcessor();
    void displayFrequency(IndexInterface *&myIndex, DocIndex &dIndex, DocParse &parser);
    void stressSearch(IndexInterface *&myIndex, std::string &stressQuery);
};

#endif // QUERYPROCESSOR_H

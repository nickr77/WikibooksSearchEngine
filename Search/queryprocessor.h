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
#include <math.h>
using namespace std;
using namespace Porter2Stemmer;
class QueryProcessor
{
private:
    //IndexInterface* myIndex = new HashTableInterface();
    TagStack myStack;
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
    void intersection(std::vector<int> &list1, std::vector<int> &list2, std::vector<int> &list3);
    void disjunction(std::vector<int> &list1, std::vector<int> &list2, std::vector<int> &list3);
    void remove(std::vector<int> & list, const int & item);
    void frequencySort(vector<int> &pageList, vector<int> &frequency, int &firstIndex, int &lastIndex);
    string search(IndexInterface *&myIndex);
    void frequencyTracker(vector<int> &originalPageList, vector<int> finalPageList, vector<int> &frequency);
public:
    QueryProcessor();
    void displayFrequency(IndexInterface *&myIndex);
};

#endif // QUERYPROCESSOR_H

#include "stopremover.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

StopRemover::StopRemover()
{
    ifstream inputFile;
    string line;
    inputFile.open("stopwords.txt");
    if (inputFile.is_open())
    {
        while(getline(inputFile, line))
        {
            stopWords.push_back(line);
        }

    }
    //cout << stopWords.size() << endl;

}

bool StopRemover::checkWord(string &word)
{
//    for(int i = 0; i < stopWords.size(); i++)
//    {
//        if (word == stopWords[i])
//        {
//            return true;
//        }
//    }
//    return false;
    if((binary_search(stopWords.begin(), stopWords.end(), word)))
    {
        //cout << word << endl;
        return true;
    }
    else
    {
        return false;
    }
}

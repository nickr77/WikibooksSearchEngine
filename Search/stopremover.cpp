#include "stopremover.h"
#include <fstream>
#include <vector>
#include <iostream>
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

}

bool StopRemover::checkWord(string word)
{
    for(int i = 0; i < stopWords.size(); i++)
    {
        if (word == stopWords[i])
        {
            return true;
        }
    }
    return false;
}

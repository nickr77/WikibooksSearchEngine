//
//  StopRemover Class
//  Search
//
//  Created by Steven Bock.
//  Copyright (c) 2014 Steven Bock. All rights reserved.
//

#ifndef STOPREMOVER_H
#define STOPREMOVER_H
#include <string>
#include <sstream>
#include <iostream>
#include <unordered_set>
using namespace std;
class StopRemover
{
private:
    std::unordered_set<std::string> stopWords;
    std::unordered_set<std::string>::const_iterator exists;
public:
    StopRemover();
    bool checkWord(std::string &word);


};

#endif // STOPREMOVER_H

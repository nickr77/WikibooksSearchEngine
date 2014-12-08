//
//  FastStem Class
//  Search
//
//  Created by Nick Roberts.
//  Copyright (c) 2014 Nick Roberts. All rights reserved.
//

#ifndef FASTSTEM_H
#define FASTSTEM_H
#include <unordered_map>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;
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

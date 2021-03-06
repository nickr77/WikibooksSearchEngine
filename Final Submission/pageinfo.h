//
//  PageInfo Class
//  Search
//
//  Created by Nick Roberts.
//  Copyright (c) 2014 Nick Roberts. All rights reserved.
//

#ifndef PAGEINFO_H
#define PAGEINFO_H
#include <string>
#include <sstream>
#include <iostream>
using namespace std;
class PageInfo
{
private:
    std::string title;
    std::string author;
    std::string date;
public:
    PageInfo();
    void setInfo(std::string &auth, std::string &time, std::string &titl);
    void setTitle(std::string &titl);
    void setAuthor(std::string &auth);
    void setDate(std::string &time);
    std::string getTitle();
    std::string getAuthor();
    std::string getDate();
    int getID();
};

#endif // PAGEINFO_H

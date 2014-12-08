//
//  TagStack Class
//  Search
//
//  Created by Steven Bock.
//  Copyright (c) 2014 Steven Bock. All rights reserved.
//

#ifndef TAGSTACK_H
#define TAGSTACK_H
#include <string>
class TagStack
{
private:
    std::string* elements;
    int current;
    int upperIndex;
public:
    TagStack();
    ~TagStack();
    void push(std::string &x);
    std::string pop();
    std::string top();
    bool isEmpty();
    bool inList(std::string x);
    std::string read(int &x);
    int quantity();
    void clear();

};

#endif // TAGSTACK_H

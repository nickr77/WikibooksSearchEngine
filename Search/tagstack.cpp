#include "tagstack.h"
#include <string>
using namespace std;
TagStack::TagStack()
{
    elements = new string[10];
    current = 0;
    upperIndex = 9;
    for(int count = 0; count <= upperIndex; count++)
    {
        elements[count] = "";
    }
}

TagStack::~TagStack()
{
    delete[] elements;
}

void TagStack::push(string x)
{
    if(current > upperIndex)
    {
        string* temp = new string[upperIndex + 11];
        for (int count = 0; count <= upperIndex; count++)
        {
            temp[count] = elements[count];
        }
        for(int count = upperIndex + 1; count <= upperIndex + 10; count++)
        {
            temp[count] = "";
        }
        upperIndex += 10;

        delete[] elements;
        elements = temp;
    }
    elements[current] = x;
    current++;
}

string TagStack::pop()
{
    string val = elements[current - 1];
    elements[current-1] = "";
    current--;
    return val;
}

bool TagStack::isEmpty()
{
    if (elements[0] == "")
    {
        return true;
    }
    else
    {
        return false;
    }
}

string TagStack::top()
{
    return elements[current-1];
}

bool TagStack::inList(string x)
{
    for (int i = 0; i <= current - 1; i++)
    {
        if (elements[i] == x)
            return true;
    }
    return false;
}

string TagStack::read(int indice)
{
    return elements[indice];
}

int TagStack::quantity()
{
    return current;
}

void TagStack::clear()
{
    while(current > 0)
    {
        pop();
    }
}

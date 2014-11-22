#include "faststem.h"

FastStem::FastStem()
{

}

bool FastStem::isStem(std::string &word)
{
    found = stemMap.find(word);
    if (found != stemMap.end())
    {
        word = found->second;
        return true;

    }

    else
    {
        return false;
    }

}

void FastStem::insert(std::string &key, std::string &value)
{
    stemMap.insert(std::make_pair(key, value));
}

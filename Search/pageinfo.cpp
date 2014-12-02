#include "pageinfo.h"
using namespace std;
PageInfo::PageInfo()
{

}

void PageInfo::setInfo(std::string &auth, std::string &time, string &titl)
{
    title = titl;
    author = auth;
    date = time;
}

string PageInfo::getAuthor()
{
    return author;
}

string PageInfo::getDate()
{
    return date;
}

string PageInfo::getTitle()
{
    return title;
}



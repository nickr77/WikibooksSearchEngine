#include "pageinfo.h"
using namespace std;
PageInfo::PageInfo()
{
    title = "N/A";
    author = "N/A";
    date = "N/A";
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

void PageInfo::setTitle(string &titl)
{
    title = titl;
}

void PageInfo::setAuthor(string &auth)
{
    author = auth;
}

void PageInfo::setDate(string &time)
{
    date = time;
}

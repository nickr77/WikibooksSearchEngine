#include "pageinfo.h"
using namespace std;
PageInfo::PageInfo()
{

}

void PageInfo::setInfo(std::string &name, std::string &auth, std::string &time)
{
    title = name;
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

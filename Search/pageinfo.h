#ifndef PAGEINFO_H
#define PAGEINFO_H
#include <string>
class PageInfo
{
private:
    std::string title;
    std::string author;
    std::string date;
public:
    PageInfo();
    void setInfo(std::string&, std::string&, std::string&);
    std::string getTitle();
    std::string getAuthor();
    std::string getDate();
};

#endif // PAGEINFO_H

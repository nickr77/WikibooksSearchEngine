#include "docindex.h"

DocIndex::DocIndex()
{
}
void DocIndex::insert(int &id, string &title, string &author, string &time)
{
    PageInfo page;
    page.setInfo(author, time, title);
    dIndex.insert(std::make_pair(id, page));
}

void DocIndex::insertTitle(int &id, std::string &title)
{

        PageInfo page;
        page.setTitle(title);
        dIndex.insert(std::make_pair(id, page));

}

void DocIndex::insertAuthor(int &id, string &author)
{
    found = dIndex.find(id);
    if (found != dIndex.end())
    {
        dIndex[id].setAuthor(author);
    }
}

void DocIndex::insertTime(int &id, string &time)
{
    found = dIndex.find(id);
    if (found != dIndex.end())
    {
        dIndex[id].setDate(time);
    }
}

void DocIndex::writeIndex()
{
    PageInfo p;
    std::ofstream outputFile;
    outputFile.open("docs.txt");
    for(printer = dIndex.begin(); printer != dIndex.end(); ++printer)
    {
        p = printer->second;
        outputFile << printer->first << std::endl;
        outputFile << p.getTitle() << std::endl;
        outputFile << p.getAuthor() << std::endl;
        outputFile << p.getDate() << std::endl;
    }
}

void DocIndex::clearIndex()
{
    dIndex.clear();
    remove("docs.txt");
}

int DocIndex::getSize()
{
    return dIndex.size();
}

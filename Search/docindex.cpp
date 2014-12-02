#include "docindex.h"

DocIndex::DocIndex()
{
}

void DocIndex::insert(int &id, std::string &title, std::string &author, std::string &date)
{

        PageInfo page;
        page.setInfo(author, date, title);
        dIndex.insert(std::make_pair(id, page));

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

#include "docindex.h"

DocIndex::DocIndex()
{
    ifstream inputFile;
    string line = "";
    inputFile.open("doclist.txt");
    if (inputFile.is_open())
    {
        while (!inputFile.eof())
        {
            while (line != "END")
            {
                getline(inputFile, line);
                if (line == "END")
                    break;
                //cout << line << endl;
                int temp = std::stoi(line);
                pageStart.push_back(temp);
                getline(inputFile, line);
                //cout << line << endl;
                docName.push_back(line);

            }
        }
    inputFile.close();
    }


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
    outputFile.close();
    outputFile.open("doclist.txt");
    for(int i = 0; i < pageStart.size(); i++)
    {
        outputFile << pageStart[i] << endl;
        outputFile << docName[i] << endl;
    }
    outputFile << "END";
    outputFile.close();

}

void DocIndex::clearIndex()
{
    dIndex.clear();
    remove("docs.txt");
}

void DocIndex::partialClear()
{
    dIndex.clear();
}

int DocIndex::getSize()
{
    return dIndex.size();
}

void DocIndex::addDocInfo(int &page, string &dName)
{
    pageStart.push_back(page);
    docName.push_back(dName);
}

void DocIndex::whereToLook(int &page, int &pageST, string &dName)
{
    for(int i = 0; i < pageStart.size(); i++)
    {
        if (page > pageStart[i])
        {
            dName = docName[i];
            pageST = pageStart[i];
        }
    }
}

void DocIndex::getPageInfo(int &id, string &title, string &author, string &date)
{
    title = dIndex[id].getTitle();
    author = dIndex[id].getAuthor();
    date = dIndex[id].getDate();
}



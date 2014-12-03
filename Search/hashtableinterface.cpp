#include "hashtableinterface.h"
HashTableInterface::HashTableInterface()
{
}

void HashTableInterface::insert(std::string &word, int &page)
{
    found = mapIndex.find(word);
    if (found != mapIndex.end())
    {
        mapIndex[word].push_back(page);

    }

    else
    {
        std::vector<int> pages {page};
        mapIndex.insert(std::make_pair(word, pages));
    }
}

void HashTableInterface::getPages(std::string &query, std::vector<int> &pageList)
{
    cout << "enter" << endl;
    found = mapIndex.find(query);
    cout << mapIndex.size() << endl;
    if (found != mapIndex.end())
    {
        cout << "pre" << endl;
        pageList = found->second;
        cout << "post" << endl;
    }
    else
        pageList.push_back(0);

    for(int i = 0; i < pageList.size(); i++)
    {
        cout << pageList[i] << endl;
    }
    std::cout << query << std::endl;
    int counter = 0;
    for (int x = 0; x < pageList.size(); x++)
    {
        std::cout << pageList[x] << " ";
        counter++;
        if (counter % 5 == 0)
        {
            std::cout << std::endl;
        }
    }
}
void HashTableInterface::writeIndex()
{
    std::ofstream outputFile;

    outputFile.open("index.txt");
    for(printer = mapIndex.begin(); printer != mapIndex.end(); ++printer)
    {
        std::vector<int> pageList = printer->second;

        outputFile << printer->first << std::endl;
        for (int i = 0; i < pageList.size(); i++)
        {
            outputFile << pageList[i] << " ";
        }
        pageList.clear();
        outputFile << std::endl;
    }
    outputFile << "c." << std::endl;
    outputFile << "1" ;
    outputFile.close();
}

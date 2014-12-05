#include "docparse.h"
#include "porter2_stemmer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <docindex.h>
using namespace std;
using namespace Porter2Stemmer;

DocParse::DocParse()
{
    tagStart = 0;
    tagEnd = 0;
    counter = 0;
    totalCounter = 0;
    titleStart = 0;
    titleEnd = 0;
    timestampStart = 0;
    timestampEnd = 0;
    usernameStart = 0;
    usernameEnd = 0;
    idStart = 0;
    idEnd = 0;
    id = 0;
    textStart = 0;
    textEnd = 0;
    idFound = false;
}

void DocParse::parse(IndexInterface* &myIndex, DocIndex &dIndex, string &fileName)
{
    ifstream inputFile;
    inputFile.open(fileName.c_str());
    int pageCounter = dIndex.getSize();
    dIndex.addDocInfo(pageCounter, fileName);
    //cout << pageCounter << endl;
//    cout << "Begin Parsing" << endl;
//    std::chrono::time_point<std::chrono::system_clock> start, end;
//    start = std::chrono::system_clock::now();
    if (inputFile.is_open())
    {
        while(!inputFile.eof())
        {
            while(getline(inputFile, line))
            {
                counter = 0;
                while (counter < line.size())
                {
                    if (line[counter] == '<')
                    {
                        tagStart = ++counter;
                        while(line[counter] != '>')
                        {
                            counter++;
                        }
                        tagEnd = counter - 1;
                        for (int i = tagStart; i <= tagEnd; i++)
                        {
                            curTag += line[i];
                        }
                    }
                    if(curTag == "title")
                    {
                        titleStart = counter + 1;
                        while(line[counter] != '<')
                        {
                            counter++;
                        }
                        titleEnd = counter -1;
                        for(int i = titleStart; i <= titleEnd; i++)
                        {
                            title += line[i];
                        }
                        pageCounter++;
                        dIndex.insertTitle(pageCounter, title);
                    }
                    else if(curTag == "timestamp")
                    {
                        timestampStart = counter + 1;
                        while(line[counter] != '<')
                        {
                            counter++;
                        }
                        timestampEnd = counter -1;
                        for(int i = timestampStart; i <= timestampEnd; i++)
                        {
                            timestamp += line[i];
                        }
                        //cout << timestamp << endl;
                        dIndex.insertTime(pageCounter, timestamp);
                    }
                    else if(curTag == "username")
                    {
                        usernameStart = counter + 1;
                        while(line[counter] != '<')
                        {
                            counter++;
                        }
                        usernameEnd = counter -1;
                        for(int i = usernameStart; i <= usernameEnd; i++)
                        {
                            username += line[i];
                        }
                        //cout << username << endl;
                        dIndex.insertAuthor(pageCounter, username);
                    }
                    else if(curTag == "text xml:space=\"preserve\"")
                    {


                        while(line[counter] != '<')
                        {
                            textStart = counter;
                            while(line[counter] != ' ')
                            {
                                if(counter >= line.size())
                                {
                                    //cout << "New Line" << endl;
                                    textEnd = counter -1;
                                    for(int i = textStart; i <= textEnd; i++)
                                    {
                                        if(line[i] < 'a' || line[i] > 'z')
                                        {
                                            text.clear();
                                            i = ++textEnd;
                                        }
                                        else
                                            text += line[i];
                                    }

                                    getline(inputFile, line);
                                    counter = 0;
                                }
                                counter++;
                            }


                            textEnd = counter -1;
                            for(int i = textStart; i <= textEnd; i++)
                            {
                                if(line[i] < 'a' || line[i] > 'z')
                                {
                                    text.clear();
                                    i = ++textEnd;
                                }
                                else
                                    text += line[i];
                            }
                            if(text == "")
                            {

                            }
                            else if(sRemove.checkWord(text) == false)
                            {
                                if(fStem.isStem(text) == false)
                                {
                                    string originalText = text;
                                    stem(text);
                                    fStem.insert(originalText, text);
                                    fStem.isStem(originalText);
                                    myIndex->insert(text, pageCounter);
                                }
                                else
                                {
                                    myIndex->insert(text, pageCounter);
                                }
                            }
                            text.clear();
                            counter++;
                        }
                        text.clear();
                        title.clear();
                        timestamp.clear();
                        username.clear();

                    }
                    else if(curTag == "text xml:space=\"preserve\" /")
                    {
                        counter+=27;
                    }
                    else if (line[counter] != '<' || line[counter] != '>')
                    {
                        ++counter;
                    }

                    curTag.clear();
                }
            }
        }
    }
    inputFile.close();

//    end = std::chrono::system_clock::now();
//    std::chrono::duration<double> elapsed_seconds = end-start;
//    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
//    cout << "End Parsing" << endl;
//    cout << "Elapsed Time: " << elapsed_seconds.count() / 60 << endl;

    dIndex.writeIndex();
    myIndex->writeIndex();
//    string y = " ";
//    while (y != "z")
//    {
//        cout << "Enter a word: " << endl;
//        cin >> y;
//        stem(y);
//        myIndex->getPages(y);
//        cout << endl;
//    }

}

void DocParse::readIndex(IndexInterface *&myIndex, DocIndex &dIndex)
{
    ifstream inputFile;
//    std::chrono::time_point<std::chrono::system_clock> start, end;
//    start = std::chrono::system_clock::now();
    //cout << "Hello!" << endl;
    inputFile.open("index.txt");
    if (inputFile.is_open())
    {
        int count = 0;
        while(!inputFile.eof())
        {

            getline(inputFile, line);
            text = line;
            getline(inputFile, line);
            counter = 0;
            while(counter < line.size() - 1)
            {
                idStart = counter;
                while(line[counter] != ' ')
                {
                    counter++;
                }
                idEnd = counter - 1;
                for(int i = idStart; i <= idEnd; i++)
                {
                    idString += line[i];
                }
                istringstream(idString) >> id;
                myIndex->insert(text, id);
                idString.clear();
                counter++;
            }
        }
    }
    inputFile.close();

    inputFile.open("docs.txt");
    if (inputFile.is_open())
    {
        while(!inputFile.eof())
        {
            getline(inputFile, line);
            idString = line;
            istringstream(idString) >> id;
            getline(inputFile, line);
            title = line;
            getline(inputFile, line);
            username = line;
            getline(inputFile, line);
            timestamp = line;
            dIndex.insert(id, title, username, timestamp);
        }
    }
    inputFile.close();
//    end = std::chrono::system_clock::now();
//    std::chrono::duration<double> elapsed_seconds = end-start;
//    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
//    cout << "End Parsing" << endl;
//    cout << "Elapsed Time: " << elapsed_seconds.count() / 60 << endl;
    //string y = " ";
    //vector<int> ax = {0};
//    while (y != "z")
//    {
//        cout << "Enter a word: " << endl;
//        cin >> y;
//        stem(y);
//        myIndex->getPages(y, ax);
//        cout << endl;
//    }

}

void DocParse::displayPageContents(int &desiredPage, DocIndex &dIndex)
{
    int pCount = 0;
    string fName = "";
    string line;
    dIndex.whereToLook(desiredPage, pCount, fName);
    ifstream inputFile;
    inputFile.open(fName.c_str());
    if (inputFile.is_open())
    {
        while(getline(inputFile, line))
        {
            counter = 0;
            while (counter < line.size())
            {
                if (line[counter] == '<')
                {
                    tagStart = ++counter;
                    while(line[counter] != '>')
                    {
                        counter++;
                    }
                    tagEnd = counter - 1;
                    for (int i = tagStart; i <= tagEnd; i++)
                    {
                        curTag += line[i];
                    }
                }
                if(curTag == "title")
                {
                    titleStart = counter + 1;
                    while(line[counter] != '<')
                    {
                        counter++;
                    }
                    titleEnd = counter -1;
                    for(int i = titleStart; i <= titleEnd; i++)
                    {
                        title += line[i];
                    }
                    pCount++;
                }
                else if (pCount == desiredPage)
                {
                    cout << line << endl;
                }

            }
        }

    }
    inputFile.close();
}

#include "docparse.h"
#include "tagstack.h"
#include "porter2_stemmer.h"
#include <fstream>
#include <iostream>
#include <sstream>
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
    idStart = 0;
    idEnd = 0;
    id = 0;
    textStart = 0;
    textEnd = 0;
    idFound = false;
}

void DocParse::parse()
{
    ifstream inputFile;
    inputFile.open("wikibooks.xml");
    int pageCounter = 0;
    cout << "Begin Parsing" << endl;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
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
                        cout << pageCounter << endl;
                        title.clear();
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
                                if(line[i] < 97 || line[i] > 122)
                                {
                                    text.clear();
                                }
                                else
                                    text += line[i];
                            }
                            if(text == "")
                            {

                            }
                            else if(sRemove.checkWord(text) == false && text.size() < 20)
                            {
                                if(fStem.isStem(text) == false)
                                {
                                    string originalText = text;
                                    stem(text);
                                    fStem.insert(originalText, text);
                                    fStem.isStem(originalText);
                                    hashIndex.insert(text, pageCounter);
                                }
                                else
                                {
                                    hashIndex.insert(text, pageCounter);
                                }
                            }
                            text.clear();
                            counter++;
                        }
                        text.clear();

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
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    cout << "End Parsing" << endl;
    cout << "Elapsed Time: " << elapsed_seconds.count() / 60 << endl;
    cout << "Index contains " << hashIndex.indexSize() << " elements." << endl;
    cout << "Writing Index" << endl;
    hashIndex.writeIndex();
    string y = " ";
    while (y != "z")
    {
        cout << "Enter a word: " << endl;
        cin >> y;
        stem(y);
        hashIndex.getPages(y);
        cout << endl;
    }

}

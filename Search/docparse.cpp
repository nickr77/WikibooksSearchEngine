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
    if (inputFile.is_open())
    {
        while(!inputFile.eof())
        {
            //cout << "Hello" << endl;
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


                        if(line[tagStart] != '/')
                        {
                            tagStack.push(curTag);
                        }
                        else //tagStart == '/'
                        {
                            tagStack.pop();
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
                        //cout << "Title: " << title << endl;
                        //cout << ++pageCounter << endl;
                        title.clear();
                    }
                    else if(curTag == "id" && tagStack.inList("revision") == false && tagStack.inList("contributor") == false)
                    {
                        idStart = counter + 1;
                        while(line[counter] != '<')
                        {
                            counter++;
                        }
                        idEnd = counter -1;
                        for(int i = idStart; i <= idEnd; i++)
                        {
                            idString += line[i];
                        }
                        id = atoi(idString.c_str());
                        //cout << "ID: " << id << endl;
                        idString.clear();
                    }
                    else if(curTag == "text xml:space=\"preserve\"")
                    {
                        textStart = counter + 1;

                        while(line[counter] != '<')
                        {

                            //cout << id << endl;
                            if(counter >= line.size())
                            {
                                //cout << "New Line" << endl;
                                textEnd = counter -1;
                                for(int i = textStart; i <= textEnd; i++)
                                {
                                    text += line[i];
                                }
                                //cout << "Text: " << text << endl;

                                getline(inputFile, line);
                                //totalCounter = totalCounter + counter;
                                counter = 0;
                            }
                            counter++;

                        }
                        textEnd = counter -1;
                        for(int i = textStart; i <= textEnd; i++)
                        {
                            text += line[i];
                        }
                        stringstream ss(text);

                        while(getline(ss, individualWord, ' '))
                        {

                            if(individualWord.find('&') != string::npos || individualWord.find(']') != string::npos)
                            {
                                //cout << individualWord << endl;
                            }
                            else if (individualWord.size() > 20)
                            {
                                //cout << individualWord << endl;
                            }
                            else
                            {
                                //cout << individualWord << endl;
                                individualWord[0] = tolower(individualWord[0]);
                                if(individualWord[0] < 'a' || individualWord[0] > 'z')
                                {
                                    //cout << individualWord << endl;
                                }
                                else if (sRemove.checkWord(individualWord) == false /*|| individualWord.size() > 3*/)
                                {
                                    //cout << individualWord << endl;
                                    stem(individualWord);
                                    //cout << individualWord << endl;
                                }


                            }

                        }
                        //cout << "Text: " << text << endl;
                        text.clear();
                    }
                    else if(curTag == "text xml:space=\"preserve\" /")
                    {
                        tagStack.pop();
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
}

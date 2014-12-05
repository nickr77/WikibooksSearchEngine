#include "queryprocessor.h"

QueryProcessor::QueryProcessor()
{
    wordStart = 0;
    wordEnd = 0;
    queryString = " ";
}

void QueryProcessor::displayFrequency(IndexInterface* &myIndex)
{
    QueryProcessor qProcessor;
    qProcessor.search(myIndex);
    while (queryString != "DONE")
    {
        queryString = qProcessor.search(myIndex);
        for(int i = 0; i < frequency.size(); i++)
        {
            cout << "Hello" << endl;
            cout << "Page " << i << "Has Frequency: " << frequency[i] << endl;
        }
    }
}

std::string QueryProcessor::search(IndexInterface *&myIndex)
{
    word = " ";
    //while (word != "DONE")

        cout << "Search using the following format <(AND/OR) (Word(s)) (NOT) (Word(s))>: " << endl;
        getline(cin, queryString);
        istringstream iss(queryString);
        string i;
        while(iss >> i)
        {
            word = i;
            if (word == "DONE")
            {
                return word;
            }
            if (word == "AND")
            {
                firstBoolean = word;
                myStack.push(word);
            }
            else if (word == "OR")
            {
                firstBoolean = word;
                myStack.push(word);
            }
            else if (word == "NOT")
            {
                secondBoolean = word;
                myStack.push(word);
            }
            else //Current word is not a boolean
            {
                if(firstBoolean == "AND" && secondBoolean != "NOT")
                {
                    if(andWord1 == "")
                    {
                        andWord1 = word;
                    }
                    else
                        andWord2 = word;
                }
                else if (firstBoolean == "OR" && secondBoolean != "NOT")
                {
                    if(orWord1 == "")
                    {
                        orWord1 = word;
                    }
                    else
                        orWord2 = word;
                }
                else if (firstBoolean == "AND" && secondBoolean == "NOT")
                {
                    notWord = word;
                }
                else if (firstBoolean == "OR" && secondBoolean == "NOT")
                {
                    notWord = word;
                }
                else if (firstBoolean != "OR" && firstBoolean != "AND" && secondBoolean == "NOT")
                {
                    notWord = word;
                }
                else //No Boolean
                {
                    cout << "Assignment" << endl;
                    singleSearchWord = word;
                }
            }
        }
        cout << "Out of Query" << endl;
        if(myStack.inList("AND") == true && myStack.inList("NOT") == true)
        {
            stem(andWord1);
            stem(andWord2);
            stem(notWord);
            myIndex->getPages(andWord1, andWord1List);
            myIndex->getPages(andWord2, andWord2List);
            myIndex->getPages(notWord, notWordList);
            intersection(andWord1List, andWord2List, andWordIntersection);
            for(int i = 0; i < notWordList.size(); i++)
            {
                remove(andWordIntersection, notWordList.at(i));
            }
            frequencyTracker(andWordIntersection, finalPageList, frequency);
            firstIndex = 0;
            lastIndex = 1;
            frequencySort(andWordIntersection, frequency, firstIndex, lastIndex);
            for(int i = 0; i < frequency.size(); i++)
            {
                frequency[i] = frequency[i] * log(178800/andWordIntersection.size());
            }
        }
        else if(myStack.inList("OR") == true && myStack.inList("NOT") == true)
        {
            stem(orWord1);
            stem(orWord2);
            stem(notWord);
            myIndex->getPages(orWord1, orWord1List);
            myIndex->getPages(orWord2, orWord2List);
            myIndex->getPages(notWord, notWordList);
            disjunction(orWord1List, orWord2List, orWordIntersection);
            for(int i = 0; i < notWordList.size(); i++)
            {
                remove(orWordIntersection, notWordList.at(i));
            }
            frequencyTracker(orWordIntersection, finalPageList, frequency);
            firstIndex = 0;
            lastIndex = 1;
            frequencySort(orWordIntersection, frequency, firstIndex, lastIndex);
            for(int i = 0; i < frequency.size(); i++)
            {
                frequency[i] = frequency[i] * log(178800/orWordIntersection.size());
            }
        }
        else if(myStack.inList("AND") == true && myStack.inList("NOT") == false)
        {
            stem(andWord1);
            stem(andWord2);
            myIndex->getPages(andWord1, andWord1List);
            myIndex->getPages(andWord2, andWord2List);
            intersection(andWord1List, andWord2List, andWordIntersection);
            frequencyTracker(andWordIntersection, finalPageList, frequency);
            firstIndex = 0;
            lastIndex = 1;
            frequencySort(andWordIntersection, frequency, firstIndex, lastIndex);
            for(int i = 0; i < frequency.size(); i++)
            {
                frequency[i] = frequency[i] * log(178800/andWordIntersection.size());
            }
        }
        else if(myStack.inList("OR") == true && myStack.inList("NOT") == false)
        {
            stem(orWord1);
            stem(orWord2);
            myIndex->getPages(orWord1, orWord1List);
            myIndex->getPages(orWord2, orWord2List);
            disjunction(orWord1List, orWord2List, orWordIntersection);
            frequencyTracker(orWordIntersection, finalPageList, frequency);
            firstIndex = 0;
            lastIndex = 1;
            frequencySort(orWordIntersection, frequency, firstIndex, lastIndex);
            for(int i = 0; i < frequency.size(); i++)
            {
                frequency[i] = frequency[i] * log(178800/orWordIntersection.size());
            }
        }
        else if(myStack.inList("AND") == false && myStack.inList("OR") == false && myStack.inList("NOT") == true)
        {
            stem(singleSearchWord);
            stem(notWord);
            myIndex->getPages(singleSearchWord, singleSearchWordList);
            myIndex->getPages(notWord, notWordList);
            for(int i = 0; i < notWordList.size(); i++)
            {
                remove(singleSearchWordList, notWordList.at(i));
            }
            frequencyTracker(singleSearchWordList, finalPageList, frequency);
            firstIndex = 0;
            lastIndex = 1;
            frequencySort(singleSearchWordList, frequency, firstIndex, lastIndex);
            for(int i = 0; i < frequency.size(); i++)
            {
                frequency[i] = frequency[i] * log(178800/singleSearchWordList.size());
            }
        }
        else //Single word search
        {
            cout << "Single Word Search" << endl;
            stem(singleSearchWord);
            cout << "stemmed" << endl;
            cout << singleSearchWord << endl;
            myIndex->getPages(singleSearchWord, singleSearchWordList);
            cout << "Got Pages" << endl;
            frequencyTracker(singleSearchWordList, finalPageList, frequency);
            cout << "Got Frequency List" << endl;
            firstIndex = 0;
            lastIndex = 1;
            frequencySort(singleSearchWordList, frequency, firstIndex, lastIndex);
            for(int i = 0; i < frequency.size(); i++)
            {
                frequency[i] = frequency[i] * log(178800/singleSearchWordList.size());
            }
        }

}

void QueryProcessor::intersection(std::vector<int> &list1, std::vector<int> &list2, std::vector<int> &list3)
{
    sort(list1.begin(), list1.end());
    sort(list2.begin(), list2.end());

    set_intersection(list1.begin(),list1.end(),list2.begin(),list2.end(),std::back_inserter(list3));

}

void QueryProcessor::disjunction(std::vector<int> &list1, std::vector<int> &list2, std::vector<int> &list3)
{
    sort(list1.begin(), list1.end());
    sort(list2.begin(), list2.end());

    std::merge(list1.begin(), list1.end(), list2.begin(), list2.end(), std::back_inserter(list3));
//    vector<int> ::iterator pte = std::unique(list3.begin(), list3.end());
//    list3.erase(pte, list3.end());

}

void QueryProcessor::remove(vector<int> & list, const int & item)
{
    list.erase(std::remove(list.begin(), list.end(), item), list.end());
}

void QueryProcessor::frequencySort(vector<int> &pageList, vector<int> &frequency, int &firstIndex, int &lastIndex)
{
    cout << "Hello" << endl;
    for(int i = 0; i < frequency.size(); i++)
    {
        cout << pageList[i] << endl;
    }
    int a = firstIndex;
    int b = lastIndex;
    int pageTemp = 0;
    int freqTemp = 0;
    int bubbleSortStopper;
    for (int count = 0; count < frequency.size(); count++)
    {
       if (frequency[count] > 1)
       {
           for(int count1 = 2; count1 <= frequency[count]; count1++)
           {
               bubbleSortStopper = 0;
               for(int count2 = 1; count2 <= frequency[count] - 1; count2++)
               {
                   if(frequency[a] < frequency[b])
                   {
                       pageTemp = pageList[a];
                       freqTemp = frequency[a];
                       pageList[a] = pageList[b];
                       frequency[a] = frequency[b];
                       pageList[b] = pageTemp;
                       frequency[b] = freqTemp;
                       bubbleSortStopper = 1;
                   }
               }
               if (bubbleSortStopper == 0)
                   break;
           }
       }
    }
    cout << "End Freq Sort" << endl;
//    for(int i = 0; i < frequency.size(); i++)
//    {
//        cout << frequency[i] << endl;
//    }
}

void QueryProcessor::frequencyTracker(vector<int> &originalPageList, vector<int> finalPageList, vector<int> &frequency)
{
    int freqTrack = 0;
    counter = 1;
    finalPageList.push_back(originalPageList[0]);
    frequency.push_back(counter);
    for(int i = 0; i < originalPageList.size(); i++)
    {
        if(originalPageList[i] == originalPageList[i+1])
        {
            counter++;
            frequency[freqTrack] == counter;
        }
        else
        {
            finalPageList.push_back(originalPageList[i + 1]);
            freqTrack++;
            counter = 1;
            frequency.push_back(counter);
        }
    }
}

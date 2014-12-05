#include "queryprocessor.h"

QueryProcessor::QueryProcessor()
{
    wordStart = 0;
    wordEnd = 0;
    //queryString = " ";
}

void QueryProcessor::first()
{
    int blank;
    cin >> blank;
}

void QueryProcessor::displayFrequency(IndexInterface* &myIndex, DocIndex &dIndex)
{
    QueryProcessor qProcessor;
    //queryString = qProcessor.search(myIndex, finalPageList, frequency);
    //qProcessor.first();
    while (queryString != "DONE")
    {
        queryString = qProcessor.search(myIndex, finalPageList, frequency);
        if(queryString != " ")
        {
            if(finalPageList.size() == 0 || frequency.size() == 0)
            {
                cout << "No Results Returned. Please Search Again" << endl;
            }
            else
            {
                for(int i = 0; i < finalPageList.size(); i++)
                {
                    if(i == 15)
                        break;
                    dIndex.getPageInfo(finalPageList[i], title, author, date);
                    cout << i+1 << ". Title: \"" << title << "\" by: " << author << " Date: " << date << "  TF/IDF: " << frequency[i] << endl;
                    cout << endl;
                }
            }
        }
    }
}

std::string QueryProcessor::search(IndexInterface *&myIndex, std::vector<int> &finalList, std::vector<int> &freq)
{
    queryString.clear();
    word.clear();
    andWord1.clear();
    andWord2.clear();
    orWord1.clear();
    orWord2.clear();
    notWord.clear();
    singleSearchWord.clear();
    myStack.clear();
    andWord1List.clear();
    andWord2List.clear();
    andWordIntersection.clear();
    orWord1List.clear();
    orWord2List.clear();
    orWordIntersection.clear();
    notWordList.clear();
    notWordIntersection.clear();
    singleSearchWordList.clear();
    firstBoolean.clear();
    secondBoolean.clear();
    finalList.clear();
    freq.clear();
    finalPageList.clear();
    frequency.clear();
    cout << "Search using the following format <(AND/OR) (Word(s)) (NOT) (Word(s))>: " << endl;
    getline(cin, queryString);
    istringstream iss(queryString);
    string i;
    while(iss >> i)
    {
        word = i;
        if (word == " ")
        {
            return word;
        }
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
                singleSearchWord = word;
            }
        }
    }
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
        frequencyTracker(andWordIntersection, finalList, freq);
        firstIndex = 0;
        lastIndex = freq.size() - 1;
        frequencySort(finalList, freq, firstIndex, lastIndex);
        for(int i = 0; i < freq.size(); i++)
        {
            freq[i] = freq[i] * log(178800/andWordIntersection.size());
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
        frequencyTracker(orWordIntersection, finalList, freq);
        firstIndex = 0;
        lastIndex = freq.size() - 1;
        frequencySort(finalList, freq, firstIndex, lastIndex);
        for(int i = 0; i < freq.size(); i++)
        {
            freq[i] = freq[i] * log(178800/orWordIntersection.size());
        }
    }
    else if(myStack.inList("AND") == true && myStack.inList("NOT") == false)
    {
        stem(andWord1);
        stem(andWord2);
        myIndex->getPages(andWord1, andWord1List);
        myIndex->getPages(andWord2, andWord2List);
        intersection(andWord1List, andWord2List, andWordIntersection);
        frequencyTracker(andWordIntersection, finalList, freq);
        firstIndex = 0;
        lastIndex = freq.size() - 1;
        frequencySort(finalList, freq, firstIndex, lastIndex);
        for(int i = 0; i < freq.size(); i++)
        {
            freq[i] = freq[i] * log(178800/andWordIntersection.size());
        }
    }
    else if(myStack.inList("OR") == true && myStack.inList("NOT") == false)
    {
        stem(orWord1);
        stem(orWord2);
        myIndex->getPages(orWord1, orWord1List);
        myIndex->getPages(orWord2, orWord2List);
        disjunction(orWord1List, orWord2List, orWordIntersection);
        frequencyTracker(orWordIntersection, finalList, freq);
        firstIndex = 0;
        lastIndex = freq.size() - 1;
        frequencySort(finalList, freq, firstIndex, lastIndex);
        for(int i = 0; i < freq.size(); i++)
        {
            freq[i] = freq[i] * log(178800/orWordIntersection.size());
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
        frequencyTracker(singleSearchWordList, finalList, freq);
        firstIndex = 0;
        lastIndex = freq.size() - 1;
        frequencySort(finalList, freq, firstIndex, lastIndex);
        for(int i = 0; i < freq.size(); i++)
        {
            freq[i] = freq[i] * log(178800/singleSearchWordList.size());
        }
    }
    else //Single word search
    {
        stem(singleSearchWord);
        myIndex->getPages(singleSearchWord, singleSearchWordList);
        frequencyTracker(singleSearchWordList, finalList, freq);
        firstIndex = 0;
        lastIndex = freq.size() - 1;
        for(int i = 0; i < freq.size(); i++)
        {
            freq[i] = freq[i] * log(178800/singleSearchWordList.size());
        }
        frequencySort(finalList, freq, firstIndex, lastIndex);
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

void QueryProcessor::frequencySort(vector<int> &pageList, vector<int> &freq, int &firstIndex, int &lastIndex)
{
    if(pageList.size() != 0)
    {
        int a = firstIndex;
        int b = lastIndex;
        int pageTemp = 0;
        int freqTemp = 0;

        int piv = freq[(firstIndex+lastIndex)/2];

        while (a <= b)
        {
            while (freq[a] > piv)
            {
                a++;
            }
            while (freq[b] < piv)
            {
                b--;
            }
            if (a <= b)
            {
                freqTemp = freq[a];
                freq[a] = freq[b];
                freq[b] = freqTemp;
                pageTemp = pageList[a];
                pageList[a] = pageList[b];
                pageList[b] = pageTemp;
                a++;
                b--;
            }
        }
        if (firstIndex < b)
            frequencySort(pageList, freq, firstIndex, b);
        if (a < lastIndex)
            frequencySort(pageList, freq, a, lastIndex);
    }
}

void QueryProcessor::frequencyTracker(vector<int> &originalPageList, vector<int> &finalList, vector<int> &freq)
{
    int freqTrack = 0;
    int listTrack = 0;
    if(originalPageList.size() != 0)
    {
        int firstElement = originalPageList[0];
        counter = 1;
        finalList.assign(1, firstElement);
        freq.assign(1, 1);
        for(int i = 0; i < originalPageList.size() - 1; i++)
        {
            if(originalPageList[i] == originalPageList[i+1])
            {
                counter++;
                freq[freqTrack] = counter;
            }
            else
            {
                freqTrack++;
                listTrack++;
                counter = 1;
                finalList.push_back(originalPageList[i + 1]);
                freq.push_back(1);
            }
        }
    }
}

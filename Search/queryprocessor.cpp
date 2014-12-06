#include "queryprocessor.h"

QueryProcessor::QueryProcessor()
{
    wordStart = 0;
    wordEnd = 0;
    andTracker = 0;
    orTracker = 0;
    notTracker = 0;
}

void QueryProcessor::first()
{
    std::string blank;
    getline(cin, blank);
}

void QueryProcessor::displayFrequency(IndexInterface* &myIndex, DocIndex &dIndex, DocParse &parser)
{
    QueryProcessor qProcessor;
    //queryString = qProcessor.search(myIndex, finalPageList, frequency);
    qProcessor.first();
    while (queryString != "EXIT")
    {

        queryString = qProcessor.search(myIndex, finalPageList, frequency);
        if(queryString == "EXIT")
        {
            break;
        }
        if(queryString != " ")
        {
            if(finalPageList.size() == 0 || frequency.size() == 0)
            {
                cout << "No Results Returned. Please Search Again" << endl;
            }
            else
            {
                cout << endl;
                cout << "Here are the Most Relevant Results:" << endl;
                for(int i = 0; i < finalPageList.size(); i++)
                {
                    if(i == 15)
                        break;
                    dIndex.getPageInfo(finalPageList[i], title, author, date);
                    cout << i+1 << ". Title: \"" << title << "\" by: " << author << " Date: " << date << "  TF/IDF: " << frequency[i] << endl;
                    cout << endl;
                    cout << endl;
                }
                cout << "1. Search Again" << endl;
                cout << "2. Expand an Article" << endl;
                cout << "Please choose an option from above: ";
                int choice;
                cin >> choice;
                while(choice < 1 || choice > 2)
                {
                    cout << "Error: please enter a valid choice" << endl;
                    cin >> choice;
                }
                if (choice == 2)
                {
                    cout << "To expand an article, enter it's corresponding number: ";
                    cin>>choice;
                    while (choice > 15 || choice < 1)
                    {
                        cout << "Invalid, enter a valid number: ";
                        cin >> choice;
                    }
                    cout << "Please Hold. The page contents will appear soon... " << endl;
                    parser.displayPageContents(finalPageList[choice - 1], dIndex);
                    qProcessor.first();
                }
                else
                {
                    qProcessor.first();
                }
            }
        }
    }
    cout << "Thank You for Using The Wikibooks Search Engine!" << endl;
    cout << "Brought to you by: Steven Bock and Nicholas Roberts" << endl;
    cout << "Goodbye" << endl;
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
    andWordVector.clear();
    orWordVector.clear();
    notWordVector.clear();
    andTracker = 0;
    orTracker = 0;
    notTracker = 0;
    newCounter = 0;
    cout << endl;
    cout << "Search using the following format [<AND/OR> Search Word(s) <NOT> Exclude Word(s)]: ";
    getline(cin, queryString);
    istringstream iss(queryString);
    string i;
    if(queryString != "")
    {
        while(iss >> i)
        {
            word = i;
            if (word == " ")
            {
                return word;
            }
            if (word == "EXIT")
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
                    if(stopRemove.checkWord(word) == false)
                    {
                        andWordVector.push_back(word);
                        andTracker++;
                    }
                }
                else if (firstBoolean == "OR" && secondBoolean != "NOT")
                {
                    if(stopRemove.checkWord(word) == false)
                    {
                        orWordVector.push_back(word);
                        orTracker++;
                    }
                }
                else if (firstBoolean == "AND" && secondBoolean == "NOT")
                {
                    if(stopRemove.checkWord(word) == false)
                    {
                        notWordVector.push_back(word);
                        notTracker++;
                    }
                }
                else if (firstBoolean == "OR" && secondBoolean == "NOT")
                {
                    if(stopRemove.checkWord(word) == false)
                    {
                        notWordVector.push_back(word);
                        notTracker++;
                    }
                }
                else if (firstBoolean != "OR" && firstBoolean != "AND" && secondBoolean == "NOT")
                {
                    if(stopRemove.checkWord(word) == false)
                    {
                        notWordVector.push_back(word);
                        notTracker++;
                    }
                }
                else //No Boolean
                {
                    if(stopRemove.checkWord(word) == false)
                    {
                        singleSearchWord = word;
                    }
                }
            }
        }
        if(myStack.inList("AND") == true && myStack.inList("NOT") == true)
        {
            if(andWordVector.empty() == false && notWordVector.empty() == false)
            {
                for(int i = 0; i < andWordVector.size(); i++)
                {
                    stem(andWordVector[i]);
                }
                for(int i = 0; i < notWordVector.size(); i++)
                {
                    stem(notWordVector[i]);
                }

                myIndex->getPages(andWordVector[0], andWord1List);
                myIndex->getPages(andWordVector[1], andWord2List);
                intersection(andWord1List, andWord2List, andWordIntersection);
                newCounter = 2;
                while(newCounter < andTracker)
                {
                    if(andWordIntersection.empty())
                    {
                        break;
                    }
                    myIndex->getPages(andWordVector[newCounter], andWord1List);
                    intersection(andWord1List, andWordIntersection, andWordIntersection);
                    newCounter++;
                }
                newCounter = 0;
                while(newCounter < notTracker)
                {
                    myIndex->getPages(notWordVector[newCounter], notWordList);
                    for(int j = 0; j < notWordList.size(); j++)
                    {
                        remove(andWordIntersection, notWordList.at(j));
                    }
                    newCounter++;
                }
                frequencyTracker(andWordIntersection, finalList, freq);
                firstIndex = 0;
                lastIndex = freq.size() - 1;
                for(int i = 0; i < freq.size(); i++)
                {
                    freq[i] = freq[i] * log(178800/andWordIntersection.size());
                }
                frequencySort(finalList, freq, firstIndex, lastIndex);
            }
            else if(andWordVector.empty() == false && notWordVector.empty() == true)
            {
                for(int i = 0; i < andWordVector.size(); i++)
                {
                    stem(andWordVector[i]);
                }
                myIndex->getPages(andWordVector[0], andWord1List);
                myIndex->getPages(andWordVector[1], andWord2List);
                intersection(andWord1List, andWord2List, andWordIntersection);
                newCounter = 2;
                while(newCounter < andTracker)
                {
                    if(andWordIntersection.empty())
                    {
                        break;
                    }
                    myIndex->getPages(andWordVector[newCounter], andWord1List);
                    intersection(andWord1List, andWordIntersection, andWordIntersection);
                    newCounter++;
                }
                frequencyTracker(andWordIntersection, finalList, freq);
                firstIndex = 0;
                lastIndex = freq.size() - 1;
                for(int i = 0; i < freq.size(); i++)
                {
                    freq[i] = freq[i] * log(178800/andWordIntersection.size());
                }
                frequencySort(finalList, freq, firstIndex, lastIndex);
            }
        }
        else if(myStack.inList("OR") == true && myStack.inList("NOT") == true)
        {
            if(orWordVector.empty() == false && notWordVector.empty() == false)
            {
                for(int i = 0; i < orWordVector.size(); i++)
                {
                    stem(orWordVector[i]);
                }
                for(int i = 0; i < notWordVector.size(); i++)
                {
                    stem(notWordVector[i]);
                }

                myIndex->getPages(orWordVector[0], orWord1List);
                myIndex->getPages(orWordVector[1], orWord2List);
                disjunction(orWord1List, orWord2List, orWordIntersection);
                newCounter = 2;
                while(newCounter < orTracker)
                {
                    myIndex->getPages(orWordVector[newCounter], orWord1List);
                    disjunction(orWord1List, orWordIntersection, orWordIntersection);
                    newCounter++;
                }
                newCounter = 0;
                while(newCounter < notTracker)
                {
                    myIndex->getPages(notWordVector[newCounter], notWordList);
                    for(int j = 0; j < notWordList.size(); j++)
                    {
                        remove(orWordIntersection, notWordList.at(j));
                    }
                    newCounter++;
                }
                frequencyTracker(orWordIntersection, finalList, freq);
                firstIndex = 0;
                lastIndex = freq.size() - 1;
                for(int i = 0; i < freq.size(); i++)
                {
                    freq[i] = freq[i] * log(178800/orWordIntersection.size());
                }
                frequencySort(finalList, freq, firstIndex, lastIndex);
            }
            else if(orWordVector.empty() == false && notWordVector.empty() == true)
            {
                for(int i = 0; i < orWordVector.size(); i++)
                {
                    stem(orWordVector[i]);
                }
                myIndex->getPages(orWordVector[0], orWord1List);
                myIndex->getPages(orWordVector[1], orWord2List);
                disjunction(orWord1List, orWord2List, orWordIntersection);
                newCounter = 2;
                while(newCounter < orTracker)
                {
                    myIndex->getPages(orWordVector[newCounter], orWord1List);
                    disjunction(orWord1List, orWordIntersection, orWordIntersection);
                    newCounter++;
                }
                frequencyTracker(orWordIntersection, finalList, freq);
                firstIndex = 0;
                lastIndex = freq.size() - 1;
                for(int i = 0; i < freq.size(); i++)
                {
                    freq[i] = freq[i] * log(178800/orWordIntersection.size());
                }
                frequencySort(finalList, freq, firstIndex, lastIndex);
            }
        }
        else if(myStack.inList("AND") == true && myStack.inList("NOT") == false)
        {
            if(andWordVector.empty() == false)
            {
                for(int i = 0; i < andWordVector.size(); i++)
                {
                    stem(andWordVector[i]);
                }
                myIndex->getPages(andWordVector[0], andWord1List);
                myIndex->getPages(andWordVector[1], andWord2List);
                intersection(andWord1List, andWord2List, andWordIntersection);
                newCounter = 2;
                while(newCounter < andTracker)
                {
                    if(andWordIntersection.empty())
                    {
                        break;
                    }
                    myIndex->getPages(andWordVector[newCounter], andWord1List);
                    intersection(andWord1List, andWordIntersection, andWordIntersection);
                    newCounter++;
                }
                frequencyTracker(andWordIntersection, finalList, freq);
                firstIndex = 0;
                lastIndex = freq.size() - 1;
                for(int i = 0; i < freq.size(); i++)
                {
                    freq[i] = freq[i] * log(178800/andWordIntersection.size());
                }
                frequencySort(finalList, freq, firstIndex, lastIndex);
            }
        }
        else if(myStack.inList("OR") == true && myStack.inList("NOT") == false)
        {
            if(orWordVector.empty() == false)
            {
                for(int i = 0; i < orWordVector.size(); i++)
                {
                    stem(orWordVector[i]);
                }
                myIndex->getPages(orWordVector[0], orWord1List);
                myIndex->getPages(orWordVector[1], orWord2List);
                disjunction(orWord1List, orWord2List, orWordIntersection);
                newCounter = 2;
                while(newCounter < orTracker)
                {
                    myIndex->getPages(orWordVector[newCounter], orWord1List);
                    disjunction(orWord1List, orWordIntersection, orWordIntersection);
                    newCounter++;
                }
                frequencyTracker(orWordIntersection, finalList, freq);
                firstIndex = 0;
                lastIndex = freq.size() - 1;
                for(int i = 0; i < freq.size(); i++)
                {
                    freq[i] = freq[i] * log(178800/orWordIntersection.size());
                }
                frequencySort(finalList, freq, firstIndex, lastIndex);
            }
        }
        else if(myStack.inList("AND") == false && myStack.inList("OR") == false && myStack.inList("NOT") == true)
        {
            if(singleSearchWord.empty() == false)
            {
                stem(singleSearchWord);
                if(notWordVector.empty() == false)
                {
                    for(int i = 0; i < notWordVector.size(); i++)
                    {
                        stem(notWordVector[i]);
                    }
                    myIndex->getPages(singleSearchWord, singleSearchWordList);
                    newCounter = 0;
                    while(newCounter < notTracker)
                    {
                        myIndex->getPages(notWordVector[newCounter], notWordList);
                        for(int j = 0; j < notWordList.size(); j++)
                        {
                            remove(singleSearchWordList, notWordList.at(j));
                        }
                        newCounter++;
                    }
                }
                else
                {
                    myIndex->getPages(singleSearchWord, singleSearchWordList);
                }
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
        else //Single word search
        {
            if(singleSearchWord.empty() == false)
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
    }
    else
        return queryString;
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

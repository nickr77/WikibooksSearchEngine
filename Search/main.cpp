#include <iostream>
#include "porter2_stemmer.h"
#include "docparse.h"
#include <chrono>
#include <ctime>
#include <docindex.h>
#include "indexinterface.h"
#include "hashtableinterface.h"
#include "avltreeinterface.h"
#include "docindex.h"
#include "queryprocessor.h"
using namespace std;
using namespace Porter2Stemmer;
void driver(int argc, char* arguments[]);



int main(int argc, char* arguments[])
{
    if (argc == 2)
    {
        driver(argc, arguments);
    }
    else
    {
        cout << "Invalid number of Arguments" << endl;
        cout << "Arguments are : maintain, user, or stress" << endl;
    }
}

void driver(int argc, char *arguments[])
{
    IndexInterface* myIndex;
    int choice = 5;
    cout << "Welcome to the Wikibooks Search Engine!" << endl;
    cout << "Please choose a data structure:" << endl;
    cout << "1. Hash Table" << endl;
    cout << "2. AVL Tree" << endl;
    cout << "0 to exit" << endl;
    while(choice > 2)
    {
        cout << "Enter the corresponding number of the structure you want to use: ";
        cin >> choice;
        if (choice == 1)
        {
            myIndex = new HashTableInterface();
        }
        else if (choice == 2)
        {
            myIndex = new AVLTreeInterface();
        }
        else if (choice == 0)
        {
            return;
        }
        else
        {
            cout << "Error: please enter a valid choice" << endl;
        }
    }
    string cArg = arguments[1];
    DocParse parser;
    DocIndex dIndex;
    QueryProcessor qProcessor;
    if (cArg == "maintain")
    {
        int i = 5;
        string fileName;
        cout << "Welcome to maintainence mode!" << endl;

        parser.readIndex(myIndex, dIndex);

        cout << "What would you like to do?" << endl;
        cout << "1. Add a file to the index." << endl;
        cout << "2. Clear the index." << endl;
        cout << "0. Exit Program." << endl;
        while ( i != 0)
        {
            cout << "Enter the corresponding number: ";
            cin >> i;
            if (i == 1)
            {
                cout << endl << "Enter the file name (with extension): ";
                cin >> fileName;
                parser.parse(myIndex, dIndex, fileName);
            }
            else if (i == 2)
            {
                myIndex->clearIndex();
                dIndex.clearIndex();
                cout << "Index has been cleared" << endl;
            }
            else if (i == 0)
            {

            }
            else
            {
                cout << "Invalid Input, please input a valid number." << endl;
            }
        }







        //parser.parse(myIndex, dIndex);
    }
    if (cArg == "user")
    {
        cout << "User Mode" << endl;
        parser.readIndex(myIndex, dIndex);
        //qProcessor.displayFrequency(myIndex);
    }
    if (cArg == "stress")
    {
        cout << "Stress Test Mode" << endl;
    }
}

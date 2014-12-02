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
using namespace std;
using namespace Porter2Stemmer;
void driver(int argc, char* arguments[]);



int main(int argc, char* arguments[])
{

    driver(argc, arguments);
}

void driver(int argc, char *arguments[])
{
    string cArg = arguments[1];
    DocParse parser;
    DocIndex dIndex;
    IndexInterface* myIndex = new HashTableInterface();
    if (cArg == "maintain")
    {
        cout << "Maintainence Mode" << endl;
    }
    if (cArg == "user")
    {
        cout << "User Mode" << endl;
    }
    if (cArg == "stress")
    {
        cout << "Stress Test Mode" << endl;
    }

    parser.parse(myIndex, dIndex);

}

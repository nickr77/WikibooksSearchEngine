#include <iostream>
#include <stopremover.h>
#include "porter2_stemmer.h"
#include "docparse.h"
using namespace std;
using namespace Porter2Stemmer;
void driver();



int main()
{
    driver();

}

void driver()
{
    DocParse parser;
    cout << "Begin Parsing" << endl;
    parser.parse();
    cout << "End Parsing" << endl;
}

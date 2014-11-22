#include <iostream>
#include "porter2_stemmer.h"
#include "docparse.h"
#include <chrono>
#include <ctime>
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

    parser.parse();

}

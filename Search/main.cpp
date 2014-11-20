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
    cout << "Begin Parsing" << endl;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    parser.parse();
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    cout << "End Parsing" << endl;
    cout << "Elapsed Time: " << elapsed_seconds.count() / 60 << endl;
}

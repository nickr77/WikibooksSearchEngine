#ifndef STRESSTEST_H
#define STRESSTEST_H
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <ctime>
#include "docparse.h"
#include "docindex.h"
#include "indexinterface.h"
#include "hashtableinterface.h"
#include "avltreeinterface.h"
#include "queryprocessor.h"
class StressTest
{
private:
    std::vector<std::string> commands;
public:
    StressTest();
    void getCommands(std::string &fileName);
    void execute(DocParse &parser, DocIndex &dIndex, IndexInterface* &myIndex, QueryProcessor &qProcess);
};

#endif // STRESSTEST_H

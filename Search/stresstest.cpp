#include "stresstest.h"
using namespace std;
StressTest::StressTest()
{
}

void StressTest::getCommands(string &fileName)
{
    ifstream inputFile;
    string line;
    inputFile.open(fileName.c_str());
    if(inputFile.is_open())
    {
        while (getline(inputFile,line))
        {
            commands.push_back(line);
            cout << line << endl;
        }
        inputFile.close();
    }


}

void StressTest::execute(DocParse &parser, DocIndex &dIndex, IndexInterface *&myIndex, QueryProcessor &qProcess)
{
    for (int i = 0; i < commands.size(); i++)
    {
        if (commands[i] == "CLR")
        {
            cout << "Clearing Index" << endl;
            dIndex.clearIndex();
            myIndex->clearIndex();
        }
        else if (commands[i] == "HSH")
        {
            cout << "Creating Hash Table" << endl;
            myIndex = new HashTableInterface();
        }

        else if (commands[i] == "AVL")
        {
            cout << "Creating AVL Tree" << endl;
            myIndex = new AVLTreeInterface();
        }
        else if (commands[i] == "RDI")
        {
            cout << "Reading Index" << endl;
            parser.readIndex(myIndex, dIndex);
        }
        else if (commands[i].find("PAR") != std::string::npos)
        {
            string fName = "";
            string pName = commands[i];
            for(int t = 4; t < pName.size(); t++)
            {

                if (pName[t] == ' ')
                {

                }
                else
                {
                    fName += pName[t];
                    //cout << fName << endl;
                }
            }
            cout << "Parsing " << fName << endl;
            parser.parse(myIndex, dIndex, fName);
        }

    }
}

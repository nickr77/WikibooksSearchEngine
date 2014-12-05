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
            cout << "Clearing Index from RAM and Disk" << endl;
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            dIndex.clearIndex();
            myIndex->clearIndex();

            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            std::time_t end_time = std::chrono::system_clock::to_time_t(end);
            cout << "Elapsed Time: " << elapsed_seconds.count()<< " seconds." << endl;

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

            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            parser.readIndex(myIndex, dIndex);

            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            std::time_t end_time = std::chrono::system_clock::to_time_t(end);
            cout << "Elapsed Time: " << elapsed_seconds.count()<< " seconds." << endl;



        }
        else if (commands[i] == "PCR")
        {
            cout << "Clearing Index from RAM" << endl;

            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            dIndex.partialClear();
            myIndex->partialClear();


            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            std::time_t end_time = std::chrono::system_clock::to_time_t(end);
            cout << "Elapsed Time: " << elapsed_seconds.count()<< " seconds." << endl;

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

            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            parser.parse(myIndex, dIndex, fName);

            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            std::time_t end_time = std::chrono::system_clock::to_time_t(end);
            cout << "Elapsed Time: " << elapsed_seconds.count() / 60 << " minutes." << endl;


        }

    }
}

#ifndef STOPREMOVER_H
#define STOPREMOVER_H
#include <string>
#include <vector>
class StopRemover
{
private:
    std::vector<std::string> stopWords;
public:
    StopRemover();
    bool checkWord(std::string word);

};

#endif // STOPREMOVER_H

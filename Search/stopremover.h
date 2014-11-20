#ifndef STOPREMOVER_H
#define STOPREMOVER_H
#include <string>
#include <unordered_set>
class StopRemover
{
private:
    std::unordered_set<std::string> stopWords;
    std::unordered_set<std::string>::const_iterator exists;
public:
    StopRemover();
    bool checkWord(std::string &word);


};

#endif // STOPREMOVER_H

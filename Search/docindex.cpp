#include "docindex.h"

DocIndex::DocIndex()
{
}

void DocIndex::insert(int &id, std::string &title, std::string &author, std::string &date)
{

        PageInfo page;
        page.setInfo(title,author,date);
        dIndex.insert(std::make_pair(id, page));

}

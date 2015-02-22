#include "site.h"

Site::Site(string n, bool hide, int clearing, vector<Treasure*> * myTreasure): Chit(n, hide)
{
    clearingLocation = clearing;
    trove = myTreasure;
}

Site::~Site()
{
    trove->clear();
    delete trove;
    trove = NULL;
}

int Site::getClearingNum()
{
    return clearingLocation;
}

Treasure* Site::loot(int location)
{
    if(location >= trove->size())
        return NULL;

    Treasure* looted = trove->at(location);
    trove->erase(trove->begin() + location);
    return looted;
}
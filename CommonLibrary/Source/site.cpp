#include "site.h"

Site::Site(string n, bool hide, vector<Treasure*> * myTreasure): Chit(n, hide)
{
    //sites always go on clearing 6???
    clearingLocation = 6;
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
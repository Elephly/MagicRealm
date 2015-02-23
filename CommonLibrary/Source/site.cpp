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

ChitType Site::getType()
{
	return CHIT_SITE;
}
Treasure* Site::loot(int diceUsed)
{
	int position = diceUsed -1;
    if(position >= trove->size())
        return NULL;

    Treasure* looted = trove->at(position);
    trove->erase(trove->begin() + position);
    return looted;
}
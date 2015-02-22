#include "treasure.h"

Treasure::Treasure(string n, int value, TreasureType t)
{
    name = n;
    goldValue = value;
    type = t;
}

string Treasure::getName()
{
    return name;
}

int Treasure::getWorth()
{
    return goldValue;
}

TreasureType Treasure::getType()
{
    return type;
}
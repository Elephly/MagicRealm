#include "treasure.h"

Treasure::Treasure(string n, int value)
{
    name = n;
    goldValue = value;
}

string Treasure::getName()
{
    return name;
}

int Treasure::getWorth()
{
    return goldValue;
}
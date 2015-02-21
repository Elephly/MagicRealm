#include "dwelling.h"

Dwelling::Dwelling(string n, Clearing* loc, bool hide)
{
    name = n;
    location = loc;
    hidden = hide;
}

string Dwelling::getName()
{
    return name;
}

Clearing* Dwelling::getLocation()
{
    return location;
}

bool Dwelling::isHidden()
{
    return hidden;
}
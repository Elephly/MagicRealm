#include "chit.h"

Chit::Chit(string n, bool hide)
{
    name = n;
    hidden = hide;
}

bool Chit::isHidden()
{
    return hidden;
}

string Chit::getName()
{
    return name;
}

void Chit::unhide()
{
    hidden = true;
}

Treasure* Chit::loot(int location)
{
    return NULL;
}
#include "warning.h"

Warning::Warning(string n, bool hide, char type): Chit(n, hide)
{
    tileType = type;
}

char Warning::getTileType()
{
    return tileType;
}
#include "site.h"

Site::Site(string n, bool hide, int clearing): Chit(n, hide)
{
    clearingLocation = clearing;
}

int Site::getClearingNum()
{
    return clearingLocation;
}
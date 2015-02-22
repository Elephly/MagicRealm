#include "sound.h"

Sound::Sound(string n, bool hide, int clnum): Chit(n, hide)
{
    clearingLocation = clnum;
}

int Sound::getClearingNum()
{
    return clearingLocation;
}
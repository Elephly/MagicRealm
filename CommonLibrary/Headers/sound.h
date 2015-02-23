#ifndef SOUND_H
#define SOUND_H

#include "shared.h"
#include "commonlibrary_global.h"

#include "chit.h"

class COMMONLIBRARY_EXPORT Sound: public Chit{
public:
    Sound(string n, bool hide, int clnum);
    virtual int getClearingNum();

private:
    int clearingLocation;
};

#endif //SOUND_H
#ifndef TREASURE_H
#define TREASURE_H

#include "shared.h"
#include "commonlibrary_global.h"

class COMMONLIBRARY_EXPORT Treasure{
public:
    Treasure(string n, int value);
    string getName();
    int getWorth();

private:
    string name;
    int goldValue;
};


#endif //TREASURE_H

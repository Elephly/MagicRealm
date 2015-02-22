#ifndef TREASURE_H
#define TREASURE_H

#include "shared.h"
#include "commonlibrary_global.h"

class COMMONLIBRARY_EXPORT Treasure{
public:
    Treasure(string n, int value, TreasureType t);
    string getName();
    int getWorth();
    TreasureType getType();

private:
    string name;
    int goldValue;
    TreasureType type;
};


#endif //TREASURE_H

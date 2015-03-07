#ifndef TREASURE_H
#define TREASURE_H

#include "shared.h"
#include "commonlibrary_global.h"

class COMMONLIBRARY_EXPORT Treasure{
public:
    Treasure(string n, TreasureType t);
    string getName();
    int getWorth();
	int getFame();
	int getNotoriety();
    TreasureType getType();

private:
    string name;
    int goldValue;
	int notorietyValue;
	int fameValue;
    TreasureType type;
	void generateGold();
	void generateFame();
	void generateNotoriety();
};


#endif //TREASURE_H

#ifndef CHARACTER_H
#define CHARACTER_H

#include "commonlibrary_global.h"
#include "clearing.h"
#include "shared.h"
#include "equipment.h"
#include <vector>

//forward declare
class Clearing;

//Abstract class, extend this with all different Character types
class  COMMONLIBRARY_EXPORT Character{
public:
	Character();
	int getGold();
	vector<Equipment *> getEquipment();
	Clearing* getCurrentLocation();
	void moveToClearing(Clearing *destination);
	bool hasAdvantage(CharAdvantages);
protected:
	int gold;
	Clearing *location;
	CharAdvantages advantages[2];
	vector<Equipment *> *equipment;
};

#endif // CHARACTER_H
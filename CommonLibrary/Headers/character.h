#ifndef CHARACTER_H
#define CHARACTER_H

#include "commonlibrary_global.h"
#include "clearing.h"
#include "shared.h"
#include "equipment.h"
#include "serializer.h"
#include <vector>
#include <string>

//forward declare
class Clearing;

//Abstract class, extend this with all different Character types
class  COMMONLIBRARY_EXPORT Character : public Serializer{
public:
	Character(CharacterTypes type);
	Character(string* serialString);
	int getGold();
	vector<Equipment *>* getEquipment();
	Clearing* getCurrentLocation();
	void moveToClearing(Clearing *destination);
	bool hasAdvantage(CharAdvantages);
	virtual string* serialize();

private:
	CharacterTypes myType;
	int gold;
	Clearing *location;
	CharAdvantages advantages[2];
	vector<Equipment *> *equipment;

	//private functions
	void initAmazon();
	void initBlackknight();
	void initCaptain();
	void initDwarf();
	void initElf();
	void initSwordsman();
};

#endif // CHARACTER_H
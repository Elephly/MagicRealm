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

private:
	int gold;
	Clearing *location;
	CharAdvantages advantages[2];
	std::vector<Equipment> *equipment;
};

#endif // CHARACTER_H
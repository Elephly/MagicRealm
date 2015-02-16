#include "character.h"

Character::Character(CharacterTypes type) {
	myType = type;
	gold = 10;
	switch (type) {
	case Amazon:
		advantages[0] = AIM;
		advantages[1] = STAMINA;
		break;
	case BlackKnight:
		advantages[0] = AIM;
		advantages[1] = FEAR;
		break;
	case Captain:
		advantages[0] = AIM;
		advantages[1] = REPUTATION;
		break;
	case Dwarf:
		advantages[0] = SHORTLEGS;
		advantages[1] = CAVEKNOWLEGDE;
		break;
	case Elf:
		advantages[0] = ELUSIVNESS;
		advantages[1] = ARCHER;
		break;
	case Swordsman:
		advantages[0] = BARTER;
		advantages[1] = CLEAVER;
		break;
	}
	//TODO setup equipment
}

int Character::getGold() {
	return gold;
}

Clearing* Character::getCurrentLocation() {
	return location;
}

vector<Equipment *>* Character::getEquipment() {
	return equipment;
}

void  Character::moveToClearing(Clearing *destination) {
	location = destination;
}

bool Character::hasAdvantage(CharAdvantages testAdvantage) {
	bool result = false;
	
	if (testAdvantage == advantages[0] || testAdvantage == advantages[1]) {
		result = true;
	}

	return result;
}
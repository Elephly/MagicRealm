#include "character.h"

Character::Character() {
	//whole lotta nothing
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
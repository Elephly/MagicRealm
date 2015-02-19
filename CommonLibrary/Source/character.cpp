#include "character.h"
#include "weapon.h"
#include "armor.h"
#include <sstream>

Character::Character(CharacterTypes type) {
	myType = type;
	gold = 10;
	equipment = new vector<Equipment*>();
	switch (type) {
	case Amazon: initAmazon();
		break;
	case BlackKnight: initBlackknight();
		break;
	case Captain: initCaptain();
		break;
	case Dwarf: initDwarf();
		break;
	case Elf: initElf();
		break;
	case Swordsman: initSwordsman();
		break;
	}
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

string* Character::serialize() {
	stringstream s;
	s << "Character";
	s << CLASSDELIM;
	s << myType;

	return new string(s.str());
}

//Character inits
void Character::initAmazon() {
	advantages[0] = AIM;
	advantages[1] = STAMINA;
	equipment->push_back(new Weapon(ShortSword));
	equipment->push_back(new Armor(Helmet));
	equipment->push_back(new Armor(Shield));
	equipment->push_back(new Armor(Breastplate));
}

void Character::initBlackknight() {
	advantages[0] = AIM;
	advantages[1] = FEAR;
	equipment->push_back(new Weapon(Mace));
	equipment->push_back(new Armor(Shield));
	equipment->push_back(new Armor(Suit));
}

void Character::initCaptain() {
	advantages[0] = AIM;
	advantages[1] = REPUTATION;
	equipment->push_back(new Weapon(ShortSword));
	equipment->push_back(new Armor(Helmet));
	equipment->push_back(new Armor(Shield));
	equipment->push_back(new Armor(Breastplate));
}

void Character::initDwarf() {
	advantages[0] = SHORTLEGS;
	advantages[1] = CAVEKNOWLEGDE;
	equipment->push_back(new Weapon(GreatAxe));
	equipment->push_back(new Armor(Helmet));
}

void Character::initElf() {
	advantages[0] = ELUSIVNESS;
	advantages[1] = ARCHER;
	equipment->push_back(new Weapon(LightBow));
}

void Character::initSwordsman() {
	advantages[0] = BARTER;
	advantages[1] = CLEAVER;
	equipment->push_back(new Weapon(ThrustingSword));
}
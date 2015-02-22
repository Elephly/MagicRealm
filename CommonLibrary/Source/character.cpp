#include "character.h"
#include "weapon.h"
#include "armor.h"
#include <sstream>

Character::Character(CharacterTypes type) {
    hidden = false;
	init(type);
}

Character::Character(string* serialString) {
	knownPaths = new vector <Path*>;
    int pos = serialString->find(CLASSDELIM);
	string first = serialString->substr(0, pos);
	string second = serialString->substr(pos + 2);

	pos = second.find(VARDELIM);
	first = second.substr(0, pos);
	second= second.substr(pos + 1);
	init((CharacterTypes) atoi(first.c_str()));

	pos = second.find(VARDELIM);
	first = second.substr(0, pos);
	second = second.substr(pos + 1);
	gold = atoi(second.c_str());
}

void Character::init(CharacterTypes type) {
	myType = type;
	gold = 10;
    location = NULL;
    knownPaths = new vector <Path*>;
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

CharacterTypes Character::getType()
{
	return myType;
}

bool Character::isDiscovered(Path* aPath)
{
    return false;
}

void Character::addPath(Path* discoveredPath)
{
    //checking to see if the path is already in this list.
    for(vector<Path*>::iterator it = knownPaths->begin(); it != knownPaths->end(); ++it){
        if(*it == discoveredPath){
            cout << "WARN: Path already known to Character, not adding to list" <<endl;
            return;
        }
    }
    knownPaths->push_back(discoveredPath);
}

bool Character::isHidden()
{
    return hidden;
}

void Character::toggleHide()
{
    hidden = !hidden;
}

char* Character::getTypeString(CharacterTypes t)
{
	switch (t)
	{
	case Amazon:
		return "Amazon";
		break;
	case BlackKnight:
		return "Black Knight";
		break;
	case Captain:
		return "Captain";
		break;
	case Dwarf:
		return "Dwarf";
		break;
	case Elf:
		return "Elf";
		break;
	case Swordsman:
		return "Swordsman";
		break;
	default:
		return "?";
		break;
	}
}

vector<DwellingType>* Character::getStartLocations(CharacterTypes t)
{
	vector<DwellingType>* out = new vector<DwellingType>();
	switch (t)
	{
	case Amazon:
		out->push_back(INN);
		break;
	case BlackKnight:
		out->push_back(INN);
		break;
	case Captain:
		out->push_back(INN);
		out->push_back(HOUSE);
		out->push_back(GUARD);
		break;
	case Dwarf:
		out->push_back(INN);
		out->push_back(GUARD);
		break;
	case Elf:
		out->push_back(INN);
		break;
	case Swordsman:
		out->push_back(INN);
		break;
	default:
		break;
	}
	return out;
}

string* Character::serialize() {
	stringstream s;
	s << "Character";
	s << CLASSDELIM;
	s << myType;
	s << VARDELIM;
	s << gold;
	//TODO serialize character equipment

	string *myString = new string(s.str());
	return myString;
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
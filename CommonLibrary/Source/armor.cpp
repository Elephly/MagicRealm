#include "armor.h"

Armor::Armor(ArmorType type, string n): Equipment(n) 
{
	this->type = type;
	damaged = false;
	switch (type) {
	case Helmet: break;
	case Breastplate: break;
	case Shield: break;
	case Suit: break;
	default: break;
	}
}
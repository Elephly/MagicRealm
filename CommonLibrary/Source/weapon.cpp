#include "weapon.h"

Weapon::Weapon(WeaponType type, string n): Equipment(n) 
{
	this->type = type;
	active = false;
	switch (type) {
	case MediumBow: length = 16;
		attackType = Missile;
		break;
	case LightBow: length = 14;
		attackType = Missile;
		break;
	case CrossBow: length = 12;
		attackType = Missile;
		break;
	case Spear: length = 10;
		attackType = Striking;
		break;
	case Staff: length = 9;
		attackType = Striking;
		break;
	case GreatSword: length = 8;
		attackType = Striking;
		break;
	case BroadSword: length = 7;
		attackType = Striking;
		break;
	case MorningStar: length = 6;
		attackType = Striking;
		break;
	case GreatAxe:  length = 5;
		attackType = Striking;
		break;
	case ThrustingSword: length = 4;
		attackType = Striking;
		break;
	case ShortSword: length = 3;
		attackType = Striking;
		break;
	case Axe: length = 2;
		attackType = Striking;
		break;
	case Mace: length = 1;
		attackType = Striking;
		break;
	default: break;
	}
}
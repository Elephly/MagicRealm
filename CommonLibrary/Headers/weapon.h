#ifndef WEPAON_H
#define WEAPON_H

#include "shared.h"
#include "equipment.h"

class COMMONLIBRARY_EXPORT Weapon : public Equipment {
public:
	Weapon(WeaponType type, string n);
	bool getActive();
	void setActive(bool);
	int getLength();

	EquipmentType getType();

private:
	bool active;
	WeaponType type;
	int length;
	int sharpness;
	AttackType attackType;
};

#endif // WEAPON_H
#ifndef ARMOR_H
#define ARMOR_H

#include "shared.h"
#include "equipment.h"

class COMMONLIBRARY_EXPORT Armor : public Equipment {
public:
	Armor(ArmorType type, string n);
	bool isDamaged();
	void setDamaged(bool status);

private:
	ArmorType type;
	bool damaged;
};

#endif // ARMOR_H
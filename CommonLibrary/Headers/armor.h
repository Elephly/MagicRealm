#ifndef ARMOR_H
#define ARMOR_H

#include "shared.h"
#include "equipment.h"

class COMMONLIBRARY_EXPORT Armor : public Equipment {
public:
	Armor(ArmorType type, string n);

private:
	ArmorType type;
	bool damaged;
};

#endif // ARMOR_H
#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "commonlibrary_global.h"
#include "shared.h"

class COMMONLIBRARY_EXPORT Equipment {
public:
	Equipment(string n);
	string getName();

	virtual bool getActive();
	virtual void setActive(bool act);
	virtual bool isDamaged();
	virtual void setDamaged(bool status);
	virtual int getLength();
	virtual EquipmentType getType() = 0;

protected:
	char weightClass;
	int value;
	string name;
};

#endif // EQUIPMENT_H
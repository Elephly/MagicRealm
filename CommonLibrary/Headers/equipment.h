#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "commonlibrary_global.h"
#include "shared.h"

class COMMONLIBRARY_EXPORT Equipment {
public:
	Equipment(string n);
	string getName();

protected:
	char weightClass;
	int value;
	string name;
};

#endif // EQUIPMENT_H
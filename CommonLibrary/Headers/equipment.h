#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "commonlibrary_global.h"
#include "shared.h"

class COMMONLIBRARY_EXPORT Equipment {
public:
	Equipment();

protected:
	char weightClass;
	int value;
};

#endif // EQUIPMENT_H
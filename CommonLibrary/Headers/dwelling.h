#ifndef DWELLING_H
#define DWELLING_H

#include "commonlibrary_global.h"
#include "shared.h"
#include "clearing.h"

class COMMONLIBRARY_EXPORT Dwelling{
public:
    Dwelling(DwellingType t, Clearing* loc, bool hide);
    string getName();
    Clearing* getLocation();
    bool isHidden();
	DwellingType getType();
	string toString();
	static char* getTypeString(DwellingType t);

private:
    string name;
    Clearing* location;
    bool hidden;
	DwellingType type;
};
#endif //DWELLING_H
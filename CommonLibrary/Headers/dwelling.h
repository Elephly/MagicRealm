#ifndef DWELLING_H
#define DWELLING_H

#include "commonlibrary_global.h"
#include "shared.h"
#include "clearing.h"

class COMMONLIBRARY_EXPORT Dwelling{
public:
    Dwelling(string n, Clearing* loc, bool hide);
    string getName();
    Clearing* getLocation();
    bool isHidden();

private:
    string name;
    Clearing* location;
    bool hidden;
};
#endif //DWELLING_H
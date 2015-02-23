#ifndef CHIT_H
#define CHIT_H

#include "shared.h"
#include "commonlibrary_global.h"
#include "treasure.h"

class COMMONLIBRARY_EXPORT Chit {
public:
    Chit(string n, bool hide);
    bool isHidden();
    string getName();
    /*
    *   unHide()
    *   Purpose:    to make the chit not hidden
    */
    void unhide();

    virtual Treasure* loot(int location);
	virtual int getClearingNum();
	virtual ChitType getType() = 0;

protected:
    string name;
    bool hidden;
};

#endif //SITE_H
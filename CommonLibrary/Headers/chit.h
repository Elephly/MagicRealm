#ifndef CHIT_H
#define CHIT_H

#include "shared.h"
#include "commonlibrary_global.h"
#include "treasure.h"
#include "serializer.h"
#include <vector>
#include <sstream>

class COMMONLIBRARY_EXPORT Chit : public Serializer {
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
	virtual vector<Chit *>* getContents();
	virtual string* serialize();
protected:
    string name;
    bool hidden;
};

#endif //SITE_H
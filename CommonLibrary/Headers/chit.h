#ifndef CHIT_H
#define CHIT_H

#include "shared.h"
#include "commonlibrary_global.h"

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

protected:
    string name;
    bool hidden;
};

#endif //SITE_H
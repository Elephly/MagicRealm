#ifndef SITE_H
#define SITE_H

#include "shared.h"
#include "commonlibrary_global.h"

#include "chit.h"

class COMMONLIBRARY_EXPORT Site: public Chit {
public:
    Site(string n, bool hide, int clearing);
    int getClearingNum();

protected:
    int clearingLocation;
};

#endif //SITE_H
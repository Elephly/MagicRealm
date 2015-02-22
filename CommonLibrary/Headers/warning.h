#ifndef WARN_H
#define WARN_H

#include "shared.h"
#include "commonlibrary_global.h"

#include "chit.h"

class COMMONLIBRARY_EXPORT Warning: public Chit{
public:
    Warning(string n, bool hide, char type);
    char getTileType();

private:
    char tileType;
};

#endif //SITE_H
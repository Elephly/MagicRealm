#ifndef WARN_H
#define WARN_H

#include "shared.h"
#include "commonlibrary_global.h"

#include "chit.h"

class COMMONLIBRARY_EXPORT Warning: public Chit{
public:
    Warning(string n, bool hide);
	virtual ChitType getType();
private:
};

#endif //SITE_H
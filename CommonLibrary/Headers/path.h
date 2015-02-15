#ifndef PATH_H
#define PATH_H

#include "commonlibrary_global.h"
#include "shared.h"
#include "clearing.h"

//forward declare
class Clearing;

class COMMONLIBRARY_EXPORT Path {
public:
	Path(Clearing c1, Clearing C2, bool isHidden);

private:
	bool hidden;
	Clearing clearing1;
	Clearing clearing2;
};

#endif // PATH_H
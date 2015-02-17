#ifndef ACTION_H
#define ACTION_H

#include "shared.h"
#include "clearing.h"

class COMMONLIBRARY_EXPORT Action {
public:
	Action();
private:
	Clearing *targetClearing;
	ActionType myAction;
}

#endif // ACTION_H
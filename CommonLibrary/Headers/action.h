#ifndef ACTION_H
#define ACTION_H

#include "shared.h"
#include "clearing.h"
#include "serializer.h"
#include "board.h"

class COMMONLIBRARY_EXPORT Action : public Serializer {
public:
	Action(ActionType, Clearing*);
	Action(string*, Board*);
	Clearing* getTarget();
	ActionType getAction();
	virtual string* serialize();
private:
	Clearing *targetClearing;
	ActionType myAction;
};

#endif // ACTION_H
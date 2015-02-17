#ifndef RECORDEDTURN_H
#define RECORDEDTURN_H

#include "shared.h"
#include "action.h"
#include <vector>

class COMMONLIBRARY_EXPORT RecordedTurn {
public:
	RecordedTurn();
private:
	vector<Action*> *actions;
};

#endif // RECORDEDTURN_H
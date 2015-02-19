#ifndef RECORDEDTURN_H
#define RECORDEDTURN_H

#include "shared.h"
#include "action.h"
#include <vector>
#include <map>
#include "serializer.h"

class COMMONLIBRARY_EXPORT RecordedTurn : public Serializer {
public:
	RecordedTurn();
	RecordedTurn(string*);

	/*
	returns result code, 1 for ok, 0 for unable to add action
	*/
	int addAction(Action*, PhaseType);
	virtual string* serialize();
private:
	vector<Action*> *actions;
	map<PhaseType, int> *availablePhases;
};

#endif // RECORDEDTURN_H
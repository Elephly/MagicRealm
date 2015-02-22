#ifndef RECORDEDTURN_H
#define RECORDEDTURN_H

#include "shared.h"
#include "action.h"
#include <vector>
#include <map>
#include "serializer.h"
#include "board.h"

class COMMONLIBRARY_EXPORT RecordedTurn : public Serializer {
public:
	RecordedTurn();
	RecordedTurn(string*);
	RecordedTurn(string*, Board*);
	~RecordedTurn();


	vector<Action*>* getActions();
	/*
	returns result code, true for ok, false for unable to add action
	*/
	bool addAction(Action*, PhaseType);
	void addPhase(PhaseType, int count = 1);
	virtual string* serialize();
private:
	vector<Action*> *actions;
	map<PhaseType, int> *availablePhases;
};

#endif // RECORDEDTURN_H
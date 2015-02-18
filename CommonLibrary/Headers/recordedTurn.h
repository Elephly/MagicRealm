#ifndef RECORDEDTURN_H
#define RECORDEDTURN_H

#include "shared.h"
#include "action.h"
#include <vector>
#include "serializer.h"

class COMMONLIBRARY_EXPORT RecordedTurn : public Serializer {
public:
	RecordedTurn();
	RecordedTurn(string*);
	virtual string* serialize();
	void addAction(Action*);
private:
	vector<Action*> *actions;
};

#endif // RECORDEDTURN_H
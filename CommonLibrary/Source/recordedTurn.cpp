#include "recordedTurn.h"

RecordedTurn::RecordedTurn() {
	actions = new vector<Action*>();
}

void RecordedTurn::addAction(Action *action) {
	actions->push_back(action);
}

string* RecordedTurn::serialize() {
	string *myString = new string();
	*myString += "RecordedTurn**";
	for (int i =0; i < actions->size(); i++) {
		*myString += *(actions->at(i)->serialize());
	}
	return myString;
}
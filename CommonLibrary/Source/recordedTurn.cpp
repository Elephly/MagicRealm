#include "recordedTurn.h"
#include <sstream>

RecordedTurn::RecordedTurn() {
	actions = new vector<Action*>();
	availablePhases = new map<PhaseType, int>();
}

RecordedTurn::RecordedTurn(string* serializedString) {
	actions = new vector<Action*>();
	availablePhases = new map<PhaseType, int>();
}

int RecordedTurn::addAction(Action *action, PhaseType phase) {
	int result = 0;
	map<PhaseType, int>::iterator myiter = availablePhases->find(phase);
	if (myiter != availablePhases->end()) {
		if (myiter->second > 0) {
			actions->push_back(action);
			myiter->second--;
			result = 1;
		}
	}

	return result;
}

string* RecordedTurn::serialize() {
	ostringstream s;
	s << "RecordedTurn" << CLASSDELIM;
	for (vector<Action*>::iterator it = actions->begin(); it != actions->end(); ++it) {
		s << *((*it)->serialize()) << LISTDELIM;
	}

	s << VARDELIM;

	for(map<PhaseType, int>::iterator it = availablePhases->begin(); 
		it != availablePhases->end(); 
		++it) {
			s << it->first << VARDELIM << it->second << LISTDELIM;
	}

	s << CLASSDELIM;
	
	string *myString = &(s.str());
	return myString;
}
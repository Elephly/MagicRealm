#include "recordedTurn.h"
#include <sstream>
#include <QtCore>

RecordedTurn::RecordedTurn() {
	actions = new vector<Action*>();
	availablePhases = new map<PhaseType, int>();
}

RecordedTurn::RecordedTurn(string* serializedString, Board* gameBoard) {
	actions = new vector<Action*>();
	availablePhases = new map<PhaseType, int>();

	int pos = serializedString->find(CLASSDELIM);

	string second = serializedString->substr(pos + 2);
	string first;
	//create list of actions
	do {
		int delimPos = second.find(LISTDELIM);
		first = second.substr(0, delimPos);
		qDebug() << QString(first.c_str()) << ", " << QString(second.c_str());
		actions->push_back(new Action(&first, gameBoard));

		second = second.substr(delimPos + 1);
	} while(second.at(0) != '^');

	second = second.substr(1);
	first = "";
	do {
		int delimPos = second.find(LISTDELIM);
		first = second.substr(0, delimPos);
		// we have "key^value"
		second = second.substr(delimPos + 1);
		string s1;
		string s2;
		delimPos = first.find(VARDELIM);
		s1 = first.substr(0, delimPos);
		s2 = first.substr(delimPos + 1);

		availablePhases->insert(map<PhaseType, int>::value_type((PhaseType) atoi(s1.c_str()), (int) atoi(s2.c_str())));

	} while(second.at(0) != '*');
}

RecordedTurn::RecordedTurn(string* serializedString) {
	actions = new vector<Action*>();
	availablePhases = new map<PhaseType, int>();

	int pos = serializedString->find(CLASSDELIM);

	string second = serializedString->substr(pos + 2);
	string first;
	second = second.substr(1);
	first = "";
	do {
		int delimPos = second.find(LISTDELIM);
		first = second.substr(0, delimPos);
		// we have "key^value"
		second = second.substr(delimPos + 1);
		string s1;
		string s2;
		delimPos = first.find(VARDELIM);
		s1 = first.substr(0, delimPos);
		s2 = first.substr(delimPos + 1);

		availablePhases->insert(map<PhaseType, int>::value_type((PhaseType) atoi(s1.c_str()), (int) atoi(s2.c_str())));

	} while(second.at(0) != '*');
}

RecordedTurn::~RecordedTurn() {
	delete actions;
	delete availablePhases;
}

bool RecordedTurn::addAction(Action *action, PhaseType phase) {
	bool result = false;
	map<PhaseType, int>::iterator myiter = availablePhases->find(phase);
	if (myiter != availablePhases->end()) {
		if (myiter->second > 0) {
			actions->push_back(action);
			myiter->second--;
			result = true;
		}
	}

	return result;
}

void RecordedTurn::addPhase(PhaseType phase, int count) {
	(*availablePhases)[phase] += count;
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
	
	string *myString = new string(s.str());
	return myString;
}

vector<Action*>* RecordedTurn::getActions() {
	return actions;
}
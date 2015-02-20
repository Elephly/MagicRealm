#include "action.h"
#include <sstream>

Action::Action(ActionType action, Clearing* target) {
	myAction = action;
	targetClearing = target;
}

Action::Action(string* serializedString, Board *gameBoard) {
	int delimPos = serializedString->find(CLASSDELIM);

	string var1 = serializedString->substr(0, delimPos);
	string var2 = serializedString->substr(delimPos + 2); //+2 due to length of CLASSDELIM

	delimPos = var2.find(VARDELIM);
	var1 = var2.substr(0, delimPos);
	var2 = var2.substr(delimPos + 1);
	myAction = (ActionType) atoi(var1.c_str());

	delimPos = var2.find(VARDELIM);
	string tileName = var2.substr(0, delimPos);
	int clearingNum = (int) atoi(var2.substr(delimPos +1).c_str());

	targetClearing = gameBoard->getTile(tileName)->getClearing(clearingNum);
}

ActionType Action::getAction() {
	return myAction;
}

Clearing* Action::getTarget() {
	return targetClearing;
}

string* Action::serialize() {
	ostringstream s;
	s << "Action" << CLASSDELIM << (int)myAction << VARDELIM << *(targetClearing->toString());

	string *myString = new string(s.str());
	return myString;
}
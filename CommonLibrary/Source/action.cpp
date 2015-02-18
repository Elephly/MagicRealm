#include "action.h"
#include <sstream>

Action::Action(ActionType action, Clearing* target) {
	myAction = action;
	targetClearing = target;
}

ActionType Action::getAction() {
	return myAction;
}

Clearing* Action::getTarget() {
	return targetClearing;
}

Action::Action(string* serializedString) {

}

string* Action::serialize() {
	ostringstream s;
	s << "Action" << "**" << (int)myAction << "^" << targetClearing->toString();
	string *myString = new string();
	*myString = s.str();
	return myString;
}
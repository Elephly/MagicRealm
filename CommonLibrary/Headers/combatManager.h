#ifndef COMBAT_MANAGER_H
#define COMBAT_MANAGER_H

#include "shared.h"
#include "character.h"
#include "commonlibrary_global.h"


class COMMONLIBRARY_EXPORT CombatManager
{
public:
    CombatManager(Character* attacker, Character* defender);
	
	Character* getAttacker();
	Character* getDefender();

private:
	Character* attacker;
	Character* defender;
};

#endif //COUNTER_H
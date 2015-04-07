#include "combatManager.h"

CombatManager::CombatManager(Character* a, Character* d){
	attacker = a;
	defender = d;
	currentPhase = PHASE_ENCOUNTER;
}

Character* CombatManager::getAttacker(){
	return attacker;
}

Character* CombatManager::getDefender(){
	return defender;
}
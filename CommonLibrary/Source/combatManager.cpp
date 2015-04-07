#include "combatManager.h"

CombatManager::CombatManager(Character* a, Character* d){
	attacker = a;
	defender = d;
	currentPhase = PHASE_ENCOUNTER;
	attackerMoveCounter = NULL;
	defenderMoveCounter = NULL;
	attackerFightCounter = NULL;
	defenderFightCounter = NULL;

	attackerFlee = false;
	defenderFlee = false;
	firstMelee = true;
	stageWinAttacker = false;
}

Character* CombatManager::getAttacker(){
	return attacker;
}

Character* CombatManager::getDefender(){
	return defender;
}

void CombatManager::submitEncounter(Character* combatant,  bool run, Counter* counterUsed)
{
	if(combatant == attacker){
		attackerFlee = run;
	}
	else if (combatant == defender){
		defenderFlee = run;
	}
	else{
		cout << "ERR: CombatManager::submitEncounter ::: Combatant not Attacker or Defender" << endl;
	}
	
	setupMoveCounter(combatant, counterUsed);
}

CombatPhaseType CombatManager::getCurrentPhase()
{
	return currentPhase;
}
void CombatManager::runEncounter()
{
	if(attackerMoveCounter == NULL){
		stageWinAttacker = false;
		return;
	}
	else if(defenderMoveCounter == NULL){
		stageWinAttacker = true;
		return;
	}

	if(attackerMoveCounter->getSpeed() == defenderMoveCounter->getSpeed()){
		if(!attackerFlee)
			stageWinAttacker = true;
		if(!defenderFlee)
			stageWinAttacker = false;
	}
	//if attacker Move is faster then the attacker won.
	(attackerMoveCounter->getSpeed() < defenderMoveCounter->getSpeed()) ? stageWinAttacker = true : stageWinAttacker = false;
	currentPhase = EncounterVictorRun() ? PHASE_FLEE : PHASE_MELEE;
}

 Character* CombatManager::getPhaseWinner()
{
	return stageWinAttacker ? attacker : defender;
}

bool CombatManager::EncounterVictorRun()
{
	return stageWinAttacker ? attackerFlee : defenderFlee;
}

void CombatManager::submitMelee(Character* combatant, Counter* fCounter, CombatFightType fType, Counter* mCounter, CombatMoveType mType)
{
	setupFightCounter(combatant, fCounter);
	setupMoveCounter(combatant, mCounter);

	if(combatant == attacker){
		attackerMoveType = mType;
		attackerFightType = fType;
		return;
	}
	if(combatant == defender){
		defenderMoveType = mType;
		defenderFightType = fType;
		return;
	}
}

void CombatManager::setupMoveCounter(Character* combatant, Counter* counterUsed){
	bool isAttacker = false;

	vector<Counter *>* characterCounters = combatant->getCounters();
	if(combatant == attacker)
		isAttacker = true;
	if(combatant == defender)
		isAttacker = false;

	if(counterUsed == NULL || counterUsed->getType() != COUNTER_MOVE){
		cout << "Attacker used invalid counter for Encounter Step" <<endl;
		isAttacker? attackerMoveCounter = NULL : defenderMoveCounter = NULL;
	}
	for(vector<Counter*>::iterator iter = characterCounters->begin(); iter != characterCounters->end(); ++iter){
		if((*iter)->getID() == counterUsed->getID() && counterUsed->isAvailable()){
			isAttacker? attackerMoveCounter = (*iter) : defenderMoveCounter = (*iter);
		}
	}
}

void CombatManager::setupFightCounter(Character* combatant, Counter* counterUsed){
	bool isAttacker = false;

	vector<Counter *>* characterCounters = combatant->getCounters();
	if(combatant == attacker)
		isAttacker = true;
	if(combatant == defender)
		isAttacker = false;

	if(counterUsed == NULL || counterUsed->getType() != COUNTER_FIGHT){
		cout << "Attacker used invalid counter for Encounter Step" <<endl;
		isAttacker? attackerFightCounter = NULL : defenderFightCounter = NULL;
	}
	for(vector<Counter*>::iterator iter = characterCounters->begin(); iter != characterCounters->end(); ++iter){
		if((*iter)->getID() == counterUsed->getID() && counterUsed->isAvailable()){
			isAttacker? attackerFightCounter = (*iter) : defenderFightCounter = (*iter);
		}
	}
}

void CombatManager::runMelee()
{

}


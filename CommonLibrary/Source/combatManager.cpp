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

	attackerResult = ACTION_MISS;
	defenderResult = ACTION_MISS;
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

void CombatManager::submitMelee(Character* combatant, Counter* fCounter, CombatFightType fType, Counter* mCounter, CombatMoveType mType, CombatShieldBlock sBlock)
{
	setupFightCounter(combatant, fCounter);
	setupMoveCounter(combatant, mCounter);

	if(combatant == attacker){
		attackerMoveType = mType;
		attackerFightType = fType;
		attackerBlock = sBlock;
		return;
	}
	if(combatant == defender){
		defenderMoveType = mType;
		defenderFightType = fType;
		defenderBlock = sBlock;
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
	bool attackerFirst = true;

	bool firstHitSecond = false;
	bool secondHitFirst = false;

	Counter* firstMoveCounter;
	Counter* secondMoveCounter;

	Counter* firstFightCounter;
	Counter* secondFightCounter;

	CombatFightType firstFightType;
	CombatFightType secondFightType;

	CombatMoveType firstMoveType;
	CombatMoveType secondMoveType;

	CombatShieldBlock firstBlock;
	CombatShieldBlock secondBlock;
	vector<Equipment*>* firstEquipment;
	vector<Equipment*>* secondEquipment;


	int attackerLength;
	int defenderLength;
	vector<Equipment*>* attackerEquipment = attacker->getEquipment();
	vector<Equipment*>* defenderEquipment = defender->getEquipment();
	//getting weapon lengths
	for(vector<Equipment*>::iterator iter = attackerEquipment->begin(); iter != attackerEquipment->end(); ++iter){
			if((*iter)->getType() == EQUIPMENT_WEAPON){
				attackerLength = (*iter)->getLength();
				break;
			}
		}
	for(vector<Equipment*>::iterator iter = defenderEquipment->begin(); iter != defenderEquipment->end(); ++iter){
			if((*iter)->getType() == EQUIPMENT_WEAPON){
				defenderLength = (*iter)->getLength();
				break;
			}
		}
	//determining who attacks first.
	if(firstMelee){
		firstMelee = false;
		if(attackerLength == defenderLength)
			attackerFirst = (attackerFightCounter->getSpeed() <= defenderFightCounter->getSpeed());
		else
			attackerFirst = (attackerLength < defenderLength);
	}
	else{
		if(attackerFightCounter->getSpeed() == defenderFightCounter->getSpeed())
			attackerFirst = (attackerLength < defenderLength);
		else
			attackerFirst = (attackerFightCounter->getSpeed() < defenderFightCounter->getSpeed());
	}

	//Ordering the attackers
	if(attackerFirst){
		firstMoveCounter = attackerMoveCounter;
		secondMoveCounter = defenderMoveCounter;

		firstFightCounter = attackerFightCounter;
		secondFightCounter = defenderFightCounter;

		firstFightType = attackerFightType;
		secondFightType = defenderFightType;

		firstMoveType = attackerMoveType;
		secondMoveType = defenderMoveType;

		firstBlock = attackerBlock;
		secondBlock = defenderBlock;

		firstEquipment = attackerEquipment;
		secondEquipment = defenderEquipment;
	}
	else{
		firstMoveCounter = defenderMoveCounter;
		secondMoveCounter = attackerMoveCounter;

		firstFightCounter = defenderFightCounter;
		secondFightCounter = attackerFightCounter;

		firstFightType = defenderFightType;
		secondFightType = attackerFightType;

		firstMoveType = defenderMoveType;
		secondMoveType = attackerMoveType;

		firstBlock = defenderBlock;
		secondBlock = attackerBlock;

		firstEquipment = defenderEquipment;
		secondEquipment = attackerEquipment;
	}
	//now execute the combat

	//executing first person to go
	firstHitSecond = (firstFightCounter->getSpeed() < secondMoveCounter->getSpeed()); //checking auto hit
	if(!firstHitSecond) //check lineup
		firstHitSecond = hitScan(firstFightType, secondMoveType);

	//if hit calculate damage done.

	if(firstHitSecond){
		if(!wasBlocked(secondEquipment, secondBlock, firstFightType)){
			if(attackerFirst)
				defenderResult = ACTION_WOUND;
			else
				attackerResult = ACTION_WOUND;
			cout << "First Player Cut off the Head of Second Player" << endl;
		}
		else{
			if(attackerFirst)
				defenderResult = ACTION_DAMAGED;
			else
				attackerResult = ACTION_DAMAGED;
		}
	}
	else{
		if(attackerFirst)
				defenderResult = ACTION_MISS;
			else
				attackerResult = ACTION_MISS;
	}
	
	//executing second person to go
	secondHitFirst = (secondMoveCounter->getSpeed() < firstFightCounter->getSpeed()); //checking auto hit
	if(!secondHitFirst) //check lineup
		secondHitFirst = hitScan(secondFightType, firstMoveType);

	//if hit calculate damage done.

	if(secondHitFirst){
		if(!wasBlocked(firstEquipment, firstBlock, secondFightType)){
			if(!attackerFirst)
				defenderResult = ACTION_WOUND;
			else
				attackerResult = ACTION_WOUND;
			cout << "Second Player Cut off the Head of First Player" << endl;
		}
		else{
			if(!attackerFirst)
				defenderResult = ACTION_DAMAGED;
			else
				attackerResult = ACTION_DAMAGED;
		}
	}
	else{
		if(!attackerFirst)
				defenderResult = ACTION_MISS;
			else
				attackerResult = ACTION_MISS;
	}
	//phase is now over result phase kicks in
	currentPhase = PHASE_RESOLVE;
}

//TODO runRESOLVE PHASE!!!!!
//TODO MISSILE COMBAT HANDLING

bool CombatManager::hitScan(CombatFightType firstFight, CombatMoveType secondMove)
{
	if(firstFight == FIGHT_THRUST && secondMove == MOVE_CHARGE)
		return true;
	if(firstFight == FIGHT_SWING && secondMove == MOVE_DODGE)
		return true;
	if(firstFight == FIGHT_SMASH && secondMove == MOVE_DUCK)
		return true;
	else
		return false;
}

bool CombatManager::wasBlocked(vector<Equipment*>* targetEquipment, CombatShieldBlock shielded, CombatFightType fightType)
{
	bool hasArmor = false;
	Equipment* shield = NULL;
	Equipment* breastplate = NULL;
	Equipment* helmet = NULL;
	Equipment* suit = NULL;
	
	//checking shield
	for(vector<Equipment *>::iterator iter = targetEquipment->begin(); iter != targetEquipment->end(); ++iter){
		if((*iter)->getName() == "Shield"){
				hasArmor = true;
				shield = (*iter);
				break;
		}
	}
	if(hasArmor && !shield->isDamaged()){
		if((shielded == SHIELD_THRUST && fightType == FIGHT_THRUST)
			|| (shielded == SHIELD_SWING && fightType == FIGHT_SWING)
			|| (shielded == SHIELD_SMASH && fightType == FIGHT_SMASH)){
			shield->setDamaged(true);
			return true;
		}
	}
	hasArmor = false;
	//checking breastplate
	for(vector<Equipment *>::iterator iter = targetEquipment->begin(); iter != targetEquipment->end(); ++iter){
		if((*iter)->getName() == "Breastplate"){
				hasArmor = true;
				breastplate = (*iter);
				break;
		}
	}
	if(hasArmor && !breastplate->isDamaged()){
		if(fightType == FIGHT_THRUST || fightType == FIGHT_SWING){
			breastplate->setDamaged(true);
			return true;
		}
	}
	hasArmor = false;

	//checking helmet
	for(vector<Equipment *>::iterator iter = targetEquipment->begin(); iter != targetEquipment->end(); ++iter){
		if((*iter)->getName() == "Helmet"){
				hasArmor = true;
				helmet = (*iter);
				break;
		}
	}
	if(hasArmor && !helmet->isDamaged()){
		if(fightType == FIGHT_SMASH){
			helmet->setDamaged(true);
			return true;
		}
	}
	hasArmor = false;

	//checking suit of armor
	for(vector<Equipment *>::iterator iter = targetEquipment->begin(); iter != targetEquipment->end(); ++iter){
		if((*iter)->getName() == "Suit"){
				hasArmor = true;
				helmet = (*iter);
				break;
		}
	}
	if(hasArmor && !suit->isDamaged()){
			suit->setDamaged(true);
			return true;
	}

	//no armor to protect you son :(

	return false;
}
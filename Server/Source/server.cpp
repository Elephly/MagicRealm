#include "server.h"

Server::Server(int port, QObject *parent = 0) : QObject(parent) {
	myPort = port;
	std::cout << "port is: " << myPort << std::endl;
	clientThreadList = new std::vector<ClientCommThread *>;
	incoming = new QTcpServer(parent);
	blockRes = false;
	blockCheckNum = 0;
	currentDay = 1;
	combat = NULL;
	combatCounter = 0;
	monsterCombatCount = 0;

	for (int i = 0; i < MAXPLAYERS; ++i) {
		selectedCharacters[i] = false;
		recTurns[i] = NULL;
	}

	QObject::connect(incoming,
		SIGNAL(newConnection()),
		this,
		SLOT(handleIncomingUsers()));
}

Server::~Server() {

}

void Server::run() {
	std::cout << "Starting up the server" << std::endl;
	bool cheatMode = false;
	cout << "Cheat Mode? (0/1)" <<endl;
	cin >> cheatMode;
	incoming->listen(QHostAddress::Any, (quint16) myPort);
	std::cout << "listening for connections" << std::endl;
    game.setupGame(cheatMode);
    //ONLY BE ACTIVATED TO RUN SPECIFIC TESTS DOES NOT CLEAN UP AFTER ITSELF
    //game.testGame();
}

void Server::handleIncomingUsers()  {
	std::cout << "new user incoming" << std::endl;
		
	if(incoming->hasPendingConnections()) {
		QTcpSocket *newClient = incoming->nextPendingConnection();
		if (clientThreadList->size() >= MAXPLAYERS) {
			std::cout << "new user has been rejected" << std::endl;
			newClient->write(DECLINECONN);
			newClient->close();
		} else {
			ClientCommThread *newThread = new ClientCommThread(newClient, this,
				clientThreadList->size());
			connect(newThread, SIGNAL(characterSelected(CharacterType, int)),
				this, SLOT(characterUnavail(CharacterType, int)));
			connect(newThread, SIGNAL(spawnSelected(DwellingType, int)),
				this, SLOT(setSpawn(DwellingType, int)));
			connect(newThread, SIGNAL(incomingTurn(QString&, int)), 
				this, SLOT(recordedTurn(QString&, int)));
			connect(newThread, SIGNAL(searchTypeReturned()),
				this, SLOT(endAction()));
			connect(newThread, SIGNAL(blockCheckReturn(bool, CharacterType)), 
				this, SLOT(blockResp(bool, CharacterType)));
			connect(newThread, SIGNAL(monsterCombatReturned(int, int, CharacterType)),
				this, SLOT(monsterCombatResp(int, int, CharacterType)));
			connect(newThread, SIGNAL(subEncounterC(CharacterType, bool, int)),
				this, SLOT(subEncounter(CharacterType, bool, int)));
			connect(newThread, SIGNAL(subMeleeC(CharacterType,int, CombatFightType, int, CombatMoveType, CombatShieldBlock)),
				this, SLOT(subMelee(CharacterType,int, CombatFightType, int, CombatMoveType, CombatShieldBlock)));
			connect(newThread, SIGNAL(playerWoundedC(CharacterType, vector<int>)),
				this, SLOT(playerWounded(CharacterType, vector<int>)));
			connect(newThread, SIGNAL(restResponseC(CharacterType, int)),
				this, SLOT(restResponse(CharacterType, int)));
			clientThreadList->push_back(newThread);
			std::cout << "new user has been accepted" << std::endl;
			stringstream s;
			s << ACCEPTCONN;
			s << CLASSDELIM;
			s << game.getTime();
			newThread->writeMessage(new string(s.str()));	//send the connection OK message
			sendBoard(newThread);

			//Inform new player of currently selected characters
			for (int i = 0; i < MAXPLAYERS; ++i) {
				if (selectedCharacters[i]) {
					stringstream s;
					s << "CharacterType";
					s << CLASSDELIM;
					s << i;
					newThread->writeMessage(new string(s.str()));
				}
			}
			for (int i = 0; i < MAXPLAYERS; ++i) {
				Character *character = game.getPlayer((CharacterType) i);
				if (character != NULL) {
					newThread->writeMessage(character->serialize());
					stringstream s;
					s << "MoveCharacter";
					s << CLASSDELIM;
					s << i;
					s << VARDELIM;
					s << *(character->getCurrentLocation()->toString());
					newThread->writeMessage(new string(s.str()));
				}
			}
			//todo send player locations to new players
		}
	}
}

void Server::characterUnavail(CharacterType type, int clientID) {
	stringstream s;
	s << "CharacterType";
	s << CLASSDELIM;
	s << type;
	
	stringstream s2;
	s2 << "Selection";
	s2 << CLASSDELIM;

	//check if character is in use
	if (selectedCharacters[(int) type]) {
		s2 << false;
	} else {
		s2 << true;
		selectedCharacters[(int) type] = true;
		game.addPlayer(type);
		writeMessageAllClients(new string(s.str()));
		writeMessageAllClients(game.getPlayer(type)->serialize());
	}
	string *message = new string(s2.str());;
	clientThreadList->at(clientID)->writeMessage(message);
}

void Server::setSpawn(DwellingType type, int clientID) {
	moveCharacter(game.getPlayer(clientThreadList->at(clientID)->getMyCharacter()),
		game.getDwelling(type)->getLocation());

	calculatePlayerTurnPhases(clientThreadList->at(clientID));
}

void Server::moveCharacter(Character *character, Clearing *dest) {
	bool result = game.moveRequest(character, dest);
	if (result) {
		stringstream s;

		s << "MoveCharacter";
		s << CLASSDELIM;
		s << character->getType();
		s << VARDELIM;
		s << *(dest->toString());
		writeMessageAllClients(new string(s.str()));
	}
}

void Server::writeMessageAllClients(string *message) {
	writeMessageAllClients(new QString(message->c_str()));
	delete message;
}

void Server::writeMessageAllClients(QString *message) {
	for (vector<ClientCommThread*>::iterator it = clientThreadList->begin();
		it != clientThreadList->end(); ++it) {
			(*it)->writeMessage(message);
	}
}

/*
We have received a recorded turn for the given client
*/
void Server::recordedTurn(QString &turn, int clientID) {
	string *s = new string(turn.toUtf8().constData());
	RecordedTurn *recTurn = new RecordedTurn(s, game.getBoard());
	recTurns[clientID] = recTurn;
	int count = 0;
	for (int i = 0; i < MAXPLAYERS; ++i) {
		if (recTurns[i] != NULL)
			++count;
	}
	if (count == clientThreadList->size()) {
		//stop accepting connections
		incoming->pauseAccepting();
		qDebug() << "no longer accepting connections";
		//start game at sunrise
		sunrise();
	}
}

/*
Creates a RecordedTurn object with the number of each type of phase
sends the serialized version of the object to the client

Birdsong stage of game
*/
void Server::calculatePlayerTurnPhases(ClientCommThread *client) {
	Character *player = game.getPlayer(client->getMyCharacter());
	RecordedTurn turn;
	turn.addPhase(BasicPhase, 2); //all players get two basic phases.
	if (player->hasAdvantage(STAMINA)) {
		turn.addPhase(MovePhase);
	}
	if (!player->hasAdvantage(SHORTLEGS)) {
		//if not in caves
		if (player->getCurrentLocation()->getClearingType() != CAVES) {
			turn.addPhase(SunlightPhase, 2);
		}
	}
	if (player->hasAdvantage(ELUSIVNESS)) {
		turn.addPhase(HidePhase);
	}
	if (player->hasAdvantage(REPUTATION)) {
		if (player->getCurrentLocation()->getDwelling() != NULL) {
			turn.addPhase(BasicPhase);
		}
	}

	client->writeMessage(turn.serialize());
}

void Server::birdsong() {
	qDebug() << "birdsong begins";
	qDebug() << "start of day: " << currentDay;
	for (vector<ClientCommThread*>::iterator it = clientThreadList->begin();
		it != clientThreadList->end(); ++it)
	{
		calculatePlayerTurnPhases((*it));
	}
}

//Determine what monsters are prwoling
void Server::sunrise() {
	qDebug() << "sunrise begins";
    daylight();
}

//play player turns in random order
void Server::daylight() {
	game.checkBlocks();

	qDebug() << "unhiding all players";
	for (vector<ClientCommThread*>::iterator it = clientThreadList->begin();
		it != clientThreadList->end(); ++it) {
			if (game.getPlayer((*it)->getMyCharacter())->isBlocked()) {
				stringstream s;
				s << "Blocked";
				s << CLASSDELIM;
				s << (*it)->getMyCharacter();
				writeMessageAllClients(new string(s.str()));
			}
			if(game.getPlayer((*it)->getMyCharacter())->isHidden()) {
				game.getPlayer((*it)->getMyCharacter())->toggleHide();
				stringstream s;
				s << "Hidden";
				s << CLASSDELIM;
				s << (*it)->getMyCharacter();
				s << VARDELIM;
				s << false;
				writeMessageAllClients(new string(s.str()));
			}
	}
	startPlayerTurn();
}

void Server::startPlayerTurn() {
	currentPlayer = 0;
	do {
		currentPlayer = game.rollDice() -1;
		qDebug() << "rolled: " << currentPlayer;
		qDebug() << "array value: " << recTurns[currentPlayer];
	} while(recTurns[currentPlayer] == NULL);
	qDebug() << "selected player: " << currentPlayer;
	currentAction = recTurns[currentPlayer]->getActions()->begin();
	if (currentAction != recTurns[currentPlayer]->getActions()->end()) {
		startAction();
	} else {
		endPlayerTurn();
	}
}

void Server::startAction() {
	qDebug() << "performing action";
	stringstream s;
	Character *character = game.getPlayer(clientThreadList->at(currentPlayer)->getMyCharacter());
	switch ((*currentAction)->getAction()) {
	case MoveAction: {
		//check target for other players, if any ask if they wish to block
		bool waitForBlockResp = false;
		const vector<Character*>* clearingOccupants = (*currentAction)->getTarget()->getCharacters();
		if (clearingOccupants->size() > 0) {
			s << "BlockRequest";
			s << CLASSDELIM;
			s << character->getType();
			waitForBlockResp = true;
			blockCheckNum = 0;
			blockRes = false;
			for (vector<Character*>::const_iterator it = clearingOccupants->begin(); it != clearingOccupants->end(); ++it) {
				CharacterType t = (*it)->getType();
				for (vector<ClientCommThread*>::iterator citer = clientThreadList->begin(); citer != clientThreadList->end(); ++citer) {
					if (t == (*citer)->getMyCharacter()) {
						++blockCheckNum;
						(*citer)->writeMessage(new string(s.str()));
					}
				}
			}
		}
		moveCharacter(character, (*currentAction)->getTarget());
		if (!waitForBlockResp) {
			endAction();
		}
		break;
	}
	case SearchAction: 
		s << "SearchTypeReq";
		s << CLASSDELIM;
		s << PEER;
		s << VARDELIM;
		s << LOCATE;
		if (game.canLoot(character)) {
			s << VARDELIM;
			s << LOOT;
		}
		clientThreadList->at(currentPlayer)->writeMessage(new string(s.str()));
		qDebug() << "wating for response from client";
		break;
	case TradeAction: break; //Not implemented yet
	case HideAction: {
		bool result = game.hideRequest(character);
		s << "Hidden";
		s << CLASSDELIM;
		s << clientThreadList->at(currentPlayer)->getMyCharacter();
		s << VARDELIM;
		s << result;
		writeMessageAllClients(new string(s.str()));
		endAction();
		break;
					 }
	case RestAction:
		clientThreadList->at(currentPlayer)->writeMessage(new string("RestRequest"));
	}
}

void Server::endAction() {
	SearchType sType;
	Character *character = game.getPlayer(clientThreadList->at(currentPlayer)->getMyCharacter());
	switch ((*currentAction)->getAction())
	{
	case MoveAction: 
		if (blockCheckNum > 0) {
			return;
		} else {
			if (blockRes) {
				//end player turn
				character->setBlock(true);
				//TODO setBlock for the player that blocked
				stringstream s;
				s << "Blocked";
				s << CLASSDELIM;
				s << character->getType();
				writeMessageAllClients(new string(s.str()));
				while(currentAction != recTurns[currentPlayer]->getActions()->end())
				{
					delete (*currentAction);
					++currentAction;
				}
				endPlayerTurn();
				return;
			}
		}
		break;
	case SearchAction:
		sType = clientThreadList->at(currentPlayer)->getSearchTypeResult();
		searchClearing(character, sType, (*currentAction)->getTarget());
		break;
	case RestAction: //TODO do stuff with response
		break;
	}

	delete (*currentAction);
	++currentAction;
	if (currentAction != recTurns[currentPlayer]->getActions()->end()) {
		startAction();
	} else {
		endPlayerTurn();
	}
}

void Server::endPlayerTurn() {
	delete recTurns[currentPlayer];
	recTurns[currentPlayer] = NULL;
	if (turnExists()) {
		startPlayerTurn();
	} else {
		sunset();
	}
}

bool Server::turnExists() {
	for (int i = 0; i < MAXPLAYERS; ++i) {
		if (recTurns[i] != NULL)
			return true;
	}
	return false;
}

void Server::sunset() {
	qDebug() << "sunset begins";
    evening();
}

//randomly select clearings with players in them
//player can rearrange belongings (not needed for iter 1)
//combat?
void Server::evening() {
	qDebug() << "evening begins";
	game.spawnMonsters(game.rollDice());
	game.moveMonsters();
	for (vector<Monster*>::iterator iter = game.getActiveMonsters()->begin(); iter != game.getActiveMonsters()->end(); ++iter) 
	{
		stringstream s;
		s << "Monster";
		s << CLASSDELIM;
		s << (*iter)->getID();
		s << VARDELIM;
		s << (*iter)->getLocation()->getTile()->getName();
		s << VARDELIM;
		s << (*iter)->getLocation()->getClearingNum();
		writeMessageAllClients(new string(s.str()));
	}
	monsterCombatCount = 0;
	for (vector<ClientCommThread*>::iterator it = clientThreadList->begin(); it != clientThreadList->end(); ++it) {
		vector<Monster*>* monsterList = game.getPlayer((*it)->getMyCharacter())->getCurrentLocation()->getMonsterList();
		if (monsterList->size() > 0) {
			for (vector<Monster*>::iterator iter = monsterList->begin(); iter != monsterList->end(); ++iter) {
				++monsterCombatCount;
				stringstream s;
				s << "FightMonsterReq";
				s << CLASSDELIM;
				s << (*iter)->getID();
				(*it)->writeMessage(new string(s.str()));
			}
		}
	}
	//TODO perform combat stuff
	if (monsterCombatCount == 0)
		startPlayerCombat();
}

void Server::startPlayerCombat() {
	//loop through all players, check for other players in same location
	for (vector<ClientCommThread*>::iterator it = clientThreadList->begin(); it != clientThreadList->end(); ++it) {
		Character* p1 = game.getPlayer((*it)->getMyCharacter());
		Character* p2 = NULL;
		if (p1->getCurrentLocation()->getCharacters()->size() > 1) {
			p2 = p1->getCurrentLocation()->getCharacters()->at(0);
			if (p2 == p1) {
				p2 = p1->getCurrentLocation()->getCharacters()->at(1);
			}
			if (combat != NULL) {
				delete combat;
			}
			ClientCommThread* temp = lookupClient(p1->getType());
			if (temp != NULL) {
				stringstream s;
				s << "PlayerCombatEncounter";
				s << CLASSDELIM;
				s << p2->getType();
				temp->writeMessage(new string(s.str()));
			}
			temp = lookupClient(p2->getType());
			if (temp != NULL) {
				stringstream s;
				s << "PlayerCombatEncounter";
				s << CLASSDELIM;
				s << p1->getType();
				temp->writeMessage(new string(s.str()));
			}
			combatCounter = 2;
			combat = new CombatManager(p1, p2);
			break;
		}
	}
	if (combat == NULL)
		endPlayerCombat();
}

void Server::subEncounter(CharacterType character, bool run, int counter) {
	qDebug() << "combatCounter = " << combatCounter;
	--combatCounter;
	qDebug() << "combatCounter = " << combatCounter;
	Character* player = game.getPlayer(character);
	Counter* actionCounter = NULL;
	for (vector<Counter*>::iterator it = player->getCounters()->begin(); it != player->getCounters()->end(); ++it) {
		if ((*it)->getID() == counter) {
			actionCounter = (*it);
			break;
		}
	}
	combat->submitEncounter(player, run, actionCounter);
	if (combatCounter == 0) {
		combat->runEncounter();
		ClientCommThread* p1 = lookupClient(combat->getAttacker()->getType());
		ClientCommThread* p2 = lookupClient(combat->getDefender()->getType());
		if (combat->EncounterVictorRun()) {
			string* mString = new string("PlayerCombatFlee");
			p1->writeMessage(mString);
			p2->writeMessage(mString);
			endPlayerCombat();
		} else {
			combatCounter = 2;
			string* mString = new string("PlayerCombatMelee");
			p1->writeMessage(mString);
			p2->writeMessage(mString);
		}
	}
}

void Server::subMelee(CharacterType character, int fightC, CombatFightType cfType, int moveC, CombatMoveType cmType, CombatShieldBlock cbType) {
	--combatCounter;
	Character* player = game.getPlayer(character);
	Counter* fightCounter = NULL, *moveCounter = NULL;
	for (vector<Counter*>::iterator it = player->getCounters()->begin(); it != player->getCounters()->end(); ++it) {
		if ((*it)->getID() == fightC)
			fightCounter = (*it);
		if ((*it)->getID() == moveC)
			moveCounter = (*it);
	}
	combat->submitMelee(player,fightCounter, cfType, moveCounter, cmType, cbType);
	if (combatCounter == 0) {
		combat->runMelee();
		combat->runResolve();
		Character *p1 = NULL, *p2 = NULL;
		CombatActionType p1Action, p2Action;
		p1 = combat->getAttacker();
		p2 = combat->getDefender();
		p1Action = combat->getResult(p1);
		p2Action = combat->getResult(p2);
		ClientCommThread *client1, *client2;
		client1 = lookupClient(p1->getType());
		client2 = lookupClient(p2->getType());
		switch(p1Action) {
		case ACTION_DAMAGED: {
			Equipment* damaged = combat->getDamaged(p1);
			stringstream s;
			s << "DamagedEquipment";
			s << CLASSDELIM;
			s << p1->getType();
			s << VARDELIM;
			s << damaged->getName();
			writeMessageAllClients(new string(s.str()));
			break;
							 }
		case ACTION_WOUND: {
			int wounds = combat->getWounds(p1);
			stringstream s;
			s << "Wounds";
			s << CLASSDELIM;
			s << wounds;
			client1->writeMessage(new string(s.str()));
			break;
						   }
		}
		switch(p2Action) {
		case ACTION_DAMAGED: {
			Equipment* damaged = combat->getDamaged(p2);
			stringstream s;
			s << CLASSDELIM;
			s << p2->getType();
			s << VARDELIM;
			s << damaged->getType();
			writeMessageAllClients(new string(s.str()));
			break;
							 }
		case ACTION_WOUND: {
			int wounds = combat->getWounds(p2);
			stringstream s;
			s << "Wounds";
			s << CLASSDELIM;
			s << wounds;
			client2->writeMessage(new string(s.str()));
			break;
						   }
		}
		switch(combat->getCurrentPhase()) {
		case PHASE_DEAD: 
			//someone is dead, end combat
			endPlayerCombat();
			break;
		case PHASE_MISSED:
			endPlayerCombat();
			break;
		case PHASE_ENCOUNTER:
			combatCounter = 2;
			stringstream s;
			s << "PlayerCombatEncounter";
			s << CLASSDELIM;
			s << client2->getMyCharacter();
			client1->writeMessage(new string(s.str()));
			stringstream s2;
			s2 << "PlayerCombatEncounter";
			s2 << CLASSDELIM;
			s2 << client1->getMyCharacter();
			client2->writeMessage(new string(s2.str()));
			break;
		}
	}
}

void Server::playerWounded(CharacterType character, vector<int> stuff) {
	if (character != NullCharacter)
	{
		Character* player = game.getPlayer(character);
		if (player != 0)
		{
			vector<Counter*>* counters = player->getCounters();
			lookupClient(character);
			for (vector<Counter*>::iterator iter = counters->begin(); iter != counters->end(); ++iter) {
				for (vector<int>::iterator it = stuff.begin(); it != stuff.end(); ++it) {
					if ((*iter)->getID() == (*it)) {
						combat->woundCounter((*iter));
						stringstream s;
						s << "WoundedPlayer";
						s << CLASSDELIM;
						s << character;
						s << VARDELIM;
						s << (*it);
						writeMessageAllClients(new string(s.str()));
					}
				}
			}
		}
	}
}

void Server::endPlayerCombat() {
	//if (combat != NULL) //can't do this since the playerwounded stuff will probably come in after
	//	delete combat;
	midnight();
}

//reset all face up mapchits
//start new day
void Server::midnight() {
	qDebug() << "midnight begins";
	++currentDay;
	if (currentDay > 28) {
		//TODO calculate winner gold+ 2*fame + 2*noter
		Character* highscore = NULL;
		for (vector<ClientCommThread*>::iterator it = clientThreadList->begin(); it != clientThreadList->end(); ++it) {
			Character* temp = game.getPlayer((*it)->getMyCharacter());
			if (highscore == NULL)
				highscore = temp;
			else if ((temp->getGold() + 2*temp->getFame() + 2*temp->getNotoriety()) > (highscore->getGold() +
				2*highscore->getFame() + 2*highscore->getNotoriety()))
				highscore = temp;
		}
		stringstream s;
		s << "GameOver";
		s << CLASSDELIM;
		s << highscore->getType();
		writeMessageAllClients(new string(s.str()));
	} else {
		birdsong();
	}
}
/*
Searches the players current location
*/
void Server::searchClearing(Character *character, SearchType type, Clearing *target) {
	DiscoveryType discover = DISCOVER_NOTHING;
	stringstream s;
	Treasure* found = NULL;
	switch(type) {
	case PEER: 
		discover = game.searchPeerRequest();
		break;
	case LOCATE: 
		discover = game.searchLocateRequest();
		break;
	case LOOT: 
		found = game.searchLootRequest(character);
		int worth;
        int fame;
        int notoriety;
		if (found != NULL) {
			worth = found->getWorth();
			character->addGold(worth);
            fame = found->getFame();
            character->addFame(fame);
            notoriety = found->getNotoriety();
            character->addNotoriety(notoriety);
		}
		s << "TreasureFound";
		s << CLASSDELIM;
		s << worth;
		s << VARDELIM;
        s << fame;
		s << VARDELIM;
        s << notoriety;
		s << VARDELIM;
		s << character->getType();
		break;
	}
	Chit* site = NULL;
	switch(discover) {
	case DISCOVER_HENEMIES: break;
	case DISCOVER_ENEMAPATH: 
	case DISCOVER_HPATH: break;
	case DISCOVER_PATHACLUES: 
	case DISCOVER_CLUES: break;
	case DISCOVER_PASSACLUES: 
	case DISCOVER_SPASS: break;
	case DISCOVER_CHIT: 
		site = target->getTile()->getSiteOrSoundChit();
		//bug we do not handle LOST CITY / LOST CASTLE here...
		if (site->getType() == CHIT_LOST) {
			int i = 0;
			vector<Chit*> *contents = site->getContents();
			do {
				site = contents->at(i);
				++i;
			} while((i < contents->size()) 
				&& ((site->getType() != CHIT_SITE)
				&&(site->getClearingNum() != character->getCurrentLocation()->getClearingNum())));
		}
		if (site != NULL && site->getType() == CHIT_SITE) {
			character->discover(site);
			s << "SiteFound";
			s << CLASSDELIM;
			s << site->getName();
			s << VARDELIM;
			s << character->getType();
		}
		break;
	case DISCOVER_CHOICE: break;
	}
	writeMessageAllClients(new string(s.str()));
	//TODO handle result of search and send message
}

/*
Attempt to the player at the current location
*/
void Server::hidePlayer(Character *character) {
	bool result = game.hideRequest(character);
	stringstream s;
	s << "Hidden";
	s << CLASSDELIM;
	s << character->getType();
	s << VARDELIM;
	s << result;

	writeMessageAllClients(new string(s.str()));
}

void Server::sendBoard(ClientCommThread* client) {

	vector<Tile*> tiles = *(game.getBoard()->getTiles());
	for (vector<Tile*>::iterator it = tiles.begin(); it != tiles.end(); ++it) 
	{
		for (int i = 0; i < 2; ++i) //loop twice 
		{   //once to handle site/sound chit, once to handle warning
			stringstream s;
			Chit* chit;
			if (i == 0)
				chit = (*it)->getSiteOrSoundChit();
			else if (i == 1)
				chit = (*it)->getWarningChit();
			if (chit == NULL)
				continue;
			s << *(chit->serialize());
			s << "Tile";
			s << CLASSDELIM;
			s << (*it)->getName(); //name of tile
			if (chit->getType() == CHIT_LOST) 
			{ //LOST CITY, has multiple inner chits
				vector <Chit*> contents = (*chit->getContents());
				for (vector<Chit*>::iterator chiter = contents.begin(); 
					chiter != contents.end(); ++chiter) 
				{
					s << LISTDELIM;
					s << *((*chiter)->serialize());
				}
			}
			client->writeMessage(new string(s.str()));
		}
	}
}

void Server::blockResp(bool answer, CharacterType responder) {
	if (answer) {
		blockRes = true;
		game.getPlayer(responder)->setBlock(true);
	}
	--blockCheckNum;
	endAction();
}

//result 0 = fought, result 1 = no fight
void Server::monsterCombatResp(int result, int monsterID, CharacterType player) {
	--monsterCombatCount;
	//TODO handle result of monster combat here
	//if success update player with fame noteriety, kill monster. notify all players
	if (result == 1) {
		vector<Monster*>* monsters = game.getActiveMonsters();
		Monster* myMonster = NULL;
		for (vector<Monster*>::iterator it = monsters->begin(); it != monsters->end(); ++it){
			if ((*it)->getID() == monsterID) {
				myMonster = (*it);
				break;
			}
		}
		if (myMonster != NULL) {
			game.killMonster(myMonster, game.getPlayer(player));
			stringstream s;
			s << "KillMonster";
			s << CLASSDELIM;
			s << monsterID;
			s << VARDELIM;
			s << player;

			writeMessageAllClients(new string(s.str()));
		}
	}
	if (monsterCombatCount == 0)
		startPlayerCombat();
}

ClientCommThread* Server::lookupClient(CharacterType type) {
	for (vector<ClientCommThread*>::iterator it = clientThreadList->begin(); it != clientThreadList->end(); ++it) {
		if ((*it)->getMyCharacter() == type)
			return (*it);
	}
	return NULL;
}

void Server::restResponse(CharacterType character, int counterId) {
	Character* player = game.getPlayer(character);
	Counter *repairThis = NULL;
	for (vector<Counter*>::iterator it = player->getCounters()->begin(); it != player->getCounters()->end(); ++it) {
		if ((*it)->getID() == counterId) {
			repairThis = (*it);
		}
	}

	if (repairThis != NULL) {
		game.restCounter(repairThis);
		stringstream s;
		s << "RestCounter";
		s << CLASSDELIM;
		s << character;
		s << VARDELIM;
		s << counterId;
		writeMessageAllClients(new string(s.str()));
	}
}
#include "server.h"

Server::Server(int port, QObject *parent = 0) : QObject(parent) {
	myPort = port;
	std::cout << "port is: " << myPort << std::endl;
	clientThreadList = new std::vector<ClientCommThread *>;
	incoming = new QTcpServer(parent);

	for (int i = 0; i < MAXPLAYERS; ++i) {
		selectedCharacters[i] = false;
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

	incoming->listen(QHostAddress::Any, (quint16) myPort);
	std::cout << "listening for connections" << std::endl;
    game.setupGame(false);
    game.runGame();
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
			clientThreadList->push_back(newThread);
			std::cout << "new user has been accepted" << std::endl;
			newThread->writeMessage(new QString(ACCEPTCONN));

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
	game.moveRequest(character, dest);

	stringstream s;

	s << "MoveCharacter";
	s << CLASSDELIM;
	s << character->getType();
	s << VARDELIM;
	s << *(dest->toString());
	writeMessageAllClients(new string(s.str()));
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
	receivedRecTurn[clientID] = true;
	recTurns[clientID] = recTurn;
	int count = 0;
	for (int i = 0; i < MAXPLAYERS; ++i) {
		if (receivedRecTurn[i])
			++count;
	}
	if (count = clientThreadList->size()) {
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
	for (vector<ClientCommThread*>::iterator it = clientThreadList->begin();
		it != clientThreadList->end(); ++it)
	{
		calculatePlayerTurnPhases((*it));
	}
}

//Determine what monsters are prwoling
void Server::sunrise() {
	qDebug() << "sunrise begins";
	int roll = game.rollDice();
    daylight();
}

//play player turns in random order
void Server::daylight() {
	qDebug() << "daylight begins";
    //execute the TURNS per player here.
	do {
		int player = 0;
		do {
			player = game.rollDice();
		} while(recTurns[player] != NULL);

		RecordedTurn *turn = recTurns[player];

		vector<Action*> *act = turn->getActions();
		for (vector<Action*>::iterator it = act->begin(); it != act->end(); ++it) {
			switch ((*it)->getAction()) {
			case MoveAction: 
				moveCharacter(game.getPlayer(clientThreadList->at(player)->getMyCharacter()),
					(*it)->getTarget());
				break;
			case SearchAction: break; //Not implemented yet
			case TradeAction: break; //Not implemented yet
			case HideAction: break; //Not implemented yet
			case PeerAction: break; //Not implemented yet
			}

			delete (*it);
		}

		delete turn;
		recTurns[player] = NULL;
	} while (turnExists());
	sunset();
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
    midnight();
}

//reset all face up mapchits
//start new day
void Server::midnight() {
	qDebug() << "midnight begins";
	birdsong();
}
/*
Searches the players current location
*/
void Server::searchClearing(Character *character) {

}

/*
Attempt to the player at the current location
*/
void Server::hidePlayer(Character *character) {

}
/*
Peer into a neighboring clearing
*/
void Server::peerClearing(Character *character, Clearing *target) {

}
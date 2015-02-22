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
			connect(newThread, SIGNAL(characterSelected(CharacterTypes, int)),
				this, SLOT(characterUnavail(CharacterTypes, int)));
			connect(newThread, SIGNAL(spawnSelected(DwellingType, int)),
				this, SLOT(setSpawn(DwellingType, int)));
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
				Character *character = game.getPlayer((CharacterTypes) i);
				if (character != NULL) {
					newThread->writeMessage(character->serialize());
				}
			}
		}
	}
}

void Server::characterUnavail(CharacterTypes type, int clientID) {
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
}

void Server::moveCharacter(Character *character, Clearing *dest) {
	game.moveRequest(character, dest);

	stringstream s;

	s << "MoveCharacter";
	s << CLASSDELIM;
	s << character->getType();
	s << VARDELIM;
	s << dest->toString();
	writeMessageAllClients(new string(s.str()));
}

void Server::writeMessageAllClients(string *message) {
	writeMessageAllClients(new QString(message->c_str()));
}

void Server::writeMessageAllClients(QString *message) {
	for (vector<ClientCommThread*>::iterator it = clientThreadList->begin();
		it != clientThreadList->end(); ++it) {
			(*it)->writeMessage(message);
	}
}
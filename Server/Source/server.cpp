#include "server.h"
#include "action.h"
#include "recordedTurn.h"
#include "clearing.h"

Server::Server(int port, QObject *parent = 0) : QObject(parent) {
	myPort = port;
	std::cout << "port is: " << myPort << std::endl;
	clientThreadList = new std::vector<ClientCommThread *>;
	incoming = new QTcpServer(parent);

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

	//test of serialization
	//Board b1;
	//Tile tile((Direction) 0, "my tile");
	//b1.addTile(&tile);
	//Clearing c1(1, &tile);
	//Clearing c2(2, &tile);
	//RecordedTurn rec;
	//rec.addPhase(BasicPhase, 3);
	//Action a1(MoveAction, &c1);
	//Action a2(SearchAction, &c1);
	//rec.addAction(&a1, BasicPhase);
	//rec.addAction(&a2, BasicPhase);
	//string serialRec = *(rec.serialize());
	//cout << serialRec << endl;

	//RecordedTurn rec2(&serialRec, &b1);
	//cout << *(rec2.serialize()) << endl;
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
			ClientCommThread *newThread = new ClientCommThread(newClient, this);
			clientThreadList->push_back(newThread);
			std::cout << "new user has been accepted" << std::endl;
			newThread->writeMessage(new QString(ACCEPTCONN));
		}
	}
}
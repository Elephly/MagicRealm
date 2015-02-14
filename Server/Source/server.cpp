#include "server.h"

Server::Server(QObject *parent = 0, int port) : QObject(parent) {
	myPort = port;
	clientThreadList = new std::vector<ClientCommThread>;
	incoming->listen(QHostAddress::Any, (quint16) myPort);
}

void Server::run() {
	std::cout << "hello this is a test" << std::endl;

}

void Server::handleIncomingUsers() {
	if(incoming->hasPendingConnections()) {
		QTcpSocket *newClient = incoming->nextPendingConnection();
		clientThreadList->push_back(new ClientCommThread(newClient));
	}
}
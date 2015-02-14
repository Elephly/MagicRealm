#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork>
#include <QtCore>
#include <iostream>
#include <vector>
#include "clientCommThread.h"

class Server : public QObject{
public:
	Server(QObject *parent, int port);
	void handleIncomingUsers();
public slots:
	void run();
private:
	quint16 myPort;
	QTcpServer *incoming;
	std::vector<ClientCommThread *> *clientThreadList;
};

#endif // SERVER_H
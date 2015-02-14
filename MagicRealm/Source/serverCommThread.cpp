#include "serverCommThread.h"

ServerCommThread::ServerCommThread(QString &hostIP, 
								   quint16 port, 
								   QObject *parent) : QObject(parent) 
{
	serverConnection = new QTcpSocket(this);
	serverConnection->connectToHost(hostIP, port);

	QObject::connect(serverConnection, SIGNAL(readRead()), this, SLOT(updateFromServer()));
}

ServerCommThread::~ServerCommThread() {
	serverConnection->close();
	free(serverConnection);
}

void ServerCommThread::updateFromServer() {
}
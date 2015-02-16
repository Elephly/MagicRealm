#include "clientCommThread.h"

ClientCommThread::ClientCommThread(QTcpSocket *socket, QObject *parent) : QObject(parent) {
	clientConnection = socket;
	QObject::connect(clientConnection, SIGNAL(readyRead()), this, SLOT(readIncomingData()));
}

ClientCommThread::~ClientCommThread() {
	clientConnection->close();
	free(clientConnection);
}

void ClientCommThread::readIncomingData() {

}
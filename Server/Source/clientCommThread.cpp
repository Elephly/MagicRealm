#include "clientCommThread.h"

ClientCommThread::ClientCommThread(QTcpSocket *socket) {
	clientConnection = socket;
}

ClientCommThread::~ClientCommThread() {
	clientConnection->close();
	free(clientConnection);
}
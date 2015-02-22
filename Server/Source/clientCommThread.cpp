#include "clientCommThread.h"

ClientCommThread::ClientCommThread(QTcpSocket *socket, Server *parent, int id) : QObject(parent) {
	clientID = id;
	this->parent = parent;
	blocksize = 0;
	clientConnection = socket;
	connect(clientConnection, SIGNAL(readyRead()), this, SLOT(readIncomingData()));
}

ClientCommThread::~ClientCommThread() {
	clientConnection->close();
	delete clientConnection;
}

void ClientCommThread::readIncomingData() {
	qDebug() << "message from client";
	do {
		QDataStream in(clientConnection);
		if (blocksize == 0) {
			if (clientConnection->bytesAvailable() < (int)sizeof(quint16)) {
				qDebug() << "bytes avail too small (less than int size)";
				return;
			}
			in >> blocksize;
		}
		if (clientConnection->bytesAvailable() < blocksize) {
			qDebug() << "bytes avail too small (less than block size)";
			return;
		}
		QString clientData;
		in >> clientData;
		qDebug() << clientData;

		if (clientData.contains(QRegExp("^RecordedTurn"))) {
			incomingTurn(clientData, clientID);
		} else if (clientData.contains(QRegExp("^CharacterType"))) {
			int pos = clientData.indexOf(QString(CLASSDELIM));
			clientData = clientData.remove(0, pos + 2);
			CharacterType data = (CharacterType)clientData.toInt();
			myCharacter = data;
			characterSelected(data, clientID);
		} else if (clientData.contains(QRegExp("^SpawnLocation"))) {
			int pos = clientData.indexOf(CLASSDELIM);
			DwellingType data = (DwellingType) clientData.remove(0, pos + 2).toInt();
			spawnSelected(data, clientID);
		}
		blocksize = 0;
	} while(true);

}

void ClientCommThread::writeMessage(QString *message) {
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	qDebug() << "outgoing message" << *message;
	out << (quint16)0;
	out << *message;
	out.device()->seek(0);
	out << (quint16)(block.size() - sizeof(quint16));

	clientConnection->write(block);
	//delete message;
}

void ClientCommThread::writeMessage(string *message) {
	writeMessage(new QString(message->c_str()));
	//delete message;
}

CharacterType ClientCommThread::getMyCharacter() {
	return myCharacter;
}
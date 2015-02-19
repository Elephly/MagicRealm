#include "clientCommThread.h"

ClientCommThread::ClientCommThread(QTcpSocket *socket, QObject *parent) : QObject(parent) {
	blocksize = 0;
	clientConnection = socket;
	connect(clientConnection, SIGNAL(readyRead()), this, SLOT(readIncomingData()));
}

ClientCommThread::~ClientCommThread() {
	clientConnection->close();
	free(clientConnection);
}

void ClientCommThread::readIncomingData() {
	qDebug() << "message from client";
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
	QString serverData;
	in >> serverData;
	qDebug() << serverData;

	blocksize = 0;
}

void ClientCommThread::writeMessage(QString *message) {
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	qDebug() << *message;
	out << (quint16)0;
	out << *message;
	out.device()->seek(0);
	out << (quint16)(block.size() - sizeof(quint16));

	clientConnection->write(block);
}
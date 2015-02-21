#include "serverCommThread.h"

ServerCommThread::ServerCommThread(GameWindow *parent) : QObject(parent) 
{
	serverConnection = 0;
	connected = 0;
	blocksize = 0;
	windowParent = parent;
	serverConnection = NULL;
}

ServerCommThread::~ServerCommThread()
{
	threadDisconnect();
}

errno_t ServerCommThread::threadConnect(QString &hostIP, quint16 hostPort)
{
	errno_t err = 0;

	serverConnection = new QTcpSocket(this);
	serverConnection->connectToHost(hostIP, hostPort);
	connect(serverConnection, SIGNAL(readyRead()), this, SLOT(updateFromServer()));

	return err;
}

errno_t ServerCommThread::threadDisconnect()
{
	errno_t err = 0;

	if (serverConnection != 0)
	{
		serverConnection->close();
		delete serverConnection;
		serverConnection = 0;
	}

	return err;
}

bool ServerCommThread::isConnected()
{
	return connected;
}

void ServerCommThread::updateFromServer()
{
	qDebug() << "data from server";
	QDataStream in(serverConnection);
	if (blocksize == 0) {
		if (serverConnection->bytesAvailable() < (int)sizeof(quint16)) {
			qDebug() << "bytes avail too small (less than int size)";
			return;
		}
		in >> blocksize;
	}
	if (serverConnection->bytesAvailable() < blocksize) {
		qDebug() << "bytes avail too small (less than block size)";
		return;
	}
	QString serverData;
	in >> serverData;
	qDebug() << serverData;

	if (serverData.compare(QString(ACCEPTCONN)) == 0) {
		connected = true;
		writeMessage(new QString(windowParent->getSelectedChar()->serialize()->c_str()));
	} else if (serverData.contains(QRegExp("^RecordedTurn"))) {
		//Server wants us to record a turn
	} else if (serverData.contains(QRegExp("^CharacterType"))) {
		//Server has listed a character as taken
	}
	blocksize = 0;
}

void ServerCommThread::writeMessage(QString *message) {
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out << (quint16)0;
	out << *message;
	out.device()->seek(0);
	out << (quint16)(block.size() - sizeof(quint16));

	serverConnection->write(block);
}

void ServerCommThread::writeMessage(string *message) {
	writeMessage(new QString(message->c_str()));
}
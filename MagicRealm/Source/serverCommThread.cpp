#include "serverCommThread.h"

ServerCommThread::ServerCommThread(GameWindow *parent) : QObject(parent) 
{
	serverConnection = 0;
	connected = 0;
	blocksize = 0;
	windowParent = parent;
}

ServerCommThread::~ServerCommThread()
{
	threadDisconnect();
}

errno_t ServerCommThread::threadConnect(QString &hostIP, quint16 hostPort)
{
	errno_t err = 0;

	serverConnection = new QTcpSocket(this);
	connect(serverConnection, SIGNAL(readyRead()), this, SLOT(updateFromServer()));
	serverConnection->connectToHost(hostIP, hostPort);

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
		windowParent->connectedToServer();
		//writeMessage(new QString(windowParent->getSelectedChar()->serialize()->c_str()));
	} else if (serverData.contains(QRegExp("^RecordedTurn"))) {
		//Server wants us to record a turn
	} else if (serverData.contains(QRegExp("^CharacterType"))) {
		int pos = serverData.indexOf(QString(CLASSDELIM));
		int character = serverData.remove(pos+2).toInt();
		windowParent->updateAvailableCharacters(character);
	} else if (serverData.contains(QRegExp("^Selection"))) {
		int pos = serverData.indexOf(QString(CLASSDELIM));
		bool ok = (bool) serverData.remove(pos+2).toInt();
		//call gamewindow function
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
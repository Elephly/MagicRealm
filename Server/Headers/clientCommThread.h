#ifndef CLIENTCOMMTHREAD_H
#define CLIENTCOMMTHREAD_H

#include <QtNetwork>
#include "shared.h"
#include "server.h"

class Server;

class ClientCommThread : public QObject{
	Q_OBJECT
public:
	ClientCommThread(QTcpSocket *socket, Server *parent);
	~ClientCommThread();
	void writeMessage(QString *message);
	void writeMessage(string *message);
public slots:
	void readIncomingData();
signals:
	void characterSelected(CharacterTypes type);
private:
	QTcpSocket *clientConnection;
	Server *parent;
	quint16 blocksize;
};

#endif // CLIENTCOMMTHREAD_H
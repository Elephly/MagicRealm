#ifndef CLIENTCOMMTHREAD_H
#define CLIENTCOMMTHREAD_H

#include <QtNetwork>
#include "shared.h"
#include "server.h"

class Server;

class ClientCommThread : public QObject{
	Q_OBJECT
public:
	ClientCommThread(QTcpSocket *socket, Server *parent, int id);
	~ClientCommThread();
	void writeMessage(QString *message);
	void writeMessage(string *message);

	CharacterTypes getMyCharacter();

public slots:
	void readIncomingData();
signals:
	void characterSelected(CharacterTypes type, int id);
	void spawnSelected(DwellingType type, int id);
	void incomingTurn(QString &turn, int id);
private:
	QTcpSocket *clientConnection;
	Server *parent;
	quint16 blocksize;
	int clientID;
	CharacterTypes myCharacter;
};

#endif // CLIENTCOMMTHREAD_H
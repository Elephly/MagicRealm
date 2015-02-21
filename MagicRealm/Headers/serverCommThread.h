#ifndef SERVERCOMMTHREAD_H
#define SERVERCOMMTHREAD_H

#include <QtNetwork>
#include "shared.h"
#include "gameWindow.h"

//forward decl
class GameWindow;

class ServerCommThread : public QObject {
	Q_OBJECT
public:
	ServerCommThread(GameWindow *parent);
	~ServerCommThread();

	errno_t threadConnect(QString &hostIP, quint16 hostPort = GAMEPORT);
	errno_t threadDisconnect();
	void writeMessage(QString *message);
	void writeMessage(string *message);

	bool isConnected();

public slots:
	void updateFromServer();

private:
	QTcpSocket *serverConnection;
	bool connected;
	quint16 blocksize;
	GameWindow *windowParent;
};

#endif // SERVERCOMMTHREAD_H
#ifndef SERVERCOMMTHREAD_H
#define SERVERCOMMTHREAD_H

#include <QtNetwork>
#include "shared.h"

class ServerCommThread : public QObject {
	Q_OBJECT
public:
	ServerCommThread(QObject *parent);
	~ServerCommThread();

	errno_t threadConnect(QString &hostIP, quint16 hostPort);
	errno_t threadDisconnect();

public slots:
	void updateFromServer();

private:
	QTcpSocket *serverConnection;
};

#endif // SERVERCOMMTHREAD_H
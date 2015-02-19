#ifndef SERVERCOMMTHREAD_H
#define SERVERCOMMTHREAD_H

#include <QtNetwork>
#include "shared.h"

class ServerCommThread : public QObject {
	Q_OBJECT
public:
	ServerCommThread(QString &hostIP, quint16 port, QObject *parent);
	~ServerCommThread();

public slots:
	void updateFromServer();

private:
	QTcpSocket *serverConnection;
};

#endif // SERVERCOMMTHREAD_H
#ifndef CLIENTCOMMTHREAD_H
#define CLIENTCOMMTHREAD_H

#include <QtNetwork>

class ClientCommThread : public QObject{
	Q_OBJECT
public:
	ClientCommThread(QTcpSocket *socket, QObject *parent);
	~ClientCommThread();
public slots:
	void readIncomingData();
private:
	QTcpSocket *clientConnection;
};

#endif // CLIENTCOMMTHREAD_H
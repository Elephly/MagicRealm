#ifndef CLIENTCOMMTHREAD_H
#define CLIENTCOMMTHREAD_H

#include <qthread.h>
#include <QtNetwork>

class ClientCommThread : public QThread {
public:
	ClientCommThread(QTcpSocket *);
	~ClientCommThread();

private:
	QTcpSocket *clientConnection;
};

#endif // CLIENTCOMMTHREAD_H
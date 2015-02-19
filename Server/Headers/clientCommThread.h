#ifndef CLIENTCOMMTHREAD_H
#define CLIENTCOMMTHREAD_H

#include <QtNetwork>

class ClientCommThread : public QObject{
	Q_OBJECT
public:
	ClientCommThread(QTcpSocket *socket, QObject *parent);
	~ClientCommThread();
	void writeMessage(QString* message);
public slots:
	void readIncomingData();
private:
	QTcpSocket *clientConnection;
	quint16 blocksize;
};

#endif // CLIENTCOMMTHREAD_H
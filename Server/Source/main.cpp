#include "server.h"
#include <QtCore/QCoreApplication>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	Server *server = new Server(42730, &a);
	QObject::connect(server, SIGNAL(finished()), &a, SLOT(quit()));

	QTimer::singleShot(0, server, SLOT(run()));
	return a.exec();
}

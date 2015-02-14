#include "server.h"
#include <QtCore/QCoreApplication>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	Server *server = new Server(&a, 42730);
	QTimer::singleShot(0, server, SLOT(run()));
	return a.exec();
}

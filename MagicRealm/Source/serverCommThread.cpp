#include "serverCommThread.h"

ServerCommThread::ServerCommThread(GameWindow *parent) : QObject(parent) 
{
	serverConnection = 0;
	connected = 0;
	blocksize = 0;
	windowParent = parent;
}

ServerCommThread::~ServerCommThread()
{
	threadDisconnect();
}

errno_t ServerCommThread::threadConnect(QString &hostIP, quint16 hostPort)
{
	errno_t err = 0;

	serverConnection = new QTcpSocket(this);
	connect(serverConnection, SIGNAL(readyRead()), this, SLOT(updateFromServer()));
	serverConnection->connectToHost(hostIP, hostPort);

	return err;
}

errno_t ServerCommThread::threadDisconnect()
{
	errno_t err = 0;

	if (serverConnection != 0)
	{
		serverConnection->close();
		delete serverConnection;
		serverConnection = 0;
	}

	return err;
}

bool ServerCommThread::isConnected()
{
	return connected;
}

void ServerCommThread::updateFromServer()
{
	qDebug() << "data from server";
	do {
		QDataStream in(serverConnection);
		if (blocksize == 0) {
			if (serverConnection->bytesAvailable() < (int)sizeof(quint16)) {
				qDebug() << "bytes avail too small (less than int size)";
				return;
			}
			in >> blocksize;
		}
		if (serverConnection->bytesAvailable() < blocksize) {
			qDebug() << "bytes avail too small (less than block size)";
			return;
		}
		QString serverData;
		in >> serverData;
		qDebug() << serverData;

		if (serverData.contains(QRegExp(ACCEPTCONN))) 
		{
			int pos = serverData.indexOf(CLASSDELIM);
			time_t time = serverData.remove(0, pos + 2).toLong();
			connected = true;
			windowParent->connectedToServer(time);
		} 
		else if (serverData.contains(QRegExp("^RecordedTurn"))) 
		{
			windowParent->doTurn(serverData);
		} 
		else if (serverData.contains(QRegExp("^CharacterType"))) 
		{
			int pos = serverData.indexOf(QString(CLASSDELIM));
			int character = serverData.remove(0, pos+2).toInt();
			windowParent->updateAvailableCharacters(character);
		} 
		else if (serverData.contains(QRegExp("^Selection"))) 
		{
			int pos = serverData.indexOf(QString(CLASSDELIM));
			bool ok = (bool) serverData.remove(0, pos+2).toInt();
			windowParent->characterRequestAcknowledged(ok);
		} 
		else if (serverData.contains(QRegExp("^Character"))) 
		{
			windowParent->addCharacterToGame(serverData);
		} 
		else if (serverData.contains(QRegExp("^MoveCharacter"))) 
		{
			int pos = serverData.indexOf(QString(CLASSDELIM));
			serverData = serverData.remove(0, pos + 2);
			pos = serverData.indexOf(QString(VARDELIM));
			CharacterType type = (CharacterType)serverData.left(pos).toInt();
			QString clearingString = serverData.right(serverData.size() - (pos + 1));
			windowParent->moveTo(type, clearingString);
		} 
		else if (serverData.contains(QRegExp("^Hidden"))) 
		{
			int pos = serverData.indexOf(QString(CLASSDELIM));
			serverData = serverData.remove(0, pos + 2);
			pos = serverData.indexOf(QString(VARDELIM));
			CharacterType type = (CharacterType)serverData.left(pos).toInt();
			bool hidden = (bool) serverData.right(serverData.size() - (pos + 1)).toInt();
			windowParent->setCharacterHidden(type, hidden);
		} 
		else if (serverData.contains(QRegExp("^SearchTypeReq"))) 
		{
			windowParent->searchTypeRequest(serverData);
		} 
		else if (serverData.contains(QRegExp("^TreasureFound"))) 
		{
			int pos = serverData.indexOf(QString(CLASSDELIM));
			serverData = serverData.remove(0, pos + 2);
			pos = serverData.indexOf(QString(VARDELIM));
			int treasureWorth = serverData.left(pos).toInt();
			serverData = serverData.remove(0, pos + 1);
			pos = serverData.indexOf(QString(VARDELIM));
			int fame = serverData.left(pos).toInt();
			serverData = serverData.remove(0, pos + 1);
			pos = serverData.indexOf(QString(VARDELIM));
			int notoriety = serverData.left(pos).toInt();
			CharacterType type = (CharacterType)serverData.right(serverData.size() - (pos + 1)).toInt();
			windowParent->treasureFound(type, treasureWorth, fame, notoriety);
		} 
		else if (serverData.contains(QRegExp("^SiteFound"))) 
		{
			int pos = serverData.indexOf(QString(CLASSDELIM));
			serverData = serverData.remove(0, pos + 2);
			pos = serverData.indexOf(QString(VARDELIM));
			QString siteName = serverData.left(pos);
			CharacterType type = (CharacterType)serverData.right(serverData.size() - (pos + 1)).toInt();
			windowParent->siteFound(type, siteName);
		} 
		else if (serverData.contains(QRegExp("^Chit"))) 
		{
			windowParent->setupChit(serverData);
		}
		else if (serverData.contains(QRegExp("^Monster")))
		{
			windowParent->manageMonsters(serverData);
		}
		else if (serverData.contains(QRegExp("^BlockRequest")))
		{
			int pos = serverData.indexOf(QString(CLASSDELIM));
			CharacterType temp = (CharacterType) serverData.remove(0, pos + 2).toInt();
			windowParent->blockRequest(temp);
		}
		else if (serverData.contains(QRegExp("^Blocked")))
		{
			int pos = serverData.indexOf(QString(CLASSDELIM));
			CharacterType temp = (CharacterType) serverData.remove(0, pos + 2).toInt();
			windowParent->blockCharacter(temp);
		}
		else if (serverData.contains(QRegExp("^FightMonsterReq"))) 
		{
			int pos = serverData.indexOf(QString(CLASSDELIM));
			int temp = serverData.remove(0, pos + 2).toInt();
			windowParent->monsterCombatRequest(temp);
		}
		else if (serverData.contains(QRegExp("^KillMonster")))
		{
			int pos = serverData.indexOf(QString(CLASSDELIM));
			serverData.remove(0, pos + 2); //strips the class delim, now = monsterID^characterType

			pos = serverData.indexOf(QString(VARDELIM));
			int monsterID = serverData.left(pos).toInt();
			CharacterType type = (CharacterType) serverData.remove(0, pos +1).toInt();
			windowParent->monsterKilledBy(monsterID, type);
		}
		else if (serverData.contains(QRegExp("^PlayerCombatMelee"))) //nothing extra
		{
			windowParent->combatMelee();
		}
		else if (serverData.contains(QRegExp("^PlayerCombatFlee"))) //nothing extra
		{
			windowParent->combatFlee();
		}
		else if (serverData.contains(QRegExp("^PlayerCombatEncounter"))) //nothing extra
		{
			int pos = serverData.indexOf(QString(CLASSDELIM));
			CharacterType playerType = (CharacterType) serverData.remove(0, pos + 2).toInt(); 
			windowParent->combatEncounter(playerType);
		}
		else if (serverData.contains(QRegExp("^DamagedEquipment")))
		{
			int pos = serverData.indexOf(QString(CLASSDELIM));
			serverData.remove(0, pos + 2).toInt();

			pos = serverData.indexOf(QString(VARDELIM));
			CharacterType playerType = (CharacterType) serverData.left(pos).toInt();
			QString counterID = serverData.remove(0, pos + 1);
			windowParent->damageEquipment(playerType, counterID);
		}
		else if (serverData.contains(QRegExp("^Wounds"))) 
		{
			int pos = serverData.indexOf(QString(CLASSDELIM));
			int woundCount = serverData.remove(0, pos + 2).toInt();
			windowParent->woundCounters(woundCount);
		}
		else if (serverData.contains(QRegExp("^woundedPlayer")))
		{
			int pos = serverData.indexOf(QString(CLASSDELIM));
			serverData.remove(0, pos + 2).toInt(); 

			pos = serverData.indexOf(QString(VARDELIM));
			CharacterType playerType = (CharacterType) serverData.left(pos).toInt();
			int counterID = serverData.remove(0, pos + 1).toInt();
			windowParent->woundPlayerCounter(playerType, counterID);
		}
		else if (serverData.contains(QRegExp("^GameOver"))) 
		{
			int pos = serverData.indexOf(QString(CLASSDELIM));
			CharacterType type = (CharacterType) serverData.remove(0, pos + 2).toInt();
			windowParent->endGame(type);
		}
		else if (serverData.contains(QRegExp("^RestRequest")))
		{
			windowParent->restCounterRequest();
		}
		else if (serverData.contains(QRegExp("^GameReady")))
		{
			windowParent->gameReady();
		}
		else if (serverData.contains(QRegExp("^RestCounter"))) //this is called when a counter has been rested on the server.
		{
			int pos = serverData.indexOf(QString(CLASSDELIM));
			serverData.remove(0, pos + 2).toInt(); 

			pos = serverData.indexOf(QString(VARDELIM));
			CharacterType playerType = (CharacterType) serverData.left(pos).toInt();
			int counterID = serverData.remove(0, pos + 1).toInt();

			windowParent->restCounter(playerType, counterID);
		}
		else if (serverData.contains(QRegExp("^DeadPlayer")))
		{
			int pos = serverData.indexOf(QString(CLASSDELIM));
			CharacterType type = (CharacterType) serverData.remove(0, pos + 2).toInt();
			windowParent->killPlayer(type);
		}
		blocksize = 0;
	} while(true);
}

void ServerCommThread::writeMessage(QString *message) {
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	qDebug() << "data sent to server: " << *message;
	out << (quint16)0;
	out << *message;
	out.device()->seek(0);
	out << (quint16)(block.size() - sizeof(quint16));

	serverConnection->write(block);
	//delete message;
}

void ServerCommThread::writeMessage(string *message) {
	writeMessage(new QString(message->c_str()));
	//delete message;
}
#include "clientCommThread.h"

ClientCommThread::ClientCommThread(QTcpSocket *socket, Server *parent, int id) : QObject(parent) {
	clientID = id;
	this->parent = parent;
	blocksize = 0;
	clientConnection = socket;
	connect(clientConnection, SIGNAL(readyRead()), this, SLOT(readIncomingData()));
}

ClientCommThread::~ClientCommThread() {
	clientConnection->close();
	delete clientConnection;
}

void ClientCommThread::readIncomingData() {
	qDebug() << "message from client";
	do {
		QDataStream in(clientConnection);
		if (blocksize == 0) {
			if (clientConnection->bytesAvailable() < (int)sizeof(quint16)) {
				qDebug() << "bytes avail too small (less than int size)";
				return;
			}
			in >> blocksize;
		}
		if (clientConnection->bytesAvailable() < blocksize) {
			qDebug() << "bytes avail too small (less than block size)";
			return;
		}
		QString clientData;
		in >> clientData;
		qDebug() << clientData;

		if (clientData.contains(QRegExp("^RecordedTurn"))) {
			incomingTurn(clientData, clientID);
		} else if (clientData.contains(QRegExp("^CharacterType"))) {
			int pos = clientData.indexOf(QString(CLASSDELIM));
			clientData = clientData.remove(0, pos + 2);
			CharacterType data = (CharacterType)clientData.toInt();
			myCharacter = data;
			characterSelected(data, clientID);
		} else if (clientData.contains(QRegExp("^SpawnLocation"))) {
			int pos = clientData.indexOf(CLASSDELIM);
			DwellingType data = (DwellingType) clientData.remove(0, pos + 2).toInt();
			spawnSelected(data, clientID);
		} else if (clientData.contains(QRegExp("^SearchTypeResp"))) {
			int pos = clientData.indexOf(QString(CLASSDELIM));
			searchTypeRes = (SearchType) clientData.remove(0, pos + 2).toInt();
			searchTypeReturned();
		} else if (clientData.contains(QRegExp("^BlockResp"))) {
			int pos = clientData.indexOf(QString(CLASSDELIM));
			bool temp = (bool) clientData.remove(0, pos + 2).toInt();
			blockCheckReturn(temp, myCharacter);
		} else if (clientData.contains(QRegExp("^MonsterCombatResp"))) {
			int pos = clientData.indexOf(QString(CLASSDELIM));
			clientData.remove(0, pos + 2); //strips the class delim, now = result^monsterID^characterType

			pos = clientData.indexOf(QString(VARDELIM));
			int result = clientData.left(pos).toInt();
			clientData.remove(0, pos +1); //monsterID^characterType

			pos = clientData.indexOf(QString(VARDELIM));
			int monsterID = clientData.left(pos).toInt();
			CharacterType type = (CharacterType) clientData.remove(0, pos + 1).toInt();
			monsterCombatReturned(result, monsterID, type);
		} else if (clientData.contains(QRegExp("^SubEncounter"))) {
			qDebug() << "hello world, from happy land";
			int pos = clientData.indexOf(QString(CLASSDELIM));
			clientData.remove(0, pos + 2); //

			pos = clientData.indexOf(QString(VARDELIM));
			CharacterType type = (CharacterType) clientData.left(pos).toInt();
			clientData.remove(0, pos +1); //

			pos = clientData.indexOf(QString(VARDELIM));
			bool run = (bool) clientData.left(pos).toInt();
			int counter = clientData.remove(0, pos + 1).toInt();

			subEncounterC(type, run, counter);
		} else if (clientData.contains(QRegExp("^SubMelee"))) {
			int pos = clientData.indexOf(QString(CLASSDELIM));
			clientData.remove(0, pos + 2); //

			pos = clientData.indexOf(QString(VARDELIM));
			CharacterType type = (CharacterType) clientData.left(pos).toInt();
			clientData.remove(0, pos +1); //

			pos = clientData.indexOf(QString(VARDELIM));
			int fID = clientData.left(pos).toInt();
			clientData.remove(0, pos + 1);

			pos = clientData.indexOf(QString(VARDELIM));
			CombatFightType fType = (CombatFightType) clientData.left(pos).toInt();
			clientData.remove(0, pos + 1);

			pos = clientData.indexOf(QString(VARDELIM));
			int mID = clientData.left(pos).toInt();
			clientData.remove(0, pos + 1);

			pos = clientData.indexOf(QString(VARDELIM));
			CombatMoveType mType = (CombatMoveType) clientData.left(pos).toInt();
			CombatShieldBlock sType = (CombatShieldBlock) clientData.remove(0, pos + 1).toInt();

			subMeleeC(type, fID, fType, mID, mType, sType);
		} else if (clientData.contains(QRegExp("^PlayerWounded"))) {
			int pos = clientData.indexOf(QString(CLASSDELIM));
			clientData.remove(0, pos + 2);

			pos = clientData.indexOf(QString(VARDELIM));
			CharacterType type = (CharacterType) clientData.left(pos).toInt();
			vector<int> ids;
			while ((pos = clientData.indexOf(QString(VARDELIM))) != -1) {
				ids.push_back(clientData.left(pos).toInt());
				clientData.remove(0, pos + 1);
			}
			
			ids.push_back(clientData.remove(0, pos +1).toInt());
			playerWoundedC(type, ids);
		} else if (clientData.contains(QRegExp("^RestResp"))) {
			int pos = clientData.indexOf(QString(CLASSDELIM));
			clientData.remove(0, pos + 2);

			pos = clientData.indexOf(QString(VARDELIM));
			CharacterType type = (CharacterType) clientData.left(pos).toInt();
			int id = clientData.remove(0, pos +1).toInt();
			restResponseC(type, id);
		}
		blocksize = 0;
	} while(true);

}

void ClientCommThread::writeMessage(QString *message) {
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	qDebug() << "outgoing message" << *message;
	out << (quint16)0;
	out << *message;
	out.device()->seek(0);
	out << (quint16)(block.size() - sizeof(quint16));

	clientConnection->write(block);
	//delete message;
}

void ClientCommThread::writeMessage(string *message) {
	writeMessage(new QString(message->c_str()));
	//delete message;
}

CharacterType ClientCommThread::getMyCharacter() {
	return myCharacter;
}

SearchType ClientCommThread::getSearchTypeResult() {
	return searchTypeRes;
}
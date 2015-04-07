#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork>
#include <QtCore>
#include <iostream>
#include <sstream>
#include <vector>
#include "clientCommThread.h"
#include "shared.h"
#include "game.h"
#include "recordedTurn.h"

class ClientCommThread;

class Server : public QObject{
	Q_OBJECT
public:
	Server(int port, QObject *parent);
	~Server();
public slots:
	void handleIncomingUsers();
	void run();
	void setSpawn(DwellingType type, int clientID);
	void characterUnavail(CharacterType type, int clientID);
	void recordedTurn(QString &turn, int clientID);
	void endAction();
	void blockResp(bool answer, CharacterType responder);
	void monsterCombatResp(int result, int monsterID, CharacterType player);
	void subEncounter(CharacterType character, bool run, int counter);
	void subMelee(CharacterType character,);
signals:
	void finished();
private:
	quint16 myPort;
	QTcpServer *incoming;
	std::vector<ClientCommThread *> *clientThreadList;
	bool selectedCharacters[MAXPLAYERS];
	bool receivedRecTurn[MAXPLAYERS];
	int blockCheckNum;
	bool blockRes;
	int monsterCombatCount;
	RecordedTurn *recTurns[MAXPLAYERS];
    Game game;
	int currentDay;
	CombatManager* combat;
	int combatCounter;

	//sending game map to client
	void sendBoard(ClientCommThread* client);

	//gameplay stuff
	void birdsong();
	void sunrise();
	void daylight();
	void sunset();
	void evening();
	void midnight();

	void startPlayerCombat();
	void endPlayerCombat();

	//daylight functions
	int currentPlayer;
	vector<Action *>::iterator currentAction;
	void startPlayerTurn();
	void startAction();
	//void endAction(), is located in public slots:
	void endPlayerTurn();
	ClientCommThread* lookupClient(CharacterType);

	bool turnExists();
	void searchClearing(Character*, SearchType, Clearing*);
	void hidePlayer(Character*);
	void moveCharacter(Character*, Clearing*);

	void writeMessageAllClients(string*);
	void writeMessageAllClients(QString*);
	void calculatePlayerTurnPhases(ClientCommThread*);
};

#endif // SERVER_H
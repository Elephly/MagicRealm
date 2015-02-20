#include <QGraphicsItem>

#include "gameWindow.h"
#include "board.h"

#include <Windows.h>

QMap<std::string, QPixmap> GameWindow::tileImages()
{
	QMap<std::string, QPixmap> map;
	map.insert("Awful Valley", QPixmap(":/images/tiles/awfulvalley1.gif"));
	map.insert("Awful Valley Enchanted", QPixmap(":/images/tiles/awfulvalley-e1.gif"));
	map.insert("Bad Valley", QPixmap(":/images/tiles/badvalley1.gif"));
	map.insert("Bad Valley Echanted", QPixmap(":/images/tiles/badvalley-e1.gif"));
	map.insert("Border Land", QPixmap(":/images/tiles/borderland1.gif"));
	map.insert("Border Land Echanted", QPixmap(":/images/tiles/borderland-e1.gif"));
	map.insert("Maple Woods", QPixmap(":/images/tiles/maplewoods1.gif"));
	map.insert("Maple Woods Echanted", QPixmap(":/images/tiles/maplewoods-e1.gif"));
	map.insert("Oak Woods", QPixmap(":/images/tiles/oakwoods1.gif"));
	map.insert("Oak Woods Echanted", QPixmap(":/images/tiles/oakwoods-e1.gif"));
	return map;
}

GameWindow::GameWindow(QObject* parent, Ui::MainWindowClass mainWindow)
	: QObject(parent), ui(mainWindow)
{
	server = new ServerCommThread(this);
	selectedCharacter = 0;
}

GameWindow::~GameWindow()
{
	if (server != 0)
	{
		delete server;
		server = 0;
	}
}

errno_t GameWindow::initialize(QString &hostIP, int character)
{
	errno_t err = 0;

	selectedCharacter = new Character((CharacterTypes)character);

	changeScreenState(ui.loadingWidget);
	
	err = server->threadConnect(hostIP, GAMEPORT);
	if (err)
	{
		return err;
	}

	int i = 0;
	while (!server->isConnected())
	{
		if (i++ >= 10)
		{
			ui.loadingWidget->setVisible(false);
			cleanup();
			return 1;
		}
		Sleep(1000);
	}
	
	gameScene = new QGraphicsScene();
	ui.graphicsView->setScene(gameScene);

	// must receive board from server
	//but for now...this
	Board* gameBoard = new Board();
	Clearing* c1 = NULL;
    Clearing* c2 = NULL;
    Clearing* c3 = NULL;
    Clearing* c4 = NULL;
    Path* p = NULL;
	Tile* oakWoodsTile = new Tile(EDGE_E, "Border Land");
    c1 = new Clearing(2, oakWoodsTile);
    c2 = new Clearing(4, oakWoodsTile);
    c3 = new Clearing(5, oakWoodsTile);
    p = new Path(c1, c2, false);
    p = new Path(c1, EDGE_B);
    p = new Path(c3, EDGE_C);
    p = new Path(c3, EDGE_D);
    p = new Path(c1, EDGE_E);
    p = new Path(c1, EDGE_F);
    gameBoard->addTile(oakWoodsTile);
	
	QMap<std::string, QPixmap> tImages = tileImages();

	Tile* currentTile = gameBoard->getTile("Border Land");
	
	QGraphicsItem* item = new QGraphicsPixmapItem(tileImages()[currentTile->getName()]);
	item->setPos(0, 0);
	
	for (int i = 0; i < ADJACENT_LENGTH; i++)
	{
		
	}
	
	gameScene->addItem(item);

	changeScreenState(ui.gameWidget);

	return err;
}

errno_t GameWindow::cleanup()
{
	errno_t err = 0;

	err = server->threadDisconnect();

	if (selectedCharacter != 0)
	{
		delete selectedCharacter;
		selectedCharacter = 0;
	}
	
	changeScreenState(ui.menuWidget);

	return err;
}


void GameWindow::changeScreenState(QWidget* screen)
{
	ui.menuWidget->setVisible(false);
	ui.loadingWidget->setVisible(false);
	ui.characterSelectWidget->setVisible(false);
	ui.gameWidget->setVisible(false);
	screen->setVisible(true);
	qApp->processEvents();
}

Character* GameWindow::getSelectedChar() {
	return selectedCharacter;
}
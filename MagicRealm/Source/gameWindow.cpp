#include <QGraphicsItem>

#include "gameWindow.h"
#include "board.h"

#include <queue>
#include <set>
#include <stack>

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
	map.insert("Cavern", QPixmap(":/images/tiles/cavern1.gif"));
	map.insert("Cavern Echanted", QPixmap(":/images/tiles/cavern-e1.gif"));
	map.insert("Caves", QPixmap(":/images/tiles/caves1.gif"));
	map.insert("Caves Echanted", QPixmap(":/images/tiles/caves-e1.gif"));
	map.insert("Cliff", QPixmap(":/images/tiles/cliff1.gif"));
	map.insert("Cliff Echanted", QPixmap(":/images/tiles/cliff-e1.gif"));
	map.insert("Crag", QPixmap(":/images/tiles/crag1.gif"));
	map.insert("Crag Echanted", QPixmap(":/images/tiles/crag-e1.gif"));
	map.insert("Curst Valley", QPixmap(":/images/tiles/curstvalley1.gif"));
	map.insert("Curst Valley Echanted", QPixmap(":/images/tiles/curstvalley-e1.gif"));
	map.insert("Dark Valley", QPixmap(":/images/tiles/darkvalley1.gif"));
	map.insert("Dark Valley Echanted", QPixmap(":/images/tiles/darkvalley-e1.gif"));
	map.insert("Deep Woods", QPixmap(":/images/tiles/deepwoods1.gif"));
	map.insert("Deep Woods Echanted", QPixmap(":/images/tiles/deepwoods-e1.gif"));
	map.insert("Evil Valley", QPixmap(":/images/tiles/evilvalley1.gif"));
	map.insert("Evil Valley Echanted", QPixmap(":/images/tiles/evilvalley-e1.gif"));
	map.insert("High Pass", QPixmap(":/images/tiles/highpass1.gif"));
	map.insert("High Pass Echanted", QPixmap(":/images/tiles/highpass-e1.gif"));
	map.insert("Ledges", QPixmap(":/images/tiles/ledges1.gif"));
	map.insert("Ledges Echanted", QPixmap(":/images/tiles/ledges-e1.gif"));
	map.insert("Linden Woods", QPixmap(":/images/tiles/lindenwoods1.gif"));
	map.insert("Linden Woods Echanted", QPixmap(":/images/tiles/lindenwoods-e1.gif"));
	map.insert("Maple Woods", QPixmap(":/images/tiles/maplewoods1.gif"));
	map.insert("Maple Woods Echanted", QPixmap(":/images/tiles/maplewoods-e1.gif"));
	map.insert("Mountain", QPixmap(":/images/tiles/mountain1.gif"));
	map.insert("Mountain Echanted", QPixmap(":/images/tiles/mountain-e1.gif"));
	map.insert("Nut Woods", QPixmap(":/images/tiles/nutwoods1.gif"));
	map.insert("Nut Woods Echanted", QPixmap(":/images/tiles/nutwoods-e1.gif"));
	map.insert("Oak Woods", QPixmap(":/images/tiles/oakwoods1.gif"));
	map.insert("Oak Woods Echanted", QPixmap(":/images/tiles/oakwoods-e1.gif"));
	map.insert("Pine Woods", QPixmap(":/images/tiles/pinewoods1.gif"));
	map.insert("Pine Woods Echanted", QPixmap(":/images/tiles/pinewoods-e1.gif"));
	map.insert("Ruins", QPixmap(":/images/tiles/ruins1.gif"));
	map.insert("Ruins Echanted", QPixmap(":/images/tiles/ruins-e1.gif"));
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
	//but for now...thisClearing* c1 = NULL;
	Board* gameBoard = new Board();
    Clearing* c1 = NULL;
    Clearing* c2 = NULL;
    Clearing* c3 = NULL;
    Clearing* c4 = NULL;
    Path* p = NULL;
    string *resultString = NULL;

    //setting up the Oak Woods Tile
    Tile* oakWoodsTile = new Tile(EDGE_E, "Oak Woods");
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

    if(gameBoard->getTile("Oak Woods") != NULL)
        cout << "Tile Found!!!" << endl;

    //resetting the clearings and paths
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;

    //setting up the Bad Valley Tile.
    Tile* badValleyTile = new Tile(EDGE_F, "Bad Valley");
    c1 = new Clearing(1, badValleyTile);
    c2 = new Clearing(2, badValleyTile);
    c3 = new Clearing(4, badValleyTile);
    c4 = new Clearing(5, badValleyTile);

    //regular paths
    p = new Path(c1, c3, false);
    p = new Path(c2, c4, false);

    //border paths
    p = new Path(c1, EDGE_F);
    p = new Path(c2, EDGE_B);
    p = new Path(c3, EDGE_C);
    p = new Path(c3, EDGE_D);
    p = new Path(c4, EDGE_E);

    gameBoard->addTile(badValleyTile);
    //resetting the clearings and paths
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;

    //Setting up the Maple Woods Tile
    Tile* mapleWoodsTile = new Tile(EDGE_C, "Maple Woods");

    c1 = new Clearing(2, mapleWoodsTile);
    c2 = new Clearing(4, mapleWoodsTile);
    c3 = new Clearing(5, mapleWoodsTile);

    p = new Path(c1, c2, false);
    
    p = new Path(c1, EDGE_D);
    p = new Path(c1, EDGE_E);
    p = new Path(c2, EDGE_F);
    p = new Path(c3, EDGE_B);
    p = new Path(c3, EDGE_C);

    gameBoard->addTile(mapleWoodsTile);

    //resetting the clearings and paths
    p = NULL;
    c1 = NULL;
    c2 = NULL;
    c3 = NULL;

    //setting up adjacent stuff
    oakWoodsTile->addConnectedTile(badValleyTile, EDGE_D);
    oakWoodsTile->addConnectedTile(mapleWoodsTile, EDGE_C);

	Tile* currTile = gameBoard->getTile("Oak Woods");
	
	QPixmap pixmap = tileImages()[currTile->getName()];
	QGraphicsItem* item = new QGraphicsPixmapItem(pixmap);
	item->setPos(0, 0);
	item->setRotation((360 / 6) * ((int)currTile->getOrientation()));
	item->setTransformOriginPoint(pixmap.width() / 2, pixmap.height() / 2);
	
	gameScene->addItem(item);

	set<Tile*> visitedTiles;
	visitedTiles.insert(currTile);

	QMap<Tile*, QPointF> locations;
	locations.insert(currTile, QPointF(0, 0));

	queue<Tile*> incompleteTiles;
	incompleteTiles.push(currTile);

	while (!incompleteTiles.empty())
	{
		currTile = incompleteTiles.front();
		incompleteTiles.pop();
		for (int i = 0; i < CONNECTED_LENGTH; i++)
		{
			Tile* newTile = currTile->getConnected((Direction)i);
			if ((newTile != 0) && (visitedTiles.find(newTile) == visitedTiles.end()))
			{
				QPixmap pixmap = tileImages()[newTile->getName()];
				QGraphicsItem* item = new QGraphicsPixmapItem(pixmap);

				int side = ((int)(currTile->getOrientation()) + i) % 6;
				QPointF pos;
				switch (side)
				{
				case 0:
					pos = QPointF(0, locations[currTile].y() + pixmap.height());
					break;
				case 1:
					pos = QPointF(locations[currTile].x() - (pixmap.width() * 0.75), locations[currTile].y() + (pixmap.height() / 2));
					break;
				case 2:
					pos = QPointF(locations[currTile].x() - (pixmap.width() * 0.75), locations[currTile].y() - (pixmap.height() / 2));
					break;
				case 3:
					pos = QPointF(0, locations[currTile].y() - pixmap.height());
					break;
				case 4:
					pos = QPointF(locations[currTile].x() + (pixmap.width() * 0.75), locations[currTile].y() - (pixmap.height() / 2));
					break;
				case 5:
					pos = QPointF(locations[currTile].x() + (pixmap.width() * 0.75), locations[currTile].y() + (pixmap.height() / 2));
					break;
				default:
					pos = QPointF(0, 0);
					break;
				}
				item->setPos(pos);

				item->setRotation((360 / 6) * ((int)newTile->getOrientation()));
				item->setTransformOriginPoint(pixmap.width() / 2, pixmap.height() / 2);

				gameScene->addItem(item);

				incompleteTiles.push(newTile);
				visitedTiles.insert(newTile);
				locations.insert(newTile, pos);
			}
		}		
	}

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
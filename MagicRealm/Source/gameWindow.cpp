#include "gameWindow.h"

#include "availableMovesDialog.h"

#include <QMessageBox>
#include <QScrollBar>

#include <queue>
#include <unordered_set>

#include <Windows.h>

GameWindow::GameWindow(QObject* parent, Ui::MainWindowClass mainWindow)
	: QObject(parent), ui(mainWindow)
{
	window = (QMainWindow*)parent;
	gameStarted = false;
	destinationCounterImage = new QPixmap(":/images/counters/characters/plan_counter.png");
	destinationCounter = 0;
	counterDepth = 0.3;
	characterImageScale = 0.2;
	characterImages = new QMap<CharacterType, QPixmap*>();
	loadCharacterImages();
	characterGraphicsItems = new QMap<CharacterType, QGraphicsPixmapItem*>();
	tileImages = new QMap<std::string, QPixmap*>();
	tileClearingOffsets = new QMap<std::string, QList<QPoint*>*>();
	loadTileImages();
	tileGraphicsItems = new QMap<Tile*, TileGraphicsItem*>();
	dwellingImageScale = 0.4;
	dwellingImages = new QMap<DwellingType, QPixmap*>();
	loadDwellingImages();
	monsterImageScale = 0.75;
	monsterImages = new QMap<string, QPixmap*>();
	monsterGraphicsItems = new QMap<int, MonsterGraphicsItem*>();
	loadMonsterImages();
	dwellingGraphicsItems = new QMap<DwellingType, QGraphicsPixmapItem*>();
	ui.graphicsView->scale(1.0, 1.0);
	ui.graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
	ui.graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	ui.graphicsView->viewport()->installEventFilter(this);
	server = new ServerCommThread(this);
	selectedCharacter = NullCharacter;
	game = 0;
	selectedTile = 0;
	selectedMonster = 0;
	updateMonsterInfoPane(selectedMonster);
	destinationClearing = 0;
	selectedAction = NoAction;
	myTurn = 0;
	turnNumber = 1;
}

GameWindow::~GameWindow()
{
	if (server != 0)
	{
		delete server;
		server = 0;
	}

	if (destinationCounter != 0)
	{
		delete destinationCounter;
		destinationCounter = 0;
	}

	if (destinationCounterImage != 0)
	{
		delete destinationCounterImage;
		destinationCounterImage = 0;
	}

	if (monsterGraphicsItems != 0)
	{
		qDeleteAll(*monsterGraphicsItems);
		monsterGraphicsItems->clear();
		delete monsterGraphicsItems;
		monsterGraphicsItems = 0;
	}

	if (monsterImages != 0)
	{
		qDeleteAll(*monsterImages);
		monsterImages->clear();
		delete monsterImages;
		monsterImages = 0;
	}

	if (dwellingGraphicsItems != 0)
	{
		qDeleteAll(*dwellingGraphicsItems);
		dwellingGraphicsItems->clear();
		delete dwellingGraphicsItems;
		dwellingGraphicsItems = 0;
	}
	
	if (dwellingImages != 0)
	{
		qDeleteAll(*dwellingImages);
		dwellingImages->clear();
		delete dwellingImages;
		dwellingImages = 0;
	}

	if (characterGraphicsItems != 0)
	{
		qDeleteAll(*characterGraphicsItems);
		characterGraphicsItems->clear();
		delete characterGraphicsItems;
		characterGraphicsItems = 0;
	}
	
	if (characterImages != 0)
	{
		qDeleteAll(*characterImages);
		characterImages->clear();
		delete characterImages;
		characterImages = 0;
	}

	if (tileGraphicsItems != 0)
	{
		tileGraphicsItems->clear();
		delete tileGraphicsItems;
		tileGraphicsItems = 0;
	}

	if (tileImages != 0)
	{
		qDeleteAll(*tileImages);
		tileImages->clear();
		delete tileImages;
		tileImages = 0;
	}

	if (tileClearingOffsets != 0)
	{
		for (QMap<string, QList<QPoint*>*>::iterator it = tileClearingOffsets->begin(); it != tileClearingOffsets->end(); ++it)
		{
			if (*it != 0)
			{
				qDeleteAll(*(*it));
				(*it)->clear();
			}
		}
		qDeleteAll(*tileClearingOffsets);
		tileClearingOffsets->clear();
		delete tileClearingOffsets;
		tileClearingOffsets = 0;
	}
}

bool GameWindow::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::Wheel)
	{
		QWheelEvent *e = static_cast<QWheelEvent *>(event);
		if (obj == ui.graphicsView->viewport())
		{
			int numDegrees = e->delta() / 8;
			int numSteps = numDegrees / 15;
			if (e->delta() >= 0)
			{
				ui.graphicsView->scale(1.1, 1.1);
			}
			else
			{
				ui.graphicsView->scale(0.9, 0.9);
			}
		}
		return true;
	}
	else
	{
		return QObject::eventFilter(obj, event);
	}
}

void GameWindow::loadCharacterImages()
{
	characterImages->insert(Amazon, new QPixmap(":/images/counters/characters/amazon.png"));
	characterImages->insert(BlackKnight, new QPixmap(":/images/counters/characters/black_knight.png"));
	characterImages->insert(Captain, new QPixmap(":/images/counters/characters/captain.png"));
	characterImages->insert(Dwarf, new QPixmap(":/images/counters/characters/dwarf.png"));
	characterImages->insert(Elf, new QPixmap(":/images/counters/characters/elf.png"));
	characterImages->insert(Swordsman, new QPixmap(":/images/counters/characters/swordsman.png"));
}

void GameWindow::loadDwellingImages()
{
	dwellingImages->insert(CHAPEL, new QPixmap(":/images/counters/dwellings_c/chapel.png"));
	dwellingImages->insert(GUARD, new QPixmap(":/images/counters/dwellings_c/guard.png"));
	dwellingImages->insert(HOUSE, new QPixmap(":/images/counters/dwellings_c/house.png"));
	dwellingImages->insert(INN, new QPixmap(":/images/counters/dwellings_c/inn.png"));
}

void GameWindow::loadMonsterImages()
{
	monsterImages->insert("Demon", new QPixmap(":/images/counters/monsters/Demon.png"));
	monsterImages->insert("Ghost", new QPixmap(":/images/counters/monsters/Ghost.png"));
	monsterImages->insert("Giant Bat", new QPixmap(":/images/counters/monsters/Giant Bat.png"));
	monsterImages->insert("Giant Club", new QPixmap(":/images/counters/monsters/Giant Club.png"));
	monsterImages->insert("Giant", new QPixmap(":/images/counters/monsters/Giant.png"));
	monsterImages->insert("Golbin with Axe", new QPixmap(":/images/counters/monsters/Golbin with Axe.png"));
	monsterImages->insert("Golbin with GreatSword", new QPixmap(":/images/counters/monsters/Golbin with GreatSword.png"));
	monsterImages->insert("Golbin with Spear", new QPixmap(":/images/counters/monsters/Golbin with Spear.png"));
	monsterImages->insert("Heavy Dragon", new QPixmap(":/images/counters/monsters/Heavy Dragon.png"));
	monsterImages->insert("Heavy Flying Dragon", new QPixmap(":/images/counters/monsters/Heavy Flying Dragon.png"));
	monsterImages->insert("Heavy Serpent", new QPixmap(":/images/counters/monsters/Heavy Serpent.png"));
	monsterImages->insert("Heavy Spider", new QPixmap(":/images/counters/monsters/Heavy Spider.png"));
	monsterImages->insert("Heavy Troll", new QPixmap(":/images/counters/monsters/Heavy Troll.png"));
	monsterImages->insert("Imp", new QPixmap(":/images/counters/monsters/Imp.png"));
	monsterImages->insert("Octopus", new QPixmap(":/images/counters/monsters/Octopus.png"));
	monsterImages->insert("Ogre", new QPixmap(":/images/counters/monsters/Ogre.png"));
	monsterImages->insert("T Dragon Head", new QPixmap(":/images/counters/monsters/T Dragon Head.png"));
	monsterImages->insert("T Flying Dragon Head", new QPixmap(":/images/counters/monsters/T Flying Dragon Head.png"));
	monsterImages->insert("Tremendous Dragon", new QPixmap(":/images/counters/monsters/Tremendous Dragon.png"));
	monsterImages->insert("Tremendous Flying Dragon", new QPixmap(":/images/counters/monsters/Tremendous Flying Dragon.png"));
	monsterImages->insert("Tremendous Serpent", new QPixmap(":/images/counters/monsters/Tremendous Serpent.png"));
	monsterImages->insert("Tremendous Spider", new QPixmap(":/images/counters/monsters/Tremendous Spider.png"));
	monsterImages->insert("Tremendous Troll", new QPixmap(":/images/counters/monsters/Tremendous Troll.png"));
	monsterImages->insert("Viper", new QPixmap(":/images/counters/monsters/Viper.png"));
	monsterImages->insert("Winged Demon", new QPixmap(":/images/counters/monsters/Winged Demon.png"));
	monsterImages->insert("Wolf1", new QPixmap(":/images/counters/monsters/Wolf1.png"));
	monsterImages->insert("Wolf2", new QPixmap(":/images/counters/monsters/Wolf2.png"));
}

void GameWindow::loadTileImages()
{
	tileImages->insert("Awful Valley", new QPixmap(":/images/tiles/awfulvalley1.gif"));
	QList<QPoint*> *awfulValleyClearings = new QList<QPoint*>();
	awfulValleyClearings->append(new QPoint(130 - 248, 152 - 216));
	awfulValleyClearings->append(new QPoint(130 - 248, 275 - 216));
	awfulValleyClearings->append(new QPoint(0, 0));
	awfulValleyClearings->append(new QPoint(306 - 248, 252 - 216));
	awfulValleyClearings->append(new QPoint(244 - 248, 88 - 216));
	awfulValleyClearings->append(new QPoint(0, 0));
	tileClearingOffsets->insert("Awful Valley", awfulValleyClearings);

	tileImages->insert("Awful Valley Enchanted", new QPixmap(":/images/tiles/awfulvalley-e1.gif"));
	QList<QPoint*> *awfulValleyEnchantedClearings = new QList<QPoint*>();
	awfulValleyEnchantedClearings->append(new QPoint(140 - 248, 152 - 216));
	awfulValleyEnchantedClearings->append(new QPoint(134 - 248, 276 - 216));
	awfulValleyEnchantedClearings->append(new QPoint(0, 0));
	awfulValleyEnchantedClearings->append(new QPoint(302 - 248, 242 - 216));
	awfulValleyEnchantedClearings->append(new QPoint(246 - 248, 82 - 216));
	awfulValleyEnchantedClearings->append(new QPoint(0, 0));
	tileClearingOffsets->insert("Awful Valley Enchanted", awfulValleyEnchantedClearings);

	tileImages->insert("Bad Valley", new QPixmap(":/images/tiles/badvalley1.gif"));
	QList<QPoint*> *badValleyClearings = new QList<QPoint*>();
	badValleyClearings->append(new QPoint(366 - 248, 280 - 216));
	badValleyClearings->append(new QPoint(137 - 248, 280 - 216));
	badValleyClearings->append(new QPoint(0, 0));
	badValleyClearings->append(new QPoint(182 - 248, 102 - 216));
	badValleyClearings->append(new QPoint(362 - 248, 150 - 216));
	badValleyClearings->append(new QPoint(0, 0));
	tileClearingOffsets->insert("Bad Valley", badValleyClearings);
	
	tileImages->insert("Bad Valley Echanted", new QPixmap(":/images/tiles/badvalley-e1.gif"));
	QList<QPoint*> *badValleyEnchantedClearings = new QList<QPoint*>();
	badValleyEnchantedClearings->append(new QPoint(306 - 248, 314 - 216));
	badValleyEnchantedClearings->append(new QPoint(134 - 248, 284 - 216));
	badValleyEnchantedClearings->append(new QPoint(0, 0));
	badValleyEnchantedClearings->append(new QPoint(192 - 248, 118 - 216));
	badValleyEnchantedClearings->append(new QPoint(360 - 248, 156 - 216));
	badValleyEnchantedClearings->append(new QPoint(0, 0));
	tileClearingOffsets->insert("Bad Valley Echanted", badValleyEnchantedClearings);
	
	tileImages->insert("Border Land", new QPixmap(":/images/tiles/borderland1.gif"));
	QList<QPoint*> *borderLandClearings = new QList<QPoint*>();
	borderLandClearings->append(new QPoint(172 - 248, 78 - 216));
	borderLandClearings->append(new QPoint(382 - 248, 200 - 216));
	borderLandClearings->append(new QPoint(312 - 248, 90 - 216));
	borderLandClearings->append(new QPoint(170 - 248, 362 - 216));
	borderLandClearings->append(new QPoint(190 - 248, 268 - 216));
	borderLandClearings->append(new QPoint(230 - 248, 180 - 216));
	tileClearingOffsets->insert("Border Land", borderLandClearings);
	
	tileImages->insert("Border Land Echanted", new QPixmap(":/images/tiles/borderland-e1.gif"));
	QList<QPoint*> *borderLandEnchantedClearings = new QList<QPoint*>();
	borderLandEnchantedClearings->append(new QPoint(200 - 248, 70 - 216));
	borderLandEnchantedClearings->append(new QPoint(416 - 248, 212 - 216));
	borderLandEnchantedClearings->append(new QPoint(320 - 248, 198 - 216));
	borderLandEnchantedClearings->append(new QPoint(236 - 248, 322 - 216));
	borderLandEnchantedClearings->append(new QPoint(150 - 248, 262 - 216));
	borderLandEnchantedClearings->append(new QPoint(204 - 248, 186 - 216));
	tileClearingOffsets->insert("Border Land Echanted", borderLandEnchantedClearings);
	
	tileImages->insert("Cavern", new QPixmap(":/images/tiles/cavern1.gif"));
	QList<QPoint*> *cavernClearings = new QList<QPoint*>();
	cavernClearings->append(new QPoint(376 - 248, 144 - 216));
	cavernClearings->append(new QPoint(248 - 248, 76 - 216));
	cavernClearings->append(new QPoint(244 - 248, 180 - 216));
	cavernClearings->append(new QPoint(254 - 248, 356 - 216));
	cavernClearings->append(new QPoint(136 - 248, 150 - 216));
	cavernClearings->append(new QPoint(298 - 248, 270 - 216));
	tileClearingOffsets->insert("Cavern", cavernClearings);
	
	tileImages->insert("Cavern Echanted", new QPixmap(":/images/tiles/cavern-e1.gif"));
	QList<QPoint*> *cavernEnchantedClearings = new QList<QPoint*>();
	cavernEnchantedClearings->append(new QPoint(366 - 248, 148 - 216));
	cavernEnchantedClearings->append(new QPoint(250 - 248, 86 - 216));
	cavernEnchantedClearings->append(new QPoint(232 - 248, 206 - 216));
	cavernEnchantedClearings->append(new QPoint(250 - 248, 352 - 216));
	cavernEnchantedClearings->append(new QPoint(134 - 248, 150 - 216));
	cavernEnchantedClearings->append(new QPoint(328 - 248, 276 - 216));
	tileClearingOffsets->insert("Cavern Echanted", cavernEnchantedClearings);
	
	tileImages->insert("Caves", new QPixmap(":/images/tiles/caves1.gif"));
	QList<QPoint*> *cavesClearings = new QList<QPoint*>();
	cavesClearings->append(new QPoint(364 - 248, 286 - 216));
	cavesClearings->append(new QPoint(134 - 248, 278 - 216));
	cavesClearings->append(new QPoint(228 - 248, 216 - 216));
	cavesClearings->append(new QPoint(276 - 248, 346 - 216));
	cavesClearings->append(new QPoint(134 - 248, 152 - 216));
	cavesClearings->append(new QPoint(314 - 248, 84 - 216));
	tileClearingOffsets->insert("Caves", cavesClearings);
	
	tileImages->insert("Caves Echanted", new QPixmap(":/images/tiles/caves-e1.gif"));
	QList<QPoint*> *cavesEchantedClearings = new QList<QPoint*>();
	cavesEchantedClearings->append(new QPoint(358 - 248, 278 - 216));
	cavesEchantedClearings->append(new QPoint(130 - 248, 276 - 216));
	cavesEchantedClearings->append(new QPoint(262 - 248, 184 - 216));
	cavesEchantedClearings->append(new QPoint(250 - 248, 334 - 216));
	cavesEchantedClearings->append(new QPoint(130 - 248, 150 - 216));
	cavesEchantedClearings->append(new QPoint(330 - 248, 76 - 216));
	tileClearingOffsets->insert("Caves Echanted", cavesEchantedClearings);
	
	tileImages->insert("Cliff", new QPixmap(":/images/tiles/cliff1.gif"));
	QList<QPoint*> *cliffClearings = new QList<QPoint*>();
	cliffClearings->append(new QPoint(132 - 248, 152 - 216));
	cliffClearings->append(new QPoint(138 - 248, 282 - 216));
	cliffClearings->append(new QPoint(246 - 248, 216 - 216));
	cliffClearings->append(new QPoint(362 - 248, 146 - 216));
	cliffClearings->append(new QPoint(364 - 248, 284 - 216));
	cliffClearings->append(new QPoint(248 - 248, 88 - 216));
	tileClearingOffsets->insert("Cliff", cliffClearings);
	
	tileImages->insert("Cliff Echanted", new QPixmap(":/images/tiles/cliff-e1.gif"));
	QList<QPoint*> *cliffEchantedClearings = new QList<QPoint*>();
	cliffEchantedClearings->append(new QPoint(130 - 248, 146 - 216));
	cliffEchantedClearings->append(new QPoint(132 - 248, 282 - 216));
	cliffEchantedClearings->append(new QPoint(248 - 248, 216 - 216));
	cliffEchantedClearings->append(new QPoint(362 - 248, 146 - 216));
	cliffEchantedClearings->append(new QPoint(362 - 248, 284 - 216));
	cliffEchantedClearings->append(new QPoint(248 - 248, 88 - 216));
	tileClearingOffsets->insert("Cliff Echanted", cliffEchantedClearings);
	
	tileImages->insert("Crag", new QPixmap(":/images/tiles/crag1.gif"));
	QList<QPoint*> *cragClearings = new QList<QPoint*>();
	cragClearings->append(new QPoint(232 - 248, 362 - 216));
	cragClearings->append(new QPoint(248 - 248, 82 - 216));
	cragClearings->append(new QPoint(174 - 248, 172 - 216));
	cragClearings->append(new QPoint(318 - 248, 286 - 216));
	cragClearings->append(new QPoint(322 - 248, 174 - 216));
	cragClearings->append(new QPoint(162 - 248, 278 - 216));
	tileClearingOffsets->insert("Crag", cragClearings);
	
	tileImages->insert("Crag Echanted", new QPixmap(":/images/tiles/crag-e1.gif"));
	QList<QPoint*> *cragEnchantedClearings = new QList<QPoint*>();
	cragEnchantedClearings->append(new QPoint(206 - 248, 354 - 216));
	cragEnchantedClearings->append(new QPoint(270 - 248, 88 - 216));
	cragEnchantedClearings->append(new QPoint(176 - 248, 146 - 216));
	cragEnchantedClearings->append(new QPoint(282 - 248, 280 - 216));
	cragEnchantedClearings->append(new QPoint(314 - 248, 184 - 216));
	cragEnchantedClearings->append(new QPoint(164 - 248, 268 - 216));
	tileClearingOffsets->insert("Crag Echanted", cragEnchantedClearings);
	
	tileImages->insert("Curst Valley", new QPixmap(":/images/tiles/curstvalley1.gif"));
	QList<QPoint*> *curstValleyClearings = new QList<QPoint*>();
	curstValleyClearings->append(new QPoint(248 - 248, 82 - 216));
	curstValleyClearings->append(new QPoint(134 - 248, 146 - 216));
	curstValleyClearings->append(new QPoint(0, 0));
	curstValleyClearings->append(new QPoint(246 - 248, 284 - 216));
	curstValleyClearings->append(new QPoint(358 - 248, 150 - 216));
	curstValleyClearings->append(new QPoint(0, 0));
	tileClearingOffsets->insert("Curst Valley", curstValleyClearings);
	
	tileImages->insert("Curst Valley Echanted", new QPixmap(":/images/tiles/curstvalley-e1.gif"));
	QList<QPoint*> *curstValleyEchantedClearings = new QList<QPoint*>();
	curstValleyEchantedClearings->append(new QPoint(248 - 248, 84 - 216));
	curstValleyEchantedClearings->append(new QPoint(136 - 248, 148 - 216));
	curstValleyEchantedClearings->append(new QPoint(0, 0));
	curstValleyEchantedClearings->append(new QPoint(248 - 248, 280 - 216));
	curstValleyEchantedClearings->append(new QPoint(360 - 248, 150 - 216));
	curstValleyEchantedClearings->append(new QPoint(0, 0));
	tileClearingOffsets->insert("Curst Valley Echanted", curstValleyEchantedClearings);
	
	tileImages->insert("Dark Valley", new QPixmap(":/images/tiles/darkvalley1.gif"));
	QList<QPoint*> *darkValleyClearings = new QList<QPoint*>();
	darkValleyClearings->append(new QPoint(362 - 248, 150 - 216));
	darkValleyClearings->append(new QPoint(252 - 248, 82 - 216));
	darkValleyClearings->append(new QPoint(0, 0));
	darkValleyClearings->append(new QPoint(186 - 248, 250 - 216));
	darkValleyClearings->append(new QPoint(362 - 248, 278 - 216));
	darkValleyClearings->append(new QPoint(0, 0));
	tileClearingOffsets->insert("Dark Valley", darkValleyClearings);
	
	tileImages->insert("Dark Valley Echanted", new QPixmap(":/images/tiles/darkvalley-e1.gif"));
	QList<QPoint*> *darkValleyEchantedClearings = new QList<QPoint*>();
	darkValleyEchantedClearings->append(new QPoint(358 - 248, 152 - 216));
	darkValleyEchantedClearings->append(new QPoint(248 - 248, 86 - 216));
	darkValleyEchantedClearings->append(new QPoint(0, 0));
	darkValleyEchantedClearings->append(new QPoint(192 - 248, 242 - 216));
	darkValleyEchantedClearings->append(new QPoint(362 - 248, 276 - 216));
	darkValleyEchantedClearings->append(new QPoint(0, 0));
	tileClearingOffsets->insert("Dark Valley Echanted", darkValleyEchantedClearings);
	
	tileImages->insert("Deep Woods", new QPixmap(":/images/tiles/deepwoods1.gif"));
	QList<QPoint*> *deepWoodsClearings = new QList<QPoint*>();
	deepWoodsClearings->append(new QPoint(164 - 248, 108 - 216));
	deepWoodsClearings->append(new QPoint(380 - 248, 218 - 216));
	deepWoodsClearings->append(new QPoint(300 - 248, 346 - 216));
	deepWoodsClearings->append(new QPoint(88 - 248, 220 - 216));
	deepWoodsClearings->append(new QPoint(148 - 248, 322 - 216));
	deepWoodsClearings->append(new QPoint(240 - 248, 240 - 216));
	tileClearingOffsets->insert("Deep Woods", deepWoodsClearings);
	
	tileImages->insert("Deep Woods Echanted", new QPixmap(":/images/tiles/deepwoods-e1.gif"));
	QList<QPoint*> *deepWoodsEchantedClearings = new QList<QPoint*>();
	/*
	deepWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	deepWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	deepWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	deepWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	deepWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	deepWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	*/
	tileClearingOffsets->insert("Deep Woods Echanted", deepWoodsEchantedClearings);
	
	tileImages->insert("Evil Valley", new QPixmap(":/images/tiles/evilvalley1.gif"));
	QList<QPoint*> *evilValleyClearings = new QList<QPoint*>();
	evilValleyClearings->append(new QPoint(132 - 248, 280 - 216));
	evilValleyClearings->append(new QPoint(132 - 248, 150 - 216));
	evilValleyClearings->append(new QPoint(0, 0));
	evilValleyClearings->append(new QPoint(312 - 248, 100 - 216));
	evilValleyClearings->append(new QPoint(362 - 248, 280 - 216));
	evilValleyClearings->append(new QPoint(0, 0));
	tileClearingOffsets->insert("Evil Valley", evilValleyClearings);
	
	tileImages->insert("Evil Valley Echanted", new QPixmap(":/images/tiles/evilvalley-e1.gif"));
	QList<QPoint*> *evilValleyEchantedClearings = new QList<QPoint*>();
	/*
	evilValleyEchantedClearings->append(new QPoint( - 248, - 216));
	evilValleyEchantedClearings->append(new QPoint( - 248, - 216));
	evilValleyEchantedClearings->append(new QPoint( - 248, - 216));
	evilValleyEchantedClearings->append(new QPoint( - 248, - 216));
	evilValleyEchantedClearings->append(new QPoint( - 248, - 216));
	evilValleyEchantedClearings->append(new QPoint( - 248, - 216));
	*/
	tileClearingOffsets->insert("Evil Valley Echanted", evilValleyEchantedClearings);
	
	tileImages->insert("High Pass", new QPixmap(":/images/tiles/highpass1.gif"));
	QList<QPoint*> *highPassClearings = new QList<QPoint*>();
	highPassClearings->append(new QPoint(340 - 248, 254 - 216));
	highPassClearings->append(new QPoint(248 - 248, 86 - 216));
	highPassClearings->append(new QPoint(358 - 248, 154 - 216));
	highPassClearings->append(new QPoint(218 - 248, 232 - 216));
	highPassClearings->append(new QPoint(250 - 248, 348 - 216));
	highPassClearings->append(new QPoint(136 - 248, 150 - 216));
	tileClearingOffsets->insert("High Pass", highPassClearings);
	
	tileImages->insert("High Pass Echanted", new QPixmap(":/images/tiles/highpass-e1.gif"));
	QList<QPoint*> *highPassEchantedClearings = new QList<QPoint*>();
	/*
	highPassEchantedClearings->append(new QPoint( - 248, - 216));
	highPassEchantedClearings->append(new QPoint( - 248, - 216));
	highPassEchantedClearings->append(new QPoint( - 248, - 216));
	highPassEchantedClearings->append(new QPoint( - 248, - 216));
	highPassEchantedClearings->append(new QPoint( - 248, - 216));
	highPassEchantedClearings->append(new QPoint( - 248, - 216));
	*/
	tileClearingOffsets->insert("High Pass Echanted", highPassEchantedClearings);
	
	tileImages->insert("Ledges", new QPixmap(":/images/tiles/ledges1.gif"));
	QList<QPoint*> *ledgesClearings = new QList<QPoint*>();
	ledgesClearings->append(new QPoint(272 - 248, 312 - 216));
	ledgesClearings->append(new QPoint(364 - 248, 154 - 216));
	ledgesClearings->append(new QPoint(376 - 248, 272 - 216));
	ledgesClearings->append(new QPoint(248 - 248, 212 - 216));
	ledgesClearings->append(new QPoint(154 - 248, 124 - 216));
	ledgesClearings->append(new QPoint(172 - 248, 350 - 216));
	tileClearingOffsets->insert("Ledges", ledgesClearings);
	
	tileImages->insert("Ledges Echanted", new QPixmap(":/images/tiles/ledges-e1.gif"));
	QList<QPoint*> *ledgesEchantedClearings = new QList<QPoint*>();
	/*
	ledgesEchantedClearings->append(new QPoint( - 248, - 216));
	ledgesEchantedClearings->append(new QPoint( - 248, - 216));
	ledgesEchantedClearings->append(new QPoint( - 248, - 216));
	ledgesEchantedClearings->append(new QPoint( - 248, - 216));
	ledgesEchantedClearings->append(new QPoint( - 248, - 216));
	ledgesEchantedClearings->append(new QPoint( - 248, - 216));
	*/
	tileClearingOffsets->insert("Ledges Echanted", ledgesEchantedClearings);
	
	tileImages->insert("Linden Woods", new QPixmap(":/images/tiles/lindenwoods1.gif"));
	QList<QPoint*> *lindenWoodsClearings = new QList<QPoint*>();
	lindenWoodsClearings->append(new QPoint(0, 0));
	lindenWoodsClearings->append(new QPoint(250 - 248, 276 - 216));
	lindenWoodsClearings->append(new QPoint(0, 0));
	lindenWoodsClearings->append(new QPoint(134 - 248, 150 - 216));
	lindenWoodsClearings->append(new QPoint(300 - 248, 124 - 216));
	lindenWoodsClearings->append(new QPoint(0, 0));
	tileClearingOffsets->insert("Linden Woods", lindenWoodsClearings);
	
	tileImages->insert("Linden Woods Echanted", new QPixmap(":/images/tiles/lindenwoods-e1.gif"));
	QList<QPoint*> *lindenWoodsEchantedClearings = new QList<QPoint*>();
	/*
	lindenWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	lindenWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	lindenWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	lindenWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	lindenWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	lindenWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	*/
	tileClearingOffsets->insert("Linden Woods Echanted", lindenWoodsEchantedClearings);
	
	tileImages->insert("Maple Woods", new QPixmap(":/images/tiles/maplewoods1.gif"));
	QList<QPoint*> *mapleWoodsClearings = new QList<QPoint*>();
	mapleWoodsClearings->append(new QPoint(0, 0));
	mapleWoodsClearings->append(new QPoint(316 - 248, 116 - 216));
	mapleWoodsClearings->append(new QPoint(0, 0));
	mapleWoodsClearings->append(new QPoint(370 - 248, 272 - 216));
	mapleWoodsClearings->append(new QPoint(144 - 248, 214 - 216));
	mapleWoodsClearings->append(new QPoint(0, 0));
	tileClearingOffsets->insert("Maple Woods", mapleWoodsClearings);
	
	tileImages->insert("Maple Woods Echanted", new QPixmap(":/images/tiles/maplewoods-e1.gif"));
	QList<QPoint*> *mapleWoodsEchantedClearings = new QList<QPoint*>();
	/*
	mapleWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	mapleWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	mapleWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	mapleWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	mapleWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	mapleWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	*/
	tileClearingOffsets->insert("Maple Woods Echanted", mapleWoodsEchantedClearings);
	
	tileImages->insert("Mountain", new QPixmap(":/images/tiles/mountain1.gif"));
	QList<QPoint*> *mountainClearings = new QList<QPoint*>();
	mountainClearings->append(new QPoint(170 - 248, 170 - 216));
	mountainClearings->append(new QPoint(120 - 248, 290 - 216));
	mountainClearings->append(new QPoint(240 - 248, 286 - 216));
	mountainClearings->append(new QPoint(248 - 248, 68 - 216));
	mountainClearings->append(new QPoint(374 - 248, 290 - 216));
	mountainClearings->append(new QPoint(344 - 248, 164 - 216));
	tileClearingOffsets->insert("Mountain", mountainClearings);
	
	tileImages->insert("Mountain Echanted", new QPixmap(":/images/tiles/mountain-e1.gif"));
	QList<QPoint*> *mountainEchantedClearings = new QList<QPoint*>();
	/*
	mountainEchantedClearings->append(new QPoint( - 248, - 216));
	mountainEchantedClearings->append(new QPoint( - 248, - 216));
	mountainEchantedClearings->append(new QPoint( - 248, - 216));
	mountainEchantedClearings->append(new QPoint( - 248, - 216));
	mountainEchantedClearings->append(new QPoint( - 248, - 216));
	mountainEchantedClearings->append(new QPoint( - 248, - 216));
	*/
	tileClearingOffsets->insert("Mountain Echanted", mountainEchantedClearings);
	
	tileImages->insert("Nut Woods", new QPixmap(":/images/tiles/nutwoods1.gif"));
	QList<QPoint*> *nutWoodsClearings = new QList<QPoint*>();
	nutWoodsClearings->append(new QPoint(0, 0));
	nutWoodsClearings->append(new QPoint(188 - 248, 106 - 216));
	nutWoodsClearings->append(new QPoint(0, 0));
	nutWoodsClearings->append(new QPoint(352 - 248, 136 - 216));
	nutWoodsClearings->append(new QPoint(244 - 248, 280 - 216));
	nutWoodsClearings->append(new QPoint(0, 0));
	tileClearingOffsets->insert("Nut Woods", nutWoodsClearings);
	
	tileImages->insert("Nut Woods Echanted", new QPixmap(":/images/tiles/nutwoods-e1.gif"));
	QList<QPoint*> *nutWoodsEchantedClearings = new QList<QPoint*>();
	/*
	nutWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	nutWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	nutWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	nutWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	nutWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	nutWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	*/
	tileClearingOffsets->insert("Nut Woods Echanted", nutWoodsEchantedClearings);
	
	tileImages->insert("Oak Woods", new QPixmap(":/images/tiles/oakwoods1.gif"));
	QList<QPoint*> *oakWoodsClearings = new QList<QPoint*>();
	oakWoodsClearings->append(new QPoint(0, 0));
	oakWoodsClearings->append(new QPoint(360 - 248, 206 - 216));
	oakWoodsClearings->append(new QPoint(0, 0));
	oakWoodsClearings->append(new QPoint(136 - 248, 282 - 216));
	oakWoodsClearings->append(new QPoint(190 - 248, 116 - 216));
	oakWoodsClearings->append(new QPoint(0, 0));
	tileClearingOffsets->insert("Oak Woods", oakWoodsClearings);
	
	tileImages->insert("Oak Woods Echanted", new QPixmap(":/images/tiles/oakwoods-e1.gif"));
	QList<QPoint*> *oakWoodsEchantedClearings = new QList<QPoint*>();
	/*
	oakWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	oakWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	oakWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	oakWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	oakWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	oakWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	*/
	tileClearingOffsets->insert("Oak Woods Echanted", oakWoodsEchantedClearings);
	
	tileImages->insert("Pine Woods", new QPixmap(":/images/tiles/pinewoods1.gif"));
	QList<QPoint*> *pineWoodsClearings = new QList<QPoint*>();
	pineWoodsClearings->append(new QPoint(0, 0));
	pineWoodsClearings->append(new QPoint(120 - 248, 192 - 216));
	pineWoodsClearings->append(new QPoint(0, 0));
	pineWoodsClearings->append(new QPoint(234 - 248, 82 - 216));
	pineWoodsClearings->append(new QPoint(360 - 248, 214 - 216));
	pineWoodsClearings->append(new QPoint(0, 0));
	tileClearingOffsets->insert("Pine Woods", pineWoodsClearings);
	
	tileImages->insert("Pine Woods Echanted", new QPixmap(":/images/tiles/pinewoods-e1.gif"));
	QList<QPoint*> *pineWoodsEchantedClearings = new QList<QPoint*>();
	/*
	pineWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	pineWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	pineWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	pineWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	pineWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	pineWoodsEchantedClearings->append(new QPoint( - 248, - 216));
	*/
	tileClearingOffsets->insert("Pine Woods Echanted", pineWoodsEchantedClearings);
	
	tileImages->insert("Ruins", new QPixmap(":/images/tiles/ruins1.gif"));
	QList<QPoint*> *ruinsClearings = new QList<QPoint*>();
	ruinsClearings->append(new QPoint(162 - 248, 148 - 216));
	ruinsClearings->append(new QPoint(324 - 248, 88 - 216));
	ruinsClearings->append(new QPoint(368 - 248, 284 - 216));
	ruinsClearings->append(new QPoint(234 - 248, 258 - 216));
	ruinsClearings->append(new QPoint(146 - 248, 328 - 216));
	ruinsClearings->append(new QPoint(328 - 248, 184 - 216));
	tileClearingOffsets->insert("Ruins", ruinsClearings);
	
	tileImages->insert("Ruins Echanted", new QPixmap(":/images/tiles/ruins-e1.gif"));
	QList<QPoint*> *ruinsEchantedClearings = new QList<QPoint*>();
	/*
	ruinsEchantedClearings->append(new QPoint( - 248, - 216));
	ruinsEchantedClearings->append(new QPoint( - 248, - 216));
	ruinsEchantedClearings->append(new QPoint( - 248, - 216));
	ruinsEchantedClearings->append(new QPoint( - 248, - 216));
	ruinsEchantedClearings->append(new QPoint( - 248, - 216));
	ruinsEchantedClearings->append(new QPoint( - 248, - 216));
	*/
	tileClearingOffsets->insert("Ruins Echanted", ruinsEchantedClearings);
}

errno_t GameWindow::initializeConnection(QString &hostIP)
{
	errno_t err = 0;

	ui.loadingMessageLabel->setText("--Connecting to server--");
	changeScreenState(ui.loadingWidget);
	
	err = server->threadConnect(hostIP, GAMEPORT);
	if (err)
	{
		cleanup();
		return err;
	}

	return err;
}

void GameWindow::connectedToServer(time_t time)
{
	game = new Game(time);

	game->setupGame(false);
	qDebug() << "client is connected to server, signal";
	for (int i = 0; i < ui.characterListView->count(); i++)
	{
		if (ui.characterListView->item(i)->flags() & Qt::ItemIsUserCheckable)
		{
			ui.characterListView->setCurrentRow(i);
			break;
		}
	}
	changeScreenState(ui.characterSelectWidget);
}

void GameWindow::updateAvailableCharacters(int removeCharacter)
{
	Qt::ItemFlags flags = ui.characterListView->item(removeCharacter)->flags();
	ui.characterListView->item(removeCharacter)->setFlags((flags & ~Qt::ItemIsSelectable & ~Qt::ItemIsUserCheckable & ~Qt::ItemIsEnabled));
}

void GameWindow::requestCharacter(CharacterType character, DwellingType startLoc)
{
	if (character >= Amazon && character <= Swordsman)
	{
		ui.loadingMessageLabel->setText("--Waiting for character acknowledgement--");
		changeScreenState(ui.loadingWidget);

		selectedCharacter = character;
		startLocation = startLoc;
	
		QString serializedCharacter;
		serializedCharacter.sprintf("CharacterType%s%d", CLASSDELIM, character);
		qDebug() << serializedCharacter;
		server->writeMessage(&serializedCharacter);
	}
}

void GameWindow::characterRequestAcknowledged(bool accepted)
{
	if (!accepted)
	{
		changeScreenState(ui.characterSelectWidget);
		QMessageBox::about(ui.centralWidget, "Error", "Character taken.");
		return;
	}

	ui.loadingMessageLabel->setText("--Waiting for game to begin--");
	changeScreenState(ui.loadingWidget);

	QString serializedStartLocation;
	serializedStartLocation.sprintf("SpawnLocation%s%d", CLASSDELIM, startLocation);
	server->writeMessage(&serializedStartLocation);
}

void GameWindow::addCharacterToGame(QString &newCharacter)
{
	Character* character = new Character(new string(newCharacter.toUtf8().constData()));
	game->addPlayer(character);
	if (gameStarted)
	{
		updateCharacterInfoPane();
		updateTileInfoPane(selectedTile);
		placeCharacter(character);
	}
}

void GameWindow::addMonsterToGame(Monster* monster)
{
	if (monster != 0)
	{
		string monsterName;
		if (monster->getName() == "Wolf")
		{
			if (monster->getHarm() == 'L')
			{
				monsterName = "Wolf1";
			}
			else if (monster->getHarm() == 'M')
			{
				monsterName = "Wolf2";
			}
		}
		else
		{
			monsterName = monster->getName();
		}
		QPixmap pxmap = *(*monsterImages)[monsterName];
		MonsterGraphicsItem* item = new MonsterGraphicsItem(pxmap, monster, this);
		item->setTransformOriginPoint(pxmap.width() / 2, pxmap.height() / 2);
		item->setZValue(counterDepth);
		item->setVisible(true);
		item->setScale(monsterImageScale);
		monsterGraphicsItems->insert(monster->getID(), item);
		placeMonster(monster);
		gameScene->addItem(item);
	}
}

void GameWindow::removeMonsterFromGame(int id)
{
	gameScene->removeItem((*monsterGraphicsItems)[id]);
}

errno_t GameWindow::initializeGame()
{
	errno_t err = 0;

	gameScene = new QGraphicsScene();

	turnNumber = 1;
	
	tileLocations = new QMap<Tile*, QPointF>();

	drawTiles();

	for (int i = 0; i <= Swordsman; i++)
	{
		QPixmap pxmap = *(*characterImages)[(CharacterType)i];
		QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pxmap);
		item->setTransformOriginPoint(pxmap.width() / 2, pxmap.height() / 2);
		characterGraphicsItems->insert((CharacterType)i, item);
		item->setZValue(counterDepth);
		item->setVisible(false);
		item->setScale(characterImageScale);
		Character* character = game->getPlayer((CharacterType)i);
		if (character != 0)
		{
			placeCharacter(character);
		}
		gameScene->addItem(item);
	}

	for (int i = 0; i <= INN; i++)
	{
		QPixmap pxmap = *(*dwellingImages)[(DwellingType)i];
		QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pxmap);
		item->setTransformOriginPoint(pxmap.width() / 2, pxmap.height() / 2);
		item->setZValue(counterDepth);
		item->setVisible(true);
		item->setScale(dwellingImageScale);
		dwellingGraphicsItems->insert((DwellingType)i, item);
		Dwelling* dwelling = game->getDwelling((DwellingType)i);
		if (dwelling != 0)
		{
			placeDwelling(dwelling);
		}
		gameScene->addItem(item);
	}
	
	initializeDestinationCounter();

	vector<Monster*> monsters = *game->getActiveMonsters();
	for (vector<Monster*>::iterator it = monsters.begin(); it != monsters.end(); ++it)
	{
		addMonsterToGame(*it);
	}
	
	ui.graphicsView->setScene(gameScene);
	changeScreenState(ui.gameWidget);

	return err;
}

errno_t GameWindow::initializeDestinationCounter()
{
	destinationCounter = new QGraphicsPixmapItem(*destinationCounterImage);
	destinationCounter->setTransformOriginPoint(destinationCounterImage->width() / 2, destinationCounterImage->height() / 2);
	destinationCounter->setZValue(counterDepth - 0.1);
	destinationCounter->setVisible(true);
	destinationCounter->setScale(characterImageScale * 3);
	gameScene->addItem(destinationCounter);
	return 0;
}

errno_t GameWindow::drawTiles()
{
	Board* gameBoard = game->getBoard();

	Tile* currTile = gameBoard->getTile("Border Land");
	if (currTile != 0)
	{
		selectTile(currTile);

		QPixmap pixmap = *(*tileImages)[currTile->getName()];
		TileGraphicsItem* item = new TileGraphicsItem(pixmap, currTile, this);
		item->setPos(0, 0);
		item->setRotation((360 / 6) * ((int)currTile->getOrientation()));
		item->setTransformOriginPoint(pixmap.width() / 2, pixmap.height() / 2);
		
		gameScene->addItem(item);

		unordered_set<Tile*> visitedTiles;
		visitedTiles.insert(currTile);

		tileLocations->insert(currTile, QPointF(0, 0));

		queue<Tile*> incompleteTiles;
		incompleteTiles.push(currTile);

		qreal xOffset = 1;
		qreal yOffset = 3;
		qreal xTileOffset = pixmap.width() - xOffset;
		qreal yTileOffset = pixmap.height() - yOffset;

		while (!incompleteTiles.empty())
		{
			tileGraphicsItems->insert(currTile, item);
			currTile = incompleteTiles.front();
			incompleteTiles.pop();
			for (int i = 0; i < CONNECTED_LENGTH; i++)
			{
				Tile* newTile = currTile->getConnected((Direction)i);
				if ((newTile != 0) && (visitedTiles.find(newTile) == visitedTiles.end()))
				{
					QPixmap pixmap = *(*tileImages)[newTile->getName()];
					TileGraphicsItem* item = new TileGraphicsItem(pixmap, newTile, this);

					int side = ((int)(currTile->getOrientation()) + i) % 6;
					QPointF pos;
					switch (side)
					{
					case 0:
						pos = QPointF((*tileLocations)[currTile].x(), (*tileLocations)[currTile].y() + yTileOffset);
						break;
					case 1:
						pos = QPointF((*tileLocations)[currTile].x() - (xTileOffset * 0.75), (*tileLocations)[currTile].y() + (yTileOffset / 2));
						break;
					case 2:
						pos = QPointF((*tileLocations)[currTile].x() - (xTileOffset * 0.75), (*tileLocations)[currTile].y() - (yTileOffset / 2));
						break;
					case 3:
						pos = QPointF((*tileLocations)[currTile].x(), (*tileLocations)[currTile].y() - yTileOffset);
						break;
					case 4:
						pos = QPointF((*tileLocations)[currTile].x() + (xTileOffset * 0.75), (*tileLocations)[currTile].y() - (yTileOffset / 2));
						break;
					case 5:
						pos = QPointF((*tileLocations)[currTile].x() + (xTileOffset * 0.75), (*tileLocations)[currTile].y() + (yTileOffset / 2));
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
					tileLocations->insert(newTile, pos);
				}
			}		
		}
		return 0;
	}
	return 1;
}

errno_t GameWindow::cleanup()
{
	errno_t err = 0;

	err = server->threadDisconnect();

	/*
	if (tileGraphicsItems != 0)
	{
		tileGraphicsItems->clear();
		delete tileGraphicsItems;
		tileGraphicsItems = 0;
	}
	*/

	if (game != 0)
	{
		delete game;
		game = 0;
	}

	gameStarted = false;
	
	changeScreenState(ui.menuWidget);

	return err;
}

void GameWindow::changeScreenState(QWidget* screen)
{
	ui.menuWidget->setEnabled(false);
	ui.loadingWidget->setEnabled(false);
	ui.characterSelectWidget->setEnabled(false);
	ui.gameWidget->setEnabled(false);
	ui.menuWidget->setVisible(false);
	ui.loadingWidget->setVisible(false);
	ui.characterSelectWidget->setVisible(false);
	ui.gameWidget->setVisible(false);
	if (screen == ui.gameWidget)
	{
		window->showFullScreen();
	}
	else
	{
		window->showNormal();
	}
	screen->setEnabled(true);
	screen->setVisible(true);
	qApp->processEvents();
}

void GameWindow::enableActions()
{
	ui.gameMoveActionButton->setEnabled(true);
	ui.gameSearchActionButton->setEnabled(true);
	ui.gameTradeActionButton->setEnabled(true);
	ui.gameHideActionButton->setEnabled(true);
}

void GameWindow::disableActions()
{
	ui.gameMoveActionButton->setDisabled(true);
	ui.gameSearchActionButton->setDisabled(true);
	ui.gameTradeActionButton->setDisabled(true);
	ui.gameHideActionButton->setDisabled(true);
}

CharacterType GameWindow::getSelectedChar()
{
	return selectedCharacter;
}

void GameWindow::selectTile(Tile* tile)
{
	selectedTile = tile;

	switch (selectedAction)
	{
	case NoAction:
		{
			break;
		}
	case MoveAction:
		{
			break;
		}
	case SearchAction:
		{
			break;
		}
	case TradeAction:
		{
			break;
		}
	case HideAction:
		{
			break;
		}
	default:
		{
			break;
		}
	}

	updateTileInfoPane(selectedTile);

	selectAction(NoAction);
}

void GameWindow::selectMonster(Monster* monster)
{
	selectedMonster = monster;
	updateMonsterInfoPane(selectedMonster);
}

void GameWindow::updateCharacterInfoPane()
{
	Character* character = game->getPlayer(selectedCharacter);
	QFont font = QFont("MS Serif", 26);
	font.setBold(true);
	font.setUnderline(true);
	ui.gameCharacterInformationBrowser->setCurrentFont(font);
	ui.gameCharacterInformationBrowser->setText(Character::getTypeString(character->getType()));
	
	font.setPointSize(14);
	font.setUnderline(false);
	ui.gameCharacterInformationBrowser->setCurrentFont(font);

	QString characterInfo;
	Clearing* loc = character->getCurrentLocation();
	characterInfo.sprintf("\nLocation: %s Clearing %d: %s", loc->getTile()->getName().c_str(), loc->getClearingNum(), Clearing::getTypeString(loc->getClearingType()));
	ui.gameCharacterInformationBrowser->append(characterInfo);
	
	characterInfo.sprintf("\nGold: %d", character->getGold());
	ui.gameCharacterInformationBrowser->append(characterInfo);

	ui.gameCharacterInformationBrowser->append("\nEquipment:");
	vector<Equipment*>* equipment = character->getEquipment();
	for (vector<Equipment*>::iterator it = equipment->begin(); it != equipment->end(); ++it)
	{
		characterInfo.sprintf("  - %s", (*it)->getName().c_str());
		ui.gameCharacterInformationBrowser->append(characterInfo);
	}
	ui.gameCharacterInformationBrowser->verticalScrollBar()->setValue(0);
}

void GameWindow::updateTileInfoPane(Tile* tile)
{
	QFont font = QFont("MS Serif", 26);
	font.setBold(true);
	font.setUnderline(true);
	ui.gameTileInformationBrowser->setCurrentFont(font);
	ui.gameTileInformationBrowser->setText(QString(tile->getName().c_str()));
	
	// CHITS INFO
	font.setPointSize(18);
	font.setUnderline(false);
	ui.gameTileInformationBrowser->setCurrentFont(font);
	ui.gameTileInformationBrowser->append("\nChits");
	Chit* siteOrSoundChit = tile->getSiteOrSoundChit();
	if (siteOrSoundChit != 0 && (!siteOrSoundChit->isHidden() ||
		(game->getPlayer(selectedCharacter)->getCurrentLocation() != 0 &&
		tile == game->getPlayer(selectedCharacter)->getCurrentLocation()->getTile())))
	{
		font.setPointSize(16);
		font.setBold(false);
		ui.gameTileInformationBrowser->setCurrentFont(font);
		QString chitInfo;
		ChitType chitType = siteOrSoundChit->getType();
		bool lost = false;
		switch (chitType)
		{
		case CHIT_SOUND:
			chitInfo.append("Sound: ");
			break;
		case CHIT_SITE:
			chitInfo.append("Site: ");
			break;
		case CHIT_LOST:
			lost = true;
		case CHIT_WARNING:
		default:
				break;
		}
		chitInfo.append(siteOrSoundChit->getName().c_str());
		ui.gameTileInformationBrowser->append(chitInfo);
		if (lost)
		{
			font.setPointSize(14);
			ui.gameTileInformationBrowser->setCurrentFont(font);
			vector<Chit*>* treasureChits = siteOrSoundChit->getContents();
			for (vector<Chit*>::iterator it = treasureChits->begin(); it != treasureChits->end(); ++it)
			{
				chitInfo.sprintf(" - %s", (*it)->getName().c_str());
				ui.gameTileInformationBrowser->append(chitInfo);
			}
		}
	}
	else
	{
		if (tile->getType() == TILE_CAVES || tile->getType() == TILE_MOUNTAIN)
		{
			ui.gameTileInformationBrowser->append("???");
		}
	}
	Chit* warningChit = tile->getWarningChit();
	if (warningChit != 0 && (!warningChit->isHidden() ||
		(game->getPlayer(selectedCharacter)->getCurrentLocation() != 0 &&
		tile == game->getPlayer(selectedCharacter)->getCurrentLocation()->getTile())))
	{
		font.setPointSize(16);
		font.setBold(false);
		ui.gameTileInformationBrowser->setCurrentFont(font);
		QString chitInfo;
		chitInfo.sprintf("Warning: %s", warningChit->getName().c_str());
		ui.gameTileInformationBrowser->append(chitInfo);
	}
	else
	{
		ui.gameTileInformationBrowser->append("???");
	}

	// CLEARINGS INFO
	font.setPointSize(18);
	font.setBold(true);
	ui.gameTileInformationBrowser->setCurrentFont(font);
	ui.gameTileInformationBrowser->append("\nClearings");
	for (int i = 1; i < CONNECTED_LENGTH+1; i++)
	{
		Clearing* c = tile->getClearing(i);
		if (c != 0)
		{
			QString clearingInfo;
			Dwelling* d = c->getDwelling();
			if (d != 0)
			{
				clearingInfo.sprintf("Clearing %d: %s\n%s", c->getClearingNum(), 
					Clearing::getTypeString(c->getClearingType()), c->getDwelling()->getName().c_str());
			}
			else
			{
				clearingInfo.sprintf("Clearing %d: %s", c->getClearingNum(), 
					Clearing::getTypeString(c->getClearingType()));
			}
			font.setPointSize(16);
			font.setBold(false);
			ui.gameTileInformationBrowser->setCurrentFont(font);
			ui.gameTileInformationBrowser->append(clearingInfo);

			vector<Character*> chrs = *c->getCharacters();
			if (chrs.size() > 0)
			{
				ui.gameTileInformationBrowser->append("Players:");
				font.setPointSize(12);
				font.setBold(true);
				ui.gameTileInformationBrowser->setCurrentFont(font);
				for (vector<Character*>::iterator chr  = chrs.begin(); chr != chrs.end(); ++chr)
				{
					QString charString;
					charString.sprintf("  - %s", Character::getTypeString((*chr)->getType()));
					if ((*chr)->isHidden())
					{
						charString.append(" (hidden)");
					}
					ui.gameTileInformationBrowser->append(charString);
				}
			}
			vector<Monster*> mons = *c->getMonsterList();
			if (mons.size() > 0)
			{
				ui.gameTileInformationBrowser->append("Monsters:");
				font.setPointSize(12);
				font.setBold(true);
				ui.gameTileInformationBrowser->setCurrentFont(font);
				for (vector<Monster*>::iterator mon  = mons.begin(); mon != mons.end(); ++mon)
				{
					QString charString;
					charString.sprintf("  - %s", (*mon)->getName().c_str());
					ui.gameTileInformationBrowser->append(charString);
				}
			}
			ui.gameTileInformationBrowser->append("");
		}
	}
	ui.gameTileInformationBrowser->verticalScrollBar()->setValue(0);
}

void GameWindow::updateMonsterInfoPane(Monster* monster)
{
	QFont font = QFont("MS Serif", 14);
	if (monster == 0)
	{
		ui.gameMonsterInformationBrowser->setCurrentFont(font);
		ui.gameMonsterInformationBrowser->setText("No monster currently selected");
	}
	else
	{
		font.setPointSize(26);
		font.setBold(true);
		font.setUnderline(true);
		ui.gameMonsterInformationBrowser->setCurrentFont(font);
		ui.gameMonsterInformationBrowser->setText(monster->getName().c_str());
		
		font.setPointSize(14);
		font.setUnderline(false);
		ui.gameMonsterInformationBrowser->setCurrentFont(font);

		QString monsterInfo;
		Clearing* loc = monster->getLocation();
		monsterInfo.sprintf("\nLocation: %s Clearing %d: %s", loc->getTile()->getName().c_str(), loc->getClearingNum(), Clearing::getTypeString(loc->getClearingType()));
		ui.gameMonsterInformationBrowser->append(monsterInfo);
	
		monsterInfo.sprintf("\nBounty:\n  - %d fame\n  - %d notoriety", monster->getFame(), monster->getNotoriety());
		ui.gameMonsterInformationBrowser->append(monsterInfo);
	}
}

int GameWindow::getXRelationalOffsetWithRotation(int x, int y, int rotation)
{
	return (int)(x * cos(qDegreesToRadians((double)rotation)) - y * sin(qDegreesToRadians((double)rotation))); // for now
}

int GameWindow::getYRelationalOffsetWithRotation(int x, int y, int rotation)
{
	return (int)(x * sin(qDegreesToRadians((double)rotation)) + y * cos(qDegreesToRadians((double)rotation))); // for now
}

void GameWindow::placeCharacter(Character* character)
{
	Clearing* clearing = character->getCurrentLocation();
	if (clearing != 0)
	{
		Tile* tile = clearing->getTile();
		if (tile != 0)
		{
			vector<Character*> characters = *clearing->getCharacters();
			int chars = characters.size();
			int charCounterDiameter = ((*characterImages)[Amazon]->width() * characterImageScale);
			TileGraphicsItem* tileItem = ((*tileGraphicsItems)[tile]);
			QPoint *clearingOffset = (*(*tileClearingOffsets)[tile->getName()])[clearing->getClearingNum() - 1];
			int characterOffsetX = getXRelationalOffsetWithRotation(clearingOffset->x(), clearingOffset->y(),
				(360 / 6) * ((int)tile->getOrientation())) - (((chars - 1) * charCounterDiameter) / 2);
			int characterOffsetY = getYRelationalOffsetWithRotation(clearingOffset->x(), clearingOffset->y(),
				(360 / 6) * ((int)tile->getOrientation()));
			if (clearing->getDwelling() != 0)
			{
				characterOffsetY += (((*dwellingImages)[CHAPEL]->height() * dwellingImageScale) / 2) + (charCounterDiameter / 2);
			}
			for (vector<Character*>::iterator it = characters.begin(); it != characters.end(); ++it)
			{
				QPixmap* charPix = (*characterImages)[(*it)->getType()];
				QGraphicsPixmapItem* charItem = (*characterGraphicsItems)[(*it)->getType()];
				if (charItem != 0)
				{
					charItem->setX((*tileLocations)[tile].x() + (tileItem->width() / 2) - (charPix->width() / 2)
						+ characterOffsetX);
					charItem->setY((*tileLocations)[tile].y() + (tileItem->height() / 2) - (charPix->height() / 2)
						+ characterOffsetY);
					charItem->setVisible(true);
					characterOffsetX += charCounterDiameter;
				}
			}
		}
	}
}

void GameWindow::placeDestinationCounter()
{
	if (destinationClearing != 0 && destinationCounter != 0)
	{
		Tile* tile = destinationClearing->getTile();
		if (tile != 0)
		{
			TileGraphicsItem* tileItem = ((*tileGraphicsItems)[tile]);
			QPoint *clearingOffset = (*(*tileClearingOffsets)[tile->getName()])[destinationClearing->getClearingNum() - 1];
			int offsetX = getXRelationalOffsetWithRotation(clearingOffset->x(), clearingOffset->y(),
				(360 / 6) * ((int)tile->getOrientation()));
			int offsetY = getYRelationalOffsetWithRotation(clearingOffset->x(), clearingOffset->y(),
				(360 / 6) * ((int)tile->getOrientation()));
			destinationCounter->setX((*tileLocations)[tile].x() + (tileItem->width() / 2) -
				(destinationCounter->pixmap().width() / 2) + offsetX);
			destinationCounter->setY((*tileLocations)[tile].y() + (tileItem->height() / 2) -
				(destinationCounter->pixmap().height() / 2) + offsetY);
		}
	}
}

void GameWindow::placeDwelling(Dwelling* dwelling)
{
	Clearing* clearing = dwelling->getLocation();
	if (clearing != 0)
	{
		Tile* tile = clearing->getTile();
		if (tile != 0)
		{
			TileGraphicsItem* tileItem = ((*tileGraphicsItems)[tile]);
			QPoint *clearingOffset = (*(*tileClearingOffsets)[tile->getName()])[clearing->getClearingNum() - 1];
			int offsetX = getXRelationalOffsetWithRotation(clearingOffset->x(), clearingOffset->y(),
				(360 / 6) * ((int)tile->getOrientation()));
			int offsetY = getYRelationalOffsetWithRotation(clearingOffset->x(), clearingOffset->y(),
				(360 / 6) * ((int)tile->getOrientation()));
			QPixmap* dwellingPix = (*dwellingImages)[dwelling->getType()];
			QGraphicsPixmapItem* dwellingItem = (*dwellingGraphicsItems)[dwelling->getType()];
			if (dwellingItem != 0)
			{
				dwellingItem->setX((*tileLocations)[tile].x() + (tileItem->width() / 2) - (dwellingPix->width() / 2)
					+ offsetX);
				dwellingItem->setY((*tileLocations)[tile].y() + (tileItem->height() / 2) - (dwellingPix->height() / 2)
					+ offsetY);
			}
		}
	}
}

void GameWindow::placeMonster(Monster* monster)
{
	Clearing* clearing = monster->getLocation();
	if (clearing != 0)
	{
		Tile* tile = clearing->getTile();
		if (tile != 0)
		{
			TileGraphicsItem* tileItem = ((*tileGraphicsItems)[tile]);
			vector<Monster*> monsters = *clearing->getMonsterList();
			int monsterCounterDiameter = ((*monsterImages)["Heavy Serpent"])->width() * monsterImageScale;
			QPoint *clearingOffset = (*(*tileClearingOffsets)[tile->getName()])[clearing->getClearingNum() - 1];
			int monsterOffsetX = getXRelationalOffsetWithRotation(clearingOffset->x(), clearingOffset->y(),
				(360 / 6) * ((int)tile->getOrientation())) - (((monsters.size() - 1) * monsterCounterDiameter) / 2);
			int monsterOffsetY = getYRelationalOffsetWithRotation(clearingOffset->x(), clearingOffset->y(),
				(360 / 6) * ((int)tile->getOrientation()));
			vector<Character*> characters = *clearing->getCharacters();
			if (clearing->getDwelling() != 0)
			{
				monsterOffsetY -= ((((*dwellingImages)[CHAPEL]->height() * dwellingImageScale) / 2) + (monsterCounterDiameter / 2));
			}
			else if (characters.size() > 0)
			{
				monsterOffsetY -= monsterCounterDiameter / 2;
				if (monsters.size() == 0)
				{
					int characterCounterDiameter = ((*characterImages)[Amazon]->width() * characterImageScale) / 2;
					for (vector<Character*>::iterator it = characters.begin(); it != characters.end(); ++it)
					{
						QPixmap* charPix = (*characterImages)[(*it)->getType()];
						QGraphicsPixmapItem* charItem = (*characterGraphicsItems)[(*it)->getType()];
						if (charItem != 0)
						{
							int currY = charItem->y();
							charItem->setY(currY + characterCounterDiameter);
						}
					}
				}
			}
			for (vector<Monster*>::iterator it = monsters.begin(); it != monsters.end(); ++it)
			{
				QPixmap* charPix = (*monsterImages)[(*it)->getName()];
				MonsterGraphicsItem* monsterItem = (*monsterGraphicsItems)[(*it)->getID()];
				if (monsterItem != 0)
				{
					monsterItem->setX((*tileLocations)[tile].x() + (tileItem->width() / 2) - (charPix->width() / 2)
						+ monsterOffsetX);
					monsterItem->setY((*tileLocations)[tile].y() + (tileItem->height() / 2) - (charPix->height() / 2)
						+ monsterOffsetY);
					monsterItem->setVisible(true);
					monsterOffsetX += monsterCounterDiameter;
				}
			}
		}
	}
}

void GameWindow::selectAction(ActionType action)
{
	selectedAction = action;
	bool actionCompleted = false;
	QString eventString;
	
	if (action == NoAction)
	{

	}
	else if (action == MoveAction)
	{
		actionCompleted = moveAction();
		if (actionCompleted)
		{
			eventString.sprintf(" - Move to %s clearing %d", destinationClearing->getTile()->getName().c_str(),
				destinationClearing->getClearingNum());
			ui.gameEventFeedBrowser->append(eventString);
		}
	}
	else if (action == SearchAction)
	{
		actionCompleted = true;
		if (actionCompleted)
		{
			eventString.sprintf(" - Search %s clearing %d", destinationClearing->getTile()->getName().c_str(),
				destinationClearing->getClearingNum());
			ui.gameEventFeedBrowser->append(eventString);
		}
	}
	else if (action == TradeAction)
	{
		actionCompleted = true;
		if (actionCompleted)
		{
			eventString.sprintf(" - Trade");
			ui.gameEventFeedBrowser->append(eventString);
		}
	}
	else if (action == HideAction)
	{
		actionCompleted = true;
		if (actionCompleted)
		{
			eventString.sprintf(" - Hide at %s clearing %d", destinationClearing->getTile()->getName().c_str(),
				destinationClearing->getClearingNum());
			ui.gameEventFeedBrowser->append(eventString);
		}
	}

	if (actionCompleted)
	{
		myTurn->addAction(new Action(action, destinationClearing), currentPhase);
		ui.gamePhaseComboBox->removeItem(ui.gamePhaseComboBox->currentIndex());
		caveCheck();
		int movablePhases = 0;
		for (int i = 0; i < ui.gamePhaseComboBox->count(); i++)
		{
			if (ui.gamePhaseComboBox->itemText(i) == "Basic")
			{
				movablePhases++;
			}
		}
		if (movablePhases <= 0)
		{
			for (int i = 0; i < sunlightPhases; i++)
			{
				ui.gamePhaseComboBox->addItem("Adding sunlight phase");
				for (int i = ui.gamePhaseComboBox->count() - 1; i > 0 ; i--)
				{
					ui.gamePhaseComboBox->setItemText(i, ui.gamePhaseComboBox->itemText(i-1));
					ui.gamePhaseComboBox->setItemIcon(i, ui.gamePhaseComboBox->itemIcon(i-1));
				}
				ui.gamePhaseComboBox->setItemText(0, "Sunlight");
				ui.gamePhaseComboBox->setItemIcon(0, QIcon(":/images/phases/sunshine.gif"));
			}
			if (sunlightPhases > 0)
			{
				enableActions();
			}
			sunlightPhases = 0;
		}
	}

	selectedAction = NoAction;
}

bool GameWindow::moveAction()
{
	vector<Path*> availablePaths = *(destinationClearing->getPaths());
	QList<Clearing*> adjacentClearings;
	for (vector<Path*>::iterator it = availablePaths.begin(); it != availablePaths.end(); ++it)
	{
		Path* p = *it;
		Clearing* end = p->getEnd(destinationClearing);
		Character* character = game->getPlayer(selectedCharacter);
		if (end != NULL && ((p->getType() == NORMAL) || character->isDiscovered(p)))
		{
			adjacentClearings.append(end);
		}
	}

	int movingPhases = countMovingPhases();

	AvailableMovesDialog* dlg = new AvailableMovesDialog(ui.centralWidget);
	for (Clearing* c : adjacentClearings)
	{
		bool noMountainClimb = true;
		bool noSunlightIntoCaves = true;

		QString option;
		option.sprintf("%s: Clearing %d", c->getTile()->getName().c_str(), c->getClearingNum());
		if ((destinationClearing->getClearingType() == MOUNTAIN && c->getClearingType() != MOUNTAIN) ||
			(destinationClearing->getClearingType() != MOUNTAIN && c->getClearingType() == MOUNTAIN))
		{
			option.append(" (Cost: 2 phases to climb/descend)");
			noMountainClimb = false;
		}
		if (c->getClearingType() == CAVES && ui.gamePhaseComboBox->currentText() == "Sunlight")
		{
			option.append(" (May not move into a cave using sunlight phase)");
			noSunlightIntoCaves = false;
		}

		dlg->addOption(option, ((noMountainClimb || (movingPhases > 1)) && noSunlightIntoCaves));
	}
	int destIndex = dlg->exec();

	bool moveConfirmed = false;

	if (destIndex != -1)
	{
		moveConfirmed = true;
		Clearing* newDest = adjacentClearings.at(destIndex);
		if ((destinationClearing->getClearingType() == MOUNTAIN && newDest->getClearingType() != MOUNTAIN) ||
			(destinationClearing->getClearingType() != MOUNTAIN && newDest->getClearingType() == MOUNTAIN))
		{
			payForMountainClimb();
		}
		destinationClearing = newDest;
		placeDestinationCounter();
	}
	delete dlg;

	return moveConfirmed;
}

void GameWindow::moveTo(CharacterType character, QString& clearingString)
{
	if (!gameStarted && (selectedCharacter != NullCharacter))
	{
		gameStarted = true;
		initializeGame();
	}
	string second(clearingString.toUtf8().constData());

	int pos = second.find(VARDELIM);
	int id = atoi(second.substr(pos + 1).c_str());
	second = second.substr(0, pos);

	Clearing* clearing = game->getBoard()->getTile(second)->getClearing(id);
	
	game->move(game->getPlayer(character), clearing);
	if (gameStarted)
	{
		if (selectedCharacter == character)
		{
			destinationClearing = clearing;
			placeDestinationCounter();
		}
		updateCharacterInfoPane();
		updateTileInfoPane(selectedTile);
		placeCharacter(game->getPlayer((CharacterType)character));
		
		QString eventString;
		eventString.sprintf("%s moved to %s clearing %d", Character::getTypeString((CharacterType)character),
			clearing->getTile()->getName().c_str(), clearing->getClearingNum());
		ui.gameEventFeedBrowser->append(eventString);
	}
}

void GameWindow::setCharacterHidden(CharacterType character, bool hidden)
{
	Character* c = game->getPlayer(character);
	QString eventString;
	if (hidden)
	{
		if (!c->isHidden())
		{
			c->toggleHide();
		}
		eventString.sprintf("%s hid.", Character::getTypeString(character));
	}
	else
	{
		if (c->isHidden())
		{
			c->toggleHide();
		}
		else
		{
			eventString.sprintf("%s failed to hide.", Character::getTypeString(character));
		}
	}
	ui.gameEventFeedBrowser->append(eventString);
}

void GameWindow::searchTypeRequest(QString& searchTypes)
{
	int pos = searchTypes.indexOf(CLASSDELIM);
	searchTypes = searchTypes.remove(0, pos + 2);
	pos = searchTypes.indexOf(VARDELIM);
	searchTypes = searchTypes.right(searchTypes.size() - (pos + 1));
	pos = searchTypes.indexOf(VARDELIM);
	int searchType;
	if (pos != -1) {
		searchType = QMessageBox::question(ui.centralWidget, "Search Type", "How would you like to search?", "Peer", "Locate", "Loot");
	} else {
		searchType = QMessageBox::question(ui.centralWidget, "Search Type", "How would you like to search?", "Peer", "Locate");
	}
	
	QString serializedSearchType;
	serializedSearchType.sprintf("SearchTypeResp%s%d", CLASSDELIM, searchType);
	server->writeMessage(&serializedSearchType);
}

void GameWindow::blockRequest(CharacterType characterType)
{
	QString question;
	question.sprintf("Do you want to block %s?", Character::getTypeString(characterType));
	int block = ((QMessageBox::question(ui.centralWidget, "Block", question) == QMessageBox::Yes) ? 1 : 0);
	
	QString serializedBlock;
	serializedBlock.sprintf("BlockResp%s%d", CLASSDELIM, block);
	server->writeMessage(&serializedBlock);
}

void GameWindow::blockCharacter(CharacterType characterType)
{
	Character* c = game->getPlayer(characterType);
	if (c != 0)
	{
		c->setBlock(true);
	}
	QString eventString;
	eventString.sprintf("%s has been blocked!", Character::getTypeString(characterType));
	ui.gameEventFeedBrowser->append(eventString);
}

void GameWindow::search(CharacterType character, SearchType searchType)
{
	Character* c = game->getPlayer(character);
	switch (searchType)
	{
	case PEER:
		game->searchPeerRequest();
		break;
	case LOCATE:
		game->searchLocateRequest();
		break;
	case LOOT:
		game->searchLootRequest(c);
		break;
	default:
		break;
	}
}

void GameWindow::treasureFound(CharacterType character, int treasureWorth)
{
	Character* c = game->getPlayer(character);
	c->addGold(treasureWorth);
	QString eventString;
	eventString.sprintf("%s found %d gold!", Character::getTypeString(character), treasureWorth);
	ui.gameEventFeedBrowser->append(eventString);
}

void GameWindow::siteFound(CharacterType character, QString& siteName)
{
	Character* c = game->getPlayer(character);
	Chit* chit = c->getCurrentLocation()->getTile()->getSiteOrSoundChit();
	if (chit->getType() == CHIT_LOST)
	{
		vector<Chit*>* lostChits = chit->getContents();
		for (vector<Chit*>::iterator it = lostChits->begin(); it != lostChits->end(); ++it)
		{
			QString chitName;
			chitName.append((*it)->getName().c_str());
			if (siteName == chitName)
			{
				chit = *it;
				break;
			}
		}
	}
	c->discover(chit);
	QString eventString;
	eventString.sprintf("%s found %s!", Character::getTypeString(character), chit->getName().c_str());
	ui.gameEventFeedBrowser->append(eventString);
}

void GameWindow::monsterCombatRequest(int monsterID)
{
	QString question;
	string monsterName;
	vector<Monster*> monsters = *game->getActiveMonsters();
	for (vector<Monster*>::iterator it = monsters.begin(); it != monsters.end(); ++it)
	{
		if ((*it)->getID() == monsterID)
		{
			monsterName = (*it)->getName();
			break;
		}
	}
	question.sprintf("Will you engage in combat with %s?", monsterName);
	int combat = ((QMessageBox::question(ui.centralWidget, "Engage Combat", question) == QMessageBox::Yes) ? 1 : 0);
	
	QString serializedCombat;
	serializedCombat.sprintf("MonsterCombatResp%s%d%s%d%s%d", CLASSDELIM, combat, VARDELIM, monsterID, VARDELIM, (int)selectedCharacter);
	server->writeMessage(&serializedCombat);
}

void GameWindow::monsterKilledBy(int monsterID, CharacterType characterType)
{
	vector<Monster*> monsters = *game->getActiveMonsters();
	Monster* myMonster = 0;
	for (vector<Monster*>::iterator it = monsters.begin(); it != monsters.end(); ++it)
	{
		if ((*it)->getID() == monsterID)
		{
			myMonster = (*it);
			break;
		}
	}
	if (myMonster != 0)
	{
		QString eventString;
		eventString.sprintf("%s killed %s!", Character::getTypeString(characterType), myMonster->getName().c_str());
		ui.gameEventFeedBrowser->append(eventString);
		removeMonsterFromGame(monsterID);
		game->killMonster(myMonster, game->getPlayer(characterType));
	}
}

void GameWindow::characterCombatRequest(CharacterType characterType)
{
	QString question;
	question.sprintf("Will you engage in combat with %s?", Character::getTypeString(characterType));
	int combat = ((QMessageBox::question(ui.centralWidget, "Engage Combat", question) == QMessageBox::Yes) ? 1 : 0);

	QString serializeCombat;
	serializeCombat.sprintf("CharacterCombatResp%s%d%sd%s%d", CLASSDELIM, combat, VARDELIM, (int)characterType, VARDELIM, (int)selectedCharacter);
	server->writeMessage(&serializeCombat);
}

void GameWindow::doTurn(QString &turnString)
{
	string *s = new string(turnString.toUtf8().constData());
	if (myTurn != 0)
	{
		delete myTurn;
		myTurn = 0;
	}
	myTurn = new RecordedTurn(s);
	delete s;

	ui.gamePhaseComboBox->clear();
	ui.gamePhaseComboBox->setEnabled(true);

	sunlightPhases = 0;

	map<PhaseType, int>* availablePhases = myTurn->getAvailablePhases();
	for (map<PhaseType, int>::iterator it = availablePhases->begin(); it != availablePhases->end(); ++it)
	{
		for (int i = 0; i < it->second; i++)
		{
			switch (it->first)
			{
			case MovePhase:
				ui.gamePhaseComboBox->addItem("Move");
				ui.gamePhaseComboBox->setItemIcon(ui.gamePhaseComboBox->count()-1, QIcon(":/images/actions/move.gif"));
				break;
			case BasicPhase:
				ui.gamePhaseComboBox->addItem("Basic");
				ui.gamePhaseComboBox->setItemIcon(ui.gamePhaseComboBox->count()-1, QIcon(":/images/phases/basic.gif"));
				break;
			case SunlightPhase:
				sunlightPhases++;
				break;
			case HidePhase:
				ui.gamePhaseComboBox->addItem("Hide");
				ui.gamePhaseComboBox->setItemIcon(ui.gamePhaseComboBox->count()-1, QIcon(":/images/actions/hide.gif"));
				break;
			default:
				break;
			}
		}
	}

	for (int i = Amazon; i <= Swordsman; i++)
	{
		Character* c = game->getPlayer((CharacterType)i);
		if (c != 0)
		{
			c->setBlock(false);
		}
	}

	destinationClearing = game->getPlayer(selectedCharacter)->getCurrentLocation();
	placeDestinationCounter();

	QString eventString;
	eventString.sprintf("Plot turn %d:", turnNumber);
	ui.gameEventFeedBrowser->append(eventString);
	caveCheck();
	ui.gameSubmitTurnButton->setEnabled(true);
}

void GameWindow::submitTurn()
{
	server->writeMessage(myTurn->serialize());
	disableActions();
	ui.gamePhaseComboBox->setDisabled(true);
	ui.gameSubmitTurnButton->setDisabled(true);
	QString eventString;
	eventString.sprintf("Turn %d submitted.", turnNumber);
	ui.gameEventFeedBrowser->append(eventString);
	turnNumber++;
}

void GameWindow::setCurrentPhaseType(const QString& phaseString)
{
	disableActions();
	if (phaseString == "Basic")
	{
		currentPhase = BasicPhase;
		enableActions();
	}
	else if (phaseString == "Sunlight")
	{
		currentPhase = SunlightPhase;
		enableActions();
	}
	else if (phaseString == "Move")
	{
		currentPhase = MovePhase;
		ui.gameMoveActionButton->setEnabled(true);
	}
	else if (phaseString == "Hide")
	{
		currentPhase = HidePhase;
		ui.gameHideActionButton->setEnabled(true);
	}
	else
	{
		qDebug() << "phase check failed";
	}
}

void GameWindow::caveCheck()
{
	int phasesToRemove = 0;

	if (destinationClearing->getClearingType() == CAVES)
	{
		sunlightPhases = 0;

		for (int i = 0; i < ui.gamePhaseComboBox->count(); i++)
		{
			if (ui.gamePhaseComboBox->itemText(i) == "Sunlight")
			{
				phasesToRemove++;
			}
		}
		ui.gameEventFeedBrowser->append(" - Sunlight phases lost in cave clearing.");
	}
	
	for (int i = 0; i < phasesToRemove; i++)
	{
		for (int j = 0; j < ui.gamePhaseComboBox->count(); j++)
		{
			if (ui.gamePhaseComboBox->itemText(j) == "Sunlight")
			{
				ui.gamePhaseComboBox->removeItem(j);
			}
		}
	}
}

int GameWindow::countMovingPhases()
{
	int movingPhases = 0;

	for (int i = 0; i < ui.gamePhaseComboBox->count(); i++)
	{
		if (isMovingPhase(i))
		{
			movingPhases++;
		}
	}

	return movingPhases;
}

bool GameWindow::isMovingPhase(int phaseIndex)
{
	return (ui.gamePhaseComboBox->itemText(phaseIndex) == "Basic" ||
			ui.gamePhaseComboBox->itemText(phaseIndex) == "Sunlight" ||
			ui.gamePhaseComboBox->itemText(phaseIndex) == "Move");
}

void GameWindow::payForMountainClimb()
{
	QString currentSelectedPhase = ui.gamePhaseComboBox->currentText();
	for (int i = 0; i < ui.gamePhaseComboBox->count(); i++)
	{
		if (ui.gamePhaseComboBox->currentIndex() != i && isMovingPhase(i))
		{
			QString eventString;
			eventString.sprintf(" - Extra %s phase used to pay for mountain climb.", 
				ui.gamePhaseComboBox->itemText(i));
			ui.gameEventFeedBrowser->append(eventString);
			ui.gamePhaseComboBox->removeItem(i);
			break;
		}
	}

	for (int i = 0; i < ui.gamePhaseComboBox->count(); i++)
	{
		if (ui.gamePhaseComboBox->itemText(i) == currentSelectedPhase)
		{
			ui.gamePhaseComboBox->setCurrentIndex(i);
			break;
		}
	}
}

void GameWindow::setupChit(QString& chitString) {
	//Strip the Chit identifier from the string
	int pos = chitString.indexOf(CLASSDELIM);
	chitString = chitString.right(chitString.size() - (pos + 2));

	//find the end of the chit name
	pos = chitString.indexOf("Tile");
	string name = string(chitString.left(pos).toUtf8().constData());

	//strip the Tile identifier from the string
	pos = chitString.indexOf(CLASSDELIM);
	chitString = chitString.right(chitString.size() - (pos + 2));
	string tName;

	Chit* chit = game->getBoard()->getChitByName(name);
	
	pos = chitString.indexOf(LISTDELIM);
	if (pos != -1)
	{
		tName = string(chitString.left(pos).toUtf8().constData());
		chitString = chitString.right(chitString.size() - (pos + 1));

		//add contents to lost chits
		vector<Chit*> *contents = new vector<Chit*>;
		string innerChit;
		while ((pos = chitString.indexOf(LISTDELIM)) != -1)
		{
			innerChit = string(chitString.left(pos).toUtf8().constData());
			chitString = chitString.right(chitString.size() - (pos + 1));
			innerChit = innerChit.substr(innerChit.find(CLASSDELIM) + 2);
			contents->push_back(game->getBoard()->getChitByName(innerChit));
		}
		innerChit = string(chitString.toUtf8().constData());
		innerChit = innerChit.substr(innerChit.find(CLASSDELIM) + 2);
		contents->push_back(game->getBoard()->getChitByName(innerChit));
		((Lost *) chit)->populateCity(contents);
	}
	else 
	{
		tName = string(chitString.toUtf8().constData());
	}

	//add chits to the correct tiles
	if (chit->getType() == CHIT_WARNING) {
		game->getBoard()->getTile(tName)->addWarningChit((Warning*)chit);
	} else {
		game->getBoard()->getTile(tName)->addSiteOrSoundChit(chit);
	}

}

void GameWindow::manageMonsters(QString& monsterString) {
	//Strip the Chit identifier from the string, string will be 123^TileName^5
	int pos = monsterString.indexOf(CLASSDELIM);
	monsterString = monsterString.right(monsterString.size() - (pos + 2));

	//get the monster ID, string will be TileName^5
	pos = monsterString.indexOf(VARDELIM);
	QString temp = monsterString.left(pos);
	monsterString = monsterString.right(monsterString.size() - (pos + 1));
	int monsterID = temp.toInt();

	Monster* myMonster = game->getBoard()->getSpawner()->getMonsterByID(monsterID);

	//get the tile name
	pos = monsterString.indexOf(VARDELIM);
	temp = monsterString.left(pos);

	//get the clearing id
	monsterString = monsterString.right(monsterString.size() - (pos + 1));
	int clearingID = monsterString.toInt();

	Clearing* myClearing = game->getBoard()->getTile(string(temp.toUtf8().constData()))->getClearing(clearingID);

	myMonster->move(myClearing);

	if (!monsterGraphicsItems->contains(myMonster->getID()))
	{
		addMonsterToGame(myMonster);
	}
	else
	{
		placeMonster(myMonster);
	}
}
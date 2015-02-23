#include "gameWindow.h"

#include "availableMovesDialog.h"

#include <QMessageBox>

#include <queue>
#include <unordered_set>

#include <Windows.h>

GameWindow::GameWindow(QObject* parent, Ui::MainWindowClass mainWindow)
	: QObject(parent), ui(mainWindow)
{
	gameStarted = false;
	characterImages = new QMap<CharacterType, QPixmap*>();
	loadCharacterImages();
	characterGraphicsItems = new QMap<CharacterType, QGraphicsPixmapItem*>();
	tileImages = new QMap<std::string, QPixmap*>();
	loadTileImages();
	tileGraphicsItems = new QMap<Tile*, TileGraphicsItem*>();
	ui.graphicsView->scale(0.5, 0.5);
	server = new ServerCommThread(this);
	selectedCharacter = NullCharacter;
	game = 0;
	selectedTile = 0;
	destinationClearing = 0;
	selectedAction = NoAction;
	myTurn = NULL;
}

GameWindow::~GameWindow()
{
	if (server != 0)
	{
		delete server;
		server = 0;
	}

	if (tileGraphicsItems != 0)
	{
		//qDeleteAll(*tileGraphicsItems);
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
}

void GameWindow::loadCharacterImages()
{
	characterImages->insert(Amazon, new QPixmap(":/images/characters/amazon.png"));
	characterImages->insert(BlackKnight, new QPixmap(":/images/characters/black_knight.png"));
	characterImages->insert(Captain, new QPixmap(":/images/characters/captain.png"));
	characterImages->insert(Dwarf, new QPixmap(":/images/characters/dwarf.png"));
	characterImages->insert(Elf, new QPixmap(":/images/characters/elf.png"));
	characterImages->insert(Swordsman, new QPixmap(":/images/characters/swordsman.png"));
}

void GameWindow::loadTileImages()
{
	tileImages->insert("Awful Valley", new QPixmap(":/images/tiles/awfulvalley1.gif"));
	tileImages->insert("Awful Valley Enchanted", new QPixmap(":/images/tiles/awfulvalley-e1.gif"));
	tileImages->insert("Bad Valley", new QPixmap(":/images/tiles/badvalley1.gif"));
	tileImages->insert("Bad Valley Echanted", new QPixmap(":/images/tiles/badvalley-e1.gif"));
	tileImages->insert("Border Land", new QPixmap(":/images/tiles/borderland1.gif"));
	tileImages->insert("Border Land Echanted", new QPixmap(":/images/tiles/borderland-e1.gif"));
	tileImages->insert("Cavern", new QPixmap(":/images/tiles/cavern1.gif"));
	tileImages->insert("Cavern Echanted", new QPixmap(":/images/tiles/cavern-e1.gif"));
	tileImages->insert("Caves", new QPixmap(":/images/tiles/caves1.gif"));
	tileImages->insert("Caves Echanted", new QPixmap(":/images/tiles/caves-e1.gif"));
	tileImages->insert("Cliff", new QPixmap(":/images/tiles/cliff1.gif"));
	tileImages->insert("Cliff Echanted", new QPixmap(":/images/tiles/cliff-e1.gif"));
	tileImages->insert("Crag", new QPixmap(":/images/tiles/crag1.gif"));
	tileImages->insert("Crag Echanted", new QPixmap(":/images/tiles/crag-e1.gif"));
	tileImages->insert("Curst Valley", new QPixmap(":/images/tiles/curstvalley1.gif"));
	tileImages->insert("Curst Valley Echanted", new QPixmap(":/images/tiles/curstvalley-e1.gif"));
	tileImages->insert("Dark Valley", new QPixmap(":/images/tiles/darkvalley1.gif"));
	tileImages->insert("Dark Valley Echanted", new QPixmap(":/images/tiles/darkvalley-e1.gif"));
	tileImages->insert("Deep Woods", new QPixmap(":/images/tiles/deepwoods1.gif"));
	tileImages->insert("Deep Woods Echanted", new QPixmap(":/images/tiles/deepwoods-e1.gif"));
	tileImages->insert("Evil Valley", new QPixmap(":/images/tiles/evilvalley1.gif"));
	tileImages->insert("Evil Valley Echanted", new QPixmap(":/images/tiles/evilvalley-e1.gif"));
	tileImages->insert("High Pass", new QPixmap(":/images/tiles/highpass1.gif"));
	tileImages->insert("High Pass Echanted", new QPixmap(":/images/tiles/highpass-e1.gif"));
	tileImages->insert("Ledges", new QPixmap(":/images/tiles/ledges1.gif"));
	tileImages->insert("Ledges Echanted", new QPixmap(":/images/tiles/ledges-e1.gif"));
	tileImages->insert("Linden Woods", new QPixmap(":/images/tiles/lindenwoods1.gif"));
	tileImages->insert("Linden Woods Echanted", new QPixmap(":/images/tiles/lindenwoods-e1.gif"));
	tileImages->insert("Maple Woods", new QPixmap(":/images/tiles/maplewoods1.gif"));
	tileImages->insert("Maple Woods Echanted", new QPixmap(":/images/tiles/maplewoods-e1.gif"));
	tileImages->insert("Mountain", new QPixmap(":/images/tiles/mountain1.gif"));
	tileImages->insert("Mountain Echanted", new QPixmap(":/images/tiles/mountain-e1.gif"));
	tileImages->insert("Nut Woods", new QPixmap(":/images/tiles/nutwoods1.gif"));
	tileImages->insert("Nut Woods Echanted", new QPixmap(":/images/tiles/nutwoods-e1.gif"));
	tileImages->insert("Oak Woods", new QPixmap(":/images/tiles/oakwoods1.gif"));
	tileImages->insert("Oak Woods Echanted", new QPixmap(":/images/tiles/oakwoods-e1.gif"));
	tileImages->insert("Pine Woods", new QPixmap(":/images/tiles/pinewoods1.gif"));
	tileImages->insert("Pine Woods Echanted", new QPixmap(":/images/tiles/pinewoods-e1.gif"));
	tileImages->insert("Ruins", new QPixmap(":/images/tiles/ruins1.gif"));
	tileImages->insert("Ruins Echanted", new QPixmap(":/images/tiles/ruins-e1.gif"));
}

errno_t GameWindow::initializeConnection(QString &hostIP)
{
	errno_t err = 0;

	ui.loadingMessageLabel->setText("--Connecting to server--");
	changeScreenState(ui.loadingWidget);
	
	game = new Game();

	game->setupGame(false);
	
	err = server->threadConnect(hostIP, GAMEPORT);
	if (err)
	{
		cleanup();
		return err;
	}

	return err;
}

void GameWindow::connectedToServer()
{
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

void GameWindow::addCharacterToGame(QString &newCharacter) {
	Character* character = new Character(new string(newCharacter.toUtf8().constData()));
	game->addPlayer(character);
	if (gameStarted)
	{
		updateCharacterInfoPane();
		updateTileInfoPane(selectedTile);
		updateCharacterLocation(character);
	}
}

errno_t GameWindow::initializeGame()
{
	errno_t err = 0;

	gameScene = new QGraphicsScene();
	
	tileLocations = new QMap<Tile*, QPointF>();

	drawTiles();
	
	for (int i = 0; i <= Swordsman; i++)
	{
		QPixmap pxmap = *(*characterImages)[(CharacterType)i];
		QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pxmap);
		item->setTransformOriginPoint(pxmap.width() / 2, pxmap.height() / 2);
		characterGraphicsItems->insert((CharacterType)i, item);
		item->setZValue(0.2);
		item->setVisible(false);
		Character* character = game->getPlayer((CharacterType)i);
		if (character != 0)
		{
			updateCharacterLocation(character);
		}
		gameScene->addItem(item);
	}
	
	ui.graphicsView->setScene(gameScene);
	changeScreenState(ui.gameWidget);

	return err;
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
	ui.gameSubmitTurnButton->setDisabled(true);
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
	/*
	for (vector<Equipment*>::iterator it = equipment->begin(); it != equipment->end(); ++it)
	{
		characterInfo.sprintf("  - %s", (*it)->
	}
	*/
}

void GameWindow::updateTileInfoPane(Tile* tile)
{
	QFont font = QFont("MS Serif", 26);
	font.setBold(true);
	font.setUnderline(true);
	ui.gameTileInformationBrowser->setCurrentFont(font);
	ui.gameTileInformationBrowser->setText(QString(tile->getName().c_str()));

	font.setPointSize(18);
	font.setUnderline(false);
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
			ui.gameTileInformationBrowser->append("Players:");
			font.setPointSize(12);
			font.setBold(true);
			ui.gameTileInformationBrowser->setCurrentFont(font);
			for (vector<Character*>::iterator chr  = chrs.begin(); chr != chrs.end(); ++chr)
			{
				QString charString;
				charString.sprintf("  - %s", Character::getTypeString((*chr)->getType()));
				ui.gameTileInformationBrowser->append(charString);
			}
			ui.gameTileInformationBrowser->append("");
		}
	}
}

void GameWindow::updateCharacterLocation(Character* character)
{
	Clearing* currClearing = character->getCurrentLocation();
	if (currClearing != 0)
	{
		Tile* currTile = currClearing->getTile();
		if (currTile != 0)
		{
			QGraphicsPixmapItem* charItem = ((*characterGraphicsItems)[character->getType()]);
			TileGraphicsItem* tileItem = ((*tileGraphicsItems)[currTile]);
			charItem->setX((*tileLocations)[currTile].x() + (tileItem->width() / 2) - (charItem->pixmap().width() / 2));
			charItem->setY((*tileLocations)[currTile].y() + (tileItem->height() / 2) - (charItem->pixmap().height() / 2));
			charItem->setVisible(true);
		}
	}
}

void GameWindow::selectAction(ActionType action)
{
	selectedAction = action;
	
	switch (action)
	{
	case NoAction:
		break;
	case MoveAction:
		moveAction();
		break;
	case SearchAction:
	case TradeAction:
	case HideAction:
	default:
		myTurn->addAction(new Action(action, destinationClearing), currentPhase);
		break;
	}

	if (ui.gamePhaseComboBox->count() <= 0)
	{
		ui.gameSubmitTurnButton->setEnabled(true);
	}
}

void GameWindow::moveAction()
{
	vector<Path*> availablePaths = *(destinationClearing->getPaths());
	QList<Clearing*> adjacentClearings;
	for (vector<Path*>::iterator it = availablePaths.begin(); it != availablePaths.end(); ++it)
	{
		Path* p = *it;
		Clearing* end = p->getEnd(destinationClearing);
		Character* character = game->getPlayer(selectedCharacter);
		if (end != NULL && (!p->isHidden() || character->isDiscovered(p)))
		{
			adjacentClearings.append(end);
		}
	}

	AvailableMovesDialog* dlg = new AvailableMovesDialog(ui.centralWidget);
	for (Clearing* c : adjacentClearings)
	{
		QString option;
		dlg->addOption(option.sprintf("%s: Clearing %d", c->getTile()->getName().c_str(), c->getClearingNum()));
	}
	int destIndex = dlg->exec();
	if (destIndex != -1)
	{
		destinationClearing = adjacentClearings.at(destIndex);
		myTurn->addAction(new Action(MoveAction, destinationClearing), currentPhase);
		ui.gamePhaseComboBox->removeItem(ui.gamePhaseComboBox->currentIndex());
	}
	delete dlg;

	selectAction(NoAction);
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
		}
		updateCharacterInfoPane();
		updateTileInfoPane(selectedTile);
		updateCharacterLocation(game->getPlayer((CharacterType)character));
	}
}

void GameWindow::setCharacterHidden(CharacterType character, bool hidden)
{
	if (hidden)
	{
		game->hideRequest(game->getPlayer(character));
	}
}

void GameWindow::searchTypeRequest()
{
	int searchType = QMessageBox::question(ui.centralWidget, "Search Type", "How would you like to search?", "Peer", "Locate", "Loot");
	
	QString serializedSearchType;
	serializedSearchType.sprintf("SearchTypeResp%s%d", CLASSDELIM, searchType);
	server->writeMessage(&serializedSearchType);
}

void GameWindow::search(CharacterType character, SearchType searchType)
{
	Character* c = game->getPlayer(character);
	game->searchRequest(c, searchType, c->getCurrentLocation());
}

void GameWindow::doTurn(QString &turnString)
{
	string *s = new string(turnString.toUtf8().constData());
	if (myTurn != NULL)
	{
		delete myTurn;
		myTurn = 0;
	}
	myTurn = new RecordedTurn(s);
	delete s;

	ui.gamePhaseComboBox->clear();
	ui.gamePhaseComboBox->setEnabled(true);

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
				ui.gamePhaseComboBox->addItem("Sunlight");
				ui.gamePhaseComboBox->setItemIcon(ui.gamePhaseComboBox->count()-1, QIcon(":/images/phases/sunshine.gif"));
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
}

void GameWindow::submitTurn()
{
	server->writeMessage(myTurn->serialize());
	ui.gamePhaseComboBox->setDisabled(true);
	ui.gameSubmitTurnButton->setDisabled(true);
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
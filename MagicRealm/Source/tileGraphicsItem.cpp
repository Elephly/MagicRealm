#include "tileGraphicsItem.h"

TileGraphicsItem::TileGraphicsItem(QPixmap pixmap, Tile* tile, GameWindow* container)
	: QGraphicsPixmapItem(pixmap)
{
	setPixmap(pixmap);
	setZValue(0);
	setAcceptHoverEvents(true);

	myWidth = pixmap.width();
	myHeight = pixmap.height();

	myTile = tile;
	myContainer = container;
}

TileGraphicsItem::~TileGraphicsItem()
{

}

void TileGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if(isUnderMouse())
	{
		setZValue(0);
		setScale(1);
		myContainer->selectTile(myTile);
	}
	QGraphicsPixmapItem::mousePressEvent(event);
}

void TileGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if(isUnderMouse())
	{
		setZValue(0.1);
		setScale(1.05);
	}
	QGraphicsPixmapItem::mouseReleaseEvent(event);
}

void TileGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
	setZValue(0.1);
	setScale(1.05);
	QGraphicsPixmapItem::hoverEnterEvent(event);
}

void TileGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
	setZValue(0);
	setScale(1);
	QGraphicsPixmapItem::hoverLeaveEvent(event);
}

int TileGraphicsItem::width()
{
	return myWidth;
}

int TileGraphicsItem::height()
{
	return myHeight;
}
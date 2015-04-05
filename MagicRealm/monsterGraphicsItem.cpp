#include "monsterGraphicsItem.h"


MonsterGraphicsItem::MonsterGraphicsItem(QPixmap pixmap, Monster* monster, GameWindow* container)
	: QGraphicsPixmapItem(pixmap)
{
	setPixmap(pixmap);
	setZValue(0);
	setAcceptHoverEvents(true);

	myWidth = pixmap.width();
	myHeight = pixmap.height();

	myMonster = monster;
	myContainer = container;
}


MonsterGraphicsItem::~MonsterGraphicsItem()
{
}

void MonsterGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if(isUnderMouse())
	{
		setZValue(0);
		setScale(1);
		myContainer->selectMonster(myMonster);
	}
	QGraphicsPixmapItem::mousePressEvent(event);
}

void MonsterGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if(isUnderMouse())
	{
		setZValue(0.1);
		setScale(1.05);
	}
	QGraphicsPixmapItem::mouseReleaseEvent(event);
}

void MonsterGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
	setZValue(0.1);
	setScale(1.05);
	QGraphicsPixmapItem::hoverEnterEvent(event);
}

void MonsterGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
	setZValue(0);
	setScale(1);
	QGraphicsPixmapItem::hoverLeaveEvent(event);
}

int MonsterGraphicsItem::width()
{
	return myWidth;
}

int MonsterGraphicsItem::height()
{
	return myHeight;
}
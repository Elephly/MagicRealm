#ifndef TILEGRAPHICSITEM_H
#define TILEGRAPHICSITEM_H

#include <QGraphicsItem>
#include "gameWindow.h"
#include "tile.h"

class TileGraphicsItem : public QGraphicsPixmapItem
{
public:
	TileGraphicsItem(QPixmap pixmap, Tile* tile, GameWindow* container);
	~TileGraphicsItem();
	int width();
	int height();

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *evernt);

private:
	Tile* myTile;
	GameWindow* myContainer;
	int myWidth;
	int myHeight;
};

#endif // TILEGRAPHICSITEM_H
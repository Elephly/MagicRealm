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

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *evernt);

private:
	Tile* myTile;
	GameWindow* myContainer;
};

#endif //TILEGRAPHICSITEM_H
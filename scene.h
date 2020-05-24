#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include "game.h"

class Scene : public QGraphicsScene
{
public:
    Scene(const QRectF &sceneRect, int gridSize, QObject *parent = 0);
    int getGridSize() const;
    void setGame(Game *game);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);

private:
    Game *game;
    int gridSize;
};

#endif // SCENE_H

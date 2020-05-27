#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class Grid;
class Scene : public QGraphicsScene
{
public:
    Scene(const QRectF &sceneRect, QObject *parent = 0);

    Grid* activeGrid();
    void setActiveGrid(Grid *grid);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);

private:
    Grid *gameActiveGrid;

    static QString defaultText;
};

#endif // SCENE_H

#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class Scene : public QGraphicsScene
{
public:
    Scene(const QRectF &sceneRect, int gridSize, QObject *parent = 0);
    int getGridSize() const;

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);

private:
    int gridSize;
};

#endif // SCENE_H

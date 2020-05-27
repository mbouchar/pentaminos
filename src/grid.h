#ifndef GRID_H
#define GRID_H

#include <QObject>
#include <QPainter>
#include <QSize>

#include "scene.h"

class Grid : public QObject
{
public:
    Grid(QSize size, int gridPixelSize, Scene *scene);

    QSize size();
    void setPos(QPoint pos);
    QPoint pos();
    void draw(QPainter *painter, QPen pen);

    bool isComplete();

    static Grid* grid4(int gridPixelSize, Scene *scene);
    static Grid* grid5(int gridPixelSize, Scene *scene);
    static Grid* grid12(int gridPixelSize, Scene *scene);

private:
    QSize gridSize;
    int gridPixelSize;
    QPoint position;

    Scene *scene;
};

#endif // GRID_H

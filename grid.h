#ifndef GRID_H
#define GRID_H

#include <QObject>
#include <QPainter>
#include <QSize>

class Grid : public QObject
{
public:
    Grid(QSize size);

    QSize size();
    void setPos(QPoint pos);
    QPoint pos();
    void draw(QPainter *painter, QPen pen);

    static Grid* grid4();
    static Grid* grid5();
    static Grid* grid12();

private:
    QSize gridSize;
    QPoint position;
};

#endif // GRID_H

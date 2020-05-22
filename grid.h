#ifndef GRID_H
#define GRID_H

#include <QGraphicsItemGroup>
#include <QSize>


class Grid : public QGraphicsItemGroup
{
public:
    Grid(QSize size, QString title);

    static Grid* grid4();
    static Grid* grid5();
    static Grid* grid12();
};

#endif // GRID_H

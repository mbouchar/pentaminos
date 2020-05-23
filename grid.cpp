#include "grid.h"

#include <QFont>
#include <QPen>

Grid::Grid(QSize size)
{
    QPen pen(Qt::gray);

    QGraphicsRectItem *item = new QGraphicsRectItem(0, 0, size.width() * 10, size.height() * 10);
    item->setPen(pen);

    this->addToGroup(item);
    // Draw horizontal lines
    for (int i = 1; i < size.height(); i++) {
        QGraphicsLineItem *line = new QGraphicsLineItem(0, i * 10, size.width() * 10, i * 10);
        line->setPen(pen);
        this->addToGroup(line);
    }
    // Draw vertical lines
    for (int i = 1; i < size.width(); i++) {
        QGraphicsLineItem *line = new QGraphicsLineItem(i * 10, 0, i * 10, size.height() * 10);
        line->setPen(pen);
        this->addToGroup(line);
    }
}

Grid* Grid::grid4()
{
    return new Grid(QSize(4, 5));
}

Grid* Grid::grid5()
{
    return new Grid(QSize(5, 5));
}

Grid* Grid::grid12()
{
    return new Grid(QSize(12, 5));
}

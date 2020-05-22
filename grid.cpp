#include "grid.h"

#include <QFont>

Grid::Grid(QSize size, QString title)
{
    QGraphicsRectItem *item = new QGraphicsRectItem(0, 0, size.width() * 10, size.height() * 10);
    this->addToGroup(item);
    // Draw horizontal lines
    for (int i = 1; i < size.height(); i++) {
        QGraphicsLineItem *line = new QGraphicsLineItem(0, i * 10, size.width() * 10, i * 10);
        this->addToGroup(line);
    }
    // Draw vertical lines
    for (int i = 1; i < size.width(); i++) {
        QGraphicsLineItem *line = new QGraphicsLineItem(i * 10, 0, i * 10, size.height() * 10);
        this->addToGroup(line);
    }

    QGraphicsTextItem *titleItem = new QGraphicsTextItem(title);
    titleItem->setTextWidth(size.width() * 10 + 15);
    QFont font;
    font.setPointSize(5);
    titleItem->setFont(font);
    titleItem->setPos(-5, size.height() * 10);
    this->addToGroup(titleItem);
}

Grid* Grid::grid4()
{
    return new Grid(QSize(4, 5), "Pentanimos 4");
}

Grid* Grid::grid5()
{
    return new Grid(QSize(5, 5), "Pentanimos 5");
}

Grid* Grid::grid12()
{
    return new Grid(QSize(12, 5), "Pentanimos 12");
}

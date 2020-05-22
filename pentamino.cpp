#include "pentamino.h"

#include <QFont>
#include <QBrush>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>

Pentamino::Pentamino()
{
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    this->setFlag(QGraphicsItem::ItemIsMovable, true);
    this->setFlag(QGraphicsItem::ItemIsFocusable, true);
    this->setFlag(QGraphicsItem::ItemClipsToShape, true);
    this->setBoundingRegionGranularity(1);

    this->currentAngle = 0;
}

void Pentamino::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    Q_UNUSED(event)

    this->currentAngle += 90;
    if (this->currentAngle >= 360) {
        this->currentAngle = 0;
    }

    QTransform transform;
    this->setTransform(transform.rotate(this->currentAngle, Qt::ZAxis));
}

void Pentamino::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // Left empty to remove the border when selecting a pentamino
}

void Pentamino::addRectItem(QRect rect, QBrush brush)
{
    QGraphicsRectItem *rectItem = new QGraphicsRectItem(rect);
    rectItem->setBrush(brush);
    this->addToGroup(rectItem);
}

void Pentamino::addTitle(QString title, QColor color)
{
    QGraphicsTextItem *titleItem = new QGraphicsTextItem(title);
    //titleItem->setTextWidth(size.width() * 10 + 15);
    QFont font;
    font.setPointSize(5);
    titleItem->setFont(font);
    titleItem->setDefaultTextColor(color);
    if (title.length() == 1)
        titleItem->setPos(-6, -10);
    else
        titleItem->setPos(-8.5, -10);
    this->addToGroup(titleItem);
}

Pentamino* Pentamino::pentamino1()
{
    QBrush brush(QColor(255, 192, 0, 255), Qt::SolidPattern);

    /* x
     * x
     * x
     * x
     * x
     */
    Pentamino *pentamino = new Pentamino();
    pentamino->addRectItem(QRect(-5, -25, 10, 10), brush);
    pentamino->addRectItem(QRect(-5, -15, 10, 10), brush);
    pentamino->addRectItem(QRect(-5, -5, 10, 10), brush);
    pentamino->addRectItem(QRect(-5, 5, 10, 10), brush);
    pentamino->addRectItem(QRect(-5, 15, 10, 10), brush);
    pentamino->addTitle("1");

    return pentamino;
}

Pentamino* Pentamino::pentamino2()
{
    QBrush brush(QColor(237, 125, 49, 255), Qt::SolidPattern);

    /* x
     * x
     * x
     * xx
     */
    Pentamino *pentamino = new Pentamino();
    pentamino->addRectItem(QRect(-5, -25, 10, 10), brush);
    pentamino->addRectItem(QRect(-5, -15, 10, 10), brush);
    pentamino->addRectItem(QRect(-5, -5, 10, 10), brush);
    pentamino->addRectItem(QRect(-5, 5, 10, 10), brush);
    // Right of the last one
    pentamino->addRectItem(QRect(5, 5, 10, 10), brush);
    pentamino->addTitle("2");

    return pentamino;
}

Pentamino* Pentamino::pentamino3()
{
    QBrush brush(QColor(192, 0, 0, 255), Qt::SolidPattern);

    /*  x
     *  x
     * xx
     *  x
     */
    Pentamino *pentamino = new Pentamino();
    pentamino->addRectItem(QRect(-5, -25, 10, 10), brush);
    pentamino->addRectItem(QRect(-5, -15, 10, 10), brush);
    pentamino->addRectItem(QRect(-5, -5, 10, 10), brush);
    pentamino->addRectItem(QRect(-5, 5, 10, 10), brush);
    // Left of the third one
    pentamino->addRectItem(QRect(-15, -5, 10, 10), brush);
    pentamino->addTitle("3", Qt::white);

    return pentamino;
}

Pentamino* Pentamino::pentamino4()
{
    QBrush brush(QColor(112, 48, 160, 255), Qt::SolidPattern);

    /*  x
     *  x
     * xx
     * x
     */
    Pentamino *pentamino = new Pentamino();
    pentamino->addRectItem(QRect(-5, -25, 10, 10), brush);
    pentamino->addRectItem(QRect(-5, -15, 10, 10), brush);
    pentamino->addRectItem(QRect(-5, -5, 10, 10), brush);
    // Left of the third one
    pentamino->addRectItem(QRect(-15, -5, 10, 10), brush);
    // Below the last one
    pentamino->addRectItem(QRect(-15, 5, 10, 10), brush);
    pentamino->addTitle("4", Qt::white);

    return pentamino;
}

Pentamino* Pentamino::pentamino5()
{
    QBrush brush(QColor(0, 32, 96, 255), Qt::SolidPattern);

    /*   x
     *   x
     * xxx
     */
    Pentamino *pentamino = new Pentamino();
    pentamino->addRectItem(QRect(-5, -25, 10, 10), brush);
    pentamino->addRectItem(QRect(-5, -15, 10, 10), brush);
    pentamino->addRectItem(QRect(-5, -5, 10, 10), brush);
    // Left of the last one
    pentamino->addRectItem(QRect(-15, -5, 10, 10), brush);
    // Left of the last one
    pentamino->addRectItem(QRect(-25, -5, 10, 10), brush);
    pentamino->addTitle("5", Qt::white);

    return pentamino;
}

Pentamino* Pentamino::pentamino6()
{
    QBrush brush(QColor(255, 0, 255, 255), Qt::SolidPattern);

    /* xx
     * xx
     * x
     */
    Pentamino *pentamino = new Pentamino();
    pentamino->addRectItem(QRect(-5, -15, 10, 10), brush);
    pentamino->addRectItem(QRect(-5, -5, 10, 10), brush);
    pentamino->addRectItem(QRect(-5, 5, 10, 10), brush);
    // Right of the first one
    pentamino->addRectItem(QRect(5, -15, 10, 10), brush);
    // Below the last one
    pentamino->addRectItem(QRect(5, -5, 10, 10), brush);
    pentamino->addTitle("6");

    return pentamino;
}

Pentamino* Pentamino::pentamino7()
{
    QBrush brush(QColor(255, 255, 153, 255), Qt::SolidPattern);

    /* xx
     *  x
     * xx
     */
    Pentamino *pentamino = new Pentamino();
    pentamino->addRectItem(QRect(-5, -15, 10, 10), brush);
    pentamino->addRectItem(QRect(-5, -5, 10, 10), brush);
    pentamino->addRectItem(QRect(-5, 5, 10, 10), brush);
    // Left of the first one
    pentamino->addRectItem(QRect(-15, -15, 10, 10), brush);
    // Left of the third one
    pentamino->addRectItem(QRect(-15, 5, 10, 10), brush);
    pentamino->addTitle("7");

    return pentamino;
}

Pentamino* Pentamino::pentamino8()
{
    QBrush brush(QColor(0, 176, 240, 255), Qt::SolidPattern);

    /*  xx
     *  x
     * xx
     */
    Pentamino *pentamino = new Pentamino();
    pentamino->addRectItem(QRect(-5, -15, 10, 10), brush);
    pentamino->addRectItem(QRect(-5, -5, 10, 10), brush);
    pentamino->addRectItem(QRect(-5, 5, 10, 10), brush);
    // Right of the first one
    pentamino->addRectItem(QRect(5, -15, 10, 10), brush);
    // Left of the third one
    pentamino->addRectItem(QRect(-15, 5, 10, 10), brush);
    pentamino->addTitle("8");

    return pentamino;
}

Pentamino* Pentamino::pentamino9()
{
    QBrush brush(QColor(192, 191, 191, 255), Qt::SolidPattern);

    /*  x
     * xxx
     * x
     */
    Pentamino *pentamino = new Pentamino();
    pentamino->addRectItem(QRect(-5, -15, 10, 10), brush);
    pentamino->addRectItem(QRect(-5, -5, 10, 10), brush);
    // Right of the second one
    pentamino->addRectItem(QRect(5, -5, 10, 10), brush);
    // Left of the second one
    pentamino->addRectItem(QRect(-15, -5, 10, 10), brush);
    // Below the last one
    pentamino->addRectItem(QRect(-15, 5, 10, 10), brush);
    pentamino->addTitle("9");

    return pentamino;
}

Pentamino* Pentamino::pentamino10()
{
    QBrush brush(QColor(255, 255, 255, 255), Qt::SolidPattern);

    /* xxx
     *  x
     *  x
     */
    Pentamino *pentamino = new Pentamino();
    pentamino->addRectItem(QRect(-5, -15, 10, 10), brush);
    pentamino->addRectItem(QRect(-5, -5, 10, 10), brush);
    pentamino->addRectItem(QRect(-5, 5, 10, 10), brush);
    // Left of the first one
    pentamino->addRectItem(QRect(-15, -15, 10, 10), brush);
    // Right of the first one
    pentamino->addRectItem(QRect(5, -15, 10, 10), brush);
    pentamino->addTitle("10");

    return pentamino;
}

Pentamino* Pentamino::pentamino11()
{
    QBrush brush(QColor(146, 208, 80, 255), Qt::SolidPattern);

    /*   x
     *  xx
     * xx
     */
    Pentamino *pentamino = new Pentamino();
    pentamino->addRectItem(QRect(5, -15, 10, 10), brush);
    pentamino->addRectItem(QRect(5, -5, 10, 10), brush);
    // Left of the second one
    pentamino->addRectItem(QRect(-5, -5, 10, 10), brush);
    // Below the last one
    pentamino->addRectItem(QRect(-5, 5, 10, 10), brush);
    // Left of the last one
    pentamino->addRectItem(QRect(-15, 5, 10, 10), brush);
    pentamino->addTitle("11");

    return pentamino;
}

Pentamino* Pentamino::pentamino12()
{
    QBrush brush(QColor(255, 0, 0, 255), Qt::SolidPattern);

    /*  x
     * xxx
     *  x
     */
    Pentamino *pentamino = new Pentamino();
    pentamino->addRectItem(QRect(-5, -15, 10, 10), brush);
    pentamino->addRectItem(QRect(-5, -5, 10, 10), brush);
    pentamino->addRectItem(QRect(-5, 5, 10, 10), brush);
    // Left of the second one
    pentamino->addRectItem(QRect(-15, -5, 10, 10), brush);
    // Right of the second one
    pentamino->addRectItem(QRect(5, -5, 10, 10), brush);
    pentamino->addTitle("12");

    return pentamino;
}

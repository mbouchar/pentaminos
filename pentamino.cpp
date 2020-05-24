#include "pentamino.h"

#include <QFont>
#include <QBrush>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTextItem>

Qt::BrushStyle Pentamino::collisionBrushStyle = Qt::DiagCrossPattern;
Qt::BrushStyle Pentamino::normalBrushStyle = Qt::SolidPattern;

Pentamino::Pentamino()
{
    // Enable selection of the item group
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    this->setFlag(QGraphicsItem::ItemIsMovable, true);
    this->setFlag(QGraphicsItem::ItemIsFocusable, true);

    // What is drawed outside of the shape will be hidden
    //this->setFlag(QGraphicsItem::ItemClipsToShape, true);

    // Enable sending position changed events
    this->setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);

    this->currentAngle = 0;
    this->currentBrush = nullptr;
    this->title = "";
    this->titleColor = Qt::black;
}

int Pentamino::type() const
{
    return Type;
}

QRectF Pentamino::boundingRect() const
{
    // Invalidate the complete path
    return this->path.boundingRect();
}

QPainterPath Pentamino::shape() const
{
    // For collision purposes, use the shape that doesn't collide on edges
    return this->shapePath;
}

void Pentamino::setBrushColor(QColor color)
{
    this->normalBrush = QBrush(color, this->normalBrushStyle);
    this->collisionBrush = QBrush(color, this->collisionBrushStyle);
    if (this->currentBrush == nullptr) {
        this->currentBrush = &this->normalBrush;
    }
}

void Pentamino::reset()
{
    this->currentAngle = 0;
    this->setRotation(this->currentAngle);
    this->setCollision(false);
}

void Pentamino::setCollision(bool collided)
{
    if (collided) {
        if (this->currentBrush != &this->collisionBrush) {
            this->currentBrush = &this->collisionBrush;
            this->update(this->boundingRect());
        }
    } else {
        if (this->currentBrush != &this->normalBrush) {
            this->currentBrush = &this->normalBrush;
            this->update(this->boundingRect());
        }
    }
}

void Pentamino::focusInEvent(QFocusEvent *event)
{
    Q_UNUSED(event)

    this->setCollision(false);
    this->setZValue(1);
}

void Pentamino::focusOutEvent(QFocusEvent *event)
{
    Q_UNUSED(event)

    if (this->collidingItems().length() != 0) {
        this->setCollision(true);
    }
    this->setZValue(0);
}

void Pentamino::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    Q_UNUSED(event)

    this->currentAngle += 90;
    if (this->currentAngle >= 360) {
        this->currentAngle = 0;
    }

    this->setRotation(this->currentAngle);
}

void Pentamino::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(*this->currentBrush);
    painter->drawPath(this->path);

    if (!this->title.isEmpty()) {
        QFont font = painter->font();
        font.setPointSize(5);
        painter->setFont(font);
        painter->setPen(this->titleColor);
        painter->drawText(QRect(-5, -5, 10, 10), Qt::AlignCenter, this->title);
    }
}

void Pentamino::setPos(const QPointF &pos)
{
    QGraphicsItem::setPos(pos);

}

QVariant Pentamino::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
        // value is the new position.
        QPointF newPos = value.toPointF();

        // Check if the pentamino will be out of bounds
        QRectF rect = this->scene()->sceneRect();
        if (!rect.contains(newPos)) {
            // Keep the item inside the scene rect.
            newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
            newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
        }

        // Snap to grid
        int gridSize = 10;//customScene->getGridSize();
        qreal xV = qRound(newPos.x() / gridSize) * gridSize;
        qreal yV = qRound(newPos.y() / gridSize) * gridSize;

        return QPointF(xV, yV);
    } else {
        if (change == ItemPositionHasChanged || change == ItemRotationHasChanged || change == ItemTransformHasChanged) {
            emit pentaminoMoved();
        }

        return QGraphicsItem::itemChange(change, value);
    }
}

void Pentamino::addRectItem(QRect rect)
{
    // Path for drawing
    this->path.addRect(rect);
    // Path for collision detection
    this->shapePath.addRect(rect.x() + 1, rect.y() + 1, rect.width() - 2, rect.height() - 2);
}

void Pentamino::addTitle(QString title, QColor color)
{
    this->title = title;
    this->titleColor = color;
}

Pentamino* Pentamino::pentamino1()
{
    /* x
     * x
     * x
     * x
     * x
     */
    Pentamino *pentamino = new Pentamino();
    pentamino->setBrushColor(QColor(255, 192, 0, 255));
    pentamino->addRectItem(QRect(-5, -25, 10, 10));
    pentamino->addRectItem(QRect(-5, -15, 10, 10));
    pentamino->addRectItem(QRect(-5, -5, 10, 10));
    pentamino->addRectItem(QRect(-5, 5, 10, 10));
    pentamino->addRectItem(QRect(-5, 15, 10, 10));
    pentamino->addTitle("1");

    return pentamino;
}

Pentamino* Pentamino::pentamino2()
{
    /* x
     * x
     * x
     * xx
     */
    Pentamino *pentamino = new Pentamino();
    pentamino->setBrushColor(QColor(237, 125, 49, 255));
    pentamino->addRectItem(QRect(-5, -25, 10, 10));
    pentamino->addRectItem(QRect(-5, -15, 10, 10));
    pentamino->addRectItem(QRect(-5, -5, 10, 10));
    pentamino->addRectItem(QRect(-5, 5, 10, 10));
    // Right of the last one
    pentamino->addRectItem(QRect(5, 5, 10, 10));
    pentamino->addTitle("2");

    return pentamino;
}

Pentamino* Pentamino::pentamino3()
{
    /*  x
     *  x
     * xx
     *  x
     */
    Pentamino *pentamino = new Pentamino();
    pentamino->setBrushColor(QColor(192, 0, 0, 255));
    pentamino->addRectItem(QRect(-5, -25, 10, 10));
    pentamino->addRectItem(QRect(-5, -15, 10, 10));
    pentamino->addRectItem(QRect(-5, -5, 10, 10));
    pentamino->addRectItem(QRect(-5, 5, 10, 10));
    // Left of the third one
    pentamino->addRectItem(QRect(-15, -5, 10, 10));
    pentamino->addTitle("3", Qt::white);

    return pentamino;
}

Pentamino* Pentamino::pentamino4()
{
    /*  x
     *  x
     * xx
     * x
     */
    Pentamino *pentamino = new Pentamino();
    pentamino->setBrushColor(QColor(112, 48, 160, 255));
    pentamino->addRectItem(QRect(-5, -25, 10, 10));
    pentamino->addRectItem(QRect(-5, -15, 10, 10));
    pentamino->addRectItem(QRect(-5, -5, 10, 10));
    // Left of the third one
    pentamino->addRectItem(QRect(-15, -5, 10, 10));
    // Below the last one
    pentamino->addRectItem(QRect(-15, 5, 10, 10));
    pentamino->addTitle("4", Qt::white);

    return pentamino;
}

Pentamino* Pentamino::pentamino5()
{
    /*   x
     *   x
     * xxx
     */
    Pentamino *pentamino = new Pentamino();
    pentamino->setBrushColor(QColor(0, 32, 96, 255));
    pentamino->addRectItem(QRect(-5, -25, 10, 10));
    pentamino->addRectItem(QRect(-5, -15, 10, 10));
    pentamino->addRectItem(QRect(-5, -5, 10, 10));
    // Left of the last one
    pentamino->addRectItem(QRect(-15, -5, 10, 10));
    // Left of the last one
    pentamino->addRectItem(QRect(-25, -5, 10, 10));
    pentamino->addTitle("5", Qt::white);

    return pentamino;
}

Pentamino* Pentamino::pentamino6()
{
    /* xx
     * xx
     * x
     */
    Pentamino *pentamino = new Pentamino();
    pentamino->setBrushColor(QColor(255, 0, 255, 255));
    pentamino->addRectItem(QRect(-5, -15, 10, 10));
    pentamino->addRectItem(QRect(-5, -5, 10, 10));
    pentamino->addRectItem(QRect(-5, 5, 10, 10));
    // Right of the first one
    pentamino->addRectItem(QRect(5, -15, 10, 10));
    // Below the last one
    pentamino->addRectItem(QRect(5, -5, 10, 10));
    pentamino->addTitle("6");

    return pentamino;
}

Pentamino* Pentamino::pentamino7()
{
    /* xx
     *  x
     * xx
     */
    Pentamino *pentamino = new Pentamino();
    pentamino->setBrushColor(QColor(255, 255, 153, 255));
    pentamino->addRectItem(QRect(-5, -15, 10, 10));
    pentamino->addRectItem(QRect(-5, -5, 10, 10));
    pentamino->addRectItem(QRect(-5, 5, 10, 10));
    // Left of the first one
    pentamino->addRectItem(QRect(-15, -15, 10, 10));
    // Left of the third one
    pentamino->addRectItem(QRect(-15, 5, 10, 10));
    pentamino->addTitle("7");

    return pentamino;
}

Pentamino* Pentamino::pentamino8()
{
    /*  xx
     *  x
     * xx
     */
    Pentamino *pentamino = new Pentamino();
    pentamino->setBrushColor(QColor(0, 176, 240, 255));
    pentamino->addRectItem(QRect(-5, -15, 10, 10));
    pentamino->addRectItem(QRect(-5, -5, 10, 10));
    pentamino->addRectItem(QRect(-5, 5, 10, 10));
    // Right of the first one
    pentamino->addRectItem(QRect(5, -15, 10, 10));
    // Left of the third one
    pentamino->addRectItem(QRect(-15, 5, 10, 10));
    pentamino->addTitle("8");

    return pentamino;
}

Pentamino* Pentamino::pentamino9()
{
    /*  x
     * xxx
     * x
     */
    Pentamino *pentamino = new Pentamino();
    pentamino->setBrushColor(QColor(192, 191, 191, 255));
    pentamino->addRectItem(QRect(-5, -15, 10, 10));
    pentamino->addRectItem(QRect(-5, -5, 10, 10));
    // Right of the second one
    pentamino->addRectItem(QRect(5, -5, 10, 10));
    // Left of the second one
    pentamino->addRectItem(QRect(-15, -5, 10, 10));
    // Below the last one
    pentamino->addRectItem(QRect(-15, 5, 10, 10));
    pentamino->addTitle("9");

    return pentamino;
}

Pentamino* Pentamino::pentamino10()
{
    /* xxx
     *  x
     *  x
     */
    Pentamino *pentamino = new Pentamino();
    pentamino->setBrushColor(QColor(255, 255, 255, 255));
    pentamino->addRectItem(QRect(-5, -15, 10, 10));
    pentamino->addRectItem(QRect(-5, -5, 10, 10));
    pentamino->addRectItem(QRect(-5, 5, 10, 10));
    // Left of the first one
    pentamino->addRectItem(QRect(-15, -15, 10, 10));
    // Right of the first one
    pentamino->addRectItem(QRect(5, -15, 10, 10));
    pentamino->addTitle("10");

    return pentamino;
}

Pentamino* Pentamino::pentamino11()
{
    /*   x
     *  xx
     * xx
     */
    Pentamino *pentamino = new Pentamino();
    pentamino->setBrushColor(QColor(146, 208, 80, 255));
    pentamino->addRectItem(QRect(5, -15, 10, 10));
    pentamino->addRectItem(QRect(5, -5, 10, 10));
    // Left of the second one
    pentamino->addRectItem(QRect(-5, -5, 10, 10));
    // Below the last one
    pentamino->addRectItem(QRect(-5, 5, 10, 10));
    // Left of the last one
    pentamino->addRectItem(QRect(-15, 5, 10, 10));
    pentamino->addTitle("11");

    return pentamino;
}

Pentamino* Pentamino::pentamino12()
{
    /*  x
     * xxx
     *  x
     */
    Pentamino *pentamino = new Pentamino();
    pentamino->setBrushColor(QColor(255, 0, 0, 255));
    pentamino->addRectItem(QRect(-5, -15, 10, 10));
    pentamino->addRectItem(QRect(-5, -5, 10, 10));
    pentamino->addRectItem(QRect(-5, 5, 10, 10));
    // Left of the second one
    pentamino->addRectItem(QRect(-15, -5, 10, 10));
    // Right of the second one
    pentamino->addRectItem(QRect(5, -5, 10, 10));
    pentamino->addTitle("12");

    return pentamino;
}

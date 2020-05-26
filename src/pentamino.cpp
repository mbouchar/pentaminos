/* Copyright (C) Mathieu Bouchard
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "pentamino.h"

#include <QFont>
#include <QBrush>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTextItem>
#include <QGraphicsSceneContextMenuEvent>

Qt::BrushStyle Pentamino::collisionBrushStyle = Qt::DiagCrossPattern;
Qt::BrushStyle Pentamino::normalBrushStyle = Qt::SolidPattern;

Pentamino::Pentamino(int id, QColor brushColor, bool canMirror)
{
    this->pentaminoId = id;

    // Enable selection of the item group
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    this->setFlag(QGraphicsItem::ItemIsMovable, true);
    this->setFlag(QGraphicsItem::ItemIsFocusable, true);

    // Enable sending position changed events
    this->setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);

    this->canMirror = canMirror;
    this->isMirrored = false;

    this->currentAngle = 0;
    this->currentBrush = nullptr;
    this->titlePenColor = Qt::black;
    this->normalPenColor = Qt::black;
    this->selectedPenColor = Qt::cyan;

    this->setBrushColor(brushColor);

}

int Pentamino::id()
{
    return this->pentaminoId;
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
    if (this->currentBrush == nullptr) {
        // If it's the first time we set the color, also update the collision brush color
        this->setCollisionBrushColor(color);
        this->currentBrush = &this->normalBrush;
    }
}

void Pentamino::setCollisionBrushColor(QColor color)
{
    this->collisionBrush = QBrush(color, this->collisionBrushStyle);
}

void Pentamino::rotate()
{
    this->currentAngle += 90;
    if (this->currentAngle >= 360) {
        this->currentAngle = 0;
    }
    this->setRotation(this->currentAngle);
    emit pentaminoMoved();
}

void Pentamino::mirror()
{
    if (this->canMirror) {
        QTransform transform(this->transform());
        transform.scale(-1, 1);
        this->setTransform(transform);

        this->isMirrored = !this->isMirrored;
        emit pentaminoMoved();
    }
}

void Pentamino::reset()
{
    // Reset rotation
    this->currentAngle = 0;
    this->setRotation(this->currentAngle);

    // Reset mirroring
    if (this->isMirrored) {
        this->mirror();
    }

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
    this->grabKeyboard();
}

void Pentamino::focusOutEvent(QFocusEvent *event)
{
    Q_UNUSED(event)

    if (this->collidingItems().length() != 0) {
        this->setCollision(true);
    }
    this->setZValue(0);
    this->ungrabKeyboard();
}

void Pentamino::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Escape:
            this->clearFocus();
            break;
        case Qt::Key_Space:
            this->mirror();
            break;
        case Qt::Key_Up:
            this->setPos(QPointF(this->pos().x(), this->pos().y() - 10));
            break;
        case Qt::Key_Down:
            this->setPos(QPointF(this->pos().x(), this->pos().y() + 10));
            break;
        case Qt::Key_Left:
            this->setPos(QPointF(this->pos().x() - 10, this->pos().y()));
            break;
        case Qt::Key_Right:
            this->setPos(QPointF(this->pos().x() + 10, this->pos().y()));
            break;
        default:
            QGraphicsItem::keyPressEvent(event);
    }
}

void Pentamino::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    event->accept();
    this->rotate();
}

void Pentamino::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // Draw pentamino blocks
    if (this->hasFocus()) {
        painter->setPen(this->selectedPenColor);
    } else {
        painter->setPen(this->normalPenColor);
    }
    painter->setBrush(*this->currentBrush);
    painter->drawPath(this->path);

    // Add pentamino number text
    QFont font = painter->font();
    font.setPointSize(5);
    painter->setFont(font);
    painter->setPen(this->titlePenColor);
    painter->drawText(QRect(-5, -5, 10, 10), Qt::AlignCenter, QString::number(this->id()));
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

void Pentamino::setTitleColor(QColor color)
{
    this->titlePenColor = color;
}

Pentamino* Pentamino::pentamino1()
{
    Pentamino *pentamino = new Pentamino(1, QColor(255, 192, 0, 255));

    /* x
     * x
     * x
     * x
     * x
     */
    pentamino->addRectItem(QRect(-5, -25, 10, 10));
    pentamino->addRectItem(QRect(-5, -15, 10, 10));
    pentamino->addRectItem(QRect(-5, -5, 10, 10));
    pentamino->addRectItem(QRect(-5, 5, 10, 10));
    pentamino->addRectItem(QRect(-5, 15, 10, 10));

    return pentamino;
}

Pentamino* Pentamino::pentamino2()
{
    Pentamino *pentamino = new Pentamino(2, QColor(237, 125, 49, 255), true);

    /* x
     * x
     * x
     * xx
     */
    pentamino->addRectItem(QRect(-5, -25, 10, 10));
    pentamino->addRectItem(QRect(-5, -15, 10, 10));
    pentamino->addRectItem(QRect(-5, -5, 10, 10));
    pentamino->addRectItem(QRect(-5, 5, 10, 10));
    // Right of the last one
    pentamino->addRectItem(QRect(5, 5, 10, 10));

    return pentamino;
}

Pentamino* Pentamino::pentamino3()
{
    Pentamino *pentamino = new Pentamino(3, QColor(192, 0, 0, 255), true);
    pentamino->setTitleColor(Qt::white);

    /*  x
     *  x
     * xx
     *  x
     */
    pentamino->addRectItem(QRect(-5, -25, 10, 10));
    pentamino->addRectItem(QRect(-5, -15, 10, 10));
    pentamino->addRectItem(QRect(-5, -5, 10, 10));
    pentamino->addRectItem(QRect(-5, 5, 10, 10));
    // Left of the third one
    pentamino->addRectItem(QRect(-15, -5, 10, 10));

    return pentamino;
}

Pentamino* Pentamino::pentamino4()
{
    Pentamino *pentamino = new Pentamino(4, QColor(112, 48, 160, 255), true);
    pentamino->setTitleColor(Qt::white);

    /*  x
     *  x
     * xx
     * x
     */
    pentamino->addRectItem(QRect(-5, -25, 10, 10));
    pentamino->addRectItem(QRect(-5, -15, 10, 10));
    pentamino->addRectItem(QRect(-5, -5, 10, 10));
    // Left of the third one
    pentamino->addRectItem(QRect(-15, -5, 10, 10));
    // Below the last one
    pentamino->addRectItem(QRect(-15, 5, 10, 10));

    return pentamino;
}

Pentamino* Pentamino::pentamino5()
{
    Pentamino *pentamino = new Pentamino(5, QColor(0, 32, 96, 255));
    pentamino->setTitleColor(Qt::white);

    /*   x
     *   x
     * xxx
     */
    pentamino->addRectItem(QRect(-5, -25, 10, 10));
    pentamino->addRectItem(QRect(-5, -15, 10, 10));
    pentamino->addRectItem(QRect(-5, -5, 10, 10));
    // Left of the last one
    pentamino->addRectItem(QRect(-15, -5, 10, 10));
    // Left of the last one
    pentamino->addRectItem(QRect(-25, -5, 10, 10));

    return pentamino;
}

Pentamino* Pentamino::pentamino6()
{
    Pentamino *pentamino = new Pentamino(6, QColor(255, 0, 255, 255), true);

    /* xx
     * xx
     * x
     */
    pentamino->addRectItem(QRect(-5, -15, 10, 10));
    pentamino->addRectItem(QRect(-5, -5, 10, 10));
    pentamino->addRectItem(QRect(-5, 5, 10, 10));
    // Right of the first one
    pentamino->addRectItem(QRect(5, -15, 10, 10));
    // Below the last one
    pentamino->addRectItem(QRect(5, -5, 10, 10));

    return pentamino;
}

Pentamino* Pentamino::pentamino7()
{
    Pentamino *pentamino = new Pentamino(7, QColor(255, 255, 153, 255));

    /* xx
     *  x
     * xx
     */
    pentamino->addRectItem(QRect(-5, -15, 10, 10));
    pentamino->addRectItem(QRect(-5, -5, 10, 10));
    pentamino->addRectItem(QRect(-5, 5, 10, 10));
    // Left of the first one
    pentamino->addRectItem(QRect(-15, -15, 10, 10));
    // Left of the third one
    pentamino->addRectItem(QRect(-15, 5, 10, 10));

    return pentamino;
}

Pentamino* Pentamino::pentamino8()
{
    Pentamino *pentamino = new Pentamino(8, QColor(0, 176, 240, 255), true);
    pentamino->setTitleColor(Qt::white);

    /*  xx
     *  x
     * xx
     */
    pentamino->addRectItem(QRect(-5, -15, 10, 10));
    pentamino->addRectItem(QRect(-5, -5, 10, 10));
    pentamino->addRectItem(QRect(-5, 5, 10, 10));
    // Right of the first one
    pentamino->addRectItem(QRect(5, -15, 10, 10));
    // Left of the third one
    pentamino->addRectItem(QRect(-15, 5, 10, 10));

    return pentamino;
}

Pentamino* Pentamino::pentamino9()
{
    Pentamino *pentamino = new Pentamino(9, QColor(192, 191, 191, 255), true);

    /*  x
     * xxx
     * x
     */
    pentamino->addRectItem(QRect(-5, -15, 10, 10));
    pentamino->addRectItem(QRect(-5, -5, 10, 10));
    // Right of the second one
    pentamino->addRectItem(QRect(5, -5, 10, 10));
    // Left of the second one
    pentamino->addRectItem(QRect(-15, -5, 10, 10));
    // Below the last one
    pentamino->addRectItem(QRect(-15, 5, 10, 10));

    return pentamino;
}

Pentamino* Pentamino::pentamino10()
{
    Pentamino *pentamino = new Pentamino(10, QColor(255, 255, 255, 255));
    pentamino->setCollisionBrushColor(QColor(0, 0, 0, 255));

    /* xxx
     *  x
     *  x
     */
    pentamino->addRectItem(QRect(-5, -15, 10, 10));
    pentamino->addRectItem(QRect(-5, -5, 10, 10));
    pentamino->addRectItem(QRect(-5, 5, 10, 10));
    // Left of the first one
    pentamino->addRectItem(QRect(-15, -15, 10, 10));
    // Right of the first one
    pentamino->addRectItem(QRect(5, -15, 10, 10));

    return pentamino;
}

Pentamino* Pentamino::pentamino11()
{
    Pentamino *pentamino = new Pentamino(11, QColor(146, 208, 80, 255));

    /*   x
     *  xx
     * xx
     */
    pentamino->addRectItem(QRect(5, -15, 10, 10));
    pentamino->addRectItem(QRect(5, -5, 10, 10));
    // Left of the second one
    pentamino->addRectItem(QRect(-5, -5, 10, 10));
    // Below the last one
    pentamino->addRectItem(QRect(-5, 5, 10, 10));
    // Left of the last one
    pentamino->addRectItem(QRect(-15, 5, 10, 10));

    return pentamino;
}

Pentamino* Pentamino::pentamino12()
{
    Pentamino *pentamino = new Pentamino(12, QColor(255, 0, 0, 255));

    /*  x
     * xxx
     *  x
     */
    pentamino->addRectItem(QRect(-5, -15, 10, 10));
    pentamino->addRectItem(QRect(-5, -5, 10, 10));
    pentamino->addRectItem(QRect(-5, 5, 10, 10));
    // Left of the second one
    pentamino->addRectItem(QRect(-15, -5, 10, 10));
    // Right of the second one
    pentamino->addRectItem(QRect(5, -5, 10, 10));

    return pentamino;
}

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

Pentamino::Pentamino(int id, QColor brushColor, int gridPixelSize, bool canMirror)
{
    this->pentaminoId = id;

    this->gridPixelSize = gridPixelSize;

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
            this->setPos(QPointF(this->pos().x(), this->pos().y() - this->gridPixelSize));
            break;
        case Qt::Key_Down:
            this->setPos(QPointF(this->pos().x(), this->pos().y() + this->gridPixelSize));
            break;
        case Qt::Key_Left:
            this->setPos(QPointF(this->pos().x() - this->gridPixelSize, this->pos().y()));
            break;
        case Qt::Key_Right:
            this->setPos(QPointF(this->pos().x() + this->gridPixelSize, this->pos().y()));
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
    painter->drawText(QRect(-(this->gridPixelSize / 2), -(this->gridPixelSize / 2), this->gridPixelSize, this->gridPixelSize), Qt::AlignCenter, QString::number(this->id()));
}

void Pentamino::setPos(const QPointF &pos)
{
    QGraphicsItem::setPos(pos);

}

QVariant Pentamino::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
        // value is the new position. The position is the new position of (0,0)
        QPointF newPos = value.toPointF();

        // Check if the pentamino will be out of bounds
        QRectF rect = this->scene()->sceneRect();
        if (!rect.contains(newPos)) {
            // Keep the item inside the scene rect.
            newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
            newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
        }

        // Snap to grid
        int gridSize = this->gridPixelSize;
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

void Pentamino::addRectItem(int leftX, int topY)
{
    // For mirroring / rotation to work correctly, we must offset the position
    // so that (0,0) is in the middle of a central square
    QRect rect(leftX - (this->gridPixelSize / 2), topY - (this->gridPixelSize / 2), this->gridPixelSize, this->gridPixelSize);

    // Path for drawing
    this->path.addRect(rect);
    // Path for collision detection
    this->shapePath.addRect(rect.x() + 1, rect.y() + 1, rect.width() - 2, rect.height() - 2);
}

void Pentamino::setTitleColor(QColor color)
{
    this->titlePenColor = color;
}

Pentamino* Pentamino::pentamino1(int gridPixelSize)
{
    Pentamino *pentamino = new Pentamino(1, QColor(255, 192, 0, 255), gridPixelSize);

    /* 1
     * 2
     * x
     * 4
     * 5
     */
    pentamino->addRectItem(0, -2 * gridPixelSize);
    pentamino->addRectItem(0, -gridPixelSize);
    pentamino->addRectItem(0, 0);
    pentamino->addRectItem(0, gridPixelSize);
    pentamino->addRectItem(0, 2 * gridPixelSize);

    return pentamino;
}

Pentamino* Pentamino::pentamino2(int gridPixelSize)
{
    Pentamino *pentamino = new Pentamino(2, QColor(237, 125, 49, 255), gridPixelSize, true);

    /* 1
     * 2
     * x
     * 45
     */
    pentamino->addRectItem(0, -2 * gridPixelSize);
    pentamino->addRectItem(0, -gridPixelSize);
    pentamino->addRectItem(0, 0);
    pentamino->addRectItem(0, gridPixelSize);
    pentamino->addRectItem(gridPixelSize, gridPixelSize);

    return pentamino;
}

Pentamino* Pentamino::pentamino3(int gridPixelSize)
{
    Pentamino *pentamino = new Pentamino(3, QColor(192, 0, 0, 255), gridPixelSize, true);
    pentamino->setTitleColor(Qt::white);

    /*  1
     *  2
     * 53
     *  4
     */
    pentamino->addRectItem(0, -2 * gridPixelSize);
    pentamino->addRectItem(0, -gridPixelSize);
    pentamino->addRectItem(0, 0);
    pentamino->addRectItem(0, gridPixelSize);
    // Left of the third one
    pentamino->addRectItem(-gridPixelSize, 0);

    return pentamino;
}

Pentamino* Pentamino::pentamino4(int gridPixelSize)
{
    Pentamino *pentamino = new Pentamino(4, QColor(112, 48, 160, 255), gridPixelSize, true);
    pentamino->setTitleColor(Qt::white);

    /*  1
     *  2
     * 43
     * 5
     */
    pentamino->addRectItem(0, -2 * gridPixelSize);
    pentamino->addRectItem(0, -gridPixelSize);
    pentamino->addRectItem(0, 0);
    // Left of the third one
    pentamino->addRectItem(-gridPixelSize, 0);
    // Below the last one
    pentamino->addRectItem(-gridPixelSize, gridPixelSize);

    return pentamino;
}

Pentamino* Pentamino::pentamino5(int gridPixelSize)
{
    Pentamino *pentamino = new Pentamino(5, QColor(0, 32, 96, 255), gridPixelSize);
    pentamino->setTitleColor(Qt::white);

    /*   1
     *   2
     * 543
     */
    pentamino->addRectItem(0, -2 * gridPixelSize);
    pentamino->addRectItem(0, -gridPixelSize);
    pentamino->addRectItem(0, 0);
    // Left of the last one
    pentamino->addRectItem(-gridPixelSize, 0);
    // Left of the last one
    pentamino->addRectItem(-2 * gridPixelSize, 0);

    return pentamino;
}

Pentamino* Pentamino::pentamino6(int gridPixelSize)
{
    Pentamino *pentamino = new Pentamino(6, QColor(255, 0, 255, 255), gridPixelSize, true);

    /* 14
     * 25
     * 3
     */
    pentamino->addRectItem(0, -gridPixelSize);
    pentamino->addRectItem(0, 0);
    pentamino->addRectItem(0, gridPixelSize);
    // Right of the first one
    pentamino->addRectItem(gridPixelSize, -gridPixelSize);
    // Below the last one
    pentamino->addRectItem(gridPixelSize, 0);

    return pentamino;
}

Pentamino* Pentamino::pentamino7(int gridPixelSize)
{
    Pentamino *pentamino = new Pentamino(7, QColor(255, 255, 153, 255), gridPixelSize);

    /* 41
     *  2
     * 53
     */
    pentamino->addRectItem(0, -gridPixelSize);
    pentamino->addRectItem(0, 0);
    pentamino->addRectItem(0, gridPixelSize);
    // Left of the first one
    pentamino->addRectItem(-gridPixelSize, -gridPixelSize);
    // Left of the third one
    pentamino->addRectItem(-gridPixelSize, gridPixelSize);

    return pentamino;
}

Pentamino* Pentamino::pentamino8(int gridPixelSize)
{
    Pentamino *pentamino = new Pentamino(8, QColor(0, 176, 240, 255), gridPixelSize, true);
    pentamino->setTitleColor(Qt::white);

    /*  14
     *  2
     * 53
     */
    pentamino->addRectItem(0, -gridPixelSize);
    pentamino->addRectItem(0, 0);
    pentamino->addRectItem(0, gridPixelSize);
    // Right of the first one
    pentamino->addRectItem(gridPixelSize, -gridPixelSize);
    // Left of the third one
    pentamino->addRectItem(-gridPixelSize, gridPixelSize);

    return pentamino;
}

Pentamino* Pentamino::pentamino9(int gridPixelSize)
{
    Pentamino *pentamino = new Pentamino(9, QColor(192, 191, 191, 255), gridPixelSize, true);

    /*  1
     * 423
     * 5
     */
    pentamino->addRectItem(0, -gridPixelSize);
    pentamino->addRectItem(0, 0);
    // Right of the second one
    pentamino->addRectItem(gridPixelSize, 0);
    // Left of the second one
    pentamino->addRectItem(-gridPixelSize, 0);
    // Below the last one
    pentamino->addRectItem(-gridPixelSize, gridPixelSize);

    return pentamino;
}

Pentamino* Pentamino::pentamino10(int gridPixelSize)
{
    Pentamino *pentamino = new Pentamino(10, QColor(255, 255, 255, 255), gridPixelSize);
    pentamino->setCollisionBrushColor(QColor(0, 0, 0, 255));

    /* 415
     *  2
     *  3
     */
    pentamino->addRectItem(0, -gridPixelSize);
    pentamino->addRectItem(0, 0);
    pentamino->addRectItem(0, gridPixelSize);
    // Left of the first one
    pentamino->addRectItem(-gridPixelSize, -gridPixelSize);
    // Right of the first one
    pentamino->addRectItem(gridPixelSize, -gridPixelSize);

    return pentamino;
}

Pentamino* Pentamino::pentamino11(int gridPixelSize)
{
    Pentamino *pentamino = new Pentamino(11, QColor(146, 208, 80, 255), gridPixelSize);

    /*   1
     *  32
     * 54
     */
    pentamino->addRectItem(gridPixelSize, -gridPixelSize);
    pentamino->addRectItem(gridPixelSize, 0);
    // Left of the second one
    pentamino->addRectItem(0, 0);
    // Below the last one
    pentamino->addRectItem(0, gridPixelSize);
    // Left of the last one
    pentamino->addRectItem(-gridPixelSize, gridPixelSize);

    return pentamino;
}

Pentamino* Pentamino::pentamino12(int gridPixelSize)
{
    Pentamino *pentamino = new Pentamino(12, QColor(255, 0, 0, 255), gridPixelSize);

    /*  1
     * 425
     *  3
     */
    pentamino->addRectItem(0, -gridPixelSize);
    pentamino->addRectItem(0, 0);
    pentamino->addRectItem(0, gridPixelSize);
    // Left of the second one
    pentamino->addRectItem(-gridPixelSize, 0);
    // Right of the second one
    pentamino->addRectItem(gridPixelSize, 0);

    return pentamino;
}

#ifndef PENTAMINO_H
#define PENTAMINO_H

#include <QGraphicsObject>
#include <QPainter>
#include <QBrush>
#include <QKeyEvent>

class Pentamino : public QGraphicsObject
{
    Q_OBJECT

public:
    enum { Type = UserType + 1001 };

    int id();

    static Pentamino* pentamino1();
    static Pentamino* pentamino2();
    static Pentamino* pentamino3();
    static Pentamino* pentamino4();
    static Pentamino* pentamino5();
    static Pentamino* pentamino6();
    static Pentamino* pentamino7();
    static Pentamino* pentamino8();
    static Pentamino* pentamino9();
    static Pentamino* pentamino10();
    static Pentamino* pentamino11();
    static Pentamino* pentamino12();

    void reset();
    void setCollision(bool collided);

    void setPos(const QPointF &pos);
    QPainterPath shape() const override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    int type() const override;

    void mirror();
    void rotate();

signals:
    void pentaminoMoved();

protected:
    Pentamino(int id, QColor brushColor, bool canMirror = false);

    void addRectItem(QRect rect);
    void setBrushColor(QColor color);
    void setCollisionBrushColor(QColor color);
    void setTitleColor(QColor color);

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    int pentaminoId;

    static Qt::BrushStyle collisionBrushStyle;
    static Qt::BrushStyle normalBrushStyle;

    QBrush *currentBrush;
    QBrush normalBrush;
    QBrush collisionBrush;

    bool canMirror;
    bool isMirrored;
    int currentAngle;

    QPainterPath path;
    QPainterPath shapePath;

    QColor titleColor;
};

#endif // PENTAMINO_H

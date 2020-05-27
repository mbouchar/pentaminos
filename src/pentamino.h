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

    static Pentamino* pentamino1(int gridPixelSize);
    static Pentamino* pentamino2(int gridPixelSize);
    static Pentamino* pentamino3(int gridPixelSize);
    static Pentamino* pentamino4(int gridPixelSize);
    static Pentamino* pentamino5(int gridPixelSize);
    static Pentamino* pentamino6(int gridPixelSize);
    static Pentamino* pentamino7(int gridPixelSize);
    static Pentamino* pentamino8(int gridPixelSize);
    static Pentamino* pentamino9(int gridPixelSize);
    static Pentamino* pentamino10(int gridPixelSize);
    static Pentamino* pentamino11(int gridPixelSize);
    static Pentamino* pentamino12(int gridPixelSize);

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
    Pentamino(int id, QColor brushColor, int gridPixelSize, bool canMirror = false);

    void addRectItem(int leftX, int topY);
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

    int gridPixelSize;

    static Qt::BrushStyle collisionBrushStyle;
    static Qt::BrushStyle normalBrushStyle;

    QColor normalPenColor;
    QColor selectedPenColor;

    QBrush *currentBrush;
    QBrush normalBrush;
    QBrush collisionBrush;

    bool canMirror;
    bool isMirrored;
    int currentAngle;

    QPainterPath path;
    QPainterPath shapePath;

    QColor titlePenColor;
};

#endif // PENTAMINO_H

#ifndef PENTAMINO_H
#define PENTAMINO_H

#include <QGraphicsItemGroup>

class Pentamino : public QGraphicsItemGroup
{
public:
    Pentamino();

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

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void addRectItem(QRect rect, QBrush brush);
    void addTitle(QString title, QColor color = Qt::black);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

private:
    int currentAngle;
};

#endif // PENTAMINO_H

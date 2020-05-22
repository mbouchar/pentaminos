#ifndef GAME_H
#define GAME_H

#include "pentamino.h"
#include "grid.h"

#include <QObject>
#include <QGraphicsScene>

class Game : public QObject
{
    Q_OBJECT

public:
    Game(QGraphicsScene *scene);

public slots:
    // Pentaminos 4
    void startPentamino4A();
    void startPentamino4B();
    void startPentamino4C();
    void startPentamino4D();
    void startPentamino4E();
    void startPentamino4F();
    void startPentamino4G();
    void startPentamino4H();
    void startPentamino4I();
    void startPentamino4J();
    void startPentamino4K();
    void startPentamino4L();

    // Pentaminos 5
    void startPentamino5A();
    void startPentamino5B();
    void startPentamino5C();
    void startPentamino5D();
    void startPentamino5E();
    void startPentamino5F();
    void startPentamino5G();
    void startPentamino5H();

    // Pentamino 12
    void startPentamino12();

protected:
    void resetGame();

private:
    Pentamino* addPentamino(Pentamino *pentamino, QPoint pos = QPoint(0, 0));
    Grid *addGrid(Grid *grid, QPoint pos = QPoint(0, 0));

    QGraphicsScene *scene;

    Pentamino *pentamino1;
    Pentamino *pentamino2;
    Pentamino *pentamino3;
    Pentamino *pentamino4;
    Pentamino *pentamino5;
    Pentamino *pentamino6;
    Pentamino *pentamino7;
    Pentamino *pentamino8;
    Pentamino *pentamino9;
    Pentamino *pentamino10;
    Pentamino *pentamino11;
    Pentamino *pentamino12;

    Grid *grid4;
    Grid *grid5;
    Grid *grid12;
};

#endif // GAME_H

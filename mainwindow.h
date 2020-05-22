#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pentamino.h"
#include "grid.h"

#include <QMainWindow>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    Pentamino* addPentamino(Pentamino *pentamino, QPoint pos);
    Grid *addGrid(Grid *grid, QPoint pos);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
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
#endif // MAINWINDOW_H

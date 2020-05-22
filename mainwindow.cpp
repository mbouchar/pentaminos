#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800, 600);
    this->setWindowTitle("Pentanimos");

    this->scene = new QGraphicsScene(QRect(-100, -100, 200, 200), this);
    this->scene->setBackgroundBrush(Qt::white);
    this->ui->graphicsView->setScene(this->scene);

    // Scale 2x
    QTransform transform;
    this->ui->graphicsView->setTransform(transform.scale(2, 2));
    this->ui->graphicsView->centerOn(0, 0);
    // Beautify the scene
    this->ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing);

    // Add all standard Pentamino
    this->pentamino1 = this->addPentamino(Pentamino::pentamino1(), QPoint(-185, -110));
    this->pentamino2 = this->addPentamino(Pentamino::pentamino2(), QPoint(-170, -110));
    this->pentamino3 = this->addPentamino(Pentamino::pentamino3(), QPoint(-135, -110));
    this->pentamino4 = this->addPentamino(Pentamino::pentamino4(), QPoint(-110, -110));
    this->pentamino5 = this->addPentamino(Pentamino::pentamino5(), QPoint(-75, -110));
    this->pentamino6 = this->addPentamino(Pentamino::pentamino6(), QPoint(-60, -110));
    this->pentamino7 = this->addPentamino(Pentamino::pentamino7(), QPoint(-25, -110));
    this->pentamino8 = this->addPentamino(Pentamino::pentamino8(), QPoint(0, -110));
    this->pentamino9 = this->addPentamino(Pentamino::pentamino9(), QPoint(35, -110));
    this->pentamino10 = this->addPentamino(Pentamino::pentamino10(), QPoint(70, -110));
    this->pentamino11 = this->addPentamino(Pentamino::pentamino11(), QPoint(105, -110));
    this->pentamino12 = this->addPentamino(Pentamino::pentamino12(), QPoint(140, -110));

    // All all grids to the scene
    this->grid4 = this->addGrid(Grid::grid4(), QPoint(-120, -25));
    this->grid5 = this->addGrid(Grid::grid5(), QPoint(-55, -25));
    this->grid12 = this->addGrid(Grid::grid12(), QPoint(20, -25));
}

Pentamino* MainWindow::addPentamino(Pentamino* pentamino, QPoint pos)
{
    // From the doc, the scene takes ownership of the item, so we don't need to delete it
    this->scene->addItem(pentamino);
    pentamino->setPos(pos);

    return pentamino;
}

Grid* MainWindow::addGrid(Grid *grid, QPoint pos)
{
    this->scene->addItem(grid);
    grid->setPos(pos);

    return grid;
}

MainWindow::~MainWindow()
{
    delete ui;
}


#include <QPushButton>
#include <QSizePolicy>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "scene.h"

int MainWindow::gridSize = 10;
// Scale 2x
int MainWindow::scale = 2;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->graphicsView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->ui->graphicsView->setMinimumSize(600, 550);
    this->setFixedSize(800, 600);
    this->setWindowTitle("Pentanimos");

    /*int sceneWidth = this->ui->graphicsView->width();
    int sceneHeight = this->ui->graphicsView->height();*/
    int sceneWidth = this->ui->graphicsView->rect().width();
    int sceneHeight = this->ui->graphicsView->rect().height();

    this->scene = new Scene(QRect(-(sceneWidth / 2) / this->scale, -(sceneHeight / 2) / this->scale, sceneWidth / this->scale, (sceneWidth - 50) / this->scale), this->gridSize, this);
    this->ui->graphicsView->setScene(this->scene);

    // Scale the view
    QTransform transform;
    this->ui->graphicsView->setTransform(transform.scale(this->scale, this->scale));
    this->ui->graphicsView->centerOn(0, 0);
    // Beautify the scene
    this->ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing);

    this->game = new Game(this->scene);

    // Pentaminos 4
    connect(this->ui->pentamino4A, SIGNAL(clicked()), this->game, SLOT(startPentamino4A()));
    connect(this->ui->pentamino4B, SIGNAL(clicked()), this->game, SLOT(startPentamino4B()));
    connect(this->ui->pentamino4C, SIGNAL(clicked()), this->game, SLOT(startPentamino4C()));
    connect(this->ui->pentamino4D, SIGNAL(clicked()), this->game, SLOT(startPentamino4D()));
    connect(this->ui->pentamino4E, SIGNAL(clicked()), this->game, SLOT(startPentamino4E()));
    connect(this->ui->pentamino4F, SIGNAL(clicked()), this->game, SLOT(startPentamino4F()));
    connect(this->ui->pentamino4G, SIGNAL(clicked()), this->game, SLOT(startPentamino4G()));
    connect(this->ui->pentamino4H, SIGNAL(clicked()), this->game, SLOT(startPentamino4H()));
    connect(this->ui->pentamino4I, SIGNAL(clicked()), this->game, SLOT(startPentamino4I()));
    connect(this->ui->pentamino4J, SIGNAL(clicked()), this->game, SLOT(startPentamino4J()));
    connect(this->ui->pentamino4K, SIGNAL(clicked()), this->game, SLOT(startPentamino4K()));
    connect(this->ui->pentamino4L, SIGNAL(clicked()), this->game, SLOT(startPentamino4L()));

    // Pentaminos 5
    connect(this->ui->pentamino5A, SIGNAL(clicked()), this->game, SLOT(startPentamino5A()));
    connect(this->ui->pentamino5B, SIGNAL(clicked()), this->game, SLOT(startPentamino5B()));
    connect(this->ui->pentamino5C, SIGNAL(clicked()), this->game, SLOT(startPentamino5C()));
    connect(this->ui->pentamino5D, SIGNAL(clicked()), this->game, SLOT(startPentamino5D()));
    connect(this->ui->pentamino5E, SIGNAL(clicked()), this->game, SLOT(startPentamino5E()));
    connect(this->ui->pentamino5F, SIGNAL(clicked()), this->game, SLOT(startPentamino5F()));
    connect(this->ui->pentamino5G, SIGNAL(clicked()), this->game, SLOT(startPentamino5G()));
    connect(this->ui->pentamino5H, SIGNAL(clicked()), this->game, SLOT(startPentamino5H()));

    // Pentamino 12
    connect(this->ui->pentamino12, SIGNAL(clicked()), this->game, SLOT(startPentamino12()));

    // Detect winning games
    connect(this->game, SIGNAL(gameWon()), this, SLOT(gameWon()));
}

void MainWindow::gameWon()
{
    // @todo: save status
    QMessageBox::information(this, "Fin de la partie", "La partie a été gagnée", QMessageBox::Ok);
}

MainWindow::~MainWindow()
{
    if (this->game != nullptr)
    {
        delete this->game;
        this->game = nullptr;
    }
    delete ui;
}


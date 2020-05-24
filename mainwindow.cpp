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

#include <QPushButton>
#include <QSizePolicy>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "settings.h"
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
    connect(this->ui->pentamino4A, SIGNAL(clicked()), this, SLOT(startPentamino4A()));
    connect(this->ui->pentamino4B, SIGNAL(clicked()), this, SLOT(startPentamino4B()));
    connect(this->ui->pentamino4C, SIGNAL(clicked()), this, SLOT(startPentamino4C()));
    connect(this->ui->pentamino4D, SIGNAL(clicked()), this, SLOT(startPentamino4D()));
    connect(this->ui->pentamino4E, SIGNAL(clicked()), this, SLOT(startPentamino4E()));
    connect(this->ui->pentamino4F, SIGNAL(clicked()), this, SLOT(startPentamino4F()));
    connect(this->ui->pentamino4G, SIGNAL(clicked()), this, SLOT(startPentamino4G()));
    connect(this->ui->pentamino4H, SIGNAL(clicked()), this, SLOT(startPentamino4H()));
    connect(this->ui->pentamino4I, SIGNAL(clicked()), this, SLOT(startPentamino4I()));
    connect(this->ui->pentamino4J, SIGNAL(clicked()), this, SLOT(startPentamino4J()));
    connect(this->ui->pentamino4K, SIGNAL(clicked()), this, SLOT(startPentamino4K()));
    connect(this->ui->pentamino4L, SIGNAL(clicked()), this, SLOT(startPentamino4L()));

    // Pentaminos 5
    connect(this->ui->pentamino5A, SIGNAL(clicked()), this, SLOT(startPentamino5A()));
    connect(this->ui->pentamino5B, SIGNAL(clicked()), this, SLOT(startPentamino5B()));
    connect(this->ui->pentamino5C, SIGNAL(clicked()), this, SLOT(startPentamino5C()));
    connect(this->ui->pentamino5D, SIGNAL(clicked()), this, SLOT(startPentamino5D()));
    connect(this->ui->pentamino5E, SIGNAL(clicked()), this, SLOT(startPentamino5E()));
    connect(this->ui->pentamino5F, SIGNAL(clicked()), this, SLOT(startPentamino5F()));
    connect(this->ui->pentamino5G, SIGNAL(clicked()), this, SLOT(startPentamino5G()));
    connect(this->ui->pentamino5H, SIGNAL(clicked()), this, SLOT(startPentamino5H()));

    // Pentamino 12
    connect(this->ui->pentamino12, SIGNAL(clicked()), this, SLOT(startPentamino12()));

    // Detect winning games
    connect(this->game, SIGNAL(gameWon()), this, SLOT(gameWon()));

    // Load game status from save file
    this->setGameStatus(Settings::loadGame());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Settings::saveGame(this->gameStatus);

    QMainWindow::closeEvent(event);
}

void MainWindow::setGameStatus(GameStatus *status)
{
    this->gameStatus = status;
    this->updateUi(Game::Pentamino4A, this->gameStatus->status(Game::Pentamino4A));
    this->updateUi(Game::Pentamino4B, this->gameStatus->status(Game::Pentamino4B));
    this->updateUi(Game::Pentamino4C, this->gameStatus->status(Game::Pentamino4C));
    this->updateUi(Game::Pentamino4D, this->gameStatus->status(Game::Pentamino4D));
    this->updateUi(Game::Pentamino4E, this->gameStatus->status(Game::Pentamino4E));
    this->updateUi(Game::Pentamino4F, this->gameStatus->status(Game::Pentamino4F));
    this->updateUi(Game::Pentamino4G, this->gameStatus->status(Game::Pentamino4G));
    this->updateUi(Game::Pentamino4H, this->gameStatus->status(Game::Pentamino4H));
    this->updateUi(Game::Pentamino4I, this->gameStatus->status(Game::Pentamino4I));
    this->updateUi(Game::Pentamino4J, this->gameStatus->status(Game::Pentamino4J));
    this->updateUi(Game::Pentamino4K, this->gameStatus->status(Game::Pentamino4K));
    this->updateUi(Game::Pentamino4L, this->gameStatus->status(Game::Pentamino4L));
    this->updateUi(Game::Pentamino5A, this->gameStatus->status(Game::Pentamino5A));
    this->updateUi(Game::Pentamino5B, this->gameStatus->status(Game::Pentamino5B));
    this->updateUi(Game::Pentamino5C, this->gameStatus->status(Game::Pentamino5C));
    this->updateUi(Game::Pentamino5D, this->gameStatus->status(Game::Pentamino5D));
    this->updateUi(Game::Pentamino5E, this->gameStatus->status(Game::Pentamino5E));
    this->updateUi(Game::Pentamino5F, this->gameStatus->status(Game::Pentamino5F));
    this->updateUi(Game::Pentamino5G, this->gameStatus->status(Game::Pentamino5G));
    this->updateUi(Game::Pentamino5H, this->gameStatus->status(Game::Pentamino5H));
    this->updateUi(Game::Pentamino12, this->gameStatus->status(Game::Pentamino12));
}

void MainWindow::gameWon()
{
    // Update game status
    if (this->gameStatus->status(this->currentGameId) < GameStatus::Won) {
        this->gameStatus->setStatus(this->currentGameId, GameStatus::Won);
        Settings::saveGame(this->gameStatus);
        this->updateUi(this->currentGameId, GameStatus::Won);
    }
}

void MainWindow::startGame(Game::GameId gameId)
{
    // Save Status if never won or tried
    if (this->gameStatus->status(gameId) < GameStatus::Tried) {
        this->gameStatus->setStatus(gameId, GameStatus::Tried);
        Settings::saveGame(this->gameStatus);
        this->updateUi(gameId, GameStatus::Tried);
    }
    this->currentGameId = gameId;
    this->game->startGame(gameId);
}

void MainWindow::updateButton(QPushButton *button, GameStatus::Status gameStatus)
{
    QPalette pal = button->palette();
    switch (gameStatus) {
        case GameStatus::NeverTried:
            pal.setColor(QPalette::Button, Qt::red);
            break;
        case GameStatus::Tried:
            pal.setColor(QPalette::Button, Qt::yellow);
            break;
        case GameStatus::Won:
            pal.setColor(QPalette::Button, Qt::green);
            break;
    }
    button->setAutoFillBackground(true);
    button->setPalette(pal);
    button->update();
}

void MainWindow::updateUi(Game::GameId gameId, GameStatus::Status status)
{
    switch (gameId) {
        case Game::Pentamino4A:
            this->updateButton(this->ui->pentamino4A, status);
            break;
        case Game::Pentamino4B:
            this->updateButton(this->ui->pentamino4B, status);
            break;
        case Game::Pentamino4C:
            this->updateButton(this->ui->pentamino4C, status);
            break;
        case Game::Pentamino4D:
            this->updateButton(this->ui->pentamino4D, status);
            break;
        case Game::Pentamino4E:
            this->updateButton(this->ui->pentamino4E, status);
            break;
        case Game::Pentamino4F:
            this->updateButton(this->ui->pentamino4F, status);
            break;
        case Game::Pentamino4G:
            this->updateButton(this->ui->pentamino4G, status);
            break;
        case Game::Pentamino4H:
            this->updateButton(this->ui->pentamino4H, status);
            break;
        case Game::Pentamino4I:
            this->updateButton(this->ui->pentamino4I, status);
            break;
        case Game::Pentamino4J:
            this->updateButton(this->ui->pentamino4J, status);
            break;
        case Game::Pentamino4K:
            this->updateButton(this->ui->pentamino4K, status);
            break;
        case Game::Pentamino4L:
            this->updateButton(this->ui->pentamino4L, status);
            break;
        case Game::Pentamino5A:
            this->updateButton(this->ui->pentamino5A, status);
            break;
        case Game::Pentamino5B:
            this->updateButton(this->ui->pentamino5B, status);
            break;
        case Game::Pentamino5C:
            this->updateButton(this->ui->pentamino5C, status);
            break;
        case Game::Pentamino5D:
            this->updateButton(this->ui->pentamino5D, status);
            break;
        case Game::Pentamino5E:
            this->updateButton(this->ui->pentamino5E, status);
            break;
        case Game::Pentamino5F:
            this->updateButton(this->ui->pentamino5F, status);
            break;
        case Game::Pentamino5G:
            this->updateButton(this->ui->pentamino5G, status);
            break;
        case Game::Pentamino5H:
            this->updateButton(this->ui->pentamino5H, status);
            break;
        case Game::Pentamino12:
            this->updateButton(this->ui->pentamino12, status);
            break;
    }
}

void MainWindow::startPentamino4A()
{
    this->startGame(Game::Pentamino4A);
}

void MainWindow::startPentamino4B()
{
    this->startGame(Game::Pentamino4B);
}

void MainWindow::startPentamino4C()
{
    this->startGame(Game::Pentamino4C);
}

void MainWindow::startPentamino4D()
{
    this->startGame(Game::Pentamino4D);
}

void MainWindow::startPentamino4E()
{
    this->startGame(Game::Pentamino4E);
}

void MainWindow::startPentamino4F()
{
    this->startGame(Game::Pentamino4F);
}

void MainWindow::startPentamino4G()
{
    this->startGame(Game::Pentamino4G);
}

void MainWindow::startPentamino4H()
{
    this->startGame(Game::Pentamino4H);
}

void MainWindow::startPentamino4I()
{
    this->startGame(Game::Pentamino4I);
}

void MainWindow::startPentamino4J()
{
    this->startGame(Game::Pentamino4J);
}

void MainWindow::startPentamino4K()
{
    this->startGame(Game::Pentamino4K);
}

void MainWindow::startPentamino4L()
{
    this->startGame(Game::Pentamino4L);
}

void MainWindow::startPentamino5A()
{
    this->startGame(Game::Pentamino5A);
}

void MainWindow::startPentamino5B()
{
    this->startGame(Game::Pentamino5B);
}

void MainWindow::startPentamino5C()
{
    this->startGame(Game::Pentamino5C);
}

void MainWindow::startPentamino5D()
{
    this->startGame(Game::Pentamino5D);
}

void MainWindow::startPentamino5E()
{
    this->startGame(Game::Pentamino5E);
}

void MainWindow::startPentamino5F()
{
    this->startGame(Game::Pentamino5F);
}

void MainWindow::startPentamino5G()
{
    this->startGame(Game::Pentamino5G);
}

void MainWindow::startPentamino5H()
{
    this->startGame(Game::Pentamino5H);
}

void MainWindow::startPentamino12()
{
    this->startGame(Game::Pentamino12);
}

MainWindow::~MainWindow()
{
    if (this->game != nullptr)
    {
        delete this->game;
        this->game = nullptr;
    }
    if (this->gameStatus != nullptr)
    {
        delete this->gameStatus;
        this->gameStatus = nullptr;
    }
    delete ui;
}


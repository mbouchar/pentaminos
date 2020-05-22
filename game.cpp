#include "game.h"

Game::Game(QGraphicsScene *scene)
{
    this->scene = scene;

    // All all grids to the scene
    this->grid4 = this->addGrid(Grid::grid4());
    this->grid5 = this->addGrid(Grid::grid5());
    this->grid12 = this->addGrid(Grid::grid12());

    // Add all standard Pentamino
    this->pentamino1 = this->addPentamino(Pentamino::pentamino1());
    this->pentamino2 = this->addPentamino(Pentamino::pentamino2());
    this->pentamino3 = this->addPentamino(Pentamino::pentamino3());
    this->pentamino4 = this->addPentamino(Pentamino::pentamino4());
    this->pentamino5 = this->addPentamino(Pentamino::pentamino5());
    this->pentamino6 = this->addPentamino(Pentamino::pentamino6());
    this->pentamino7 = this->addPentamino(Pentamino::pentamino7());
    this->pentamino8 = this->addPentamino(Pentamino::pentamino8());
    this->pentamino9 = this->addPentamino(Pentamino::pentamino9());
    this->pentamino10 = this->addPentamino(Pentamino::pentamino10());
    this->pentamino11 = this->addPentamino(Pentamino::pentamino11());
    this->pentamino12 = this->addPentamino(Pentamino::pentamino12());
}

void Game::resetGame()
{
    this->pentamino1->setPos(QPoint(-140, -110));
    this->pentamino1->hide();
    this->pentamino2->setPos(QPoint(-120, -110));
    this->pentamino2->hide();
    this->pentamino3->setPos(QPoint(-80, -110));
    this->pentamino3->hide();
    this->pentamino4->setPos(QPoint(-50, -110));
    this->pentamino4->hide();
    this->pentamino5->setPos(QPoint(-10, -110));
    this->pentamino5->hide();
    this->pentamino6->setPos(QPoint(10, -110));
    this->pentamino6->hide();
    this->pentamino7->setPos(QPoint(50, -110));
    this->pentamino7->hide();
    this->pentamino8->setPos(QPoint(80, -110));
    this->pentamino8->hide();
    this->pentamino9->setPos(QPoint(120, -110));
    this->pentamino9->hide();
    this->pentamino10->setPos(QPoint(-130, -60));
    this->pentamino10->hide();
    this->pentamino11->setPos(QPoint(-90, -60));
    this->pentamino11->hide();
    this->pentamino12->setPos(QPoint(-50, -60));
    this->pentamino12->hide();

    this->grid4->setPos(QPoint(-5, -5));
    this->grid4->hide();
    this->grid5->setPos(QPoint(-5, -5));
    this->grid5->hide();
    this->grid12->setPos(QPoint(-5, -5));
    this->grid12->hide();
}

Pentamino* Game::addPentamino(Pentamino* pentamino, QPoint pos)
{
    // From the doc, the scene takes ownership of the item, so we don't need to delete it
    this->scene->addItem(pentamino);
    pentamino->setPos(pos);
    pentamino->hide();

    return pentamino;
}

Grid* Game::addGrid(Grid *grid, QPoint pos)
{
    this->scene->addItem(grid);
    grid->setPos(pos);
    grid->hide();

    return grid;
}

void Game::startPentamino4A()
{
    this->resetGame();
    this->grid4->show();
    this->pentamino2->show();
    this->pentamino4->show();
    this->pentamino5->show();
    this->pentamino8->show();
}

void Game::startPentamino4B()
{
    this->resetGame();
    this->grid4->show();
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino7->show();
    this->pentamino9->show();
}

void Game::startPentamino4C()
{
    this->resetGame();
    this->grid4->show();
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino5->show();
    this->pentamino6->show();
}

void Game::startPentamino4D()
{
    this->resetGame();
    this->grid4->show();
    this->pentamino3->show();
    this->pentamino6->show();
    this->pentamino7->show();
    this->pentamino9->show();
}

void Game::startPentamino4E()
{
    this->resetGame();
    this->grid4->show();
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino6->show();
    this->pentamino8->show();
}

void Game::startPentamino4F()
{
    this->resetGame();
    this->grid4->show();
    this->pentamino2->show();
    this->pentamino6->show();
    this->pentamino7->show();
    this->pentamino9->show();
}

void Game::startPentamino4G()
{
    this->resetGame();
    this->grid4->show();
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino6->show();
    this->pentamino11->show();
}

void Game::startPentamino4H()
{
    this->resetGame();
    this->grid4->show();
    this->pentamino3->show();
    this->pentamino4->show();
    this->pentamino5->show();
    this->pentamino10->show();
}

void Game::startPentamino4I()
{
    this->resetGame();
    this->grid4->show();
    this->pentamino2->show();
    this->pentamino5->show();
    this->pentamino6->show();
    this->pentamino8->show();
}

void Game::startPentamino4J()
{
    this->resetGame();
    this->grid4->show();
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino6->show();
    this->pentamino10->show();
}

void Game::startPentamino4K()
{
    this->resetGame();
    this->grid4->show();
    this->pentamino3->show();
    this->pentamino4->show();
    this->pentamino6->show();
    this->pentamino7->show();
}

void Game::startPentamino4L()
{
    this->resetGame();
    this->grid4->show();
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino5->show();
    this->pentamino7->show();
}

void Game::startPentamino5A()
{
    this->resetGame();
    this->grid5->show();
    this->pentamino2->show();
    this->pentamino4->show();
    this->pentamino5->show();
    this->pentamino7->show();
    this->pentamino8->show();
}

void Game::startPentamino5B()
{
    this->resetGame();
    this->grid5->show();
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino7->show();
    this->pentamino8->show();
    this->pentamino9->show();
}

void Game::startPentamino5C()
{
    this->resetGame();
    this->grid5->show();
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino5->show();
    this->pentamino6->show();
    this->pentamino9->show();
}

void Game::startPentamino5D()
{
    this->resetGame();
    this->grid5->show();
    this->pentamino3->show();
    this->pentamino6->show();
    this->pentamino7->show();
    this->pentamino9->show();
    this->pentamino10->show();
}

void Game::startPentamino5E()
{
    this->resetGame();
    this->grid5->show();
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino6->show();
    this->pentamino8->show();
    this->pentamino11->show();
}

void Game::startPentamino5F()
{
    this->resetGame();
    this->grid5->show();
    this->pentamino2->show();
    this->pentamino6->show();
    this->pentamino7->show();
    this->pentamino9->show();
    this->pentamino12->show();
}

void Game::startPentamino5G()
{
    this->resetGame();
    this->grid5->show();
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino4->show();
    this->pentamino6->show();
    this->pentamino11->show();
}

void Game::startPentamino5H()
{
    this->resetGame();
    this->grid5->show();
    this->pentamino3->show();
    this->pentamino4->show();
    this->pentamino5->show();
    this->pentamino9->show();
    this->pentamino10->show();
}

void Game::startPentamino12()
{
    this->resetGame();
    this->grid12->show();
    this->pentamino1->show();
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino4->show();
    this->pentamino5->show();
    this->pentamino6->show();
    this->pentamino7->show();
    this->pentamino8->show();
    this->pentamino9->show();
    this->pentamino10->show();
    this->pentamino11->show();
    this->pentamino12->show();
}

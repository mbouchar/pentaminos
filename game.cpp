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

#include "game.h"
#include "scene.h"

#include <QObject>

Game::Game(Scene *scene)
{
    this->scene = scene;
    this->scene->setGame(this);

    // All all grids to the scene
    this->grid4 = this->addGrid(Grid::grid4());
    this->grid5 = this->addGrid(Grid::grid5());
    this->grid12 = this->addGrid(Grid::grid12());

    // Add text
    this->showDefaultText();

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

    this->gameActiveGrid = nullptr;

    foreach(Pentamino *pentamino, this->pentaminos) {
        connect(pentamino, SIGNAL(pentaminoMoved()), this, SLOT(checkStatus()));
    }
}

QString Game::title()
{
    return this->gameTitle;
}

Grid* Game::activeGrid()
{
    return this->gameActiveGrid;
}

void Game::checkStatus()
{
    bool collisionDetected = false;

    // Detect if there's any collisions with the last moved pentamino
    Pentamino *lastMoved = qobject_cast<Pentamino*>(QObject::sender());
    QList<QGraphicsItem*> collidingItems;
    if (lastMoved != nullptr) {
        collidingItems = lastMoved->collidingItems();
        if (collidingItems.length() > 0)
        {
            foreach (QGraphicsItem *item, collidingItems) {
                // Make sure the item is of type Pentamino before calling setCollision
                Pentamino *pentamino = qgraphicsitem_cast<Pentamino*>(item);
                if (pentamino != nullptr) {
                    pentamino->setCollision(true);
                    // Detect only collision with other pentaminos
                    collisionDetected = true;
                }
            }
        }
    }
    // Detect collision with all remaining pentaminos
    foreach (Pentamino *pentamino, this->pentaminos) {
        if (pentamino != lastMoved && collidingItems.indexOf(pentamino) == -1) {
            if (pentamino->collidingItems().length() == 0) {
                pentamino->setCollision(false);
            } else {
                pentamino->setCollision(true);
            }
        }
    }

    // Detect if the game has been won
    if (!collisionDetected && this->activeGrid() != nullptr)
    {
        int gridWith = this->activeGrid()->size().width();
        int gridHeight = this->activeGrid()->size().height();

        QPoint gridPos = this->activeGrid()->pos();
        QTransform transform;

        for (int x = 0; x < gridWith; x++)
        {
            for (int y = 0; y < gridHeight; y++)
            {
                int xPos = (x * 10) + gridPos.x() + 5;
                int yPos = (y * 10) + gridPos.y() + 5;

                // A case doesn't have any piece
                if (this->scene->itemAt(xPos, yPos, transform) == 0)
                {
                    return;
                }
            }
        }

        // All cases are filled
        emit gameWon();
    }
}

void Game::showDefaultText()
{
    this->gameTitle = "Sélectionnez un pentanimo";
}

void Game::resetGame()
{
    this->pentamino1->setPos(QPoint(-140, -110));
    this->pentamino2->setPos(QPoint(-120, -110));
    this->pentamino3->setPos(QPoint(-80, -110));
    this->pentamino4->setPos(QPoint(-50, -110));
    this->pentamino5->setPos(QPoint(-10, -110));
    this->pentamino6->setPos(QPoint(10, -110));
    this->pentamino7->setPos(QPoint(50, -110));
    this->pentamino8->setPos(QPoint(80, -110));
    this->pentamino9->setPos(QPoint(120, -110));
    this->pentamino10->setPos(QPoint(-130, -60));
    this->pentamino11->setPos(QPoint(-90, -60));
    this->pentamino12->setPos(QPoint(-50, -60));

    foreach (Pentamino *pentamino, this->pentaminos) {
        pentamino->reset();
        pentamino->hide();
    }

    this->grid4->setPos(QPoint(-5, -5));
    this->grid5->setPos(QPoint(-5, -5));
    this->grid12->setPos(QPoint(-5, -5));

    this->showDefaultText();

    this->scene->invalidate(this->scene->sceneRect(), QGraphicsScene::BackgroundLayer);
}

Pentamino* Game::addPentamino(Pentamino* pentamino, QPoint pos)
{
    this->pentaminos.append(pentamino);

    // From the doc, the scene takes ownership of the item, so we don't need to delete it
    this->scene->addItem(pentamino);
    pentamino->setPos(pos);
    pentamino->hide();

    return pentamino;
}

Grid* Game::addGrid(Grid *grid, QPoint pos)
{
    grid->setPos(pos);
    return grid;
}

void Game::startGame(GameId gameId)
{
    switch (gameId) {
        case Pentamino4A:
            startPentamino4A();
            break;
        case Pentamino4B:
            startPentamino4B();
            break;
        case Pentamino4C:
            startPentamino4C();
            break;
        case Pentamino4D:
            startPentamino4D();
            break;
        case Pentamino4E:
            startPentamino4E();
            break;
        case Pentamino4F:
            startPentamino4F();
            break;
        case Pentamino4G:
            startPentamino4G();
            break;
        case Pentamino4H:
            startPentamino4H();
            break;
        case Pentamino4I:
            startPentamino4I();
            break;
        case Pentamino4J:
            startPentamino4J();
            break;
        case Pentamino4K:
            startPentamino4K();
            break;
        case Pentamino4L:
            startPentamino4L();
            break;
        case Pentamino5A:
            startPentamino5A();
            break;
        case Pentamino5B:
            startPentamino5B();
            break;
        case Pentamino5C:
            startPentamino5C();
            break;
        case Pentamino5D:
            startPentamino5D();
            break;
        case Pentamino5E:
            startPentamino5E();
            break;
        case Pentamino5F:
            startPentamino5F();
            break;
        case Pentamino5G:
            startPentamino5G();
            break;
        case Pentamino5H:
            startPentamino5H();
            break;
        case Pentamino12:
            startPentamino12();
            break;
    }
}

void Game::startPentamino4A()
{
    this->resetGame();
    this->gameActiveGrid = this->grid4;
    this->pentamino2->show();
    this->pentamino4->show();
    this->pentamino5->show();
    this->pentamino8->show();

    this->gameTitle = "Pentanimo 4A";
}

void Game::startPentamino4B()
{
    this->resetGame();
    this->gameActiveGrid = this->grid4;
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino7->show();
    this->pentamino9->show();

    this->gameTitle = "Pentanimo 4B";
}

void Game::startPentamino4C()
{
    this->resetGame();
    this->gameActiveGrid = this->grid4;
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino5->show();
    this->pentamino6->show();

    this->gameTitle = "Pentanimo 4C";
}

void Game::startPentamino4D()
{
    this->resetGame();
    this->gameActiveGrid = this->grid4;
    this->pentamino3->show();
    this->pentamino6->show();
    this->pentamino7->show();
    this->pentamino9->show();

    this->gameTitle = "Pentanimo 4D";
}

void Game::startPentamino4E()
{
    this->resetGame();
    this->gameActiveGrid = this->grid4;
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino6->show();
    this->pentamino8->show();

    this->gameTitle = "Pentanimo 4E";
}

void Game::startPentamino4F()
{
    this->resetGame();
    this->gameActiveGrid = this->grid4;
    this->pentamino2->show();
    this->pentamino6->show();
    this->pentamino7->show();
    this->pentamino9->show();

    this->gameTitle = "Pentanimo 4F";
}

void Game::startPentamino4G()
{
    this->resetGame();
    this->gameActiveGrid = this->grid4;
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino6->show();
    this->pentamino11->show();

    this->gameTitle = "Pentanimo 4G";
}

void Game::startPentamino4H()
{
    this->resetGame();
    this->gameActiveGrid = this->grid4;
    this->pentamino3->show();
    this->pentamino4->show();
    this->pentamino5->show();
    this->pentamino10->show();

    this->gameTitle = "Pentanimo 4H";
}

void Game::startPentamino4I()
{
    this->resetGame();
    this->gameActiveGrid = this->grid4;
    this->pentamino2->show();
    this->pentamino5->show();
    this->pentamino6->show();
    this->pentamino8->show();

    this->gameTitle = "Pentanimo 4I";
}

void Game::startPentamino4J()
{
    this->resetGame();
    this->gameActiveGrid = this->grid4;
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino6->show();
    this->pentamino10->show();

    this->gameTitle = "Pentanimo 4J";
}

void Game::startPentamino4K()
{
    this->resetGame();
    this->gameActiveGrid = this->grid4;
    this->pentamino3->show();
    this->pentamino4->show();
    this->pentamino6->show();
    this->pentamino7->show();

    this->gameTitle = "Pentanimo 4K";
}

void Game::startPentamino4L()
{
    this->resetGame();
    this->gameActiveGrid = this->grid4;
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino5->show();
    this->pentamino7->show();

    this->gameTitle = "Pentanimo 4L";
}

void Game::startPentamino5A()
{
    this->resetGame();
    this->gameActiveGrid = this->grid5;
    this->pentamino2->show();
    this->pentamino4->show();
    this->pentamino5->show();
    this->pentamino7->show();
    this->pentamino8->show();

    this->gameTitle = "Pentanimo 5A";
}

void Game::startPentamino5B()
{
    this->resetGame();
    this->gameActiveGrid = this->grid5;
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino7->show();
    this->pentamino8->show();
    this->pentamino9->show();

    this->gameTitle = "Pentanimo 5B";
}

void Game::startPentamino5C()
{
    this->resetGame();
    this->gameActiveGrid = this->grid5;
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino5->show();
    this->pentamino6->show();
    this->pentamino9->show();

    this->gameTitle = "Pentanimo 5C";
}

void Game::startPentamino5D()
{
    this->resetGame();
    this->gameActiveGrid = this->grid5;
    this->pentamino3->show();
    this->pentamino6->show();
    this->pentamino7->show();
    this->pentamino9->show();
    this->pentamino10->show();

    this->gameTitle = "Pentanimo 5D";
}

void Game::startPentamino5E()
{
    this->resetGame();
    this->gameActiveGrid = this->grid5;
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino6->show();
    this->pentamino8->show();
    this->pentamino11->show();

    this->gameTitle = "Pentanimo 5E";
}

void Game::startPentamino5F()
{
    this->resetGame();
    this->gameActiveGrid = this->grid5;
    this->pentamino2->show();
    this->pentamino6->show();
    this->pentamino7->show();
    this->pentamino9->show();
    this->pentamino12->show();

    this->gameTitle = "Pentanimo 5F";
}

void Game::startPentamino5G()
{
    this->resetGame();
    this->gameActiveGrid = this->grid5;
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino4->show();
    this->pentamino6->show();
    this->pentamino11->show();

    this->gameTitle = "Pentanimo 5G";
}

void Game::startPentamino5H()
{
    this->resetGame();
    this->gameActiveGrid = this->grid5;
    this->pentamino3->show();
    this->pentamino4->show();
    this->pentamino5->show();
    this->pentamino9->show();
    this->pentamino10->show();

    this->gameTitle = "Pentanimo 5H";
}

void Game::startPentamino12()
{
    this->resetGame();
    this->gameActiveGrid = this->grid12;
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

    this->gameTitle = "Pentanimo 12";
}

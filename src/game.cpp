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

Game::Game(int gridPixelSize, Scene *scene)
{
    Q_ASSERT(gridPixelSize > 0);

    this->sceneGridPixelSize = gridPixelSize;
    this->scene = scene;

    // All all grids to the scene
    this->grid4 = this->addGrid(Grid::grid4(this->gridPixelSize(), this->scene));
    this->grid5 = this->addGrid(Grid::grid5(this->gridPixelSize(), this->scene));
    this->grid12 = this->addGrid(Grid::grid12(this->gridPixelSize(), this->scene));

    // Add all standard Pentamino
    this->pentamino1 = this->addPentamino(Pentamino::pentamino1(this->gridPixelSize()));
    this->pentamino2 = this->addPentamino(Pentamino::pentamino2(this->gridPixelSize()));
    this->pentamino3 = this->addPentamino(Pentamino::pentamino3(this->gridPixelSize()));
    this->pentamino4 = this->addPentamino(Pentamino::pentamino4(this->gridPixelSize()));
    this->pentamino5 = this->addPentamino(Pentamino::pentamino5(this->gridPixelSize()));
    this->pentamino6 = this->addPentamino(Pentamino::pentamino6(this->gridPixelSize()));
    this->pentamino7 = this->addPentamino(Pentamino::pentamino7(this->gridPixelSize()));
    this->pentamino8 = this->addPentamino(Pentamino::pentamino8(this->gridPixelSize()));
    this->pentamino9 = this->addPentamino(Pentamino::pentamino9(this->gridPixelSize()));
    this->pentamino10 = this->addPentamino(Pentamino::pentamino10(this->gridPixelSize()));
    this->pentamino11 = this->addPentamino(Pentamino::pentamino11(this->gridPixelSize()));
    this->pentamino12 = this->addPentamino(Pentamino::pentamino12(this->gridPixelSize()));

    foreach(Pentamino *pentamino, this->pentaminos) {
        connect(pentamino, SIGNAL(pentaminoMoved()), this, SLOT(checkStatus()));
    }
}

int Game::gridPixelSize()
{
    return this->sceneGridPixelSize;
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
    if (!collisionDetected && this->scene->activeGrid() != nullptr && this->scene->activeGrid()->isComplete()) {
        emit gameWon();
    }
}

void Game::resetGame()
{
    int gridPixelSize = this->gridPixelSize();

    // @todo: still hardcoded
    this->pentamino1->setPos(QPoint(-145, -105));
    this->pentamino2->setPos(QPoint(-125, -105));
    this->pentamino3->setPos(QPoint(-85, -105));
    this->pentamino4->setPos(QPoint(-55, -105));
    this->pentamino5->setPos(QPoint(-15, -105));
    this->pentamino6->setPos(QPoint(15, -105));
    this->pentamino7->setPos(QPoint(55, -105));
    this->pentamino8->setPos(QPoint(85, -105));
    this->pentamino9->setPos(QPoint(125, -105));
    this->pentamino10->setPos(QPoint(-135, -55));
    this->pentamino11->setPos(QPoint(-95, -55));
    this->pentamino12->setPos(QPoint(-55, -55));

    this->grid4->setPos(QPoint(-gridPixelSize / 2, -gridPixelSize / 2));
    this->grid5->setPos(QPoint(-gridPixelSize / 2, -gridPixelSize / 2));
    this->grid12->setPos(QPoint(-gridPixelSize / 2, -gridPixelSize / 2));

    foreach (Pentamino *pentamino, this->pentaminos) {
        pentamino->reset();
        pentamino->hide();
    }

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
        default:
            return;
    }
}

void Game::startPentamino4A()
{
    this->resetGame();
    this->scene->setActiveGrid(this->grid4);
    this->pentamino2->show();
    this->pentamino4->show();
    this->pentamino5->show();
    this->pentamino8->show();
}

void Game::startPentamino4B()
{
    this->resetGame();
    this->scene->setActiveGrid(this->grid4);
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino7->show();
    this->pentamino9->show();
}

void Game::startPentamino4C()
{
    this->resetGame();
    this->scene->setActiveGrid(this->grid4);
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino5->show();
    this->pentamino6->show();
}

void Game::startPentamino4D()
{
    this->resetGame();
    this->scene->setActiveGrid(this->grid4);
    this->pentamino3->show();
    this->pentamino6->show();
    this->pentamino7->show();
    this->pentamino9->show();
}

void Game::startPentamino4E()
{
    this->resetGame();
    this->scene->setActiveGrid(this->grid4);
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino6->show();
    this->pentamino8->show();
}

void Game::startPentamino4F()
{
    this->resetGame();
    this->scene->setActiveGrid(this->grid4);
    this->pentamino2->show();
    this->pentamino6->show();
    this->pentamino7->show();
    this->pentamino9->show();
}

void Game::startPentamino4G()
{
    this->resetGame();
    this->scene->setActiveGrid(this->grid4);
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino6->show();
    this->pentamino11->show();
}

void Game::startPentamino4H()
{
    this->resetGame();
    this->scene->setActiveGrid(this->grid4);
    this->pentamino3->show();
    this->pentamino4->show();
    this->pentamino5->show();
    this->pentamino10->show();
}

void Game::startPentamino4I()
{
    this->resetGame();
    this->scene->setActiveGrid(this->grid4);
    this->pentamino2->show();
    this->pentamino5->show();
    this->pentamino6->show();
    this->pentamino8->show();
}

void Game::startPentamino4J()
{
    this->resetGame();
    this->scene->setActiveGrid(this->grid4);
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino6->show();
    this->pentamino10->show();
}

void Game::startPentamino4K()
{
    this->resetGame();
    this->scene->setActiveGrid(this->grid4);
    this->pentamino3->show();
    this->pentamino4->show();
    this->pentamino6->show();
    this->pentamino7->show();
}

void Game::startPentamino4L()
{
    this->resetGame();
    this->scene->setActiveGrid(this->grid4);
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino5->show();
    this->pentamino7->show();
}

void Game::startPentamino5A()
{
    this->resetGame();
    this->scene->setActiveGrid(this->grid5);
    this->pentamino2->show();
    this->pentamino4->show();
    this->pentamino5->show();
    this->pentamino7->show();
    this->pentamino8->show();
}

void Game::startPentamino5B()
{
    this->resetGame();
    this->scene->setActiveGrid(this->grid5);
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino7->show();
    this->pentamino8->show();
    this->pentamino9->show();
}

void Game::startPentamino5C()
{
    this->resetGame();
    this->scene->setActiveGrid(this->grid5);
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino5->show();
    this->pentamino6->show();
    this->pentamino9->show();
}

void Game::startPentamino5D()
{
    this->resetGame();
    this->scene->setActiveGrid(this->grid5);
    this->pentamino3->show();
    this->pentamino6->show();
    this->pentamino7->show();
    this->pentamino9->show();
    this->pentamino10->show();
}

void Game::startPentamino5E()
{
    this->resetGame();
    this->scene->setActiveGrid(this->grid5);
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino6->show();
    this->pentamino8->show();
    this->pentamino11->show();
}

void Game::startPentamino5F()
{
    this->resetGame();
    this->scene->setActiveGrid(this->grid5);
    this->pentamino2->show();
    this->pentamino6->show();
    this->pentamino7->show();
    this->pentamino9->show();
    this->pentamino12->show();
}

void Game::startPentamino5G()
{
    this->resetGame();
    this->scene->setActiveGrid(this->grid5);
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino4->show();
    this->pentamino6->show();
    this->pentamino11->show();
}

void Game::startPentamino5H()
{
    this->resetGame();
    this->scene->setActiveGrid(this->grid5);
    this->pentamino3->show();
    this->pentamino4->show();
    this->pentamino5->show();
    this->pentamino9->show();
    this->pentamino10->show();
}

void Game::startPentamino12()
{
    this->resetGame();
    this->scene->setActiveGrid(this->grid12);
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

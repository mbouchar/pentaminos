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

    this->activeGrid = nullptr;

    foreach(Pentamino *pentamino, this->pentaminos) {
        connect(pentamino, SIGNAL(pentaminoMoved()), this, SLOT(checkStatus()));
    }
}

QString Game::getTitle()
{
    return this->title;
}

Grid* Game::getActiveGrid()
{
    return this->activeGrid;
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
    if (!collisionDetected && this->activeGrid != nullptr)
    {
        int gridWith = this->activeGrid->getSize().width();
        int gridHeight = this->activeGrid->getSize().height();

        QPoint gridPos = this->activeGrid->pos();
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
    this->title = "Sélectionnez un pentanimo";
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

void Game::startPentamino4A()
{
    this->resetGame();
    this->activeGrid = this->grid4;
    this->pentamino2->show();
    this->pentamino4->show();
    this->pentamino5->show();
    this->pentamino8->show();

    this->title = "Pentanimo 4A";
}

void Game::startPentamino4B()
{
    this->resetGame();
    this->activeGrid = this->grid4;
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino7->show();
    this->pentamino9->show();

    this->title = "Pentanimo 4B";
}

void Game::startPentamino4C()
{
    this->resetGame();
    this->activeGrid = this->grid4;
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino5->show();
    this->pentamino6->show();

    this->title = "Pentanimo 4C";
}

void Game::startPentamino4D()
{
    this->resetGame();
    this->activeGrid = this->grid4;
    this->pentamino3->show();
    this->pentamino6->show();
    this->pentamino7->show();
    this->pentamino9->show();

    this->title = "Pentanimo 4D";
}

void Game::startPentamino4E()
{
    this->resetGame();
    this->activeGrid = this->grid4;
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino6->show();
    this->pentamino8->show();

    this->title = "Pentanimo 4E";
}

void Game::startPentamino4F()
{
    this->resetGame();
    this->activeGrid = this->grid4;
    this->pentamino2->show();
    this->pentamino6->show();
    this->pentamino7->show();
    this->pentamino9->show();

    this->title = "Pentanimo 4F";
}

void Game::startPentamino4G()
{
    this->resetGame();
    this->activeGrid = this->grid4;
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino6->show();
    this->pentamino11->show();

    this->title = "Pentanimo 4G";
}

void Game::startPentamino4H()
{
    this->resetGame();
    this->activeGrid = this->grid4;
    this->pentamino3->show();
    this->pentamino4->show();
    this->pentamino5->show();
    this->pentamino10->show();

    this->title = "Pentanimo 4H";
}

void Game::startPentamino4I()
{
    this->resetGame();
    this->activeGrid = this->grid4;
    this->pentamino2->show();
    this->pentamino5->show();
    this->pentamino6->show();
    this->pentamino8->show();

    this->title = "Pentanimo 4I";
}

void Game::startPentamino4J()
{
    this->resetGame();
    this->activeGrid = this->grid4;
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino6->show();
    this->pentamino10->show();

    this->title = "Pentanimo 4J";
}

void Game::startPentamino4K()
{
    this->resetGame();
    this->activeGrid = this->grid4;
    this->pentamino3->show();
    this->pentamino4->show();
    this->pentamino6->show();
    this->pentamino7->show();

    this->title = "Pentanimo 4K";
}

void Game::startPentamino4L()
{
    this->resetGame();
    this->activeGrid = this->grid4;
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino5->show();
    this->pentamino7->show();

    this->title = "Pentanimo 4L";
}

void Game::startPentamino5A()
{
    this->resetGame();
    this->activeGrid = this->grid5;
    this->pentamino2->show();
    this->pentamino4->show();
    this->pentamino5->show();
    this->pentamino7->show();
    this->pentamino8->show();

    this->title = "Pentanimo 5A";
}

void Game::startPentamino5B()
{
    this->resetGame();
    this->activeGrid = this->grid5;
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino7->show();
    this->pentamino8->show();
    this->pentamino9->show();

    this->title = "Pentanimo 5B";
}

void Game::startPentamino5C()
{
    this->resetGame();
    this->activeGrid = this->grid5;
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino5->show();
    this->pentamino6->show();
    this->pentamino9->show();

    this->title = "Pentanimo 5C";
}

void Game::startPentamino5D()
{
    this->resetGame();
    this->activeGrid = this->grid5;
    this->pentamino3->show();
    this->pentamino6->show();
    this->pentamino7->show();
    this->pentamino9->show();
    this->pentamino10->show();

    this->title = "Pentanimo 5D";
}

void Game::startPentamino5E()
{
    this->resetGame();
    this->activeGrid = this->grid5;
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino6->show();
    this->pentamino8->show();
    this->pentamino11->show();

    this->title = "Pentanimo 5E";
}

void Game::startPentamino5F()
{
    this->resetGame();
    this->activeGrid = this->grid5;
    this->pentamino2->show();
    this->pentamino6->show();
    this->pentamino7->show();
    this->pentamino9->show();
    this->pentamino12->show();

    this->title = "Pentanimo 5F";
}

void Game::startPentamino5G()
{
    this->resetGame();
    this->activeGrid = this->grid5;
    this->pentamino2->show();
    this->pentamino3->show();
    this->pentamino4->show();
    this->pentamino6->show();
    this->pentamino11->show();

    this->title = "Pentanimo 5G";
}

void Game::startPentamino5H()
{
    this->resetGame();
    this->activeGrid = this->grid5;
    this->pentamino3->show();
    this->pentamino4->show();
    this->pentamino5->show();
    this->pentamino9->show();
    this->pentamino10->show();

    this->title = "Pentanimo 5H";
}

void Game::startPentamino12()
{
    this->resetGame();
    this->activeGrid = this->grid12;
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

    this->title = "Pentanimo 12";
}

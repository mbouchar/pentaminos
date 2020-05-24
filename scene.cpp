#include "scene.h"

#include <QPainter>

Scene::Scene(const QRectF &sceneRect, int gridSize, QObject *parent) :
    QGraphicsScene(sceneRect, parent)
{
    Q_ASSERT(gridSize > 0);
    this->game = nullptr;

    this->setBackgroundBrush(Qt::white);
}

void Scene::setGame(Game *game)
{
    this->game = game;
}

int Scene::getGridSize() const
{
    return this->gridSize;
}

void Scene::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    QPen pen(Qt::gray);

    if (this->game != nullptr)
    {
        Grid *grid = this->game->getActiveGrid();
        if (grid != nullptr)
        {
            grid->draw(painter, pen);
        }
    }

    // Draw title
    QString title = this->game->getTitle();
    if (!title.isEmpty()) {
        QFont font = painter->font();
        font.setPointSize(5);
        painter->setFont(font);
        painter->setPen(pen);
        painter->drawText(QRect(-50, 50, 100, 10), Qt::AlignCenter, title);
    }
}

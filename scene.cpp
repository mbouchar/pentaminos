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

void Scene::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    if (this->game != nullptr)
    {
        Grid *grid = this->game->activeGrid();
        if (grid != nullptr)
        {
            grid->draw(painter, QPen(Qt::gray));
        }
    }

    // Draw title
    QString title = this->game->title();
    if (!title.isEmpty()) {
        QFont font = painter->font();
        font.setPointSize(5);
        painter->setFont(font);
        painter->setPen(QPen(Qt::black));
        painter->drawText(QRect(-50, 50, 100, 10), Qt::AlignCenter, title);
    }
}

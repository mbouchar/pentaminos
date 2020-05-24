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

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
#include "grid.h"
#include <QPainter>

QString Scene::defaultText = "Sélectionnez un pentamino";

Scene::Scene(const QRectF &sceneRect, QObject *parent) :
    QGraphicsScene(sceneRect, parent)
{
    this->gameActiveGrid = nullptr;

    this->setBackgroundBrush(Qt::white);
}

Grid* Scene::activeGrid()
{
    return this->gameActiveGrid;
}

void Scene::setActiveGrid(Grid *grid)
{
    this->gameActiveGrid = grid;
}

void Scene::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    if (this->activeGrid() != nullptr) {
        this->activeGrid()->draw(painter, QPen(Qt::gray));
    } else {
        // Draw default text
        QFont font = painter->font();
        font.setPointSize(5);
        painter->setFont(font);
        painter->setPen(QPen(Qt::black));
        painter->drawText(QRect(-50, 50, 100, 10), Qt::AlignCenter, Scene::defaultText);
    }
}

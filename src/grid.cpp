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

#include "grid.h"

#include <QFont>
#include <QPen>

Grid::Grid(QSize size, int gridPixelSize, Scene *scene)
{
    this->scene = scene;
    this->gridSize = size;
    this->gridPixelSize = gridPixelSize;
}

void Grid::setPos(QPoint pos)
{
    this->position = pos;
}

QPoint Grid::pos()
{
    return this->position;
}

void Grid::draw(QPainter *painter, QPen pen)
{
    int width = this->size().width() * this->gridPixelSize;
    int height = this->size().height() * this->gridPixelSize;

    // Draw rectangle
    painter->setPen(pen);
    painter->drawRect(this->pos().x() - (width / 2), this->pos().y(), width, height);

    // Draw horizontal lines
    for (int i = 1; i < this->size().height(); i++) {
        painter->drawLine(this->pos().x() - (width / 2), this->pos().y() + i * this->gridPixelSize, this->pos().x() + (width / 2), this->pos().y() + i * this->gridPixelSize);
    }
    // Draw vertical lines
    for (int i = 1; i < this->size().width(); i++) {
        painter->drawLine(this->pos().x() + i * this->gridPixelSize - (width / 2), this->pos().y(), this->pos().x() + i * this->gridPixelSize - (width / 2), this->pos().y() + height);
    }
}

bool Grid::isComplete()
{
    int gridWith = this->size().width();
    int gridHeight = this->size().height();

    QTransform transform;

    for (int x = 0; x < gridWith; x++)
    {
        for (int y = 0; y < gridHeight; y++)
        {
            int xPos = (x * this->gridPixelSize) + this->pos().x() + (this->gridPixelSize / 2) - (gridWith * this->gridPixelSize / 2);
            int yPos = (y * this->gridPixelSize) + this->pos().y() + (this->gridPixelSize / 2);

            // A case doesn't have any piece
            if (this->scene->itemAt(xPos, yPos, transform) == 0)
            {
                return false;
            }
        }
    }

    // All cases are filled
    return true;
}

QSize Grid::size()
{
    return this->gridSize;
}

Grid* Grid::grid4(int gridPixelSize, Scene *scene)
{
    return new Grid(QSize(4, 5), gridPixelSize, scene);
}

Grid* Grid::grid5(int gridPixelSize, Scene *scene)
{
    return new Grid(QSize(5, 5), gridPixelSize, scene);
}

Grid* Grid::grid12(int gridPixelSize, Scene *scene)
{
    return new Grid(QSize(12, 5), gridPixelSize, scene);
}

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

Grid::Grid(QSize size)
{
    this->gridSize = size;
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
    // Draw rectangle
    painter->setPen(pen);
    painter->drawRect(this->position.x(), this->position.y(), this->size().width() * 10, this->size().height() * 10);

    // Draw horizontal lines
    for (int i = 1; i < this->size().height(); i++) {
        painter->drawLine(this->position.x(), this->position.y() + i * 10, this->position.x() + this->size().width() * 10, this->position.y() + i * 10);
    }
    // Draw vertical lines
    for (int i = 1; i < this->size().width(); i++) {
        painter->drawLine(this->position.x() + i * 10, this->position.y(), this->position.x() + i * 10, this->position.y() + this->size().height() * 10);
    }
}

QSize Grid::size()
{
    return this->gridSize;
}

Grid* Grid::grid4()
{
    return new Grid(QSize(4, 5));
}

Grid* Grid::grid5()
{
    return new Grid(QSize(5, 5));
}

Grid* Grid::grid12()
{
    return new Grid(QSize(12, 5));
}

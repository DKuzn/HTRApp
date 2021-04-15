// paintscene.cpp
//
// Copyright 2021 Дмитрий Кузнецов
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "paintscene.h"

PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent) {

}

PaintScene::~PaintScene() = default;

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    addEllipse(event->scenePos().x() - 5,
               event->scenePos().y() - 5,
               5,
               5,
               QPen(Qt::NoPen),
               QBrush(Qt::black));

    previousPoint = event->scenePos();
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    addLine(previousPoint.x(),
            previousPoint.y(),
            event->scenePos().x(),
            event->scenePos().y(),
            QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap));

    previousPoint = event->scenePos();
}

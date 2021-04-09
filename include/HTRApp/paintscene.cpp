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

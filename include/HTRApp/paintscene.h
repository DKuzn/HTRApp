#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>


class PaintScene : public QGraphicsScene {
Q_OBJECT

public:
    explicit PaintScene(QObject *parent = nullptr);

    ~PaintScene() override;

private:
    QPointF previousPoint;

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

};

#endif // PAINTSCENE_H

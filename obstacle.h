#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <QRectF>
#include <QPixmap>
#include <QDebug>

class Obstacle
{
private:
    QRectF top;
    QRectF bottom;
public:
    Obstacle();
    Obstacle(QRect top, QRect bottom, QPixmap px, int type=0, bool box=false, int boxType=0);
    QPixmap px;
    bool approved;
    bool hasBox;
    int dir;
    int type;
    int boxType;
    double opacity;
    QRectF getTop();
    QRectF getBottom();
    QRectF train;
    QRectF train2;
    QRectF box;
    void moveBy(double x,double y);
};

#endif // OBSTACLE_H

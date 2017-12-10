#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <QRectF>
#include <QPixmap>
#include <QVector>
#include <QDebug>

class Obstacle
{
private:
    QRectF top;
    QRectF bottom;
public:
    Obstacle();
    Obstacle(QRect top, QRect bottom, int type=0, bool box=false, int boxType=0);
    QPixmap px;
    bool approved;
    bool hasBox;
    bool del;
    int dir;
    int type;
    int boxType;
    int am;
    int am2;
    QVector <int> nums;
    QVector <int> nums2;
    double opacity;
    QRectF getTop();
    QRectF getBottom();
    QRectF train;
    QRectF train2;
    QRectF box;
    void moveBy(double x,double y, double speed=0.5);
};

#endif // OBSTACLE_H

#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <QRect>

class Obstacle
{
private:
    QRectF top;
    QRectF bottom;
public:
    Obstacle();
    Obstacle(QRect top,QRect bottom, int type=0);
    bool approved;
    int type;
    QRectF getTop();
    QRectF getBottom();
    void moveBy(double x,double y);
};

#endif // OBSTACLE_H

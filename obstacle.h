#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <QRect>
#include <QPixmap>

class Obstacle
{
private:
    QRectF top;
    QRectF bottom;
public:
    Obstacle();
    Obstacle(QRect top, QRect bottom, QPixmap px, int type=0);
    QPixmap px;
    bool approved;
    int type;
    QRectF getTop();
    QRectF getBottom();
    void moveBy(double x,double y);
};

#endif // OBSTACLE_H

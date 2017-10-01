#ifndef PLAYER_H
#define PLAYER_H
#include <QRect>

class Player
{
private:
    QRectF rect;
    double velD;
    int benis;
public:
    Player(QRectF rect);
    void setPos(int x, int y);
    void setVelD(double velD);
    void setBenis(int benis);
    int getBenis();
    double getVelD();
    QRectF getRect();
};

#endif // PLAYER_H

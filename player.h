#ifndef PLAYER_H
#define PLAYER_H
#include <QRect>
#include <QPixmap>
#include <QDebug>

class Player
{
private:
    QRectF rect;
    double velD;
    int benis;
    QPixmap g0;
    QPixmap g1;
    QPixmap g2;
public:
    Player(QRectF rect);
    int an;
    bool dir;
    double tilt;
    bool tdir;
    double tstep;
    QPixmap getPx();
    void setPos(int x, int y);
    void setVelD(double velD);
    void setBenis(int benis);
    int getBenis();
    double getVelD();
    QRectF getRect();
};

#endif // PLAYER_H

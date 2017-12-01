#ifndef PLAYER_H
#define PLAYER_H
#include <QRect>
#include <QPolygonF>
#include <QPixmap>
#include <QDebug>

class Player
{
private:
    QRectF rect;
    double velD;
    int benis;
public:
    Player(QRectF rect);
    QPixmap g0;
    QPixmap g1;
    QPixmap g2;
    int an;
    int coins;
    bool dir;
    double tilt;
    bool tdir;
    double tstep;
    QPixmap getPx();
    void setPos(double x, double y);
    void setVelD(double velD);
    void setBenis(int benis);
    void reload(int id);
    int getBenis();
    double getVelD();
    QRectF getRect();
    QPolygonF getPoly();
};

#endif // PLAYER_H

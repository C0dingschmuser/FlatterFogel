#ifndef PLAYER_H
#define PLAYER_H
#include <QRect>
#include <QPolygonF>
#include <QPixmap>
#include <QVector>
#include <QDebug>

class Player
{
private:
    QRectF rect;
    QRectF collRect;
    double velD;
    unsigned long long benis;
public:
    Player(QRectF rect);
    QPixmap g0;
    QPixmap g1;
    QPixmap g2;
    int an;
    int coins;
    bool dir;
    bool circle;
    bool hasAn;
    bool fin;
    double tilt;
    bool tdir;
    double tstep;
    QPixmap getPx();
    void setPos(double x, double y);
    void setVelD(double velD);
    void setBenis(unsigned long long benis);
    void setCollRect(int offX, int offY, int offW, int offH);
    void reload(int id);
    unsigned long long getBenis();
    double getVelD();
    QRectF getRect();
    QRectF getCollRect();
    QPolygonF getPoly();
};

#endif // PLAYER_H

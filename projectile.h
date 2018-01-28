#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <QRectF>
#include <QtMath>

class Projectile
{
public:
    Projectile();
    Projectile(QRectF r, double angle, double speed, int damage);
    void move();
    QRectF r;
    double angle;
    double vx;
    double vy;
    double speed;
    int damage;
    bool del;
};

#endif // PROJECTILE_H

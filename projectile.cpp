#include "projectile.h"

Projectile::Projectile()
{

}

Projectile::Projectile(QRectF r, double angle, double speed, int damage)
{
    this->r = r;
    this->angle = angle;
    this->speed = speed;
    this->damage = damage;
    del = false;
    vx = qCos(qDegreesToRadians((double)angle))*2;
    vy = qSin(qDegreesToRadians((double)angle))*2;
}

void Projectile::move()
{
    r.moveTo(r.x()+(vx*speed),r.y()+(vy*speed));
}

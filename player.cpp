#include "player.h"

Player::Player(QRectF rect)
{
    this->rect = rect;
    velD = 0;
    benis = 10000;
}

void Player::setPos(int x, int y)
{
    rect.moveTo(x,y);
}

void Player::setVelD(double velD)
{
    this->velD = velD;
}

void Player::setBenis(int benis)
{
    this->benis = benis;
}

int Player::getBenis()
{
    return benis;
}

double Player::getVelD()
{
    return velD;
}

QRectF Player::getRect()
{
    return rect;
}

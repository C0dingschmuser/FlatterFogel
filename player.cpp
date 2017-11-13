#include "player.h"

Player::Player(QRectF rect)
{
    this->rect = rect;
    velD = 0;
    benis = 10000;
    coins = 0;
    g0 = QPixmap(":/images/player/gondola0.png");
    g1 = QPixmap(":/images/player/gondola1.png");
    g2 = QPixmap(":/images/player/gondola2.png");
    an = 0;
    dir = 0; //unten
    tilt = 45;
    tdir = 0;
    tstep = 1;
}

QPixmap Player::getPx()
{
    switch(an) {
        case 0:
            return g0;
        break;
        case 1:
            return g1;
        break;
        case 2:
            return g2;
        break;
    }
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

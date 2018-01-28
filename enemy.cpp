#include "enemy.h"

Enemy::Enemy()
{

}

Enemy::Enemy(QRect rect, int type, int hp)
{
    this->rect = rect;
    this->type = type;
    this->hp = hp;
    this->maxhp = hp;
    showhp = 0;
    prehp = hp;
    opacity = 1;
    dead = false;
}

void Enemy::moveTo(int x, int y)
{
    rect.moveTo(x,y);
}

#ifndef ENEMY_H
#define ENEMY_H
#include <QRect>

class Enemy
{
private:

public:
    Enemy();
    Enemy(QRect rect, int type, int hp=100);
    void moveTo(int x, int y);
    QRect rect;
    int type;
    int hp;
    int prehp;
    int maxhp;
    int showhp;
    bool dead;
    double opacity;
};

#endif // ENEMY_H

#ifndef SHOP_H
#define SHOP_H

#include <QObject>
#include <QPixmap>
#include <QFont>
#include <QVector>
#include <QPainter>
#include "player.h"

class Shop : public QObject
{
    Q_OBJECT
private:
    Player *player;
    bool active;
    QPixmap background;
    QPixmap item1;
    QPixmap item2;
    QPixmap btn;
    QPixmap sel;
    int selected;
    QFont font;
public:
    explicit Shop(Player *player,QFont font,QObject *parent = nullptr);
    int item1Count;
    int item2Count;
    int multiplier;
    int tapMultiplier;
    int speedLvl;
    int mMax;
    int tMax;
    void load(int ic1,int ic2);
    void draw(QPainter &painter);
    void setActive(bool active);
    bool getActive();
    void mousePress(QPoint pos);
    QPixmap getPixmap(int item);

signals:
    void back();
    void msg(QString msg);
    void buy(int am);
public slots:
};

#endif // SHOP_H

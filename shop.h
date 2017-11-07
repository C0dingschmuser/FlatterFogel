#ifndef SHOP_H
#define SHOP_H

#include <QObject>
#include <QPixmap>
#include <QFont>
#include <QVector>
#include <QPainter>
#include "player.h"
#include "translation.h"

class Shop : public QObject
{
    Q_OBJECT
private:
    Player *player;
    bool active;
    QPixmap item1;
    QPixmap item2;
    QPixmap item3;
    QPixmap item4;
    QPixmap btn;
    QPixmap sel;
    int selected;
    QFont font;
    Translation* transl;
public:
    explicit Shop(Player *player,QFont font,Translation *transl,QObject *parent = nullptr);
    QPixmap background;
    int item1Count;
    int item2Count;
    int item3Count;
    int item4Count;
    int multiplier;
    int tapMultiplier;
    int speedLvl;
    int mMax;
    int tMax;
    void load(int ic1,int ic2, int ic3, int ic4);
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

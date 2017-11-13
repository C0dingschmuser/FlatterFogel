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
    QPixmap btnInfoPx;
    QPixmap coinPx;
    int selected;
    int page;
    QFont font;
    Translation* transl;
    void drawSkin(int x, int y, int w, int h, int num, QPainter &painter);
public:
    explicit Shop(Player *player,QFont font,Translation *transl,QPixmap coinPx, QObject *parent = nullptr);
    QPixmap background;
    QPixmap g2;
    int item1Count;
    int item2Count;
    int item3Count;
    int item4Count;
    int item1Price;
    int item2Price;
    int item3Price;
    int item4Price;
    int multiplier;
    int tapMultiplier;
    int speedLvl;
    int mMax;
    int tMax;
    int chosenSkin;
    int shopX;
    QVector <int> skinPrice;
    QVector <int> ownedSkins;
    void load(int ic1,int ic2, int ic3, int ic4);
    void draw(QPainter &painter);
    void setActive(bool active);
    bool getActive();
    void mousePress(QPoint pos);
    QString skinsToString();
    QPixmap getPixmap(int item);
    QVector <QPixmap> skins;

signals:
    void back();
    void msg(QString msg);
    void buy(int am, bool bu=true, bool co=false);
public slots:
};

#endif // SHOP_H

#ifndef SHOP_H
#define SHOP_H

#include <QObject>
#include <QPixmap>
#include <QFont>
#include <QVector>
#include <QPainter>
#include "player.h"
#include "translation.h"
#include "background.h"

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
    QPixmap btnShop;
    QPixmap btnInfoPx;
    QPixmap btnChangePx;
    QPixmap btnPowPx;
    QPixmap btnBGPx;
    QPixmap btnSkinsPx;
    QPixmap coinPx;
    QPixmap itemBcPx;
    QPixmap cloudPx;
    int selected;
    int page;
    QFont font;
    Translation* transl;
    void drawSkin(int x, int y, int w, int h, int num, QPainter &painter);
    void drawBg(int x, int y, int w, int h, int num, QPainter &painter);
public:
    explicit Shop(Player *player,QFont font,Translation *transl,QPixmap coinPx, QPixmap cloudPx, QObject *parent = nullptr);
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
    int chosenBackground;
    int shopX;
    QVector <int> skinPrice;
    QVector <int> bgPrice;
    QVector <int> ownedSkins;
    QVector <Background*> backgrounds;
    QVector <int> ownedbackgrounds;
    void load(int ic1,int ic2, int ic3, int ic4);
    void draw(QPainter &painter);
    void setActive(bool active);
    bool getActive();
    void mousePress(QPoint pos, bool &cave);
    QString skinsToString();
    QString bgsToString();
    QPixmap getPixmap(int item);
    QVector <QPixmap> skins;

signals:
    void back();
    void msg(QString msg);
    void buy(int am, bool bu=true, bool co=false);
public slots:
};

#endif // SHOP_H

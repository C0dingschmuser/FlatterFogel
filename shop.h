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
    QPixmap btnPipePx;
    QPixmap btnTailPx;
    QPixmap coinPx;
    QPixmap itemBcPx;
    QPixmap cloudPx;
    int selected;
    int page;
    QFont font;
    Translation* transl;
    void drawSkin(int x, int y, int w, int h, int num, QPainter &painter);
    void drawBg(int x, int y, int w, int h, int num, QPainter &painter);
    void drawPipe(int x, int y, int w, int h, int num, QPainter &painter);
    void drawTail(int x, int y, int w, int h, int num, QPainter &painter);
public:
    explicit Shop(Player *player,QFont font,Translation *transl,QPixmap coinPx, QPixmap cloudPx, QObject *parent = nullptr);
    QPixmap background;
    QPixmap g2;
    int item1Count;
    int item2Count;
    int item3Count;
    int item4Count;
    unsigned int item1Price;
    unsigned int item2Price;
    unsigned int item3Price;
    unsigned int item4Price;
    int multiplier;
    int tapMultiplier;
    int speedLvl;
    unsigned long mMax;
    unsigned long tMax;
    int chosenSkin;
    int chosenBackground;
    int chosenPipe;
    int chosenTail;
    int shopX;
    int yOffset;
    QVector <int> skinPrice;
    QVector <int> bgPrice;
    QVector <int> pipePrice;
    QVector <int> tailPrice;
    QVector <int> ownedSkins;
    QVector <Background*> backgrounds;
    QVector <int> ownedbackgrounds;
    QVector <int> ownedPipes;
    QVector <int> ownedTails;
    void load(int ic1,int ic2, int ic3, int ic4);
    void draw(QPainter &painter);
    void setActive(bool active);
    bool getActive();
    void mousePress(QPoint pos, bool &cave);
    void setSkin(int num);
    QString skinsToString();
    QString bgsToString();
    QString pipesToString();
    QString tailsToString();
    QPixmap getPixmap(int item);
    QVector <QPixmap> skins;
    QVector <QPixmap> pipes;
    QVector <QPixmap> tails;

signals:
    void back();
    void msg(QString msg);
    void buy(int am, bool bu=true, bool co=false, bool mid=false);
public slots:
};

#endif // SHOP_H

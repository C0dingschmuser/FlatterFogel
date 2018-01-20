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
    uint selected;
    int page;
    int skinpage;
    int bgpage;
    QFont font;
    Translation* transl;
    void drawSkin(int x, int y, int w, int h, uint num, QPainter &painter);
    void drawBg(int x, int y, int w, int h, uint num, QPainter &painter);
    void drawPipe(int x, int y, int w, int h, uint num, QPainter &painter);
    void drawTail(int x, int y, int w, int h, uint num, QPainter &painter);
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
    uint chosenSkin;
    uint chosenBackground;
    uint chosenPipe;
    uint chosenTail;
    int shopX;
    int yOffset;
    QVector <int> skinPrice;
    QVector <int> bgPrice;
    QVector <int> pipePrice;
    QVector <int> tailPrice;
    std::vector <int> ownedSkins;
    std::vector <Background*> backgrounds;
    std::vector <int> ownedbackgrounds;
    std::vector <int> ownedPipes;
    std::vector <int> ownedTails;
    void load(int ic1,int ic2, int ic3, int ic4);
    void draw(QPainter &painter, int rgb_red, int rgb_green, int rgb_blue, QColor textColor);
    void setActive(bool active);
    bool getActive();
    bool checkDonatorItem(int num, int type);
    void mousePress(QPoint pos, bool &cave, bool &space, bool &flip, bool &underwater);
    void setSkin(int num);
    QString skinsToString();
    QString bgsToString();
    QString pipesToString();
    QString tailsToString();
    QString getItemCount(int num);
    QPixmap getPixmap(int item);
    std::vector <QPixmap> skins;
    std::vector <QPixmap> pipes;
    std::vector <QPixmap> tails;
    bool vContains(std::vector<int> v, int value);
signals:
    void back();
    void msg(QString msg);
    void buy(int am, bool bu=true, bool co=false, bool mid=false);
public slots:
};

#endif // SHOP_H

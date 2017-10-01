#include "shop.h"

Shop::Shop(Player *player,QObject *parent) : QObject(parent)
{
    active = false;
    this->player = player;
    this->item1 = QPixmap(":/images/items/item1.png");
    this->item2 = QPixmap(":/images/items/item2.png");
    background = QPixmap(":/images/shopM.png");
    btn = QPixmap(":/images/button.png");
    sel = QPixmap(":/images/sel.png");
    selected = 0;
    item1Count = 2;
    item2Count = 2;
    multiplier = 10;
    tapMultiplier = 1;
    speedLvl = 1;
    mMax = multiplier*500+(((multiplier-10)*2500)*2);
    tMax = tapMultiplier*5000+((tapMultiplier*5000)*2);
}

void Shop::load(int ic1, int ic2)
{
    item1Count = ic1;
    item2Count = ic2;
    mMax = multiplier*500+(((multiplier-10)*2500)*2);
    tMax = tapMultiplier*5000+((tapMultiplier*5000)*2);
}

void Shop::draw(QPainter &painter)
{
    QFont f("Arial");
    f.setBold(true);
    f.setPixelSize(110);
    painter.setFont(f);
    painter.drawPixmap(165,460,750,1000,background);
    painter.drawPixmap(200,490,200,200,item1);
    painter.drawPixmap(200,790,200,200,item2);
    painter.setPen(QColor(0,143,255));
    painter.drawText(470,640,QString::number(multiplier)+"x");
    painter.drawText(700,640,QString::number(tapMultiplier)+"x");
    painter.setPen(Qt::NoPen);
    painter.drawPixmap(609,1304,300,150,btn);
    painter.drawPixmap(169,1304,300,150,btn);
    f.setPixelSize(70);
    painter.setFont(f);
    painter.setPen(QColor(108,67,43));
    painter.drawText(640,1405,"Kaufen");
    painter.drawText(195,1405,"Zurück");
    f.setPixelSize(30);
    painter.setFont(f);
    painter.setPen(Qt::white);
    painter.drawText(210,720,"B 5000 ("+QString::number(item1Count)+"x)");
    painter.drawText(480,720,"B "+QString::number(mMax));
    painter.drawText(710,720,"B "+QString::number(tMax));
    painter.drawText(210,1020,"B 5000 ("+QString::number(item2Count)+"x)");
    switch(selected) {
        case 1:
            painter.drawPixmap(200,490,30,30,sel);
            f.setPixelSize(40);
            painter.setFont(f);
            painter.drawText(35,1600,"Wenn aktiviert hast du für 30 Sekunden 1 extra Leben");
        break;
        case 2:
            painter.drawPixmap(470,490,30,30,sel);
            f.setPixelSize(40);
            painter.setFont(f);
            painter.drawText(35,1600,"Erhöht den Benismultiplikator (Hindernisse & Gegner)");
        break;
        case 3:
            painter.drawPixmap(700,490,30,30,sel);
            f.setPixelSize(40);
            painter.setFont(f);
            painter.drawText(65,1600,"Erhöht den Benismultiplikator (Benis pro Touch)");
        break;
        case 4:
            painter.drawPixmap(200,790,30,30,sel);
            f.setPixelSize(40);
            painter.setFont(f);
            painter.drawText(130,1600,"Kann für einen Schnellstart benutzt werden");
        break;
    }
}

void Shop::setActive(bool active)
{
    if(!active) selected = 0;
    this->active = active;
}

bool Shop::getActive()
{
    return active;
}

void Shop::mousePress(QPoint pos)
{
    QRect r(pos.x(),pos.y(),1,1);
    if(r.intersects(QRect(169,1304,300,150))) {
        emit back();
    }
    if(r.intersects(QRect(200,490,200,200))) {
        selected = 1;
    } else if(r.intersects(QRect(470,490,200,200))) {
        selected = 2;
    } else if(r.intersects(QRect(700,490,200,200))) {
        selected = 3;
    } else if(r.intersects(QRect(200,790,200,200))) {
        selected = 4;
    }
    if(r.intersects(QRect(609,1304,300,150))) {
        if(!selected) {
            emit msg("Wähle zuerst etwas zum kaufen aus!");
            return;
        }
        switch(selected) {
            case 1: //revive
                if(player->getBenis()<5000) {
                    emit msg("Du hast nicht genug Benis!");
                } else {
                    player->setBenis(player->getBenis()-5000);
                    item1Count++;
                    emit buy(5000);
                }
            break;
            case 2: //multiplier
                mMax = multiplier*500+(((multiplier-10)*2500)*2);
                if(player->getBenis()<mMax) {
                    emit msg("Du hast nicht genug Benis!");
                } else {
                    player->setBenis(player->getBenis()-mMax);
                    multiplier+=1;
                    mMax = multiplier*500+(((multiplier-10)*2500)*2);
                    emit buy(mMax);
                }
            break;
            case 3: //tap multiplier
                tMax = tapMultiplier*5000+((tapMultiplier*5000)*2);
                if(player->getBenis()<tMax) {
                    emit msg("Du hast nicht genug Benis!");
                } else {
                    player->setBenis(player->getBenis()-tMax);
                    tapMultiplier+=1;
                    tMax = tapMultiplier*5000+((tapMultiplier*5000)*2);
                    emit buy(tMax);
                }
            break;
            case 4:
                if(player->getBenis()<5000) {
                    emit msg("Du hast nicht genug Benis!");
                } else {
                    player->setBenis(player->getBenis()-5000);
                    item2Count++;
                    emit buy(5000);
                }
            break;
        }
    }
}

QPixmap Shop::getPixmap(int item)
{
    switch(item) {
        case 1:
            return item1;
        break;
        case 2:
            return item2;
        break;
    }
}

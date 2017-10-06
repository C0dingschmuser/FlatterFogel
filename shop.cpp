#include "shop.h"

Shop::Shop(Player *player, QFont font, Translation *transl, QObject *parent) : QObject(parent)
{
    this->transl = transl;
    active = false;
    this->player = player;
    this->font = font;
    this->item1 = QPixmap(":/images/items/item1.png");
    this->item2 = QPixmap(":/images/items/item2.png");
    this->item3 = QPixmap(":/images/items/item3.png");
    background = QPixmap(":/images/shopM.png");
    btn = QPixmap(":/images/button.png");
    sel = QPixmap(":/images/sel.png");
    selected = 0;
    item1Count = 2;
    item2Count = 2;
    item3Count = 0;
    multiplier = 10;
    tapMultiplier = 1;
    speedLvl = 1;
    mMax = multiplier*500+(((multiplier-10)*2500)*2);
    tMax = tapMultiplier*5000+((tapMultiplier*5000)*2);
}

void Shop::load(int ic1, int ic2, int ic3)
{
    item1Count = ic1;
    item2Count = ic2;
    item3Count = ic3;
    mMax = multiplier*500+(((multiplier-10)*2500)*2);
    tMax = tapMultiplier*5000+((tapMultiplier*5000)*2);
}

void Shop::draw(QPainter &painter)
{
    QFont f = font;
    f.setPixelSize(72);
    painter.setFont(f);
    painter.drawPixmap(165,460,750,1000,background);
    painter.drawPixmap(200,790,200,200,item1);
    painter.drawPixmap(200,1090,200,200,item2);
    painter.drawPixmap(470,790,200,200,item3);
    painter.setPen(QColor(0,143,255));
    painter.drawText(200,640,QString::number(multiplier)+"x");
    painter.drawText(460,640,QString::number(tapMultiplier)+"x"); //710 3
    painter.setPen(Qt::NoPen);
    painter.drawPixmap(609,1324,300,130,btn);
    painter.drawPixmap(169,1324,300,130,btn);
    Text back = transl->getBtn_Shop_Back();
    Text buy = transl->getBtn_Shop_Buy();
    f.setPixelSize(buy.size);
    painter.setFont(f);
    painter.setPen(QColor(0,143,255));
    painter.drawText(buy.pos,buy.text);
    f.setPixelSize(back.size);
    painter.drawText(back.pos,back.text);
    f.setPixelSize(22);
    painter.setFont(f);
    painter.setPen(Qt::white);
    painter.drawText(210,1020,"B 4000("+QString::number(item1Count)+"x)");
    painter.drawText(220,720,"B "+QString::number(mMax));
    painter.drawText(470,720,"B "+QString::number(tMax));
    painter.drawText(210,1320,"B 5000("+QString::number(item2Count)+"x)");
    painter.drawText(470,1020,"B 7500("+QString::number(item3Count)+"x)");
    Text selText;
    switch(selected) {
        case 1:
            painter.drawPixmap(200,490,30,30,sel);
            selText = transl->getText_Shop_MP1();
            f.setPixelSize(selText.size);
            painter.setFont(f);
            painter.drawText(selText.pos,selText.text);
        break;
        case 2:
            painter.drawPixmap(470,490,30,30,sel);
            selText = transl->getText_Shop_MP2();
            f.setPixelSize(selText.size);
            painter.setFont(f);
            painter.drawText(selText.pos,selText.text);
        break;
        case 4:
            painter.drawPixmap(200,790,30,30,sel);
            selText = transl->getText_Shop_Item1();
            f.setPixelSize(selText.size);
            painter.setFont(f);
            painter.drawText(selText.pos,selText.text);
        break;
        case 5:
            painter.drawPixmap(470,790,30,30,sel);
            painter.setPen(Qt::red);
            selText = transl->getText_Shop_Item3();
            f.setPixelSize(selText.size);
            painter.setFont(f);
            painter.drawText(selText.pos,selText.text);
        break;
        case 7:
            painter.drawPixmap(200,1090,30,30,sel);
            selText = transl->getText_Shop_Item2();
            f.setPixelSize(selText.size);
            painter.setFont(f);
            painter.drawText(selText.pos,selText.text);
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
        //selected = 3;
    } else if(r.intersects(QRect(200,790,200,200))) {
        selected = 4;
    } else if(r.intersects(QRect(470,790,200,200))) {
        selected = 5;
    } else if(r.intersects(QRect(700,790,200,200))) {
        selected = 6;
    } else if(r.intersects(QRect(200,1090,200,200))) {
        selected = 7;
    }
    if(r.intersects(QRect(609,1304,300,150))) {
        if(!selected) {
            emit msg(transl->getText_Shop_NotSelected().text);
            return;
        }
        switch(selected) {
            case 1: //mp
                mMax = multiplier*500+(((multiplier-10)*2500)*2);
                if(player->getBenis()<mMax) {
                    emit msg(transl->getText_Shop_NotEnough().text);
                } else {
                    player->setBenis(player->getBenis()-mMax);
                    multiplier+=1;
                    mMax = multiplier*500+(((multiplier-10)*2500)*2);
                    emit buy(mMax);
                }
            break;
            case 2: //tmp
                tMax = tapMultiplier*5000+((tapMultiplier*5000)*2);
                if(player->getBenis()<tMax) {
                    emit msg(transl->getText_Shop_NotEnough().text);
                } else {
                    player->setBenis(player->getBenis()-tMax);
                    tapMultiplier+=1;
                    tMax = tapMultiplier*5000+((tapMultiplier*5000)*2);
                    emit buy(tMax);
                }
            break;
            case 4: //revive
                if(player->getBenis()<4000) {
                    emit msg(transl->getText_Shop_NotEnough().text);
                } else {
                    player->setBenis(player->getBenis()-4000);
                    item1Count++;
                    emit buy(4000);
                }
            break;
            case 5: //reviveL
                if(player->getBenis()<7500) {
                    emit msg(transl->getText_Shop_NotEnough().text);
                } else {
                    player->setBenis(player->getBenis()-7500);
                    item3Count++;
                    emit buy(7500);
                }
            break;
            case 7: //speed
                if(player->getBenis()<5000) {
                    emit msg(transl->getText_Shop_NotEnough().text);
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
    QPixmap p;
    switch(item) {
        case 1:
            p = item1;
        break;
        case 2:
            p = item2;
        break;
        case 3:
            p = item3;
        break;

    }
    return p;
}

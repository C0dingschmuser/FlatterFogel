#include "shop.h"

void Shop::drawSkin(int x, int y, int w, int h, int num, QPainter &painter)
{
    if(selected!=num+1) painter.setOpacity(0.4);
    painter.setPen(Qt::NoPen);
    painter.drawPixmap(x,y,w,h,skins[num]);
    if(selected!=num+1) {
        painter.drawPixmap(x,y,w,h,g2);
    } else {
        painter.drawPixmap(x,y,w,h,player->getPx());
    }
    painter.setPen(Qt::white);
    painter.setOpacity(1);
    if(!ownedSkins.contains(num)) {
        painter.drawText(x+45,y+140,QString::number(skinPrice[num]));
        painter.drawPixmap(x,y+95,42,42,coinPx);
    }
}

Shop::Shop(Player *player, QFont font, Translation *transl, QPixmap coinPx, QObject *parent) : QObject(parent)
{
    shopX = -1080;
    ownedSkins.insert(0,0);
    this->transl = transl;
    active = false;
    this->player = player;
    this->font = font;
    this->coinPx = coinPx;
    this->item1 = QPixmap(":/images/items/item1.png");
    this->item2 = QPixmap(":/images/items/item2.png");
    this->item3 = QPixmap(":/images/items/item3.png");
    this->item4 = QPixmap(":/images/items/item4.png");
    background = QPixmap(":/images/shopM.png");
    btn = QPixmap(":/images/button.png");
    btnInfoPx = QPixmap(":/images/btnInfo.png");
    selected = 0;
    item1Count = 2;
    item2Count = 2;
    item3Count = 0;
    item4Count = 0;
    item1Price = 3000;
    item2Price = 4000;
    item3Price = 7500;
    item4Price = 7500;
    skinPrice.append(0);
    skinPrice.append(99);
    skinPrice.append(1);
    skinPrice.append(1);
    skinPrice.append(1);
    skinPrice.append(1);
    skinPrice.append(1);
    skinPrice.append(1);
    skinPrice.append(1);
    skinPrice.append(1);
    chosenSkin = 1;
    multiplier = 10;
    page = 0;
    tapMultiplier = 1;
    speedLvl = 1;
    mMax = multiplier*500+(((multiplier-10)*2500)*2);
    tMax = tapMultiplier*500+((tapMultiplier*1000)*2);
}

void Shop::load(int ic1, int ic2, int ic3, int ic4)
{
    item1Count = ic1;
    item2Count = ic2;
    item3Count = ic3;
    item4Count = ic4;
    mMax = multiplier*500+(((multiplier-10)*2500)*2);
    tMax = tapMultiplier*500+((tapMultiplier*1000)*2);
}

void Shop::draw(QPainter &painter)
{
    QFont f = font;
    painter.drawPixmap(shopX+165,460,750,1130,background);
    painter.setBrush(QColor(238,77,46));
    painter.setOpacity(0.5);
    painter.setPen(Qt::NoPen);
    Text selText;
    if(!page) {
        switch(selected) {
            case 1:
                painter.drawEllipse(shopX+200,490,200,200);
            break;
            case 2:
                painter.drawEllipse(shopX+470,490,200,200);
            break;
            case 4:
                painter.drawEllipse(shopX+200,790,200,200);
            break;
            case 5:
                painter.drawEllipse(shopX+470,790,200,200);
            break;
            case 7:
                painter.drawEllipse(shopX+200,1090,200,200);
            break;
            case 8:
                painter.drawEllipse(shopX+470,1090,200,200);
            break;
        }
    }
    painter.setOpacity(1);
    if(selected) {
        f.setPixelSize(30);
        painter.setFont(f);
        painter.setPen(QColor(238,77,48));
        painter.drawText(shopX+100,1691,"Drücke auf 'i' für mehr Infos");
    }
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255,153,0));
    painter.drawRect(shopX+190,1454,720,120);
    painter.drawRect(shopX+609,1350,300,230);
    painter.drawRect(shopX+169,1350,300,140);
    painter.drawPixmap(shopX+609,1324,300,130,btn); //buy
    painter.drawPixmap(shopX+609,1454,300,130,btn); //sell
    painter.drawPixmap(shopX+169,1454,300,130,btn); //back
    painter.drawPixmap(shopX+469,1454,140,130,btnInfoPx); //info
    painter.drawPixmap(shopX+169,1324,300,130,btn); //skins
    Text back = transl->getBtn_Shop_Back();
    Text buy = transl->getBtn_Shop_Buy();
    Text sell = transl->getBtn_Shop_Sell();
    f.setPixelSize(buy.size);
    painter.setFont(f);
    painter.setPen(QColor(0,143,255));
    painter.drawText(QPoint(shopX+buy.pos.x(),buy.pos.y()),buy.text);
    f.setPixelSize(sell.size);
    painter.setFont(f);
    painter.setPen(QColor(0,143,255));
    painter.drawText(QPoint(shopX+sell.pos.x(),sell.pos.y()),sell.text);
    f.setPixelSize(back.size);
    painter.setFont(f);
    painter.drawText(QPoint(shopX+back.pos.x(),back.pos.y()),back.text);
    if(!page) {
        f.setPixelSize(72);
        painter.setFont(f);
        painter.setPen(Qt::NoPen);
        painter.drawPixmap(shopX+200,790,200,200,item1);
        painter.drawPixmap(shopX+200,1090,200,200,item2);
        painter.drawPixmap(shopX+470,790,200,200,item3);
        painter.drawPixmap(shopX+470,1090,200,200,item4);
        painter.setPen(QColor(0,143,255));
        painter.drawText(shopX+200,640,QString::number(multiplier)+"x");
        painter.drawText(shopX+460,640,QString::number(tapMultiplier)+"x"); //710 3
        f.setPixelSize(22);
        painter.setFont(f);
        painter.setPen(Qt::white);
        painter.drawText(shopX+210,1020,"B "+QString::number(item1Price)+"("+QString::number(item1Count)+"x)");
        painter.drawText(shopX+220,720,"B "+QString::number(mMax));
        painter.drawText(shopX+470,720,"B "+QString::number(tMax));
        painter.drawText(shopX+210,1320,"B "+QString::number(item2Price)+"("+QString::number(item2Count)+"x)");
        painter.drawText(shopX+470,1020,"B "+QString::number(item3Price)+"("+QString::number(item3Count)+"x)");
        painter.drawText(shopX+470,1320,"B "+QString::number(item4Price)+"("+QString::number(item4Count)+"x)");
        painter.setPen(QColor(0,143,255));
        f.setPixelSize(42);
        painter.setFont(f);
        painter.drawText(shopX+220,1415,"Skins");
    } else {
        painter.setPen(Qt::NoPen);
        drawSkin(shopX+200,500,100,100,0,painter);
        drawSkin(shopX+350,500,100,100,1,painter);
        drawSkin(shopX+500,500,100,100,2,painter);
        drawSkin(shopX+650,500,100,100,3,painter);
        drawSkin(shopX+200,650,100,100,4,painter);
        drawSkin(shopX+350,650,100,100,5,painter);
        drawSkin(shopX+500,650,100,100,6,painter);
        drawSkin(shopX+650,650,100,100,7,painter);
        drawSkin(shopX+200,800,100,100,8,painter);
        drawSkin(shopX+350,800,100,100,9,painter);
        painter.setPen(QColor(0,143,255));
        f.setPixelSize(35);
        painter.setFont(f);
        painter.drawText(shopX+182,1407,"Powerups");
    }
}

void Shop::setActive(bool active)
{
    if(!active) selected = 0;
    this->active = active;
    if(active&&page) {
        selected = chosenSkin;
    }
}

bool Shop::getActive()
{
    return active;
}

void Shop::mousePress(QPoint pos)
{
    QRect r(pos.x(),pos.y(),1,1);
    if(shopX!=0) return;
    if(r.intersects(QRect(169,1454,300,130))) {
        if(page) {
            if(ownedSkins.contains(selected-1)) {
                chosenSkin = selected;
            } else {
                chosenSkin = 1;
            }
        }
        emit back();
    }
    if(!page) {
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
           //selected = 6;
        } else if(r.intersects(QRect(200,1090,200,200))) {
            selected = 7;
        } else if(r.intersects(QRect(470,1090,200,200))) {
            selected = 8;
        }
    } else {
        if(r.intersects(QRect(200,500,100,100))) {
            selected = 1;
        } else if(r.intersects(QRect(350,500,100,100))) {
            selected = 2;
        } else if(r.intersects(QRect(500,500,100,100))) {
            selected = 3;
        } else if(r.intersects(QRect(650,500,100,100))) {
            selected = 4;
        } else if(r.intersects(QRect(200,650,100,100))) {
            selected = 5;
        } else if(r.intersects(QRect(350,650,100,100))) {
            selected = 6;
        } else if(r.intersects(QRect(500,650,100,100))) {
            selected = 7;
        } else if(r.intersects(QRect(650,650,100,100))) {
            selected = 8;
        } else if(r.intersects(QRect(200,800,100,100))) {
            selected = 9;
        } else if(r.intersects(QRect(350,800,100,100))) {
            selected = 10;
        }
    }
    if(r.intersects(QRect(609,1304,300,150))) { //buy
        if(!selected) {
            emit msg(transl->getText_Shop_NotSelected().text);
            return;
        }
        if(!page) {
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
                    tMax = tapMultiplier*500+((tapMultiplier*1000)*2);
                    if(player->getBenis()<tMax) {
                        emit msg(transl->getText_Shop_NotEnough().text);
                    } else {
                        player->setBenis(player->getBenis()-tMax);
                        tapMultiplier+=1;
                        tMax = tapMultiplier*500+((tapMultiplier*1000)*2);
                        emit buy(tMax);
                    }
                break;
                case 4: //revive
                    if(player->getBenis()<item1Price) {
                        emit msg(transl->getText_Shop_NotEnough().text);
                    } else {
                        player->setBenis(player->getBenis()-item1Price);
                        item1Count++;
                        emit buy(item1Price);
                    }
                break;
                case 5: //reviveL
                    if(player->getBenis()<item3Price) {
                        emit msg(transl->getText_Shop_NotEnough().text);
                    } else {
                        player->setBenis(player->getBenis()-item3Price);
                        item3Count++;
                        emit buy(item3Price);
                    }
                break;
                case 7: //speed
                    if(player->getBenis()<item2Price) {
                        emit msg(transl->getText_Shop_NotEnough().text);
                    } else {
                        player->setBenis(player->getBenis()-item2Price);
                        item2Count++;
                        emit buy(item2Price);
                    }
                break;
                case 8: //speed+
                    if(player->getBenis()<item4Price) {
                        emit msg(transl->getText_Shop_NotEnough().text);
                    } else {
                        player->setBenis(player->getBenis()-item4Price);
                        item4Count++;
                        emit buy(item4Price);
                    }
                break;
            }
        } else {
            int coins = player->coins;
            int price = skinPrice[selected-1];
            if(coins<price) {
                emit msg(transl->getText_Shop_NotEnough("Coins").text);
            } else {
                coins-=price;
                ownedSkins.append(selected-1);
                player->coins = coins;
                emit buy(1,true,true);
            }
        }
    } else if(r.intersects(QRect(609,1454,300,130))) { //sell
        if(page) {
            emit msg(transl->getText_Shop_NoSell().text);
            return;
        }
        if(!selected) {
            emit msg(transl->getText_Shop_NotSelected().text);
            return;
        }
        switch(selected) {
            case 4: //revive
                if(item1Count) {
                    item1Count--;
                    player->setBenis(player->getBenis()+(item1Price/2));
                    emit buy(item1Price/2,false);
                } else {
                    emit msg(transl->getText_Shop_NotEnough("Items").text);
                }
            break;
            case 5: //reviveL
                if(item3Count) {
                    item3Count--;
                    player->setBenis(player->getBenis()+(item3Price/2));
                    emit buy(item3Price/2,false);
                } else {
                    emit msg(transl->getText_Shop_NotEnough("Items").text);
                }
            break;
            case 7: //speed
                if(item2Count) {
                    item2Count--;
                    player->setBenis(player->getBenis()+(item2Price/2));
                    emit buy(item2Price/2,false);
                } else {
                    emit msg(transl->getText_Shop_NotEnough("Items").text);
                }
            break;
            case 8: //speed+
                if(item4Count) {
                    item4Count--;
                    player->setBenis(player->getBenis()+(item4Price/2));
                    emit buy(item4Price/2,false);
                } else {
                    emit msg(transl->getText_Shop_NotEnough("Items").text);
                }
            break;
        }
    } else if(r.intersects(QRect(469,1454,140,130))) {
        Text t;
        if(!page) {
            switch(selected) {
            case 1:
                emit msg(transl->getText_Shop_MP1().text);
                break;
            case 2:
                emit msg(transl->getText_Shop_MP2().text);
                break;
            case 4:
                emit msg(transl->getText_Shop_Item1().text);
                break;
            case 5:
                emit msg(transl->getText_Shop_Item3().text);
                break;
            case 7:
                emit msg(transl->getText_Shop_Item2().text);
                break;
            case 8:
                emit msg(transl->getText_Shop_Item4().text);
                break;
            }
        } else {
            emit msg(transl->getText_Shop_Skin().text);
        }
    } else if(r.intersects(QRect(169,1324,300,130))) {
        if(page) {
            chosenSkin = selected;
            selected = 0;
            page = 0;
        } else {
            selected = chosenSkin;
            page = 1;
        }
    }
}

QString Shop::skinsToString()
{
    QString s;
    for(int i=1;i<ownedSkins.size();i++) {
        s.append(QString::number(ownedSkins[i])+"~");
    }
    return s;
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
        case 4:
            p = item4;
        break;

    }
    return p;
}

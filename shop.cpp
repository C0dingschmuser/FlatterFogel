#include "shop.h"

Shop::Shop(Player *player, QFont font, Translation *transl, QPixmap coinPx, QPixmap cloudPx, QObject *parent) : QObject(parent)
{
    shopX = -1080;
    ownedSkins.insert(0,0);
    ownedbackgrounds.insert(0,0);
    ownedPipes.insert(0,0);
    ownedTails.insert(0,0);
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
    btn = QPixmap(":/images/buttons/button.png");
    btnShop = QPixmap(":/images/buttons/buttonShop.png");
    btnInfoPx = QPixmap(":/images/buttons/btnInfo.png");
    btnSkinsPx = QPixmap(":/images/buttons/btnSkins.png");
    btnPowPx = QPixmap(":/images/buttons/btnPow.png");
    btnBGPx = QPixmap(":/images/buttons/btnBG.png");
    btnChangePx = QPixmap(":/images/buttons/btnChange.png");
    btnPipePx = QPixmap(":/images/buttons/btnPipe.png");
    btnTailPx = QPixmap(":/images/buttons/btnTail.png");
    itemBcPx = QPixmap(":/images/items/item_bc.png");
    this->cloudPx = cloudPx;
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
    skinPrice.append(1);
    skinPrice.append(1);
    skinPrice.append(2);
    skinPrice.append(2);
    skinPrice.append(2);
    skinPrice.append(2);
    skinPrice.append(2);
    skinPrice.append(2);
    skinPrice.append(3);
    skinPrice.append(3);
    skinPrice.append(3);
    skinPrice.append(3);
    skinPrice.append(3);
    skinPrice.append(99);
    bgPrice.append(0);
    bgPrice.append(1);
    bgPrice.append(1);
    bgPrice.append(2);
    bgPrice.append(99);
    pipePrice.append(0);
    pipePrice.append(2);
    pipePrice.append(1);
    pipePrice.append(1);
    pipePrice.append(1);
    pipePrice.append(1);
    pipePrice.append(1);
    pipePrice.append(1);
    pipePrice.append(99);
    pipePrice.append(3);
    pipePrice.append(2);
    tailPrice.append(0);
    tailPrice.append(1);
    tailPrice.append(1);
    tailPrice.append(2);
    tailPrice.append(2);
    tailPrice.append(1);
    setSkin(1);
    chosenBackground = 1;
    chosenPipe = 1;
    chosenTail = 1;
    multiplier = 10;
    page = 0;
    tapMultiplier = 1;
    speedLvl = 1;
    yOffset = 70;
    mMax = multiplier*500+(((multiplier-10)*2500)*2);
    tMax = tapMultiplier*500+((tapMultiplier*1000)*2);
}

void Shop::drawSkin(int x, int y, int w, int h, int num, QPainter &painter)
{
    if(selected!=num+1) painter.setOpacity(0.4);
    painter.setPen(Qt::NoPen);
    if(num!=21) {
        painter.drawPixmap(x,y,w,h,skins[num]);
    }
    if(selected!=num+1) {
        bool ok=false;
        if(skinPrice[num]>1) {
            player->reload(num);
            ok=true;
        }
        if(num!=18&&num!=22) painter.drawPixmap(x,y,w,h,player->g2);
        if(ok) {
            player->reload(1);
        }
    } else {
        bool ok=false;
        if(skinPrice[num]>1) {
            player->reload(num);
            ok=true;
        }
        painter.drawPixmap(x,y,w,h,player->getPx());
        if(ok) {
            player->reload(1);
        }
    }
    painter.setPen(Qt::white);
    painter.setOpacity(1);
    if(!ownedSkins.contains(num)) {
        painter.drawText(x+45,y+140,QString::number(skinPrice[num]));
        painter.drawPixmap(x,y+95,42,42,coinPx);
    }
}

void Shop::drawPipe(int x, int y, int w, int h, int num, QPainter &painter)
{
    if(selected!=num+1) painter.setOpacity(0.4);
    painter.setPen(Qt::NoPen);
    painter.drawPixmap(x,y,w,h,pipes[num]);
    painter.setPen(Qt::white);
    if(!ownedPipes.contains(num)) {
        painter.drawText(x+45,y+140,QString::number(pipePrice[num]));
        painter.drawPixmap(x,y+95,42,42,coinPx);
    }
    painter.setOpacity(1);
}

void Shop::drawTail(int x, int y, int w, int h, int num, QPainter &painter)
{
    if(selected!=num+1) painter.setOpacity(0.4);
    painter.setPen(Qt::NoPen);
    painter.drawPixmap(x,y,w,h,tails[num]);
    painter.setPen(Qt::white);
    if(!ownedTails.contains(num)) {
        painter.drawText(x+45,y+140,QString::number(tailPrice[num]));
        painter.drawPixmap(x,y+95,42,42,coinPx);
    }
    painter.setOpacity(1);
}

void Shop::drawBg(int x, int y, int w, int h, int num, QPainter &painter)
{
    painter.setPen(Qt::NoPen);
    if(selected!=num+1) {
        painter.setOpacity(0.4);
    } else {
        painter.setBrush(Qt::blue);
        painter.drawRect(x-2,y-2,w+4,h+4);
    }
    if(!backgrounds[num]->p) {
        painter.drawPixmap(x,y,w,h,backgrounds[num]->background);
    } else {
        painter.drawPixmap(x,y,w,h,backgrounds[num]->backgroundP);
    }
    if(backgrounds[num]->cloud) {
        painter.drawPixmap(x,y+70,w,32,cloudPx);
    }
    painter.setPen(Qt::white);
    painter.setOpacity(1);
    if(!ownedbackgrounds.contains(num)) {
        painter.drawText(x+45,y+240,QString::number(bgPrice[num]));
        painter.drawPixmap(x,y+195,42,42,coinPx);
    }
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

void Shop::draw(QPainter &painter, int rgb_red, int rgb_green, int rgb_blue)
{
    QFont f = font;
    painter.drawPixmap(shopX+165,460,750,1200,background);
    painter.setBrush(QColor(238,77,46));
    painter.setOpacity(0.5);
    painter.setPen(Qt::NoPen);
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
    if(page!=0&&page!=-1) painter.setOpacity(0.4);
    painter.drawRect(shopX+169,1394,300,130);
    painter.drawPixmap(shopX+169,1394,300,130,btn); //sell
    painter.setOpacity(1);
    painter.drawRect(shopX+469,1394,300,130);
    painter.drawPixmap(shopX+469,1394,300,130,btnShop); //buy
    painter.drawPixmap(shopX+169,1520,300,130,btn); //back
    if(page!=-1) painter.setOpacity(0.4);
    painter.drawPixmap(shopX+769,544+yOffset,140,130,btnChangePx); //change
    painter.setOpacity(1);
    if(page!=0) painter.setOpacity(0.4);
    painter.drawPixmap(shopX+769,674+yOffset,140,130,btnPowPx); //powerups
    painter.setOpacity(1);
    if(page!=1) painter.setOpacity(0.4);
    painter.drawPixmap(shopX+769,934+yOffset,140,130,btnSkinsPx); //skins
    painter.setOpacity(1);
    if(page!=2) painter.setOpacity(0.4);
    painter.drawPixmap(shopX+769,1064+yOffset,140,130,btnBGPx); //bg
    painter.setOpacity(1);
    if(page!=3) painter.setOpacity(0.4);
    painter.drawPixmap(shopX+769,804+yOffset,140,130,btnPipePx); //pipe
    painter.setOpacity(1);
    if(page!=4) painter.setOpacity(0.4);
    painter.drawPixmap(shopX+769,1194+yOffset,140,130,btnTailPx); //tail
    painter.setOpacity(1);
    painter.drawPixmap(shopX+769,1324+yOffset,140,130,btnInfoPx); //info
    Text back = transl->getBtn_Shop_Back();
    Text buy = transl->getBtn_Shop_Buy();
    Text sell = transl->getBtn_Shop_Sell();
    f.setPixelSize(buy.size);
    painter.setFont(f);
    painter.setPen(QColor(0,143,255));
    painter.drawText(QRect(shopX+469,1394,300,130),Qt::AlignCenter,buy.text);
    f.setPixelSize(sell.size);
    painter.setFont(f);
    painter.setPen(QColor(0,143,255));
    painter.drawText(QRect(shopX+169,1394,300,130),Qt::AlignCenter,sell.text);
    f.setPixelSize(back.size);
    painter.setFont(f);
    painter.drawText(QRect(shopX+169,1520,300,130),Qt::AlignCenter,back.text);
    switch(page) {
    case -1:
        painter.drawPixmap(shopX+200,500,400,400,itemBcPx);
        f.setPixelSize(72);
        painter.setFont(f);
        painter.setPen(Qt::white);
        painter.drawText(shopX+200,910,"300k B");
        /*f.setPixelSize(32);
        painter.setFont(f);
        painter.drawText(100,1200,"Coin "+transl->getText_Shop_BC().text+" Benis: 100k");*/
        break;
    case 0:
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
        break;
    case 1:
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
        drawSkin(shopX+500,800,100,100,10,painter);
        drawSkin(shopX+650,800,100,100,11,painter);
        drawSkin(shopX+200,950,100,100,12,painter);
        drawSkin(shopX+350,950,100,100,13,painter);
        drawSkin(shopX+500,950,100,100,14,painter);
        drawSkin(shopX+650,950,100,100,15,painter);
        drawSkin(shopX+200,1100,100,100,16,painter);
        drawSkin(shopX+350,1100,100,100,17,painter);
        drawSkin(shopX+500,1100,100,100,18,painter);
        drawSkin(shopX+650,1100,100,100,19,painter);
        drawSkin(shopX+200,1250,100,100,20,painter);
        drawSkin(shopX+350,1250,100,100,21,painter);
        drawSkin(shopX+500,1250,100,100,22,painter);
        drawSkin(shopX+650,1250,100,100,23,painter);
        break;
    case 2:
        drawBg(shopX+200,500,124,190,0,painter);
        drawBg(shopX+350,500,124,190,1,painter);
        drawBg(shopX+500,500,124,190,2,painter);
        drawBg(shopX+200,750,124,190,3,painter);
        drawBg(shopX+350,750,124,190,4,painter);
        break;
    case 3:
        drawPipe(shopX+200,500,100,100,0,painter);
        drawPipe(shopX+350,500,100,100,1,painter);
        drawPipe(shopX+500,500,100,100,2,painter);
        drawPipe(shopX+650,500,100,100,3,painter);
        drawPipe(shopX+200,650,100,100,4,painter);
        drawPipe(shopX+350,650,100,100,5,painter);
        drawPipe(shopX+500,650,100,100,6,painter);
        drawPipe(shopX+650,650,100,100,7,painter);
        drawPipe(shopX+200,800,100,100,8,painter);
        drawPipe(shopX+350,800,100,100,9,painter);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(rgb_red,rgb_green,rgb_blue,100));
        painter.drawRect(shopX+350,800,100,100);
        drawPipe(shopX+500,800,100,100,10,painter);
        break;
    case 4:
        drawTail(shopX+200,500,100,100,0,painter);
        drawTail(shopX+350,500,100,100,1,painter);
        drawTail(shopX+500,500,100,100,2,painter);
        drawTail(shopX+650,500,100,100,3,painter);
        drawTail(shopX+200,650,100,100,4,painter);
        drawTail(shopX+350,650,100,100,5,painter);
        break;
    }
}

void Shop::setActive(bool active)
{
    if(!active) selected = 0;
    this->active = active;
    if(active) {
        switch(page) {
        case 1:
            selected = chosenSkin;
            break;
        case 2:
            selected = chosenBackground;
            break;
        case 3:
            selected = chosenPipe;
            break;
        case 4:
            selected = chosenTail;
            break;
        }
    }
}

bool Shop::getActive()
{
    return active;
}

void Shop::mousePress(QPoint pos, bool &cave)
{
    QRect r(pos.x(),pos.y(),1,1);
    if(shopX!=0) return;
    if(r.intersects(QRect(169,1520,300,130))) {
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
        switch(page) {
        case 1: //skins
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
                } else if(r.intersects(QRect(500,800,100,100))) {
                    selected = 11;
                } else if(r.intersects(QRect(650,800,100,100))) {
                    selected = 12;
                } else if(r.intersects(QRect(200,950,100,100))) {
                    selected = 13;
                } else if(r.intersects(QRect(350,950,100,100))) {
                    selected = 14;
                } else if(r.intersects(QRect(500,950,100,100))) {
                    selected = 15;
                } else if(r.intersects(QRect(650,950,100,100))) {
                    selected = 16;
                } else if(r.intersects(QRect(200,1100,100,100))) {
                    selected = 17;
                } else if(r.intersects(QRect(350,1100,100,100))) {
                    selected = 18;
                } else if(r.intersects(QRect(500,1100,100,100))) {
                    selected = 19;
                } else if(r.intersects(QRect(650,1100,100,100))) {
                    selected = 20;
                } else if(r.intersects(QRect(200,1250,100,100))) {
                    selected = 21;
                } else if(r.intersects(QRect(350,1250,100,100))) {
                    selected = 22;
                } else if(r.intersects(QRect(500,1250,100,100))) {
                    selected = 23;
                } else if(r.intersects(QRect(650,1250,100,100))) {
                    selected = 24;
                }
                //if(skinPrice[selected-1]>1) player->reload(selected-1);
                if(ownedSkins.contains(selected-1)) {
                    setSkin(selected);
                }
            break;
        case 2://bgs
                if(r.intersects(QRect(200,500,124,190))) {
                    selected = 1;
                } else if(r.intersects(QRect(350,500,124,190))) {
                    selected = 2;
                } else if(r.intersects(QRect(500,500,124,190))) {
                    selected = 3;
                } else if(r.intersects(QRect(200,750,124,190))) {
                    selected = 4;
                } else if(r.intersects(QRect(350,750,124,190))) {
                    selected = 5;
                }
                if(ownedbackgrounds.contains(selected-1)) {
                    chosenBackground = selected;
                    if(chosenBackground==4) {
                        cave = true;
                    } else {
                        cave = false;
                    }
                }
            break;
        case 3: //pipeskins
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
                } else if(r.intersects(QRect(500,800,100,100))) {
                    selected = 11;
                }
                if(ownedPipes.contains(selected-1)) {
                    chosenPipe = selected;
                }
            break;
        case 4: //tailskins
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
            }
            if(ownedTails.contains(selected-1)) {
                chosenTail = selected;
            }
            break;
        }
    }
    if(r.intersects(QRect(469,1394,300,130))) { //buy
        if(!selected&&page!=-1) {
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
            switch(page) {
            case -1:
                {
                    int b = player->getBenis();
                    if(b<300000) {
                        emit msg(transl->getText_Shop_NotEnough().text);
                    } else {
                        b-=300000;
                        player->coins++;
                        player->setBenis(b);
                        emit buy(300000);
                    }
                    break;
                }
            case 1:
                {
                    int price = skinPrice[selected-1];
                    if(coins<price) {
                        emit msg(transl->getText_Shop_NotEnough("Coins").text);
                    } else if(!ownedSkins.contains(selected-1)) {
                        coins-=price;
                        ownedSkins.append(selected-1);
                        setSkin(selected);
                        player->coins = coins;
                        emit buy(price,true,true);
                    }
                    break;
                }
            case 2:
                {
                    int price = bgPrice[selected-1];
                    if(coins<price) {
                        emit msg(transl->getText_Shop_NotEnough("Coins").text);
                    } else if(!ownedbackgrounds.contains(selected-1)){
                        coins-=price;
                        ownedbackgrounds.append(selected-1);
                        chosenBackground = selected;
                        player->coins = coins;
                        emit buy(price,true,true);
                    }
                    break;
                }
            case 3:
                {
                int price = pipePrice[selected-1];
                if(coins<price) {
                    emit msg(transl->getText_Shop_NotEnough("Coins").text);
                } else if(!ownedPipes.contains(selected-1)) {
                    coins-=price;
                    ownedPipes.append(selected-1);
                    chosenPipe = selected;
                    player->coins = coins;
                    emit buy(price,true,true);
                }
                break;
                }
            case 4:
                {
                int price = tailPrice[selected-1];
                if(coins<price) {
                    emit msg(transl->getText_Shop_NotEnough("Coins").text);
                } else if(!ownedTails.contains(selected-1)) {
                    coins-=price;
                    ownedTails.append(selected-1);
                    chosenTail = selected;
                    player->coins = coins;
                    emit buy(price,true,true);
                }
                break;
                }
            }
        }
    } else if(r.intersects(QRect(169,1394,300,130))) { //sell
        if(page&&page!=-1) {
            return;
        }
        if(!selected&&page!=-1) {
            emit msg(transl->getText_Shop_NotSelected().text);
            return;
        }
        if(page==-1) {
            int c = player->coins;
            if(!c) {
                emit msg(transl->getText_Shop_NotEnough("Coins").text);
            } else {
                c--;
                player->setBenis(player->getBenis()+150000);
                player->coins = c;
                emit buy(1,true,true);
            }
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
    } else if(r.intersects(QRect(769,1324+yOffset,140,130))) { //info
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
            switch(page) {
            case 1:
                emit msg(transl->getText_Shop_Skin().text);
                break;
            case 2:
                emit msg(transl->getText_Shop_Background().text);
                break;
            }
        }
    } else if(r.intersects(QRect(769,950+yOffset,140,130))) { //btnSkins
        if(page!=1) {
            selected = chosenSkin;
        }
        page = 1;
        /*if(page) {
            chosenSkin = selected;
            selected = 0;
            page = 0;
        } else {
            selected = chosenSkin;
            page = 1;
        }*/
    } else if(r.intersects(QRect(769,674+yOffset,140,130))) { //btnPow
        page = 0;
    } else if(r.intersects(QRect(769,1064+yOffset,140,130))) { //btnbg
        if(page!=2) {
            selected = chosenBackground;
        }
        page = 2;
    } else if(r.intersects(QRect(769,825+yOffset,140,130))) { //btnpipe
        if(page!=3) selected = chosenPipe;
        page = 3;
    } else if(r.intersects(QRect(769,1194+yOffset,140,130))) { //btntail
        if(page!=4) selected = chosenTail;
        page = 4;
    } else if(r.intersects(QRect(769,544+yOffset,140,130))) { //change
        page = -1;
    }
}

void Shop::setSkin(int num)
{
    //if(num<13) {
    player->circle = true;
    player->setCollRect(0,0,0,0);
    if(num==15) {
        player->circle = false;
    }
    if(num==14||num==15||num==17||num==18) {
        player->hasAn = false;
    } else {
        player->hasAn = true;
    }
    /*} else {
        player->circle = false;
        int offX;
        int offY;
        int offW;
        int offH;
        switch(num) {
            case 13:
                offX=0;
                offY=8;
                offW=0;
                offH=-13;
            break;
            case 14:
                offX=0;
            break;
        }
    }*/
    chosenSkin = num;
}

QString Shop::skinsToString()
{
    QString s;
    for(int i=1;i<ownedSkins.size();i++) {
        s.append(QString::number(ownedSkins[i])+"~");
    }
    return s;
}

QString Shop::bgsToString()
{
    QString s;
    for(int i=1;i<ownedbackgrounds.size();i++) {
        s.append(QString::number(ownedbackgrounds[i])+"~");
    }
    return s;
}

QString Shop::pipesToString()
{
    QString s;
    for(int i=1;i<ownedPipes.size();i++) {
        s.append(QString::number(ownedPipes[i])+"~");
    }
    return s;
}

QString Shop::tailsToString()
{
    QString s;
    for(int i=1;i<ownedTails.size();i++) {
        s.append(QString::number(ownedTails[i])+"~");
    }
    return s;
}

QString Shop::getItemCount(int num)
{
    int count = 0;
    switch(num) {
    case 1:
        count = item1Count;
        break;
    case 2:
        count = item2Count;
        break;
    case 3:
        count = item3Count;
        break;
    case 4:
        count = item4Count;
        break;
    }
    if(count>99) count = 99;
    QString string = QString::number(count);
    if(count<10) string.insert(0,"0");
    return string;
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

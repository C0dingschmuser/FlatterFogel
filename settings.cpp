#include "settings.h"

Settings::Settings(QPixmap *background, QPixmap *btnPx, Translation *transl, QObject *parent) : QObject(parent)
{
    settingsX = -1080;
    this->background = *background;
    this->btnPx = *btnPx;
    this->transl = transl;
    active = false;
}

void Settings::draw(QPainter &painter, QColor textColor)
{
    painter.drawPixmap(settingsX+50,460,980,1200,background);
    painter.drawPixmap(settingsX+58,1520,300,130,btnPx); //back
    if(!music) painter.setOpacity(0.4);
    painter.drawPixmap(QRect(settingsX+66,478,948,100),btnPx); //musik
    if(!soundEffects) {
        painter.setOpacity(0.4);
    } else {
        painter.setOpacity(1);
    }
    painter.drawPixmap(QRect(settingsX+66,578,948,100),btnPx); //soundEffects
    if(lowGraphics) {
        painter.setOpacity(0.4);
    } else {
        painter.setOpacity(1);
    }
    painter.drawPixmap(QRect(settingsX+66,678,948,100),btnPx); //grafik
    painter.setOpacity(1);
    Text back = transl->getBtn_Shop_Back();
    QFont f = painter.font();
    f.setPixelSize(back.size);
    painter.setFont(f);
    painter.setPen(textColor);
    f.setPixelSize(32);
    if(!music) painter.setOpacity(0.4);
    painter.drawText(QRect(settingsX+66,478,948,100),Qt::AlignCenter,"Musik");
    if(!soundEffects) {
        painter.setOpacity(0.4);
    } else {
        painter.setOpacity(1);
    }
    painter.drawText(QRect(settingsX+66,578,948,100),Qt::AlignCenter,"Toneffekte");
    if(lowGraphics) {
        painter.setOpacity(0.4);
    } else {
        painter.setOpacity(1);
    }
    painter.drawText(QRect(settingsX+66,678,948,100),Qt::AlignCenter,"Animationen");
    painter.setOpacity(1);
    painter.drawText(QRect(settingsX+58,1520,300,130),Qt::AlignCenter,back.text);
}

void Settings::mousePress(int x, int y, bool &music, bool &soundEffects, bool &lowGraphics)
{
    QRect pos(x,y,1,1);
    if(pos.intersects(QRect(58,1520,300,130))) { //zurück
        emit back();
    } else if(pos.intersects(QRect(66,478,948,100))) {//musik
        if(music) {
            music = false;
        } else {
            music = true;
        }
        this->music = music;
        emit play();
    } else if(pos.intersects(QRect(66,578,948,100))) {//soundEffects
        if(soundEffects) {
            soundEffects = false;
        } else {
            soundEffects = true;
        }
        this->soundEffects = soundEffects;
    } else if(pos.intersects(QRect(66,678,948,100))) {//grafik
        if(lowGraphics) {
            lowGraphics = false;
        } else {
            lowGraphics = true;
        }
        this->lowGraphics = lowGraphics;
    }
}

#include "settings.h"

void Settings::changeFPS(FPSMode newFps)
{
    fps = newFps;

    emit updateFPS(newFps);
}

Settings::Settings(QPixmap *background, QPixmap *btnPx, Translation *transl, Scoreboard *scoreboard, NetworkManager *network, QObject *parent) : QObject(parent)
{
    settingsX = -1080;
    this->background = *background;
    this->btnPx = *btnPx;
    this->transl = transl;
    this->scoreboard = scoreboard;
    this->network = network;
    active = false;
}

void Settings::draw(QPainter &painter, QColor textColor, int &schmuserEnemy)
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
    painter.drawPixmap(QRect(settingsX+66,678,948,100),btnPx); //animationen
    if(!schmuserEnemy) {
        painter.setOpacity(0.4);
    } else {
        painter.setOpacity(1);
    }
    painter.drawPixmap(QRect(settingsX+66,778,474,100),btnPx); //schmuser
    if(schmuserEnemy) {
        painter.setOpacity(0.4);
    } else {
        painter.setOpacity(1);
    }
    painter.drawPixmap(QRect(settingsX+540,778,474,100),btnPx); //mieser
    painter.setOpacity(1);

    for(int i = 0; i < 4; i++) {

        int num = 30 + 30 * i;

        if((int)fps == num) {
            painter.setOpacity(1);
        } else {
            painter.setOpacity(0.5);
        }

        painter.drawPixmap(QRect(settingsX+66+(238 * i),978,238,100),btnPx); //animationen
    }

    painter.setOpacity(1);
    painter.drawPixmap(QRect(settingsX+66,1378,948,100),btnPx);

    Text back = transl->getBtn_Shop_Back();
    QFont f = painter.font();
    f.setPixelSize(back.size);
    painter.setFont(f);
    painter.setPen(textColor);
    f.setPixelSize(32);
    if(!music) painter.setOpacity(0.4);
    painter.drawText(QRect(settingsX+66,478,948,100),Qt::AlignCenter,transl->getText_Options_Music().text);
    if(!soundEffects) {
        painter.setOpacity(0.4);
    } else {
        painter.setOpacity(1);
    }
    painter.drawText(QRect(settingsX+66,578,948,100),Qt::AlignCenter,transl->getText_Options_SoundEffects().text);
    if(lowGraphics) {
        painter.setOpacity(0.4);
    } else {
        painter.setOpacity(1);
    }
    painter.drawText(QRect(settingsX+66,678,948,100),Qt::AlignCenter,transl->getText_Options_Animations().text);
    if(!schmuserEnemy) {
        painter.setOpacity(0.4);
    } else {
        painter.setOpacity(1);
    }
    painter.drawText(QRect(settingsX+66,778,474,100),Qt::AlignCenter,transl->gettext_Options_Schmuser().text); //schmuser
    if(schmuserEnemy) {
        painter.setOpacity(0.4);
    } else {
        painter.setOpacity(1);
    }
    painter.drawText(QRect(settingsX+540,778,474,100),Qt::AlignCenter,transl->getText_Options_Mieser().text); //mieser

    painter.setOpacity(1);
    painter.drawText(QRect(settingsX+66,878,948,100),Qt::AlignCenter,transl->getText_Options_FPS().text); //fps anzeigetext

    for(int i = 0; i < 4; i++) {
        int num = 30 + 30 * i;

        if((int)fps == num) {
            painter.setOpacity(1);
        } else {
            painter.setOpacity(0.5);
        }

        painter.drawText(QRect(settingsX+66+(238 * i),978,238,100),Qt::AlignCenter,QString::number(num)); //FPS-Zahl
    }

    painter.setOpacity(1);
    painter.drawText(QRect(settingsX+66,1278,948,100),Qt::AlignCenter,transl->getText_Options_DSGVO().text); //dsgvo titel anzeigetext
    painter.drawText(QRect(settingsX+66,1378,948,100),Qt::AlignCenter,transl->getText_Options_DSGVO_Request().text); //dsgvo button text

    painter.drawText(QRect(settingsX+58,1520,300,130),Qt::AlignCenter,back.text);
}

void Settings::mousePress(int x, int y, bool &music, bool &soundEffects, bool &lowGraphics, int &schmuserEnemy)
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
    } else if(pos.intersects(QRect(66,778,474,100))) {//schmuser
        schmuserEnemy = true;
    } else if(pos.intersects(QRect(540,778,474,100))) {//mieser
        schmuserEnemy = false;
    } else if(pos.intersects(QRect(settingsX+66,1378,948,100))) { //dsgvo

        emit dsgvoCheck();

    } else {
        //FPS
        for(int i = 0; i < 4; i++) {
            int num = 30 + 30 * i;

            if(pos.intersects(QRect(settingsX+66+(238 * i), 978, 238, 100))) {

                changeFPS((FPSMode)num);

                break;
            }
        }
    }
}

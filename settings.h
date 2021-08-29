#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QPainter>
#include <QUrlQuery>
#include <QMessageBox>
#include "scoreboard.h"
#include "networkmanager.h"
#include "translation.h"

enum class FPSMode {
    Low = 30,
    Medium = 60,
    High = 90,
    Max = 120,
};

class Settings : public QObject
{
    Q_OBJECT
private:
    QPixmap background;
    QPixmap btnPx;
    Translation *transl;
    Scoreboard *scoreboard;
    NetworkManager *network;
public:
    explicit Settings(QPixmap *background, QPixmap *btnPx, Translation *transl, Scoreboard *scoreboard, NetworkManager *network, QObject *parent = nullptr);
    void draw(QPainter &painter, QColor textColor, int &schmuserEnemy);
    void mousePress(int x, int y, bool &music, bool &soundEffects, bool &lowGraphics, int &schmuserEnemy);
    void changeFPS(FPSMode newFps);
    bool active;
    bool music;
    bool soundEffects;
    bool lowGraphics;
    int settingsX;

    //60 FPS default
    FPSMode fps = FPSMode::Medium;

signals:
    void back();
    void play();
    void updateFPS(FPSMode newFPS);
    void dsgvoCheck();
public slots:
};

#endif // SETTINGS_H

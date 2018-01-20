#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QPainter>
#include "translation.h"

class Settings : public QObject
{
    Q_OBJECT
private:
    QPixmap background;
    QPixmap btnPx;
    Translation *transl;
public:
    explicit Settings(QPixmap *background, QPixmap *btnPx, Translation *transl, QObject *parent = nullptr);
    void draw(QPainter &painter, QColor textColor);
    void mousePress(int x, int y, bool &music, bool &soundEffects, bool &lowGraphics);
    bool active;
    bool music;
    bool soundEffects;
    bool lowGraphics;
    int settingsX;

signals:
    void back();
    void play();
public slots:
};

#endif // SETTINGS_H

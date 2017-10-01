#ifndef BLUS_H
#define BLUS_H
#include <QRectF>
#include <QtMath>
#include <QPixmap>
#include <QColor>
class Blus
{
private:
    double vx;
    double vy;
    QRectF rect;
    QPixmap p;
    bool text;
    QString string;
    double opacity;
public:
    Blus();
    Blus(int angle,QRectF rect,QPixmap p);
    Blus(int angle, QRectF rect, QString text, int size=56);
    Blus(int angle, QRectF rect);
    int size;
    bool isRect;
    QColor color;
    void move();
    void setOpacity(double opacity);
    QRectF getRect();
    QPixmap getPixmap();
    bool isText();
    QString getText();
    double getOpacity();
};

#endif // BLUS_H

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
    double oSpeed;
public:
    Blus();
    Blus(int angle,QRectF rect,QPixmap p, int w=40, int h=40);
    Blus(int angle, QRectF rect, QString text, int size=48);
    Blus(int angle, QRectF rect, double vSpeed=8, double oSpeed=1);
    int size;
    int width;
    int height;
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

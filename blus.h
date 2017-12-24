#ifndef BLUS_H
#define BLUS_H
#include <QRectF>
#include <QtMath>
#include <QPixmap>
#include <QColor>
#include <QDebug>
class Blus
{
private:
    QRectF rect;
    QPixmap p;
    bool text;
    QString string;
    double opacity;
public:
    Blus();
    Blus(int angle,QRectF rect,QPixmap p, int w=40, int h=40, double oSpeed=1, double vSpeed=2, bool snow=false);
    Blus(int angle, QRectF rect, QString text, int size=48);
    Blus(int angle, QRectF rect, double vSpeed=8, double oSpeed=1, bool hardcore=false);
    double oSpeed;
    bool snow;
    bool hardcore;
    bool spark;
    bool used;
    bool gift;
    bool tail;
    int item;
    int size;
    int width;
    int height;
    double vx;
    double vy;
    bool isRect;
    QColor color;
    void move(double s);
    void setOpacity(double opacity);
    void setAngle(int angle, double vSpeed=2);
    QRectF getRect();
    QPixmap getPixmap();
    bool isText();
    QString getText();
    double getOpacity();
};

#endif // BLUS_H

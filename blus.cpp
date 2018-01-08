#include "blus.h"

Blus::Blus()
{

}

Blus::Blus(int angle, QRectF rect, QPixmap p, int w, int h, double oSpeed, double vSpeed, bool snow)
{
    this->color = QColor(255,255,255);
    opacity = 255;
    this->p = p;
    this->rect = rect;
    this->width = w;
    this->height = h;
    vx = qCos(qDegreesToRadians((double)angle))*vSpeed;
    vy = qSin(qDegreesToRadians((double)angle))*vSpeed;
    text = false;
    isRect = false;
    this->oSpeed = oSpeed;
    this->snow = snow;
    bg = false;
    spark = false;
    item = false;
    used = false;
    gift = false;
    tail = false;
}

Blus::Blus(int angle, QRectF rect, QString text, int size)
{
    this->color = QColor(255,255,255);
    this->size = size;
    opacity = 255;
    this->rect = rect;
    vx = qCos(qDegreesToRadians((double)angle))*2;
    vy = qSin(qDegreesToRadians((double)angle))*2;
    this->string = text;
    this->text = true;
    isRect = false;
    oSpeed = 1;
    bg = false;
    snow = false;
    spark = false;
    item = false;
    used = false;
    gift = false;
    tail = false;
}

Blus::Blus(int angle, QRectF rect, double vSpeed,double oSpeed, bool hardcore)
{
    this->color = QColor(255,255,255);
    this->rect = rect;
    opacity = 255;
    vx = qCos(qDegreesToRadians((double)angle))*vSpeed;
    vy = qSin(qDegreesToRadians((double)angle))*vSpeed;
    isRect = true;
    this->oSpeed = oSpeed;
    this->hardcore = hardcore;
    snow = false;
    spark = false;
    bg = false;
    item = false;
    used = false;
    gift = false;
    tail = false;
}

void Blus::move(double s)
{
    double sx = vx;
    double sy = vy;
    if(snow||item||tail) {
        if(snow!=2) sx+=s;
        sy*=0.5;
    }
    if(opacity) {
        opacity -= oSpeed;
        rect.moveTo(rect.x()+sx,rect.y()+vy);
    } else {
        rect.moveTo(-5000,1000);
    }
}

void Blus::setOpacity(double opacity)
{
    this->opacity = opacity;
}

void Blus::setAngle(int angle, double vSpeed)
{
    vx = qCos(qDegreesToRadians((double)angle))*vSpeed;
    vy = qSin(qDegreesToRadians((double)angle))*vSpeed;
}

QRectF Blus::getRect()
{
    return rect;
}

QPixmap Blus::getPixmap()
{
    return p;
}

bool Blus::isText()
{
    return text;
}

QString Blus::getText()
{
    return string;
}

double Blus::getOpacity()
{
    return opacity;
}

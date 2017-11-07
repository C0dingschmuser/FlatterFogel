#include "blus.h"

Blus::Blus()
{

}

Blus::Blus(int angle, QRectF rect, QPixmap p, int w, int h)
{
    opacity = 255;
    this->p = p;
    this->rect = rect;
    this->width = w;
    this->height = h;
    vx = qCos(qDegreesToRadians((double)angle))*2;
    vy = qSin(qDegreesToRadians((double)angle))*2;
    text = false;
    isRect = false;
    oSpeed = 1;
}

Blus::Blus(int angle, QRectF rect, QString text, int size)
{
    this->size = size;
    opacity = 255;
    this->rect = rect;
    vx = qCos(qDegreesToRadians((double)angle))*2;
    vy = qSin(qDegreesToRadians((double)angle))*2;
    this->string = text;
    this->text = true;
    isRect = false;
    oSpeed = 1;
}

Blus::Blus(int angle, QRectF rect, double vSpeed,double oSpeed)
{
    this->rect = rect;
    opacity = 255;
    vx = qCos(qDegreesToRadians((double)angle))*vSpeed;
    vy = qSin(qDegreesToRadians((double)angle))*vSpeed;
    isRect = true;
    this->oSpeed = oSpeed;
}

void Blus::move()
{
    if(opacity>0) {
        opacity -= oSpeed;
        rect.moveTo(rect.x()+vx,rect.y()+vy);
    }
}

void Blus::setOpacity(double opacity)
{
    this->opacity = opacity;
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

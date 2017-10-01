#include "blus.h"

Blus::Blus()
{

}

Blus::Blus(int angle, QRectF rect, QPixmap p)
{
    opacity = 255;
    this->p = p;
    this->rect = rect;
    vx = qCos(qDegreesToRadians((double)angle))*2;
    vy = qSin(qDegreesToRadians((double)angle))*2;
    text = false;
    isRect = false;
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
}

Blus::Blus(int angle, QRectF rect)
{
    this->rect = rect;
    opacity = 255;
    vx = qCos(qDegreesToRadians((double)angle))*8;
    vy = qSin(qDegreesToRadians((double)angle))*8;
    isRect = true;
}

void Blus::move()
{
    //if(text) {
        opacity -= 1;
    //}
    rect.moveTo(rect.x()+vx,rect.y()+vy);
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

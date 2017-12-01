#include "background.h"

Background::Background(int id, QColor color, bool stars, bool cloud, bool windows, bool p)
{
    this->background = QPixmap(":/images/backgrounds/bg"+QString::number(id)+".png");
    this->p = p;
    if(p) {
        this->backgroundP = QPixmap(":/images/backgrounds/bg"+QString::number(id)+"p.png");
    }
    this->bColor = color;
    this->stars = stars;
    this->cloud = cloud;
    this->windows = windows;
}

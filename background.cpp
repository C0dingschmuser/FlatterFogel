#include "background.h"

Background::Background(int id, QColor color, bool stars, bool cloud, bool windows)
{
    this->background = QPixmap(":/images/backgrounds/bg"+QString::number(id)+".png");
    this->bColor = color;
    this->stars = stars;
    this->cloud = cloud;
    this->windows = windows;
}

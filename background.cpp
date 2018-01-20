#include "background.h"

Background::Background(int id, QColor color, bool stars, bool cloud, bool windows, bool p, bool train, bool custombg, int customid, bool flag)
{
    if(customid) id = customid;
    this->background = QPixmap(":/images/backgrounds/bg"+QString::number(id)+".png");
    this->p = p;
    if(p) {
        this->backgroundP = QPixmap(":/images/backgrounds/bg"+QString::number(id)+"p.png");
    }
    this->bColor = color;
    this->stars = stars;
    this->cloud = cloud;
    this->windows = windows;
    this->train = train;
    this->custombg = custombg;
    this->flag = flag;
    if(custombg) ground = QPixmap(":/images/backgrounds/ground/"+QString::number(id)+".png");
}

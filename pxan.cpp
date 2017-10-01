#include "pxan.h"

PxAn::PxAn(QPixmap px, QObject *parent) : QObject(parent)
{
    this->px = px;
    active = true;
    t_timeout = new QTimer();
    connect(t_timeout,SIGNAL(timeout()),this,SLOT(on_ttimeout()));
    t_timeout->start(30000);
}

void PxAn::on_ttimeout()
{
    active = false;
    t_timeout->stop();
}

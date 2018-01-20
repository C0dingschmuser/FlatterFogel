#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <QPixmap>
#include <QString>
#include <QColor>

class Background
{
public:
    Background(int id, QColor color, bool stars, bool cloud, bool windows, bool p=false, bool train=true, bool custombg=false, int customid=0, bool flag=true);
    QPixmap background;
    QPixmap backgroundP;
    QPixmap ground;
    bool p;
    bool stars;
    bool cloud;
    bool windows;
    bool train;
    bool custombg;
    bool flag;
    QColor bColor;
};

#endif // BACKGROUND_H

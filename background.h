#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <QPixmap>
#include <QString>
#include <QColor>

class Background
{
public:
    Background(int id, QColor color, bool stars, bool cloud, bool windows, bool p=false);
    QPixmap background;
    QPixmap backgroundP;
    bool p;
    bool stars;
    bool cloud;
    bool windows;
    QColor bColor;
};

#endif // BACKGROUND_H

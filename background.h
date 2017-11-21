#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <QPixmap>
#include <QString>
#include <QColor>

class Background
{
public:
    Background(int id, QColor color, bool stars, bool cloud, bool windows);
    QPixmap background;
    bool stars;
    bool cloud;
    bool windows;
    QColor bColor;
};

#endif // BACKGROUND_H

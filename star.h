#ifndef STAR_H
#define STAR_H
#include <QRect>

class Star
{
public:
    Star();
    Star(QRect rect);
    QRect rect;
    double opacity;
    bool dir;
};

#endif // STAR_H

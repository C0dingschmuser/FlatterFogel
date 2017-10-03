#ifndef WINDOW_H
#define WINDOW_H
#include <QRect>

class Window
{
public:
    Window();
    Window(QRect rect);
    bool visible;
    QRect rect;
};

#endif // WINDOW_H

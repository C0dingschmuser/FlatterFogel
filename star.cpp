#include "star.h"

Star::Star()
{

}

Star::Star(QRect rect)
{
    this->rect = rect;
    int r = qrand() %(100-0) + 0;
    opacity = r/100.0;
    dir = qrand() % 2;
}

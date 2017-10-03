#include "window.h"

Window::Window()
{

}

Window::Window(QRect rect)
{
    this->rect = rect;
    visible = true;
}

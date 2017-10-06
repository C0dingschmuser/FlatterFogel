#include "text.h"

Text::Text()
{

}

Text::Text(QString text, QPoint pos, int size)
{
    this->text = text;
    this->pos = pos;
    this->size = size;
}

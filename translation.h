#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <QString>
#include <QPoint>
#include <QLocale>
#include "text.h"
class Translation
{
public:
    Translation();
    QLocale locale;
    Text getBtn_Go();
    Text getBtn_Shop();
    Text getBtn_Shop_Back();
    Text getBtn_Shop_Buy();
    Text getText_Shop_Item1();
    Text getText_Shop_MP1();
    Text getText_Shop_MP2();
    Text getText_Shop_Item2();
    Text getText_Shop_Item3();
    Text getText_Shop_NotEnough();
    Text getText_Shop_NotSelected();
    Text getText_Schmuser1();
    Text getText_Schmuser2();
    Text getText_Schmuser3();
};

#endif // LOCALE_H

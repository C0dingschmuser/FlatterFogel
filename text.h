#ifndef TEXT_H
#define TEXT_H
#include <QString>
#include <QPoint>
class Text
{
public:
    Text();
    Text(QString text,QPoint pos, int size);
    QString text;
    QPoint pos;
    int size;
};

#endif // TEXT_H

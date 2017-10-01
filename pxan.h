#ifndef PXAN_H
#define PXAN_H

#include <QObject>
#include <QPixmap>
#include <QTimer>

class PxAn : public QObject
{
    Q_OBJECT
private slots:
    void on_ttimeout();
private:
    QTimer *t_timeout;
public:
    explicit PxAn(QPixmap px,QObject *parent = nullptr);
    QPixmap px;
    double opacity;
    bool active;

signals:

public slots:
};

#endif // PXAN_H

#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QPixmap>
#include <QTimer>
#include <QFont>
#include <QPainter>
#include <QApplication>
#include <QTcpSocket>
#include "translation.h"

class Scoreboard : public QObject
{
    Q_OBJECT
private slots:
    void on_tcpRecv();
private:
    QPixmap bg;
    QPixmap btnPx;
    QVector<QString>players;
    QFont font;
    Translation *transl;
    QString maas(QString n);
public:
    explicit Scoreboard(QPixmap bg, QPixmap btnPx, QFont f, Translation *transl, QObject *parent = nullptr);
    void draw(QPainter &painter, int highscore);
    void setScore(int score);
    void getScores();
    void mpress(QPoint pos);
    bool active;
    bool wasConnected;
    QString first;
    QString name;
    QTcpSocket *socket;

signals:
    void wrongName();
    void connFail();
    void write();
public slots:
};

#endif // SCOREBOARD_H

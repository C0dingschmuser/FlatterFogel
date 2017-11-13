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
    int scoreX;
    QString first;
    QString name;
    QTcpSocket *socket;
    QVector <QPixmap> medals;

signals:
    void wrongName();
    void connFail();
    void write();
    void back();
public slots:
};

#endif // SCOREBOARD_H

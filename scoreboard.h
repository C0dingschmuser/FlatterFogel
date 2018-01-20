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
#include <QMessageBox>
#include "translation.h"

class Scoreboard : public QObject
{
    Q_OBJECT
private slots:
    void on_tcpRecv();
private:
    QPixmap bg;
    QPixmap btnPx;
    QPixmap btnNormal;
    QPixmap btnCave;
    QPixmap btnHardcore;
    QPixmap btnSpace;
    QPixmap btnUM;
    QVector<QString>players;
    QFont font;
    Translation *transl;
    int hs;
    int hs_H;
    int hs_C;
    int hs_S;
    int hs_UM;
    QString maas(QString n);
public:
    explicit Scoreboard(QPixmap bg, QPixmap btnPx, QFont f, Translation *transl, QObject *parent = nullptr);
    void draw(QPainter &painter, int highscore, QColor textColor);
    void setScore(int his=0, int his_H=0, int his_C=0, int his_S=0, int his_UM=0);
    void getScores();
    void mpress(QPoint pos);
    bool active;
    bool wasConnected;
    int scoreX;
    int page;
    QString first;
    QString name;
    QTcpSocket *socket;
    QVector <QPixmap> medals;

signals:
    void wrongName();
    void connFail();
    void write(int type);
    void back();
public slots:
};

#endif // SCOREBOARD_H

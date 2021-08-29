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
#include <QUrlQuery>
#include <QInputDialog>
#include <QMessageBox>
#include "networkmanager.h"
#include "translation.h"
#include "scoreboardplayer.h"

class Scoreboard : public QObject
{   
    Q_OBJECT
private slots:
    void on_tcpRecv();
private:
    NetworkManager *networkManager;
    QPixmap bg;
    QPixmap btnPx;
    QPixmap btnNormal;
    QPixmap btnCave;
    QPixmap btnHardcore;
    QPixmap btnSpace;
    QPixmap btnUM;
    QVector<ScoreboardPlayer> playerList;
    QVector<QString>players;
    QFont font;
    Translation *transl;
    int hs;
    int hs_H;
    int hs_C;
    int hs_S;
    int hs_UM;
    QString maas(QString n);
public slots:
    void HandleSetScore(QString response);
    void HandleGetScore(QString response);
    void HandleNameChange(QString response);
public:
    explicit Scoreboard(NetworkManager *networkManager, QPixmap bg, QPixmap btnPx, QFont f, Translation *transl, QObject *parent = nullptr);
    void draw(QPainter &painter, int highscore, QColor textColor);
    void setScore(int his=0, int his_H=0, int his_C=0, int his_S=0, int his_UM=0);
    void getScores();
    void mpress(QPoint pos, QWidget *parent);
    bool checkName(QString n);
    bool active;
    bool wasConnected;
    int scoreX;
    int page;
    QString first;
    QString name;
    QTcpSocket *socket;
    QVector <QPixmap> medals;

signals:
    void wrongName(int type);
    void connFail();
    void write(int type);
    void back();
    void open();
public slots:
};

#endif // SCOREBOARD_H

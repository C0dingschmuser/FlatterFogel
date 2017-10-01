#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QOpenGLWidget>
#include <QStandardPaths>
#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QColor>
#include <QVector>
#include <QMessageBox>
#include <QThread>
#include <QMouseEvent>
#include <QPixmap>
#include <QFont>
#include <QFile>
#include <QTime>
#include "blus.h"
#include "player.h"
#include "obstacle.h"
#include "shop.h"
#include "pxan.h"

namespace Ui {
class FrmMain;
}

class FrmMain : public QOpenGLWidget
{
    Q_OBJECT
private slots:
    void on_tdraw();
    void on_tmain();
    void on_tObst();
    void on_tEvent();
    void on_shopBack();
    void on_shopMsg(QString msg);
    void on_shopBuy(int amount);
    void on_trevive();
    void on_tboost();
public:
    explicit FrmMain(QOpenGLWidget *parent = 0);
    ~FrmMain();

private:
    Ui::FrmMain *ui;
    QTimer *t_draw;
    QTimer *t_main;
    QTimer *t_obst;
    QTimer *t_event;
    QTimer *t_revive;
    QTimer *t_boost;
    double scaleX;
    double scaleY;
    Player *player;
    Shop *shop;
    int active;
    QPoint mousePos;
    QThread *workerThread;
    QVector <Obstacle*> obstacles;
    QVector <Blus*> blusse;
    QVector <PxAn*> pxans;
    int random(int min, int max);
    QPixmap end;
    QPixmap blus;
    QPixmap minus;
    QPixmap schmuserkadser;
    QPixmap enemyPixmap;
    QPixmap maas;
    QPixmap btnPx;
    QString enemy;
    QRectF enemyRect;
    int enemytype;
    int enemydir;
    int enemylife;
    int score;
    int highscore;
    int schmuser;
    int maxX;
    int maxY;
    double boost;
    bool revive;
    QFile file;
    void loadData();
    void write();
    void reset(int type=0);
protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *e) override;
    void closeEvent(QCloseEvent *event);
};

#endif // FRMMAIN_H

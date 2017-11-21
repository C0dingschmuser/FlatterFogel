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
#include <QInputDialog>
#include <QTime>
#include <QGuiApplication>
#include <QInputMethod>
#include <QFontDatabase>
#include <QFont>
#include <bitset>
#include <QPushButton>
#include <QMessageBox>
#include "translation.h"
#include "blus.h"
#include "player.h"
#include "obstacle.h"
#include "shop.h"
#include "window.h"
#include "pxan.h"
#include "star.h"
#include "scoreboard.h"
#include "background.h"

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
    void on_shopBuy(int amount, bool buy=true, bool coin=false);
    void on_trevive();
    void on_tboxDeathAn();
    void on_tboost();
    void on_tAn();
    void on_tTilt();
    void on_tChange();
    void on_tflag();
    void on_tstar();
    void on_sbWrongName();
    void on_sbConnFail();
    void on_write();
    void on_tresume();
    void on_scoreBack();
    void on_scoreWrite();
    void on_tAnimation();
public:
    explicit FrmMain(QOpenGLWidget *parent = 0);
    ~FrmMain();

private:
    Ui::FrmMain *ui;
    int mainX;
    int endX;
    bool anDir;
    int movingObstacles;
    int moveAn;
    QTimer *t_draw;
    QTimer *t_main;
    QTimer *t_obst;
    QTimer *t_event;
    QTimer *t_revive;
    QTimer *t_boost;
    QTimer *t_an;
    QTimer *t_tilt;
    QTimer *t_tchange;
    QTimer *t_flag;
    QTimer *t_star;
    QTimer *t_boxDeathAn;
    QTimer *t_resume;
    QTimer *t_animation;
    QFont font;
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
    QVector <Window*> windows;
    QVector <Star*> stars;
    QVector <QPixmap> skins;
    QVector <Background*> backgrounds;
    int currentskin;
    int random(int min, int max);
    QPixmap end;
    QPixmap blus;
    QPixmap minus;
    QPixmap schmuserkadser;
    QPixmap enemyPixmap;
    QPixmap maas;
    QPixmap btnPx;
    QPixmap ground;
    QPixmap bg;
    QPixmap medal_bronze;
    QPixmap medal_silver;
    QPixmap medal_gold;
    QPixmap medal_platin;
    QPixmap medal_diamond;
    QPixmap flag_de;
    QPixmap flag_en;
    QPixmap stats;
    QPixmap trainPx;
    QPixmap train2Px;
    QPixmap boxPx;
    QPixmap box2Px;
    QPixmap box3Px;
    QPixmap pause0;
    QPixmap pause1;
    QPixmap coinPx;
    QPixmap cloudPx;
    QPixmap referralPx1;
    QPixmap referralPx2;
    QVector <QPixmap> boxPxAn;
    QVector <QPixmap> explosion;
    QString enemy;
    QString version;
    QString refkey;
    QRectF enemyRect;
    bool fastboost;
    Translation *transl;
    Scoreboard *scoreboard;
    QString name;
    int enemytype;
    int enemydir;
    int enemylife;
    int score;
    int highscore;
    int schmuser;
    int maxX;
    int maxY;
    int medal;
    int boxCount;
    int boxDeath;
    int obsNum;
    int boxState;
    int resumeTime;
    int event;
    int referrals;
    bool invited;
    bool refActive;
    double cloud1X;
    double cloud2X;
    double flashOpacity;
    double g1x;
    double g2x;
    double boost;
    int revive;
    bool flag;
    bool pause;
    bool changelog;
    QFile file;
    void loadData();
    void write();
    void reset(int type=0);
    void moveGround(double speed);
    void createWindows();
    QString genKey();
    QString lucaAlg(QString text);
    bool checkKey(QString key);
    bool checkConfirm(QString key);
protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *e) override;
    void closeEvent(QCloseEvent *event);
};

#endif // FRMMAIN_H

#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QOpenGLWidget>
#include <QStandardPaths>
#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QDateTime>
#include <QColor>
#include <QVector>
#include <QSoundEffect>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QThread>
#include <QMouseEvent>
#include <QPixmap>
#include <QFont>
#include <QFile>
#include <QInputDialog>
#include <QTime>
#include <QGuiApplication>
#include <QDesktopServices>
#include <QUrl>
#include <QInputMethod>
#include <QFontDatabase>
#include <QFont>
#include <bitset>
#include <QPushButton>
#include <QMessageBox>
#include <QMediaPlaylist>
#include <QPainterPath>
#include <QDir>
#include <QUrlQuery>
#include <QRandomGenerator>
#include <QInAppStore>
#include <QInAppProduct>
#include <QInAppTransaction>
#include <QOpenGLPaintDevice>

/*#include "D:/FF_QT515/purchasing/inapp/inappproduct.h"
#include "D:/FF_QT515/purchasing/inapp/inapppurchasebackend.h"
#include "D:/FF_QT515/purchasing/inapp/inappstore.h"
#include "D:/FF_QT515/purchasing/inapp/inapptransaction.h"
#include "D:/FF_QT515/purchasing/qmltypes/inappproductqmltype.h"
#include "D:/FF_QT515/purchasing/qmltypes/inappstoreqmltype.h"*/

#ifdef Q_OS_ANDROID
    #include <QtAndroid>
#endif
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
#include "settings.h"
#include "enemy.h"
#include "projectile.h"
#include "networkmanager.h"

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
    void on_shopBuy(int amount, bool buy=true, bool coin=false, bool mid=false);
    void on_tboxDeathAn();
    void on_tboost();
    void on_tAn();
    void on_tTilt();
    void on_tChange();
    void on_tflag();
    void on_tstar();
    void on_sbWrongName(int type);
    void on_sbConnFail();
    void on_write();
    void on_tresume();
    void on_scoreBack();
    void on_scoreWrite(int type=0);
    void on_tAnimation();
    void on_tblus();
    void on_tnewHS();
    void on_tTail();
    void on_tRgb();
    void on_mediastateChanged(QMediaPlayer::MediaStatus status);
    void on_appStateChanged(Qt::ApplicationState state);
    void on_test();
    void on_settingsBack();
    void on_settingsPlay();
    void on_tbackup();
    void on_treload();
    void on_tregen();
    void handleTransaction(QInAppTransaction *transaction);
    void productRegistered(QInAppProduct *product);
    void productUnknown(QInAppProduct::ProductType ptype,QString id);
    void HandleStatus(QString response);
    void AuthSave(QString auth);
    void OpenScoreboard();
    void UpdateFps(FPSMode newFps);
    void DSGVOCheck();
    void DSGVODone(QString response);

public:
    explicit FrmMain(QOpenGLWidget *parent = 0);
    ~FrmMain();

private:
    Ui::FrmMain *ui;
    QMediaPlayer *sound;
    QMediaPlaylist *playlist;

    QInAppStore *store;

    NetworkManager *networkManager;

    bool soundEnabled;
    bool soundEffectsEnabled;
    bool suspended;
    bool unlockedSpeed;
    bool schmuserDefend;
    bool boostDisabled;
    bool closeSave;
    bool pInit = false;
    int schmuserEnemy;
    int mainX;
    int endX;
    bool anDir;
    int newHS;
    int stationaryObstacles;
    int moveAn;
    double schmuserReload;
    int schmuserRegen;
    int schmuserRange;
    int schmuserCredits;
    int schmuserDmg;
    std::vector <int> schmuserCost;
    unsigned long cBox;
    unsigned long cBTouch;
    unsigned long cBPipe;
    double radR;
    double playTime;
    double localPlayTime;
    double reviveTime;
    bool hardcore;
    bool cave;
    bool space;
    bool loading;
    bool lowGraphics;
    int donator;
    int ad;
    bool ad_active;
    QDateTime currentDateTime;
    QTimer *t_draw;
    QTimer *t_main;
    QTimer *t_obst;
    QTimer *t_event;
    QTimer *t_boost;
    QTimer *t_an;
    QTimer *t_tilt;
    QTimer *t_tchange;
    QTimer *t_flag;
    QTimer *t_star;
    QTimer *t_boxDeathAn;
    QTimer *t_resume;
    QTimer *t_animation;
    QTimer *t_blus;
    QTimer *t_newHS;
    QTimer *t_tail;
    QTimer *t_rgb;
    QTimer *t_backup;
    QTimer *t_reload;
    QTimer *t_regen;
    QFont font;
    double scaleX;
    double scaleY;
    QRectF aimingAt;
    Player *player;
    Shop *shop;
    int active;
    uint schmuserWaveSize;
    int schmuserWave;
    int schmuserkills;
    int schmuserKillsneeded;
    int schmuserBaseHP;
    int schmuserBaseMaxHP;
    int schmuserHP;
    QPoint mousePos;
    QThread *workerThread;
    QThread *blusThread;
    QThread *animationThread;
    QThread *musicThread;
    std::vector <Obstacle*> obstacles;
    std::vector <Blus*> blusse;
    QVector <Window*> windows;
    QVector <Star*> stars;
    std::vector <QPixmap> skins;
    std::vector <QPixmap> pipes;
    std::vector <QPixmap> tails;
    std::vector <QPixmap> planets;
    std::vector <QSoundEffect*> soundEffects;
    std::vector <Enemy*> enemys;
    std::vector <Projectile*> projectiles;
    QVector <QPixmap> thumbs;
    QVector <QPixmap> powerupPx;
    std::vector <Background*> backgrounds;
    int currentskin;
    int random(int min, int max);
    QPixmap vol0;
    QPixmap vol1;
    QPixmap end;
    QPixmap blus;
    QPixmap minus;
    QPixmap schmuserkadser;
    QPixmap enemyPixmap;
    QPixmap maas;
    QPixmap btnPx;
    QPixmap settingsBtn;
    QPixmap ground;
    QPixmap bg;
    QPixmap medal_bronze;
    QPixmap medal_silver;
    QPixmap medal_gold;
    QPixmap medal_platin;
    QPixmap medal_diamond;
    QPixmap medal_emerald;
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
    QPixmap mieserkadserPx;
    QPixmap ad_px;
    QPixmap ad_px_eng;
    QPixmap restorePx;
    QPixmap btnup;
    QPixmap btndown;
    QPixmap windowPx;
    QPixmap dsgvoPx_de;
    QPixmap dsgvoPx_en;
    QVector <QPixmap> boxPxAn;
    QString enemy;
    QString version;
    QString refkey;
    QString confirmkey;
    QString lastPost;
    QRectF enemyRect;
    QPolygonF polyTop;
    QPolygonF polyBottom;
    QPolygonF polyColl;
    bool firstlaunch = true;
    bool dsgvo = false;
    bool fastboost;
    bool newpost;
    bool crate;
    Translation *transl;
    Scoreboard *scoreboard;
    Settings *settings;
    QString name;
    QColor textColor;
    int enemytype;
    int enemydir;
    int enemylife;
    int score;
    int highscore;
    int highscore_H;
    int highscore_C;
    int highscore_S;
    int highscore_UM;
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
    int caveSpawnCount;
    int cnum1;
    int cnum2;
    int cnum3;
    int cnum4;
    int go;
    int rgb_red;
    int rgb_blue;
    int rgb_green;
    int rgb_mode;
    int mouseX;
    int mouseY;
    double planetX;
    double planetY;
    int chosenPlanet;
    bool invited;
    bool refActive;
    bool outdated;
    bool boostused;
    bool flip;
    bool eLoad;
    bool underwater;
    bool closing;
    bool vContains(std::vector<int> v, int value);
    double textFade;
    double cloud1X;
    double cloud2X;
    double flashOpacity;
    double g1x;
    double g2x;
    double boost;
    int revive;
    Blus *lastbenpos;
    double gameSpeed;
    bool flag;
    bool pause;
    bool changelog;
    bool mousePressed;
    QFile file;
    QFile fileE;
    void setupIAP();
    void loadData();
    void write(bool normal=true, int bscore=0);
    void reset(int type=0);
    void moveGround(double speed);
    void createWindows();
    void handleBox();
    void playFlatter();
    void doSchmuserDefend();
    void drawSchmuserDefend(QPainter &painter, QFont f);
    void drawSchmuserDefendEnd(QPainter &painter, QFont f);
    QString genKey();
    QString lucaAlg(QString text);
    QString lucaAlgR(QString text);
    bool checkKey(QString key);
    bool checkConfirm(QString key);
    bool intersectsWithCircle(QRectF rect, QRectF circle);
    bool intersectsWithCircle2(QRectF rect, int r, QPoint center);
    void checkPost();
    void initSound();
    void error(QString errorString);
    void startStop(bool start);
    void tap(int x, int y);
    void changeSpeed(bool faster);
    void initPurchase(int packageCode);
    double getDistance(QPointF p1,QPointF p2);
protected:
    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *e) override;
    void closeEvent(QCloseEvent *event);
};

#endif // FRMMAIN_H

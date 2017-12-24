#include "frmmain.h"
#include "ui_frmmain.h"

FrmMain::FrmMain(QOpenGLWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::FrmMain)
{
    ui->setupUi(this);
    lastPost = "2294406";
    loading = true;
    mainX = 0;
    newHS = 0;
    caveSpawnCount = 0;
    endX = 1080;
    cloud1X = 0;
    cloud2X = 1079;
    event = 0;
    donator = false;
    playTime = 0;
    localPlayTime = 0;
    cBox = 0;
    cBTouch = 0;
    cBPipe = 0;
    go = 1;
    hardcore = false;
    radR = 2700;
    anDir = false;
    moveAn = false;
    refActive = false;
    version = "1.2.7r2";
    t_draw = new QTimer();
    t_main = new QTimer();
    t_obst = new QTimer();
    t_event = new QTimer();
    t_boxDeathAn = new QTimer();
    t_boost = new QTimer();
    t_an = new QTimer();
    t_tilt = new QTimer();
    t_tchange = new QTimer();
    t_flag = new QTimer();
    t_star = new QTimer();
    t_resume = new QTimer();
    t_animation = new QTimer();
    t_blus = new QTimer();
    t_newHS = new QTimer();
    t_tail = new QTimer();
    flashOpacity = 0;
    pause = false;
    transl = new Translation();
    int id = QFontDatabase::addApplicationFont(":/font/PressStart2P.ttf");
    QString fam = QFontDatabase::applicationFontFamilies(id).at(0);
    font = QFont(fam);
    connect(t_event,SIGNAL(timeout()),this,SLOT(on_tEvent()));
    connect(t_main,SIGNAL(timeout()),this,SLOT(on_tmain()));
    connect(t_draw,SIGNAL(timeout()),this,SLOT(on_tdraw()));
    connect(t_obst,SIGNAL(timeout()),this,SLOT(on_tObst()));
    connect(t_boost,SIGNAL(timeout()),this,SLOT(on_tboost()));
    connect(t_an,SIGNAL(timeout()),this,SLOT(on_tAn()));
    connect(t_tilt,SIGNAL(timeout()),this,SLOT(on_tTilt()));
    connect(t_tchange,SIGNAL(timeout()),this,SLOT(on_tChange()));
    connect(t_flag,SIGNAL(timeout()),this,SLOT(on_tflag()));
    connect(t_star,SIGNAL(timeout()),this,SLOT(on_tstar()));
    connect(t_boxDeathAn,SIGNAL(timeout()),this,SLOT(on_tboxDeathAn()));
    connect(t_resume,SIGNAL(timeout()),this,SLOT(on_tresume()));
    connect(t_animation,SIGNAL(timeout()),this,SLOT(on_tAnimation()));
    connect(t_blus,SIGNAL(timeout()),this,SLOT(on_tblus()));
    connect(t_newHS,SIGNAL(timeout()),this,SLOT(on_tnewHS()));
    connect(t_tail,SIGNAL(timeout()),this,SLOT(on_tTail()));
    //this->showMaximized();
    referrals = 3;
    invited = false;
    end = QPixmap(":/images/end.png");
    btnPx = QPixmap(":/images/buttons/button.png");
    blus = QPixmap(":/images/blus.png");
    minus = QPixmap(":/images/minus.png");
    ground = QPixmap(":/images/ground.png");
    bg = QPixmap(":/images/backgrounds/bg2.png");
    medal_bronze = QPixmap(":/images/medals/bronze.png");
    medal_silver = QPixmap(":/images/medals/silber.png");
    medal_gold = QPixmap(":/images/medals/gold.png");
    medal_platin = QPixmap(":/images/medals/platin.png");
    medal_diamond = QPixmap(":/images/medals/diamant.png");
    medal_emerald = QPixmap(":/images/medals/smaragd.png");
    cloudPx = QPixmap(":/images/cloud.png");
    QVector <QPixmap> medalsPx;
    medalsPx.append(medal_bronze);
    medalsPx.append(medal_silver);
    medalsPx.append(medal_gold);
    medalsPx.append(medal_platin);
    medalsPx.append(medal_diamond);
    medalsPx.append(medal_emerald);
    flag_de = QPixmap(":/images/flag/de.png");
    flag_en = QPixmap(":/images/flag/en.png");
    stats = QPixmap(":/images/stats.png");
    trainPx = QPixmap(":/images/train.png");
    train2Px = QPixmap(":/images/train2.png");
    boxPx = QPixmap(":/images/box/box.png");
    box2Px = QPixmap(":/images/box/box2.png");
    box3Px = QPixmap(":/images/box/box3.png");
    pause0 = QPixmap(":/images/buttons/pause0.png");
    pause1 = QPixmap(":/images/buttons/pause1.png");
    coinPx = QPixmap(":/images/coin.png");
    referralPx1 = QPixmap(":/images/referral.png");
    referralPx2 = QPixmap(":/images/referral2.png");
    mieserkadserPx = QPixmap(":/images/mieserkadser.png");
    for(int i=0;i<24;i++) {
        skins.append(QPixmap(":/images/player/skins/"+QString::number(i)+".png"));
    }
    for(int i=0;i<9;i++) {
        pipes.append(QPixmap(":/images/pipes/"+QString::number(i)+".png"));
    }
    for(int i=0;i<6;i++) {
        tails.append(QPixmap(":/images/tails/"+QString::number(i)+".png"));
    }
    for(int i=0;i<29;i++) {
        thumbs.append(QPixmap(":/images/pipes/thumbs/"+QString::number(i)+".jpg"));
    }
    backgrounds.append(new Background(1,QColor(22,22,24),true,false,true));
    backgrounds.append(new Background(2,QColor(0,143,255),false,true,true));
    backgrounds.append(new Background(3,QColor(95,95,95),true,false,false));
    backgrounds.append(new Background(4,QColor(95,95,95),false,false,false,true));
    backgrounds.append(new Background(5,QColor(255,207,43),false,false,false));
    for(int i=0;i<3;i++) {
        boxPxAn.append(QPixmap(":/images/box/box_"+QString::number(i+1)+".png"));
    }
    player = new Player(QRectF(1080/2-250,1920/2-40,80,80));
    shop = new Shop(player,font,transl,coinPx,cloudPx);
    shop->skins = skins;
    shop->pipes = pipes;
    shop->tails = tails;
    shop->g2 = player->g2;
    scoreboard = new Scoreboard(shop->background,btnPx,font,transl);
    shop->backgrounds = backgrounds;
    scoreboard->medals = medalsPx;
    connect(scoreboard,SIGNAL(connFail()),this,SLOT(on_sbConnFail()));
    connect(scoreboard,SIGNAL(wrongName()),this,SLOT(on_sbWrongName()));
    connect(scoreboard,SIGNAL(write(int)),this,SLOT(on_scoreWrite(int)));
    connect(scoreboard,SIGNAL(back()),this,SLOT(on_scoreBack()));
    connect(shop,SIGNAL(back()),this,SLOT(on_shopBack()));
    connect(shop,SIGNAL(msg(QString)),this,SLOT(on_shopMsg(QString)));
    connect(shop,SIGNAL(buy(int,bool,bool,bool)),this,SLOT(on_shopBuy(int,bool,bool,bool)));
    enemyRect = QRectF(-300,100,300,200);
    enemy = "Mieserkadser";
    enemylife = 10;
    boxDeath = 0;
    obsNum = 0;
    boxState = 0;
    resumeTime = 0;
    stationaryObstacles = 0;
    //window
    createWindows();
    //~Window
    flag = false;
    changelog = false;
    newpost = false;
    active = 0;
    enemydir = 1; //unten
    score = 0;
    schmuser = 0;
    highscore = 0;
    highscore_H = 0;
    highscore_C = 0;
    boost = 0;
    crate = false;
    fastboost = false;
    lowGraphics = false;
    cave = false;
    outdated = false;
    medal = 0;
    g1x = 0;
    g2x = 1080;
    boxCount = 0;
    revive = false;
    qsrand(QDateTime::currentDateTime().toTime_t());
    currentDateTime = QDateTime::currentDateTime();
    loadData();
    workerThread = new QThread();
    blusThread = new QThread();
    animationThread = new QThread();
    t_main->start(5);
    t_draw->setTimerType(Qt::PreciseTimer);
    t_draw->start(10);
    t_obst->start(50);
    t_blus->start(5);
    t_event->start(500);
    t_flag->start(750);
    t_star->start(125);
    t_an->start(150);
    t_animation->setTimerType(Qt::PreciseTimer);
    t_animation->start(1);
    t_tchange->setSingleShot(true);
    t_animation->moveToThread(animationThread);
    t_an->moveToThread(workerThread);
    t_main->moveToThread(workerThread);
    t_obst->moveToThread(workerThread);
    t_boost->moveToThread(workerThread);
    t_tilt->moveToThread(workerThread);
    t_tchange->moveToThread(workerThread);
    t_flag->moveToThread(workerThread);
    t_star->moveToThread(workerThread);
    t_boxDeathAn->moveToThread(workerThread);
    t_resume->moveToThread(workerThread);
    t_blus->moveToThread(blusThread);
    t_tail->moveToThread(blusThread);
    t_newHS->moveToThread(workerThread);
    workerThread->start();
    blusThread->start();
    animationThread->start();
    qApp->setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; }");
}

FrmMain::~FrmMain()
{
    delete player;
    delete ui;
}

void FrmMain::checkPost()
{
    QTcpSocket *socket = new QTcpSocket();
    socket->connectToHost("flatterfogel.ddns.net",38900);
    socket->waitForConnected(500);
    if(socket->state()==QTcpSocket::ConnectedState) {
        QString data = ".-1#"+lastPost+"#"+scoreboard->name+"#"+version+"#~";
        socket->write(data.toUtf8());
        socket->waitForBytesWritten(500);
        socket->waitForReadyRead(1000);
        QString input = socket->readAll();
        QStringList split = input.split("#");
        if(split.at(0)!=lastPost) {
            lastPost = split.at(0);
            write();
            newpost = true;
        }
        if(split.at(1).toInt()) { //spender
            if(!shop->ownedbackgrounds.contains(4)||!shop->ownedPipes.contains(8)||
                    !shop->ownedSkins.contains(23)) {
                donator = true;
            }
        }
        if(split.at(2)!=version&&!split.at(2).contains("b")) outdated = true;
    }
    socket->close();
    delete socket;
}

double FrmMain::getDistance(QPointF p1, QPointF p2)
{
    return qSqrt(qPow(qFabs(p2.x()-(double)p1.x()),2)+qPow(qFabs(p2.y()-(double)p1.y()),2));
}

void FrmMain::on_tTail()
{
    if(boost||pause) return;
    switch(shop->chosenTail) {
    case 2: //blus
    case 3: //minus
    case 6: //coin
        {
        Blus *b = new Blus(0,QRect(player->getRect().x()-50,player->getRect().y()+player->getRect().height()/2-25,50,50),tails[shop->chosenTail-1],40,40,0,0);
        b->tail = true;
        blusse.append(b);
        break;
        }
    case 4: //nyan
    case 5: //de flag
        {
        Blus *b = new Blus(0,QRect(player->getRect().x()-10,player->getRect().y()+player->getRect().height()/2-40,5,80),tails[shop->chosenTail-1],5,60,0,0);
        b->tail = true;
        blusse.append(b);
        break;
        }
    }
}

void FrmMain::on_tdraw()
{
    if(QGuiApplication::applicationState()==Qt::ApplicationSuspended) {
        if(active==1&&!pause) {
            if(!t_boost->isActive()&&!revive) pause = true;
        }
        return;
    }
    update();
}

void FrmMain::on_tblus()
{
    if(QGuiApplication::applicationState()==Qt::ApplicationSuspended) return;
    for(int i=0;i<blusse.size();i++) {
        if(pause) return;
        if(boost) {
            blusse[i]->move(-boost);
        } else {
            if(!blusse[i]->tail||(blusse[i]->tail&&active==1)) {
                int s = 0;
                if(active==1) s = -1;
                blusse[i]->move(s);
            }
            //if(blusse[i]->item) qDebug()<<blusse[i]->getRect();
        }
    }
    for(int i=0;i<blusse.size();i++) {
        if((!blusse[i]->getRect().intersects(QRectF(0,0,1080,1920))&&!blusse[i]->isText())||blusse[i]->getOpacity()<=0) {
            if((!blusse[i]->snow&&!blusse[i]->item)||(blusse[i]->snow&&blusse[i]->getOpacity()<=0)||((blusse[i]->snow||blusse[i]->item)&&blusse[i]->getRect().x()<=0)||
                    (blusse[i]->item&&blusse[i]->getOpacity()<=0)) {
                delete blusse[i];
                blusse.removeAt(i);
            }
            //break;
        }
    }
}

void FrmMain::on_tnewHS()
{
    newHS = 2;
    QMetaObject::invokeMethod(t_newHS,"stop");
}

void FrmMain::on_tmain()
{
    if(pause) return;
    //moveAn = 3;
    if(flashOpacity) {
        flashOpacity -= 0.0125;
    }
    if(backgrounds[shop->chosenBackground-1]->cloud&&!lowGraphics) {
        cloud1X-=0.15;
        cloud2X-=0.15;
        if(cloud1X<=-1079) {
            cloud1X = 1079;
        } else if(cloud2X<=-1079) {
            cloud2X = 1079;
        }
    }
    if(active<1) return;
    if(active==1&&!boxDeath) {
        localPlayTime+=0.005;
        if(revive==1) {
            reviveTime-=5;
            if(reviveTime<=0) {
                revive = 0;
                reviveTime = 0;
            }
        }
        for(int i=0;i<obstacles.size();i++) {
            if(boost) {
                obstacles[i]->moveBy(-boost,0);
                moveGround(-boost);
            } else {
                double speed=0.5;
                if(hardcore) {
                    speed = 0.70;
                }
                obstacles[i]->moveBy(-1,0,speed);
                moveGround(-1);
            }
            bool co = false;
            if(!boost&&active==1&&!cave) {
                if(!player->circle) {
                    if(player->getCollRect().intersects(obstacles[i]->getBottom())||
                          player->getCollRect().intersects(obstacles[i]->getTop())) {
                        co = true;
                    }
                } else {
                    if(intersectsWithCircle(obstacles[i]->getBottom(),player->getCollRect())||
                            intersectsWithCircle(obstacles[i]->getTop(),player->getCollRect())) co = true;
                }
            }
            if(co) {
                active = 3;
                flashOpacity = 0.5;
            }
        }
        if((score>highscore&&!cave&&!hardcore)&&(score>highscore_H&&!cave&&hardcore)&&(score>highscore_C&&cave&&!hardcore)&&!newHS&&highscore) {
            newHS = 1;
            Blus *b = new Blus(90,QRectF(4,180,1,1),transl->getText_NHS().text);
            b->color = QColor(255,0,130);
            blusse.append(b);
            QMetaObject::invokeMethod(t_newHS,"start",Q_ARG(int,250));
        }
        if(cave) {
            QPolygonF poly;
            for(int i=0;i<obstacles.size();i++) {
                QPointF oben(obstacles[i]->getBottom().x(),obstacles[i]->getBottom().y());
                poly.append(oben);
            }
            for(int i=obstacles.size()-1;i>=0;i--) {
                QPointF unten(obstacles[i]->getBottom().x(),obstacles[i]->getBottom().y()+obstacles[i]->getBottom().height());
                poly.append(unten);
            }
            QPolygonF polyTop;
            for(int i=0;i<obstacles.size();i++) {
                QPointF oben(obstacles[i]->getTop().x(),obstacles[i]->getTop().y());
                polyTop.append(oben);
            }
            for(int i=obstacles.size()-1;i>=0;i--) {
                QPointF unten(obstacles[i]->getTop().x(),obstacles[i]->getTop().y()+obstacles[i]->getTop().height());
                polyTop.append(unten);
            }
            polyBottom = poly;
            this->polyTop = polyTop;
            bool co=false;
            if(!boost) {
                QPolygonF c1 = player->getPoly().intersected(polyTop);
                QPolygonF c2 = player->getPoly().intersected(polyBottom);
                if(c1.size()) {
                    co = true;
                    polyColl = c1;
                } else if(c2.size()) {
                    co = true;
                    polyColl = c2;
                }
            }
            if(co) {
                active = 3;
                flashOpacity = 0.5;
            }
        }
        for(int i=0;i<blusse.size();i++) {
            if(blusse[i]->item) {
                if(player->getCollRect().intersects(blusse[i]->getRect())) {
                    if(blusse[i]->item==1) {
                        score++;
                        blusse[i]->move(-5000);
                        if((score%100==0&&score!=0)||(score%30==0&&hardcore)) {
                            on_shopBuy(1,false,true);
                            player->coins++;
                            write();
                        } else {
                            player->setBenis(player->getBenis()+(score*shop->multiplier));
                            int b = score*shop->multiplier;
                            cBPipe += b;
                            player->setBenis(player->getBenis()+b);
                            if(hardcore) b*=1.5;
                            blusse.append(new Blus(90,QRectF(4,180,1,1),"+"+QString::number(b)));
                            if(!lowGraphics) {
                                QPixmap bpx = blus;
                                if(shop->chosenSkin==14) bpx = minus;
                                for(int a=0;a<360;a+=12) {
                                    blusse.append(new Blus(a,QRectF(player->getRect().center().x()-20,player->getRect().center().y()-20,40,40),bpx));
                                }
                            }
                        }
                    } else if(!blusse[i]->used){
                        blusse[i]->used = true;
                        blusse[i]->oSpeed = 4;
                        blusse[i]->setAngle(-90);
                        boxCount++;
                        cBox++;
                    }
                }
            }
        }
    }
    bool dead = false;
    if(player->getRect().y()<1600&&active>0) {
        double velD = player->getVelD();
        if(velD<10) velD += 0.1;
        player->setVelD(velD);
        QRectF r = player->getCollRect();
        if(!cave) {
            if(r.y()+velD>1600) {
                velD = 1600-r.y();
            }
            player->setPos(r.x(),r.y()+velD);
        } else {
            QRectF r2 = QRectF(r.x(),r.y()+velD,r.width(),r.height());
            QPolygonF inters = QPolygonF(r2).intersected(polyBottom);
            //QPolygonF intersT = QPolygonF(r2).intersected(polyTop);
            if(!inters.size()) {
                player->setPos(r2.x(),r2.y());
            } else {
                if(!boost) {
                    dead = true;
                } else {
                    player->setPos(r2.x(),r2.y());
                }
            }
        }
    }
    if(player->getRect().y()>=1600||dead) {
        if(!revive) {
            if(active==1) {
                flashOpacity = 0.5;
            }
            QMetaObject::invokeMethod(t_boost,"stop");
            QMetaObject::invokeMethod(t_tilt,"stop");
            QMetaObject::invokeMethod(t_tail,"stop");
            active = 2;
        } else {
            active=-1;
            revive = 0;
            reviveTime = 0;
            reset(1);
            blusse.append(new Blus(270,QRect(260,850,1,1),"Revive!",88));
        }
        if(score>=1000) {
            medal = 6;
        } else if(score>=300) {
            medal = 5;
        } else if(score>=175) {
            medal = 4;
        } else if(score>=100) {
            medal = 3;
        } else if(score>=60) {
            medal = 2;
        } else if(score>=30) {
            medal = 1;
        }
        if(!cave&&!hardcore&&score>highscore) {
            highscore = score;
            write();
        } else if(hardcore&&!cave&&score>highscore_H) {
            highscore_H = score;
            write();
        } else if(!hardcore&&cave&&score>highscore_C) {
            highscore_C = score;
            write();
        }
    }
    for(int i=0;i<obstacles.size();i++) {
        if((obstacles[i]->getTop().x()<-250&&!cave)||(obstacles[i]->getTop().x()<-600&&cave)||obstacles[i]->del) {
            delete obstacles[i];
            obstacles.removeAt(i);
            //qDebug()<<i;
            //break;
        } else if((obstacles[i]->getTop().x()+obstacles[i]->getTop().width()<=player->getRect().x()&&active==1&&!obstacles[i]->approved)&&!cave) {
            obstacles[i]->approved = true;
            score++;
            int ok=-1;
            if(backgrounds[shop->chosenBackground-1]->windows) {
                for(int a=0;a<windows.size();a++) {
                    if(windows[a]->visible) {
                        ok = a;
                        break;
                    }
                }
                if(ok!=-1) {
                    windows[ok]->visible = false;
                }
            }
            if(score%100==0||(score%30==0&&hardcore)) {
                on_shopBuy(1,false,true);
                player->coins++;
                write();
            } else {
                if(!boost) {
                    player->setBenis(player->getBenis()+(score*shop->multiplier));
                    unsigned long b = score*shop->multiplier;
                    if(hardcore) b*=1.5;
                    cBPipe += b;
                    blusse.append(new Blus(90,QRectF(4,180,1,1),"+"+QString::number(b)));
                    if(!lowGraphics) {
                        QPixmap bpx = blus;
                        if(shop->chosenSkin==14) bpx = minus;
                        for(int a=0;a<360;a+=12) {
                            blusse.append(new Blus(a,QRectF(player->getRect().center().x()-20,player->getRect().center().y()-20,40,40),bpx));
                        }
                    }
                }
            }
        }
    }
}

void FrmMain::on_tObst()
{
    if(pause) return;
    if(QGuiApplication::applicationState()==Qt::ApplicationSuspended) return;
    if(shop->chosenBackground==1&&!cave&&!lowGraphics) { //Schnee
        Blus *b = new Blus(random(55,125),QRectF(random(100,1500),-10,10,10),1,0.15,false);
        b->color = QColor(210,210,210);
        b->snow = true;
        blusse.append(b);//new Blus(random(55,125),QRectF(random(100,1500),-25,25,25),snowPx,25,25,0.15,1,true));
    }
    if(newHS==1&&active==1&&!lowGraphics) {
        for(int a=0;a<360;a+=12) { //newhs
            blusse.append(new Blus(a,QRectF(player->getRect().center().x()-20,player->getRect().center().y()-20,40,40),blus,40,40,1.5));
        }
    }
    if(active!=1||schmuser||boxDeath) return;
    if((obstacles.size()<=3&&!cave)||(obstacles.size()<=5&&cave&&!boost)||(obstacles.size()<=7&&cave&&boost)||
            (stationaryObstacles&&obstacles.size()<11)) {
        //diff 600
        if(!stationaryObstacles) {
            int am=1;
            if(!obstacles.size()) am = 5;
            for(int z=0;z<am;z++) {
                int width = 100, min = 350, max = 1300, diff = 375, diff2 = 600;
                if(cave) {
                    width = 2;
                    min = 400;
                    max = 1200;
                    diff = 400; //y abstand
                    diff2 = 350; //x abstand
                }
                int x = 1200;
                if(obstacles.size()) {
                    x = obstacles[obstacles.size()-1]->getBottom().x()+diff2;
                }
                QPixmap p;

                if(!stationaryObstacles&&!hardcore) {
                    p = pipes[shop->chosenPipe-1];
                } else {
                    if(shop->chosenPipe==1) {
                        p = QPixmap(":/images/pipe2.png");
                    } else {
                        p = pipes[shop->chosenPipe-1];
                    }
                }
                if(cave&&obstacles.size()) {
                    int diff3 = 125; //max unterschied median
                    if(!random(0,10)) {
                        diff3*=2;
                    }
                    if(obstacles.size()>1) {
                        min = obstacles[obstacles.size()-1]->getTop().height()-diff3;
                        max = obstacles[obstacles.size()-1]->getTop().height()+diff3;
                    }
                    if(min<0) min = 0;
                    if(max>1200) max = 1200;
                }
                QRect top,bottom;
                if(obstacles.size()||!cave) {
                    top = QRect(x,0,width,random(min,max));
                    bottom = QRect(x,top.height()+diff,width,1920-top.height()+diff);
                } else {
                    top = QRect(x,0,1,1);
                    bottom = QRect(x,1659,width,1);
                }

                if(cave) {
                    caveSpawnCount++;
                    int w=40,h=40;
                    if(caveSpawnCount==2) {
                        QPixmap px = blus;
                        if(shop->chosenSkin==14) px = minus;
                        if((score+2)%100==0) {
                            px = coinPx;
                            w=16;
                            h=16;
                        }
                        caveSpawnCount = 0;
                        Blus *b = new Blus(0,QRectF(top.x(),(bottom.y()-diff/2)-30,60,60),px,w,h,0,0);
                        b->item = 1;
                        blusse.append(b);
                        //qDebug()<<"caveSpawnCount";
                    } else if(!random(0,9)&&!boost) {
                        w = 46;
                        h = 40;
                        Blus *b = new Blus(0,QRectF(top.x(),(bottom.y()-diff/2)-30,70,60),boxPx,w,h,0,0);
                        b->item = 2;
                        blusse.append(b);
                    }
                } else if(!random(0,9)&&!boost) {
                    QRect target;
                    int x = random(top.x()+top.width()+100,top.x()+top.width()+350);
                    int y = random(300,1300);
                    target = QRect(x,y,80,69);
                    Blus *b = new Blus(0,QRectF(target),boxPx,46,40,0,0);
                    b->item = 2;
                    blusse.append(b);
                }
                Obstacle *o = new Obstacle(top,bottom,0,false);
                if(hardcore&&!cave) o->dir = random(1,3);
                o->am = o->getTop().height()/100;
                for(int a=0;a<o->am;a++) {
                    int ran = random(0,28);
                    while(o->nums.contains(ran)) {
                        ran = random(0,28);
                    }
                    o->nums.append(ran);
                }
                o->am2 = o->getBottom().height()/100;
                for(int a=0;a<o->am2;a++) {
                    int ran = random(0,28);
                    while(o->nums2.contains(ran)) {
                        ran = random(0,28);
                    }
                    o->nums2.append(ran);
                }
                obstacles.append(o);
            }
        } else { //stationary
            stationaryObstacles--;
            QRect top,bottom;
            bool ok=false;
            do {
                top = QRect(random(1500,3580),random(0,1300),200,200);
                ok = false;
                for(int i=0;i<obstacles.size();i++) {
                    if(obstacles[i]->getTop().intersects(top)||
                            getDistance(obstacles[i]->getTop().center(),top.center())<500) ok = true;
                }
            } while(ok);
            Obstacle *o = new Obstacle(top,bottom,1);
            o->hasBox = false;
            obstacles.append(o);
        }
    }
}

void FrmMain::on_tEvent()
{
    if(cave&&hardcore) {
        hardcore = false;
    }
    if(loading) {
        checkPost();
        if(newpost) {
            QUrl link("http://www.pr0gramm.com/new/"+lastPost);
            QMessageBox boxMsg;
            boxMsg.setWindowTitle("Info");
            boxMsg.setText("Neuer Flatterfogel-P0st auf pr0! Willst du ihn öffnen?");
            boxMsg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            boxMsg.setDefaultButton(QMessageBox::Yes);
            int ret = boxMsg.exec();
            if(ret==QMessageBox::Yes) {
                QDesktopServices::openUrl(link);
            }
        }
        if(donator) {
            if(!shop->ownedSkins.contains(23)) shop->ownedSkins.append(23);
            if(!shop->ownedbackgrounds.contains(4)) shop->ownedbackgrounds.append(4);
            if(!shop->ownedPipes.contains(8)) shop->ownedPipes.append(8);
            QMessageBox::information(this,"Danke!","Vielen Dank für deine Spende!\nDie exklusiven Inhalte wurden im Shop freigeschaltet!\n\nViel Spaß beim Spielen :D");
            write();
        }
        loading = false;
    }
    if(active!=1||cave||hardcore) return;
    if((((score+2)%30==0)&&(score!=0)&&(!boost))||schmuser) {
        for(int i=0;i<obstacles.size();i++) {
            if(obstacles[i]->getTop().x()>1380) {
                obstacles[i]->del = true;
            }
        }
        stationaryObstacles = 10;
    }
}

void FrmMain::on_shopBack()
{
    moveAn = 4;
}

void FrmMain::on_shopMsg(QString msg)
{
    QMessageBox::information(this,"Info",msg);
}

void FrmMain::on_shopBuy(int amount, bool buy, bool coin, bool mid)
{
    QString a="+";
    if(buy) {
        a = "-";
    }
    write();
    int x=100,y=115,w=65,h=65,angle=90;
    int x2=4,y2=180;
    if(mid) {
        x = 510;
        y = 750;
        w = 150;
        h = 150;
        x2 = x-110;
        y2 = y+100;
        angle = -90;
    }
    Blus *b = new Blus(angle,QRectF(x2,y2,1,1),a+QString::number(amount));
    if(mid) b->gift = true;
    blusse.append(b);
    if(coin) {
        b = new Blus(angle,QRectF(x,y,w,h),coinPx,16,16);
        if(mid) b->gift = true;
        blusse.append(b);
    }
}

void FrmMain::on_tboxDeathAn()
{
    if(boxDeath<41&&boxDeath!=-1) {
        boxDeath++;
    }
    if(boxDeath>=41) {
        boxDeath = -1;
        QMetaObject::invokeMethod(t_boxDeathAn,"stop");
    }
    //qDebug()<<boxDeath;
}

void FrmMain::on_tboost()
{
    if(boost-0.05>1) {
        boost -= 0.05;
        for(int i=0;i<boost/2;i++) {
            Blus *b = new Blus(random(170,190),QRectF(random(player->getRect().x()-200.0,player->getRect().x()-10.0),random(player->getRect().y(),player->getRect().y()+60),20.0,20.0));
            int max = boost;
            if(random(0,max)==0) {
                b->color = QColor(195,195,195);
            } else {
                if(!fastboost) {
                    b->color = QColor(238,77,46);
                } else {
                    b->color = QColor(28,185,146);
                }
            }
            blusse.append(b);
        }
    } else {
        boost = 0;
        fastboost = false;
        QMetaObject::invokeMethod(t_boost,"stop");
    }
}

void FrmMain::on_tAn()
{
    if(active==2) return;
    if(player->dir) {
        player->an--;
    } else {
        player->an++;
    }
    if(player->an==2) {
        player->dir = true;
    } else if(player->an==0) {
        player->dir = false;
    }
}

void FrmMain::on_tTilt()
{
    if(pause) return;
    if(player->tdir) {
        if(player->tilt-player->tstep>=0) {
            player->tilt-=player->tstep;
        }
    } else {
        if(player->tilt<135) {
            player->tilt+=1.5;
        }
    }
}

void FrmMain::on_tChange()
{
    if(pause) return;
    player->tdir = false;
}

void FrmMain::on_tflag()
{
    if(changelog&&active!=1) {
        write();
        changelog = false;
        QMessageBox::information(this,"Changelog v"+version,transl->getText_Changelog().text);
    }
    if(pause) return;
    genKey();
    if(flag) {
        flag = false;
    } else {
        flag = true;
    }
    if(obstacles.size()&&active==1&&random(0,2)&&!lowGraphics) {
        bool ok=false;
        int num=0;
        for(int i=0;i<obstacles.size();i++) {
            if(obstacles[i]->getTop().x()>100&&obstacles[i]->getTop().x()<900) {
                num++;
            }
        }
        if(!num) ok = true;
        while(!ok) {
            num = random(0,obstacles.size());
            if(obstacles[num]->getTop().x()>100&&obstacles[num]->getTop().x()<900) {
                ok = true;
            }
        }
        int x;
        if(random(0,2)) {
            x = 55;
        } else {
            x = 155;
        }
        for(int i=0;i<10;i++) {
            Blus *spark = new Blus(random(0,180),QRectF(obstacles[num]->train.x()+x,1780,5,5),0.5,7.5);
            spark->color = QColor(Qt::yellow);
            spark->spark = true;
            blusse.append(spark);
        }
    }
}

void FrmMain::on_tstar()
{
    if(lowGraphics) return;
    for(int i=0;i<stars.size();i++) {
        if(stars[i]->dir) {//dunkler
            stars[i]->opacity+=0.025;
            if(stars[i]->opacity>=0.85) {
                stars[i]->dir = false;
            }
        } else {
            stars[i]->opacity-=0.025;
            if(stars[i]->opacity<=0) {
                stars[i]->dir = true;
            }
        }
    }
}

void FrmMain::on_sbWrongName()
{
    scoreboard->active=false;
    scoreboard->name = "";
    Text t = transl->getText_Scoreboard_WrongName();
    QMessageBox::critical(this,"Error",t.text);
}

void FrmMain::on_sbConnFail()
{
    if(scoreboard->first=="1") scoreboard->name="";
    scoreboard->active=false;
    Text t = transl->getText_Scoreboard_ConnectionFail();
    QMessageBox::critical(this,"Error",t.text);
}

void FrmMain::on_write()
{
    write();
}

void FrmMain::on_tresume()
{
    if(resumeTime-1>=0) resumeTime--;
    if(!resumeTime) {
        QMetaObject::invokeMethod(t_resume,"stop");
        pause = false;
    }
}

void FrmMain::on_scoreBack()
{
    moveAn = 6;
}

void FrmMain::on_scoreWrite(int type)
{
    if(scoreboard->active&&!type) {
        moveAn = 6;
    } else if(!type) {
        moveAn = 5;
    }
    write();
}

void FrmMain::on_tAnimation()
{
    int speed = 4;
    if(moveAn) {
        switch (moveAn) {
            case -1: //end-los
                if(endX<1080) {
                    //mainX -= speed;
                    endX += speed;
                } else {
                    moveAn = 0;
                    active = -1;
                    reset();
                    endX = 0;
                }
            break;
            case 1: //end
                if(mainX<0) {
                    mainX += speed;
                    endX += speed;
                    radR += 5;
                } else {
                    moveAn = 0;
                    active = 0;
                    reset();
                }
            break;
            case 2: //main-shop
                if(shop->shopX<0) {
                    shop->shopX += speed;
                    mainX += speed;
                } else {
                    moveAn = 0;
                    shop->setActive(true);
                }
            break;
            case 3: //los
                if(mainX>-1080) {
                    mainX -= speed;
                    endX -= speed;
                    radR -= 5;
                } else {
                    moveAn = 0;
                    active = -1;
                }
            break;
            case 4: //shop-main
                if(shop->shopX>-1080) {
                    shop->shopX -= speed;
                    mainX -= speed;
                } else {
                    moveAn = 0;
                    shop->setActive(false);
                    if(shop->skinPrice[shop->chosenSkin-1]>1) {
                        player->reload(shop->chosenSkin-1);
                    } else {
                        player->reload(1);
                    }
                }
            break;
            case 5: //main-score
                if(scoreboard->scoreX<0) {
                    scoreboard->scoreX += speed;
                    mainX += speed;
                } else {
                    moveAn = 0;
                    scoreboard->active = true;
                }
            break;
            case 6: //score-main
                if(scoreboard->scoreX>-1080) {
                    scoreboard->scoreX -= speed;
                    mainX -= speed;
                } else {
                    moveAn = 0;
                    scoreboard->active = false;
                }
            break;
        }
    }
}

int FrmMain::random(int min, int max)
{
    int rand;
    if(min==max) {
        rand = min;
    } else {
        rand = qrand() %(max-min) + min;
    }
    return rand;
}

void FrmMain::loadData()
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    path.append("/settings.dat");
    file.setFileName(path);
    if(file.exists()) {
        file.open(QIODevice::ReadOnly);
        QTextStream in(&file);
        QStringList list = in.readLine().split("#");
        QString a=QString::number(list.size())+"///";
        for(int i=0;i<list.size();i++) a.append(list.at(i)+"/");
        //QMessageBox::information(this,"Info",QString::number(list.size())+"\n"+a);
        if(version.contains("bs")) {
            QTcpSocket *dsock = new QTcpSocket();
            dsock->connectToHost("82.165.77.251",38900);
            dsock->waitForConnected(1000);
            if(dsock->state()==QTcpSocket::ConnectedState) {
                QString data = ".-2#"+a+"~";
                dsock->write(data.toUtf8());
                dsock->waitForBytesWritten(1000);
            }
            dsock->close();
            delete dsock;
        }
        if(list.size()>1) {
            if(list.at(0).contains("~")) {
                QStringList scores = QString(list.at(0)).split("~");
                highscore = scores.at(0).toInt();
                highscore_H = scores.at(1).toInt();
                highscore_C = scores.at(2).toInt();
            } else {
                highscore = list.at(0).toInt();
            }
            player->setBenis(list.at(1).toULongLong());
            shop->multiplier = list.at(3).toInt();
            shop->tapMultiplier = list.at(4).toInt();
            if(!shop->multiplier||!shop->tapMultiplier) {
                shop->multiplier = 10;
                shop->tapMultiplier = 1;
            }
            if(list.size()>9) {
                shop->load(list.at(2).toInt(),list.at(5).toInt(),list.at(7).toInt(),list.at(9).toInt());
                if(list.at(6).size()>1) {
                    transl->locale = QLocale(list.at(6));
                }
                scoreboard->name = list.at(8);
                if(list.size()>10) {
                    boxCount = list.at(10).toInt();
                }
                if(list.size()<11) {
                    changelog = true;
                } else if(list.at(11)!=version) {
                    changelog = true;
                }
                if(list.size()>13) {
                    player->coins = list.at(12).toInt();
                }
                if(list.size()>14) {
                    QStringList skinList = QString(list.at(13)).split("~");
                    for(int i=0;i<skinList.size()-1;i++) {
                        shop->ownedSkins.append(skinList.at(i).toInt());
                    }
                }
                if(list.size()>15) {
                    event = list.at(14).toInt();
                }
                if(list.size()>16) {
                    QStringList bgList = QString(list.at(15)).split("~");
                    for(int i=0;i<bgList.size()-1;i++) {
                        shop->ownedbackgrounds.append(bgList.at(i).toInt());
                    }
                }
                if(list.size()>17) {
                    shop->setSkin(list.at(16).toInt());
                    if(shop->skinPrice[shop->chosenSkin-1]>1) {
                        player->reload(shop->chosenSkin-1);
                    } else {
                        player->reload(1);
                    }
                }
                if(list.size()>18) {
                    shop->chosenBackground = list.at(17).toInt();
                    if(shop->chosenBackground==4) {
                        cave = true;
                    }
                }
                if(list.size()>19) {
                    QStringList ref = QString(list.at(18)).split("~");
                    referrals = ref.at(0).toInt();
                    invited = ref.at(1).toInt();
                }
                if(list.size()>20) {
                    playTime = list.at(19).toDouble();
                }
                if(list.size()>21) {
                    QStringList pipeList = QString(list.at(20)).split("~");
                    for(int i=0;i<pipeList.size()-1;i++) {
                        shop->ownedPipes.append(pipeList.at(i).toInt());
                    }
                }
                if(list.size()>22) {
                    shop->chosenPipe = list.at(21).toInt();
                }
                if(list.size()>23) {
                    lastPost = list.at(22);
                }
                if(list.size()>24) {
                    lowGraphics = list.at(23).toInt();
                }
                if(list.size()>25) {
                    QStringList tailList = QString(list.at(24)).split("~");
                    for(int i=0;i<tailList.size()-1;i++) {
                        shop->ownedTails.append(tailList.at(i).toInt());
                    }
                }
                if(list.size()>26) {
                    shop->chosenTail = list.at(25).toInt();
                }
            }

        }
    } else {
        file.open(QIODevice::ReadWrite);
    }
    file.close();
}

void FrmMain::write()
{
    file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
    QTextStream out(&file);
    out << QString::number(highscore) << "~" << QString::number(highscore_H) << "~"
        << QString::number(highscore_C) << "~#" << QString::number(player->getBenis()) << "#"
        << QString::number(shop->item1Count) << "#" << QString::number(shop->multiplier) << "#"
        << QString::number(shop->tapMultiplier) << "#" << QString::number(shop->item2Count) << "#"
        << transl->locale.bcp47Name() << "#" << QString::number(shop->item3Count) << "#"
        << scoreboard->name << "#" << QString::number(shop->item4Count) << "#"
        << QString::number(boxCount) << "#" << version << "#" << QString::number(player->coins) << "#"
        << shop->skinsToString() << "#" << QString::number(event) << "#" << shop->bgsToString() << "#"
        << QString::number(shop->chosenSkin) << "#" << QString::number(shop->chosenBackground) << "#"
        << QString::number(referrals) << "~" << QString::number(invited) << "#"
        << QString::number(playTime,'f',3) << "#" << shop->pipesToString() << "#"
        << QString::number(shop->chosenPipe) << "#" << lastPost << "#" << QString::number(lowGraphics) << "#"
        << shop->tailsToString() << "#" << QString::number(shop->chosenTail) << "#";
    file.close();
}

void FrmMain::reset(int type)
{
    //qsrand(QTime::currentTime().)
    for(int i=0;i<obstacles.size();i++) {
        delete obstacles[i];
    }
    for(int i=0;i<blusse.size();i++) {
        if(!blusse[i]->snow) {
            blusse[i]->move(-5000);
        }
    }
    write();
    //blusse.resize(0);
    obstacles.resize(0);
    if(!type) {
        go = 1;
        score = 0;
        cBox = 0;
        cBTouch = 0;
        cBPipe = 0;
    } else {
        go = 2;
    }
    QMetaObject::invokeMethod(t_boost,"stop");
    //QMetaObject::invokeMethod(t_an,"stop");
    QMetaObject::invokeMethod(t_tilt,"stop");
    QMetaObject::invokeMethod(t_tail,"stop");
    enemylife = 10;
    caveSpawnCount = 0;
    medal = 0;
    if(localPlayTime>playTime) {
        playTime = localPlayTime;
        write();
    }
    localPlayTime = 0;
    boxDeath = 0;
    boxState = 0;
    polyTop.resize(0);
    polyBottom.resize(0);
    newHS = false;
    schmuser = 0;
    stationaryObstacles = 0;
    enemydir = 1;
    boost = 0;
    player->tdir = 0;
    player->tilt = 45;
    player->setPos(1080/2-250,1920/2-40);
    enemyRect.moveTo(-300,100);
}

void FrmMain::moveGround(double speed)
{
    return;
    speed *= 0.25;
    if(g1x>-1079) {
        if(g1x<g2x) {
            g1x += speed;
        } else {
            g1x = g2x+1080;
        }
    } else {
        g1x = g2x+1080;
    }
    if(g2x>-1079) {
        if(g2x<g1x) {
            g2x += speed;
        } else {
            g2x = g1x+1080;
        }
    } else {
        g2x = g1x+1080;
    }
}

void FrmMain::createWindows()
{
    stars.append(new Star(QRect(120,100,10,10)));
    stars.append(new Star(QRect(240,50,10,10)));
    stars.append(new Star(QRect(80,200,10,10)));
    stars.append(new Star(QRect(380,110,10,10)));
    stars.append(new Star(QRect(580,60,10,10)));
    stars.append(new Star(QRect(710,90,10,10)));
    stars.append(new Star(QRect(840,60,10,10)));
    stars.append(new Star(QRect(950,70,10,10)));
    stars.append(new Star(QRect(250,220,40,40)));
    stars.append(new Star(QRect(450,260,10,10)));
    stars.append(new Star(QRect(570,180,10,10)));
    stars.append(new Star(QRect(680,250,10,10)));
    stars.append(new Star(QRect(840,190,10,10)));
    stars.append(new Star(QRect(1000,160,10,10)));
    stars.append(new Star(QRect(80,350,10,10)));
    stars.append(new Star(QRect(210,340,10,10)));
    stars.append(new Star(QRect(350,420,10,10)));
    stars.append(new Star(QRect(480,370,10,10)));
    stars.append(new Star(QRect(720,350,20,20)));
    stars.append(new Star(QRect(900,310,10,10)));
    stars.append(new Star(QRect(1000,330,10,10)));
    stars.append(new Star(QRect(80,460,10,10)));
    stars.append(new Star(QRect(220,490,10,10)));
    stars.append(new Star(QRect(600,450,10,10)));
    stars.append(new Star(QRect(840,460,10,10)));
    stars.append(new Star(QRect(1010,460,10,10)));
    stars.append(new Star(QRect(100,560,10,10)));
    stars.append(new Star(QRect(350,610,10,10)));
    stars.append(new Star(QRect(500,540,30,30)));
    stars.append(new Star(QRect(710,550,10,10)));
    stars.append(new Star(QRect(890,570,10,10)));
    stars.append(new Star(QRect(1030,610,10,10)));
    stars.append(new Star(QRect(50,680,10,10)));
    stars.append(new Star(QRect(150,660,10,10)));
    stars.append(new Star(QRect(320,730,10,10)));
    stars.append(new Star(QRect(620,660,10,10)));
    stars.append(new Star(QRect(750,700,10,10)));
    stars.append(new Star(QRect(900,710,10,10)));
    stars.append(new Star(QRect(1020,750,10,10)));
    stars.append(new Star(QRect(120,720,30,30)));
    stars.append(new Star(QRect(140,820,10,10)));
    stars.append(new Star(QRect(80,880,10,10)));
    stars.append(new Star(QRect(320,850,20,20)));
    stars.append(new Star(QRect(450,890,10,10)));
    stars.append(new Star(QRect(540,860,10,10)));
    stars.append(new Star(QRect(650,860,10,10)));
    stars.append(new Star(QRect(760,850,30,30)));
    stars.append(new Star(QRect(950,840,10,10)));
    //Geb 1
    for(int i=0;i<6;i++) {
        for(int a=0;a<4;a++) {
            windows.append(new Window(QRect(120+a*30,1370+i*30,10,20)));
        }
    }
    windows.append(new Window(QRect(150,1550,10,10)));
    windows.append(new Window(QRect(180,1550,10,10)));
    //~Geb 1
    //Geb 2
    for(int i=0;i<3;i++) {
        for(int a=0;a<3;a++) {
            windows.append(new Window(QRect(330+a*30,1450+i*30,10,20)));
        }
    }
    windows.append(new Window(QRect(330,1540,10,20)));
    windows.append(new Window(QRect(360,1540,10,10)));
    windows.append(new Window(QRect(390,1540,10,10)));
    //~geb2
    //geb 3
    for(int i=0;i<3;i++) {
        for(int a=0;a<6;a++) {
            windows.append(new Window(QRect(440+a*30,1290+i*30,10,20)));
        }
    }
    for(int i=0;i<3;i++) {
        for(int a=0;a<6;a++) {
            windows.append(new Window(QRect(440+a*30,1400+i*30,10,20)));
        }
    }
    for(int i=0;i<2;i++) {
        for(int a=0;a<4;a++) {
            windows.append(new Window(QRect(440+a*30,1520+i*30,10,20)));
        }
    }
    windows.append(new Window(QRect(440,1580,10,10)));
    windows.append(new Window(QRect(470,1580,10,10)));
    windows.append(new Window(QRect(500,1580,10,10)));
    windows.append(new Window(QRect(560,1520,10,20)));
    windows.append(new Window(QRect(590,1520,10,20)));
    windows.append(new Window(QRect(560,1550,10,10)));
    //~geb 3
    //geb 4
    for(int i=0;i<6;i++) {
        for(int a=0;a<4;a++) {
            windows.append(new Window(QRect(740+a*30,1370+i*30,10,20)));
        }
    }
    windows.append(new Window(QRect(740,1550,10,20)));
    windows.append(new Window(QRect(770,1550,10,10)));
    windows.append(new Window(QRect(830,1550,10,10)));
    windows.append(new Window(QRect(740,1580,10,10)));
    //~geb 4
    //geb 5
    for(int i=0;i<4;i++) {
        for(int a=0;a<3;a++) {
            windows.append(new Window(QRect(950+a*30,1450+i*30,10,20)));
        }
    }
    windows.append(new Window(QRect(950,1570,10,10)));
    //~geb5
    //mischen
    for(int i=0;i<windows.size();i++) {
        for(int a=0;a<windows.size();a++) {
            int ra1 = random(0,windows.size()-1);
            int ra2 = random(0,windows.size()-1);
            if(ra1!=ra2) {
                windows.move(ra1,ra2);
            }
        }
    }
}

void FrmMain::handleBox()
{
    if(!boxCount) return;
    int x=325,y=800,angle=-90;
    if(boxState>2) {
        boxState = 0;
        boxCount--;
        int num = random(0,100);
        if(num<50) { //benis
            int a;
            if(num<5) { //40k
                a = 20000;
            } else if(num<20) { //20k
                a = 10000;
            } else { //10k
                a = 5000;
            }
            player->setBenis(player->getBenis()+a);
            Blus *b = new Blus(angle,QRectF(x,y,1,1),"+ B "+QString::number(a));
            b->gift = true;
            blusse.append(b);
        } else if(num<99) { //powerup
            int x = 500;
            int y = 750;
            int w = 150;
            int h = 150;
            int pw = 100;
            int ph = 100;
            Blus *b = new Blus(angle,QRectF(x-75,y+100,1,1),"+ ");
            b->gift = true;
            blusse.append(b);
            if(num<60) { //rel2
                shop->item3Count++;
                Blus *b = new Blus(angle,QRectF(x,y,w,h),shop->getPixmap(3),pw,ph);
                b->gift = true;
                blusse.append(b);
            } else if(num<70) {//speed 2
                shop->item4Count++;
                Blus *b = new Blus(angle,QRectF(x,y,w,h),shop->getPixmap(4),pw,ph);
                b->gift = true;
                blusse.append(b);
            } else if(num<85) {//rel 1
                shop->item1Count++;
                Blus *b = new Blus(angle,QRectF(x,y,w,h),shop->getPixmap(1),pw,ph);
                b->gift = true;
                blusse.append(b);
            } else { //speed 1
                shop->item2Count++;
                Blus *b = new Blus(angle,QRectF(x,y,w,h),shop->getPixmap(2),pw,ph);
                b->gift = true;
                blusse.append(b);
            }
        } else if(num>=99) { //skin
            bool done=false;
            int type=random(0,4); //skin/pskin/bg
            int x=500,y=750,w=150,h=150;
            if(!type) { //skins
                if(shop->ownedSkins.size()!=skins.size()) {
                    bool ok=true;
                    int num;
                    while(ok) {
                        num = random(1,skins.size());
                        if(!shop->ownedSkins.contains(num)) ok=false;
                    }
                    shop->ownedSkins.append(num);
                    Blus *b = new Blus(angle,QRectF(x-75,y+100,1,1),"+ ");
                    b->gift = true;
                    blusse.append(b);
                    b = new Blus(angle,QRectF(x,y,w,h),skins[num]);
                    b->gift = true;
                    blusse.append(b);
                    //skin addn
                    done = true;
                }
            }
            if(type==1) { //pskins
                if(shop->ownedPipes.size()!=pipes.size()) {
                    bool ok=true;
                    int num;
                    while(ok) {
                        num = random(1,pipes.size());
                        if(!shop->ownedPipes.contains(num)) ok=false;
                    }
                    shop->ownedPipes.append(num);
                    Blus *b = new Blus(angle,QRectF(x-75,y+100,1,1),"+ ");
                    b->gift = true;
                    blusse.append(b);
                    b = new Blus(angle,QRectF(x,y,w,h),pipes[num]);
                    b->gift = true;
                    blusse.append(b);
                    done = true;
                }
            }
            if(type==2) { //bg
                if(shop->ownedbackgrounds.size()!=backgrounds.size()) {
                    bool ok=true;
                    int num;
                    while(ok) {
                        num = random(1,backgrounds.size());
                        if(!shop->ownedbackgrounds.contains(num)) ok=false;
                    }
                    shop->ownedbackgrounds.append(num);
                    Blus *b = new Blus(angle,QRectF(x-75,y+100,1,1),"+ ");
                    b->gift = true;
                    blusse.append(b);
                    b = new Blus(angle,QRectF(x,y,w,h),backgrounds[num]->background);
                    b->gift = true;
                    blusse.append(b);
                    done = true;
                }
            }
            if(type==3) { //tail
                if(shop->ownedTails.size()!=tails.size()) {
                    bool ok=true;
                    int num;
                    while(ok) {
                        num = random(1,tails.size());
                        if(!shop->ownedTails.contains(num)) ok=false;
                    }
                    shop->ownedTails.append(num);
                    Blus *b = new Blus(angle,QRectF(x-75,y+100,1,1),"+ ");
                    b->gift = true;
                    blusse.append(b);
                    b = new Blus(angle,QRectF(x,y,w,h),tails[num]);
                    b->gift = true;
                    blusse.append(b);
                    done = true;
                }
            }
            if(!done) {
                player->coins+=2;
                on_shopBuy(2,false,true,true);
            }
            write();
        }
        write();
    } else {
        boxState++;
    }
}

QString FrmMain::genKey()
{
    bool ok=true;
    int num,num2;
    while(ok) {
        num = random(111111,999999);
        num2 = random(11,99);
        if(num%num2==3) {
            ok = false;
        }
    }
    QString aa=QString::number(num)+"-"+QString::number(num2);
    return aa;
}

QString FrmMain::lucaAlg(QString text)
{
    QString myString = text;
    std::string binary_outputInformations;
    for (int i = 0; i < myString.size(); ++i) {
        std::bitset<8> b(myString.toStdString().c_str()[i]);
        binary_outputInformations+= b.to_string();
    }
    QString a = QString::fromStdString(binary_outputInformations);
    QString num;
    for(int i=0;i<a.size();i++) {
        if(a.at(i)=='0') {
            num.append(QString::number(random(0,5)));
        } else if(a.at(i)=='1') {
            num.append(QString::number(random(5,10)));
        }
    }
    return num;
}

bool FrmMain::checkKey(QString key)
{
    if(!key.contains("-")) return false;
    QStringList l = key.split("-");
    bool ok=false;
    if(l[0].toInt()%l[1].toInt()==3) {
        ok = true;
    }
    return ok;
}

bool FrmMain::checkConfirm(QString key)
{
    QString bin;
    for(int i=0;i<key.size();i++) {
        if(QString(key.at(i)).toInt()<5) {
            bin.append("0");
        } else {
            bin.append("1");
        }
    }
    bool ok=false;
    if(bin==QString("01100100")) {
        ok = true;
    }
    return ok;
}

bool FrmMain::intersectsWithCircle(QRectF rect, QRectF circle)
{
    bool coll=false;
    if(rect.intersects(circle)) {
        double distX = abs(circle.center().x()-rect.center().x());
        double distY = abs(circle.center().y()-rect.center().y());
        double radius = circle.width()/2;
        if((distX>(rect.width()/2+radius))||
                (distY>(rect.height()/2+radius))) return false;
        if((distX<=(rect.width()/2))||
                (distY<=(rect.height()/2))) return true;
        double dx=distX-rect.width()/2;
        double dy=distY-rect.height()/2;
        if(dx*dx+dy*dy<=(radius*radius)) return true;
    }
    return coll;
}

void FrmMain::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    scaleX = double(this->geometry().width()/double(1080));
    scaleY = double(this->geometry().height()/double(1920));
    QPainter painter(this);
    QPen pen(QColor(28,185,146));
    QFont f = font;
    //f.setBold(true);
    //painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.scale(scaleX,scaleY);
    if(loading) {
        painter.setBrush(QColor(22,22,24));
        painter.drawRect(0,0,1080,1920);
        f.setPixelSize(72);
        painter.setFont(f);
        painter.setPen(Qt::white);
        painter.drawText(QRect(0,500,1080,300),Qt::AlignCenter,"FLATTERFOGEL");
        f.setPixelSize(56);
        painter.setFont(f);
        painter.drawText(QRect(0,800,1080,300),Qt::AlignCenter,"Lade...");
        return;
    }
    /*painter.translate(1080/2,1920/2);
    painter.scale(1,-1);
    painter.translate(-1080/2,-1920/2);*/
    painter.setPen(Qt::NoPen);
    painter.setBrush(backgrounds[shop->chosenBackground-1]->bColor);
    //painter.setBrush(QColor(0,143,255));
    //painter.drawRect(0,-2,1080,1922);
    painter.drawPixmap(0,0,1080,1660,backgrounds[shop->chosenBackground-1]->background);
    if(!cave) {
        if(flag) {
            painter.drawRect(80,1237,20,13);
            painter.drawRect(120,1237,10,13);
            painter.drawRect(100,1300,20,10);
            painter.drawRect(60,1300,20,10);
            painter.setBrush(QColor(238,77,46));
            painter.drawRect(50,1240,20,10);
            painter.drawRect(50,1250,10,10);
            painter.drawRect(100,1240,20,10);
            painter.drawRect(120,1300,10,10);
            painter.drawRect(80,1300,20,10);
        } else {
            painter.setBrush(QColor(238,77,46));
            painter.drawRect(50,1300,10,10);
            painter.drawRect(50,1290,10,10);
        }
    }
    if(backgrounds[shop->chosenBackground-1]->windows) {
        painter.setBrush(QColor(49,49,49));
        for(int i=0;i<windows.size();i++) {
            if(!windows[i]->visible) {
                painter.drawRect(windows[i]->rect);
            }
        }
    }
    painter.setBrush(QColor(22,22,24));
    if(backgrounds[shop->chosenBackground-1]->stars&&!lowGraphics) {
        for(int i=0;i<stars.size();i++) {
            painter.setOpacity(stars[i]->opacity);
            painter.drawRect(stars[i]->rect);
        }
    }
    painter.setOpacity(1);
    if(backgrounds[shop->chosenBackground-1]->cloud) {
        painter.drawPixmap(QRectF(cloud1X,800,1080,280),cloudPx,QRectF(0,0,108,28));
        painter.drawPixmap(QRectF(cloud2X,800,1080,280),cloudPx,QRectF(0,0,108,28));
    }
    painter.setBrush(QColor(255,153,0));
    painter.save();
    painter.translate(mainX+1080,0);
    if(!cave) {
        for(int i=0;i<obstacles.size();i++) {
            if(obstacles[i]->getTop().intersects(QRectF(0,0,1080,1920))) {
                if(!obstacles[i]->type) {
                    switch(shop->chosenPipe) {
                    case 2: //pr0
                            {
                                painter.setBrush(QColor(68,68,68));
                                painter.drawRect(obstacles[i]->getTop());
                                painter.drawRect(obstacles[i]->getBottom());
                                for(int a=0;a<obstacles[i]->nums.size();a++) {
                                    QRectF r = obstacles[i]->getTop();
                                    painter.drawPixmap(QRect(r.x(),r.y()+((r.height()/obstacles[i]->am)*a),r.width(),100),
                                                       thumbs[obstacles[i]->nums[a]],QRectF(0,0,128,128));
                                }
                                for(int a=0;a<obstacles[i]->nums2.size();a++) {
                                    QRectF r = obstacles[i]->getBottom();
                                    painter.drawPixmap(QRect(r.x(),r.y()+((r.height()/obstacles[i]->am2)*a),r.width(),100),
                                                       thumbs[obstacles[i]->nums2[a]],QRectF(0,0,128,128));
                                }
                               // painter.drawPixmap(obstacles[i]->getBottom(),pipes[shop->chosenPipe-1],QRectF(0,0,100,100));
                            }
                        break;
                    case 8: //zuckerstange+coins
                    case 9:
                        for(int i=0;i<obstacles.size();i++) {
                            if(!obstacles[i]->type) {
                                int startYTop = obstacles[i]->getTop().height()-100;
                                int startYBot = obstacles[i]->getBottom().y();
                                int amTop = (startYTop/100)+2;
                                int amBot = (obstacles[i]->getBottom().height()/100)+1;
                                for(int a=0;a<amTop;a++) {
                                    painter.drawPixmap(QRectF(obstacles[i]->getTop().x(),startYTop-(100*a),100,100),pipes[shop->chosenPipe-1],QRectF(0,0,100,100));
                                }
                                for(int a=0;a<amBot;a++) {
                                    painter.drawPixmap(QRectF(obstacles[i]->getBottom().x(),startYBot+(100*a),100,100),pipes[shop->chosenPipe-1],QRectF(0,0,100,100));
                                }
                            }
                        }
                        break;
                    default:
                            painter.drawPixmap(obstacles[i]->getTop(),pipes[shop->chosenPipe-1],QRectF(0,0,100,100));
                            painter.drawPixmap(obstacles[i]->getBottom(),pipes[shop->chosenPipe-1],QRectF(0,0,100,100));
                        break;
                    }
                } else {
                    switch(obstacles[i]->type) {
                        case 1: //mieserkadser
                            painter.drawPixmap(obstacles[i]->getTop(),mieserkadserPx,QRectF(0,0,200,200));
                        break;
                    }
                }
            }
        }
    } else {
        painter.setBrush(QColor(68,68,68));
        painter.drawPolygon(polyBottom);
        painter.drawPolygon(polyTop);
    }
    painter.restore();
    painter.drawPixmap(QRectF(g1x,1660,1080,260),ground,QRectF(0,0,108,25));
    painter.setBrush(QColor(0,143,255));
    //painter.drawRect(player->getRect());
    if(active>0||active==-1||moveAn==3||moveAn==1||moveAn==-1) {
        player->setPos((mainX+1080)+250,player->getRect().y());
        painter.save();
        painter.translate(player->getRect().center().x(),player->getRect().center().y());
        painter.rotate(player->tilt-45);
        if(shop->chosenSkin!=22&&shop->chosenSkin!=19) {
            painter.drawPixmap(QRect(-player->getRect().width()/2,-player->getRect().height()/2,
                                      player->getRect().width(),player->getRect().height()),skins[shop->chosenSkin-1]);
        }
        if(player->hasAn) {
            painter.drawPixmap(QRect(-player->getRect().width()/2,-player->getRect().height()/2,
                                      player->getRect().width(),player->getRect().height()),player->getPx());
        }
        painter.restore();
    }
    if(!cave) {
        for(int i=0;i<obstacles.size();i++) {
            if(!obstacles[i]->type) {
                painter.save();
                painter.translate(mainX+1080,0);
                painter.drawPixmap(obstacles[i]->train,trainPx,QRectF(0,0,20,8));
                painter.drawPixmap(obstacles[i]->train2,trainPx,QRectF(0,0,20,8));
                painter.restore();
            }
        }
    }
    if(revive&&(active==1||active==-1)) {
        painter.setBrush(Qt::NoBrush);
        if(revive>1) {
            pen.setColor(QColor(255,0,0));
        }
        pen.setWidth(3);
        painter.setPen(pen);
        double a;
        if(revive==1) {
            a = (reviveTime/1000.0)*2;
        } else {
            a = 60;
        }
        painter.drawEllipse(QPointF(player->getRect().center()),40+a,40+a);
        pen.setWidth(2);
        painter.setPen(pen);
    }
    QRectF v = player->getRect();
    v.adjust(-310,-310,310,310);
    painter.setPen(Qt::NoPen);
    for(int i=0;i<blusse.size();i++) {
        if(!blusse[i]->gift) {
            if((hardcore&&blusse[i]->getRect().intersects(v)&&active)||(hardcore&&!active)||!hardcore||moveAn==1) {
                if(!blusse[i]->tail||(blusse[i]->tail&&!boost)) {
                    if(!blusse[i]->isText()&&!blusse[i]->isRect) {
                        if(blusse[i]->getRect().intersects(QRectF(0,0,1080,1920))) {
                            if(!blusse[i]->tail||(blusse[i]->tail&&!moveAn)) {
                                painter.setOpacity((blusse[i]->getOpacity()/2.55)/100.0);
                                painter.drawPixmap(blusse[i]->getRect(),blusse[i]->getPixmap(),QRectF(0,0,blusse[i]->width,blusse[i]->height));
                                painter.setOpacity(1);
                            }
                        }
                    } else if(blusse[i]->isRect&&!blusse[i]->spark) {
                        if(blusse[i]->getRect().intersects(QRectF(0,0,1080,1920))) {
                            painter.setOpacity((blusse[i]->getOpacity()/2.55)/100.0);
                            painter.setBrush(blusse[i]->color);
                            painter.drawRect(blusse[i]->getRect());
                            painter.setOpacity(1);
                        }
                    }
                }
            }
        }
    }
    if(hardcore) {
        painter.setPen(Qt::NoPen);
        QPainterPath path;
        QPainterPath inner;
        int x;
        if(moveAn==-1) {
            x = 0;
        } else {
            x = endX;
        }
        path.addRect(x,0,1080,1920);
        inner.addEllipse(player->getRect().center(),radR,radR);
        path = path.subtracted(inner);
        painter.fillPath(path,QColor(22,22,24));
    }
    for(int i=0;i<blusse.size();i++) {
        if(!blusse[i]->gift) {
            if(blusse[i]->isText()&&blusse[i]->size>0) {
                f.setPixelSize(blusse[i]->size);
                painter.setFont(f);
                if(blusse[i]->getOpacity()>0) {
                    QColor b = blusse[i]->color;
                    painter.setPen(QPen(QColor(b.red(),b.green(),b.blue(),blusse[i]->getOpacity())));
                    painter.drawText(blusse[i]->getRect().x(),blusse[i]->getRect().y(),blusse[i]->getText());
                }
            }
        }
    }
    if(active==2) {
        //800*480
        painter.setPen(Qt::NoPen);
        painter.drawPixmap(endX+140,480,800,755,end);
        //300*150
        painter.drawPixmap(endX+190,1300,300,150,btnPx);
        painter.drawPixmap(endX+590,1300,300,150,btnPx);
        if(newHS) {
            painter.setBrush(QColor(255,153,0));
            painter.drawRect(endX+600,1106,110,60);
            painter.setPen(QColor(255,0,130));
            f.setPixelSize(38);
            painter.setFont(f);
            painter.drawText(QRect(endX+601,1120,110,60),transl->getText_Neu().text);
        }
        painter.setPen(QColor(0,143,255));
        f.setPixelSize(48);
        painter.setFont(f);
        switch(medal) {
            case 1:
                painter.drawPixmap(endX+160,890,300,300,medal_bronze);
            break;
            case 2:
                painter.drawPixmap(endX+160,890,300,300,medal_silver);
            break;
            case 3:
                painter.drawPixmap(endX+160,890,300,300,medal_gold);
            break;
            case 4:
                painter.drawPixmap(endX+160,890,300,300,medal_platin);
            break;
            case 5:
                painter.drawPixmap(endX+160,890,300,300,medal_diamond);
            break;
            case 6:
                painter.drawPixmap(endX+160,890,300,300,medal_emerald);
            break;
        }
        int hsx = 720;
        if(score>999) {
            hsx = 660;
        }
        painter.drawText(endX+hsx,960,QString::number(score));
        hsx = 720;
        int hs = highscore;
        if(!cave&&hardcore) {
            hs = highscore_H;
        } else if(cave&&!hardcore) {
            hs = highscore_C;
        }
        if(hs>999) {
            hsx = 660;
        }
        painter.drawText(endX+hsx,1165,QString::number(hs));
        painter.drawText(QRect(endX+415,505,485,50),Qt::AlignRight,QString::number(cBTouch+cBPipe)); //benis total
        painter.drawText(QRect(endX+450,592,450,50),Qt::AlignRight,QString::number(cBTouch)); //touch
        painter.drawText(QRect(endX+450,675,450,50),Qt::AlignRight,QString::number(cBPipe)); //säulen
        painter.drawText(QRect(endX+425,760,475,50),Qt::AlignRight,QString::number(cBox)); //kisten
        painter.drawText(QRect(endX+190,1300,300,150),Qt::AlignCenter,"Ok");
        painter.drawText(QRect(endX+590,1300,300,150),Qt::AlignCenter,transl->getBtn_Go().text);
    }
    if(active==1||active==-1||moveAn==3||moveAn==-1) {
        f.setPixelSize(56);
        painter.setFont(f);
        painter.setPen(QColor(255,0,130));
        if(score<10) {
            painter.drawText((mainX+1080)+510,750,QString::number(score));
        } else if(score<100) {
            painter.drawText((mainX+1080)+490,750,QString::number(score));
        } else if(score<1000) {
            painter.drawText((mainX+1080)+470,750,QString::number(score));
        } else if(score<10000) {
            painter.drawText((mainX+1080)+450,750,QString::number(score));
        } else if(score<100000) {
            painter.drawText((mainX+1080)+430,750,QString::number(score));
        }
        if(!shop->item1Count||active==-1||boost) {
            painter.setOpacity(0.5);
        }
        painter.drawPixmap((mainX+1080)+100,1640,90,90,shop->getPixmap(1)); //item1
        painter.setOpacity(1);
        f.setPixelSize(44);
        painter.setFont(f);
        painter.setPen(QColor(238,77,46));
        painter.drawText((mainX+1080)+100,1755,QString::number(shop->item1Count)+"x");
        if(!shop->item2Count||active!=-1||(active==-1&&score)||hardcore||cave) {
            painter.setOpacity(0.5);
        }
        painter.drawPixmap((mainX+1080)+250,1640,90,90,shop->getPixmap(2)); //item2
        painter.setOpacity(1);
        painter.drawText((mainX+1080)+250,1755,QString::number(shop->item2Count)+"x");
        if(!shop->item3Count||active==-1) {
            painter.setOpacity(0.5);
        }
        painter.drawPixmap((mainX+1080)+400,1640,90,90,shop->getPixmap(3)); //item3
        painter.setOpacity(1);
        painter.drawText((mainX+1080)+400,1755,QString::number(shop->item3Count)+"x");
        if(!shop->item4Count||active!=-1||(active==-1&&score)||hardcore||cave) {
            painter.setOpacity(0.5);
        }
        painter.drawPixmap((mainX+1080)+550,1640,90,90,shop->getPixmap(4)); //item4
        painter.setOpacity(1);
        painter.drawText((mainX+1080)+550,1755,QString::number(shop->item4Count)+"x");
        if(!shop->item4Count||active==-1) {
            painter.setOpacity(0.5);
        }
        painter.setOpacity(1);
        if(pause) {
            painter.drawPixmap((mainX+1080)+955,0,125,125,pause0);
        } else {
            painter.setOpacity(0.5);
            painter.drawPixmap((mainX+1080)+955,0,125,125,pause1);
            painter.setOpacity(1);
        }

    }
    if((!active&&!shop->getActive()&&!scoreboard->active)||moveAn) {
        Text go = transl->getBtn_Go();
        Text shopT = transl->getBtn_Shop();
        f.setPixelSize(go.size);
        painter.setPen(Qt::NoPen);
        if(highscore>=1000) {
            painter.drawPixmap(mainX+180,1538,150,150,medal_emerald);
        } else if(highscore>=300) {
            painter.drawPixmap(mainX+180,1538,150,150,medal_diamond);
        } else if(highscore>=175) {
            painter.drawPixmap(mainX+180,1538,150,150,medal_platin);
        } else if(highscore>=100) {
            painter.drawPixmap(mainX+180,1538,150,150,medal_gold);
        } else if(highscore>=60) {
            painter.drawPixmap(mainX+180,1538,150,150,medal_silver);
        } else if(highscore>=30) {
            painter.drawPixmap(mainX+180,1538,150,150,medal_bronze);
        }
        painter.setFont(f);
        painter.drawPixmap(QRect(mainX+390,900,300,150),btnPx);
        painter.drawPixmap(QRect(mainX+390,1100,300,150),btnPx);
        painter.drawPixmap(QRect(mainX+390,1300,300,150),btnPx);
        if(lowGraphics) painter.setOpacity(0.7);
        painter.drawPixmap(QRect(mainX+350,1810,360,96),btnPx); //btn animation
        painter.setOpacity(1);
        painter.drawPixmap(QRect(mainX+439,1308,200,120),stats);
        painter.drawPixmap(QRect(mainX+10,1810,160,96),flag_de);
        painter.drawPixmap(QRect(mainX+175,1810,160,96),flag_en);
        painter.drawPixmap(QRect(mainX+910,1810,160,96),referralPx1);
        painter.setBrush(QColor(238,77,46));
        painter.drawRect(QRect(mainX+725,1810,180,96));
        painter.setBrush(QColor(162,162,162));
        painter.drawRect(mainX,925,25,10);
        painter.drawRect(mainX,1200,25,10);
        painter.drawPixmap(QRect(mainX+20,900,75,325),btnPx);
        painter.setPen(QColor(0,143,255));
        f.setPixelSize(26);
        painter.setFont(f);
        if(lowGraphics) painter.setOpacity(0.7);
        painter.drawText(QRect(mainX+350,1810,360,96),Qt::AlignCenter,"Animationen");
        painter.setOpacity(1);
        f.setPixelSize(32);
        painter.setFont(f);
        if(hardcore) {
            painter.drawText(QRect(mainX+23,900,75,325),Qt::AlignCenter,"H\nA\nR\nD\nC\nO\nR\nE");
        } else {
            painter.drawText(QRect(mainX+23,900,75,325),Qt::AlignCenter,"N\nO\nR\nM\nA\nL");
        }
        f.setPixelSize(25);
        painter.setFont(f);
        painter.drawText(QRect(mainX+725,1810,180,96),Qt::AlignCenter,"Spenden");
        painter.setBrush(QColor(22,22,24));
        painter.setOpacity(0.75);
        if(transl->locale.language()==QLocale::German) {
            painter.drawRect(mainX+175,1810,160,96);
        } else {
            painter.drawRect(mainX+10,1810,160,96);
        }
        painter.setOpacity(1);
        f.setPixelSize(go.size);
        painter.setFont(f);
        painter.drawText(QPoint(mainX+go.pos.x(),go.pos.y()),go.text);
        f.setPixelSize(shopT.size);
        painter.setFont(f);
        painter.drawText(QPoint(mainX+shopT.pos.x(),shopT.pos.y()),shopT.text);
        if(crate) {
            painter.setBrush(QColor(22,22,24,200));
            painter.setPen(Qt::NoPen);
            painter.drawRect(0,0,1080,1920);
            if(!boxCount) painter.setOpacity(0.5);
            if(!boxState) {
                painter.drawPixmap(QRectF(mainX+400,760,420,365),boxPx,QRectF(0,0,46,40));
            } else {
                painter.drawPixmap(QRectF(mainX+400,760,420,365),boxPxAn[boxState-1],QRectF(0,0,46,40));
            }
            painter.setOpacity(1);
            for(int i=0;i<blusse.size();i++) {
                if(blusse[i]->gift) {
                    if(blusse[i]->isText()&&blusse[i]->size>0) {
                        f.setPixelSize(blusse[i]->size);
                        painter.setFont(f);
                        if(blusse[i]->getOpacity()>0) {
                            QColor b = blusse[i]->color;
                            painter.setPen(QPen(QColor(b.red(),b.green(),b.blue(),blusse[i]->getOpacity())));
                            painter.drawText(blusse[i]->getRect().x(),blusse[i]->getRect().y(),blusse[i]->getText());
                        }
                    } else if(!hardcore||moveAn==1) {
                        if(!blusse[i]->isText()&&!blusse[i]->isRect) {
                            if(blusse[i]->getRect().intersects(QRectF(0,0,1080,1920))) {
                                painter.setOpacity((blusse[i]->getOpacity()/2.55)/100.0);
                                painter.drawPixmap(QRect(blusse[i]->getRect().x(),blusse[i]->getRect().y(),
                                                         blusse[i]->getRect().width(),blusse[i]->getRect().height()),blusse[i]->getPixmap());
                                painter.setOpacity(1);
                            }
                        } else if(blusse[i]->isRect&&!blusse[i]->spark) {
                            if(blusse[i]->getRect().intersects(QRectF(0,0,1080,1920))) {
                                painter.setOpacity((blusse[i]->getOpacity()/2.55)/100.0);
                                painter.setBrush(blusse[i]->color);
                                painter.drawRect(blusse[i]->getRect());
                                painter.setOpacity(1);
                            }
                        }
                    }
                }
            }
            f.setPixelSize(42);
            painter.setFont(f);
            painter.setPen(Qt::white);
            painter.drawText(50,1200,"29% 05k Benis");
            painter.drawText(50,1300,"15% 10k Benis");
            painter.drawText(50,1400,"15%    /");
            painter.drawPixmap(QRect(225,1325,100,100),shop->getPixmap(1)); //grün rev
            painter.drawPixmap(QRect(395,1325,100,100),shop->getPixmap(2)); //sped
            painter.drawText(50,1500,"10%    /");
            painter.drawPixmap(QRect(225,1425,100,100),shop->getPixmap(3)); //rot rev
            painter.drawPixmap(QRect(395,1425,100,100),shop->getPixmap(4)); //grün sped
            painter.drawText(50,1600,"05% 20k Benis");
            painter.drawText(50,1700,"01% 2x");
            painter.drawPixmap(QRect(325,1625,100,100),coinPx); //coins
            painter.drawText(50,1800,"01%    /   /   /");
            painter.drawPixmap(QRect(225,1725,100,100),backgrounds[cnum1]->background);
            painter.drawPixmap(QRect(395,1725,100,100),skins[cnum2]);
            painter.drawPixmap(QRect(565,1725,100,100),pipes[cnum3]);
            painter.drawPixmap(QRect(735,1725,100,100),tails[cnum4]);
        }
        if(!boxCount) painter.setOpacity(0.5);
        painter.drawPixmap(QRectF(mainX+775,1550,160,139),boxPx,QRectF(0,0,46,40));
        painter.setOpacity(1);
        painter.setPen(QColor(238,77,46));
        f.setPixelSize(48);
        painter.setFont(f);
        painter.drawText(mainX+890,1650,QString::number(boxCount)+"x");
        if(refActive) {
            painter.setOpacity(1);
            painter.drawPixmap(165,460,750,1130,shop->background);
            f.setPixelSize(26);
            painter.setFont(f);
            painter.drawText(QRect(180,500,750,1130),transl->getText_Referral_Get(refkey,QString::number(referrals)).text);
            painter.setPen(Qt::NoPen);
            if(!referrals) painter.setOpacity(0.4);
            painter.drawPixmap(165,1460,300,130,btnPx);
            painter.setOpacity(1);
            if(invited) painter.setOpacity(0.4);
            painter.drawPixmap(455,1460,300,130,btnPx);
            painter.setOpacity(1);
            painter.drawPixmap(750,1460,160,130,btnPx);
            painter.setPen(QColor(0,143,255));
            painter.drawText(QRect(170,1460,300,130),Qt::AlignCenter,transl->getText_Referral_btnConfirm().text);
            painter.drawText(QRect(455,1460,300,130),Qt::AlignCenter,transl->getText_Referral_btnInvite().text);
            painter.drawText(QRect(750,1460,160,130),Qt::AlignCenter,"Ok");
        }
        f.setPixelSize(42);
        painter.setFont(f);
        if(outdated) painter.drawText(mainX+25,200,"Ein Update ist verfügbar!");
    }
    if((!active&&shop->getActive())||(moveAn==2||moveAn==4)) {
        shop->draw(painter);
    } else if((!active&&scoreboard->active)||(moveAn==5||moveAn==6)) {
        scoreboard->draw(painter,highscore);
    }
    f.setPixelSize(48);
    painter.setFont(f);
    painter.setPen(Qt::white);
    painter.drawText(4,50,"BENIS "+QString::number(player->getBenis()));
    painter.drawText(90,115,QString::number(player->coins));
    painter.setPen(Qt::NoPen);
    painter.drawPixmap(4,50,75,75,coinPx);
    if(flashOpacity) {
        painter.setBrush(Qt::white);
        painter.setOpacity(flashOpacity);
        painter.drawRect(0,0,1080,1920);
    }
    painter.setOpacity(1);
    if(resumeTime) {
        painter.setPen(Qt::white);
        f.setPixelSize(88);
        painter.setFont(f);
        painter.drawText(500,1000,QString::number(resumeTime));
    }
}

void FrmMain::mousePressEvent(QMouseEvent *e)
{
    int x = e->pos().x()/scaleX;
    int y = e->pos().y()/scaleY;
    mousePos = QPoint(x,y);
    switch(active) {
    case 0:
        if(shop->getActive()) {
            shop->mousePress(QPoint(x,y),cave);
        } else if(scoreboard->active) {
            scoreboard->mpress(QPoint(x,y));
        }
        break;
    }
    if(moveAn||shop->getActive()||scoreboard->active||loading) return;
    switch(active) {
        case 0:
            if(crate) {
                if(QRect(x,y,1,1).intersects(QRect(340,760,400,453))) {
                    handleBox();
                } else {
                    crate = false;
                }
                return;
            }
            if(refActive) {
                if(QRect(x,y,1,1).intersects(QRect(165,1460,300,130))&&referrals) { //btnconfirm
                    bool ok=false;
                    QGuiApplication::inputMethod()->show();
                    QString n = QInputDialog::getText(this,tr("Key"),"Key: ",QLineEdit::Normal,"",&ok);
                    if(ok) {
                        if(checkConfirm(n)&&n!=confirmkey) {
                            player->setBenis(player->getBenis()+250000);
                            on_shopBuy(250000,false);
                            referrals--;
                            write();
                            QMessageBox::information(this,"Info",transl->getText_Referral_Confirmed2().text);
                        } else {
                            QMessageBox::information(this,"Info",transl->getText_Referral_WrongKey().text);
                        }
                    }
                    refActive = false;
                } else if(QRect(x,y,1,1).intersects(QRect(455,1460,300,130))&&!invited) { //btnwurde
                    bool ok=false;
                    QGuiApplication::inputMethod()->show();
                    QString n = QInputDialog::getText(this,tr("Key"),"Key: ",QLineEdit::Normal,"",&ok);
                    if(ok) {
                        if(checkKey(n)&&n!=refkey) {
                            player->setBenis(player->getBenis()+100000);
                            on_shopBuy(100000,false);
                            invited = 1;
                            write();
                            confirmkey = lucaAlg("d");
                            QMessageBox::information(this,tr("Info"),transl->getText_Referral_Confirmed().text+confirmkey);
                        } else {
                            QMessageBox::information(this,tr("Info"),transl->getText_Referral_WrongKey().text);
                        }
                    }
                    refActive = false;
                } else if(QRect(x,y,1,1).intersects(QRect(750,1460,160,130))) { //btnok
                    refActive = false;
                }
                return;
            }
            if(QRect(x,y,1,1).intersects(QRect(50,1236,75,71))) {
                if(event<3) {
                    event++;
                    if(event==3) {
                        boxCount += 25;
                        QMessageBox::information(this,"I bims der Schmuserkadser","Schmuserkadser hat dir 25 Geschenke gegeben!\nFrohe Weihnachten!");
                        write();
                    }
                }
            } else if(QRect(x,y,1,1).intersects(QRect(390,900,300,150))) {
                radR = 1700;
                moveAn = 3;
            } else if(QRect(x,y,1,1).intersects(QRect(390,1100,300,150))) { //shop
                moveAn = 2;
            } else if(QRect(x,y,1,1).intersects(QRect(10,1810,160,96))) {
                transl->locale = QLocale("de");
                write();
            } else if(QRect(x,y,1,1).intersects(QRect(175,1810,160,96))) {
                transl->locale = QLocale("en");
                write();
            } else if(QRect(x,y,1,1).intersects(QRect(390,1300,300,150))) { //scoreboard
                bool ok=true;
                if(scoreboard->name=="") {
                    QGuiApplication::inputMethod()->show();
                    QString n = QInputDialog::getText(this,tr("Nickname"),transl->getText_Scoreboard_SetName().text,QLineEdit::Normal,"",&ok);
                    if(n.isEmpty()||n.contains("äüö#~ÄÖÜ")||n.size()>12||n.contains(" ")) {
                        if(ok) {
                            ok = false;
                            Text t = transl->gettext_Scoreboard_Falsch();
                            QMessageBox::critical(this,"Error",t.text);
                        }
                    } else {
                        scoreboard->name = n;
                        scoreboard->first="1";
                    }
                } else {
                    scoreboard->first="0";
                }
                if(highscore&&ok) {
                    //if(highscore*3>playTime) num = -1;
                    scoreboard->setScore(highscore,highscore_H,highscore_C);
                    if(scoreboard->wasConnected==1) {
                        if(scoreboard->first=="1") scoreboard->first=="0";
                        scoreboard->getScores();
                    }
                }
                if(ok&&scoreboard->wasConnected==1) scoreboard->active = true;
            } else if(QRect(x,y,1,1).intersects(QRect(775,1550,150,135))&&!crate) { //kiste
                if(boxCount) {
                    if(!crate) {
                        cnum1 = random(1,backgrounds.size());
                        cnum2 = random(1,skins.size());
                        cnum3 = random(1,pipes.size());
                        cnum4 = random(1,tails.size());
                        crate = true;
                        return;
                    }
                }
            } else if(QRect(x,y,1,1).intersects(QRect(910,1810,160,100))) { //ref
                refActive = true;
                if(refkey!="") return;
                for(int i=0;i<10;i++) refkey = genKey();
            } else if(QRect(x,y,1,1).intersects(QRect(mainX+725,1810,180,96))) {//spenden
                QMessageBox::information(this,"Info",transl->getText_Donate().text);
            } else if(QRect(x,y,1,1).intersects(QRect(20,900,75,325))) { //hardcore
                if(!cave&&shop->chosenPipe!=2) {
                    if(hardcore) {
                        hardcore = false;
                    } else {
                        hardcore = true;
                    }
                }
            } else if(QRect(x,y,1,1).intersects(QRect(350,1810,360,96))) {//animation
                if(lowGraphics) {
                    lowGraphics = false;
                } else {
                    lowGraphics = true;
                }
                write();
            }
        break;
        case -1:
            {
                QMetaObject::invokeMethod(t_tilt,"start",Q_ARG(int,10));
                int interval = 0;
                switch(shop->chosenTail) {
                case 2:
                case 3:
                case 6:
                    interval = 100;
                    break;
                case 4:
                case 5:
                    interval = 15;
                    break;
                }
                //if(lowGraphics) interval = 0;
                if(interval) QMetaObject::invokeMethod(t_tail,"start",Q_ARG(int,interval));
                active = 1;
            }
        case 1:
            if(player->getRect().y()-10>0) {
                bool buy = false;
                if(QRect(x,y,1,1).intersects(QRect(955,0,125,125))) {
                    if(!t_resume->isActive()) {
                        if(pause) {
                            resumeTime = 3;
                            QMetaObject::invokeMethod(t_resume,"start",Q_ARG(int,1000));
                        } else {
                            if(!t_boost->isActive()&&!revive) {
                                pause = true;
                            } else {
                                blusse.append(new Blus(90,QRectF(4,180,1,1),transl->getText_PauseError().text,30));
                            }
                        }
                    }
                    return;
                }
                if(pause) return;
                player->tstep = (player->tilt/200)*10;
                player->tdir = true;
                QMetaObject::invokeMethod(t_tchange,"stop");
                QMetaObject::invokeMethod(t_tchange,"start",Q_ARG(int,200));
                if(!go&&QRectF(x,y,1,1).intersects(QRectF(100,1640,90,90))) { //item1
                    if(shop->item1Count&&!revive&&!boost) {
                        buy = true;
                        shop->item1Count--;
                        revive = 1;
                        reviveTime = 30000;
                    }
                }
                if(QRectF(x,y,1,1).intersects(QRectF(250,1640,90,90))&&go==1) {  //item2
                    if(shop->item2Count&&!boost&&!hardcore&&!cave) {
                        shop->item2Count--;
                        boost=11;
                        localPlayTime+=60;
                        fastboost = false;
                        QMetaObject::invokeMethod(t_boost,"start",Q_ARG(int,50));
                    }
                }
                if(QRectF(x,y,1,1).intersects(QRectF(400,1640,90,90))) {  //item3
                    if(shop->item3Count&&!revive&&!boost) {
                        shop->item3Count--;
                        revive = 2;
                        buy = true;
                    }
                }
                if(QRectF(x,y,1,1).intersects(QRectF(550,1640,90,90))&&go==1) {  //item4
                    if(shop->item4Count&&!boost&&!hardcore&&!cave) {
                        shop->item4Count--;
                        boost=20;
                        localPlayTime+=120;
                        fastboost = true;
                        QMetaObject::invokeMethod(t_boost,"start",Q_ARG(int,50));
                    }
                }
                if(!buy) {
                    player->setVelD(-5);
                    if(QRectF(x,y,1,1).intersects(enemyRect)) {
                        if(enemytype!=2) {
                            blusse.append(new Blus(random(0,360),QRectF(x-20,y-20,40,40),minus));
                        } else {
                            blusse.append(new Blus(random(0,360),QRectF(x-20,y-20,40,40),"██",36));
                        }
                        blusse.append(new Blus(90,QRectF(4,180,1,1),"+"+QString::number(score*5)));
                        player->setBenis(player->getBenis()+score*(shop->multiplier/2));
                    } else {
                        cBTouch += shop->tapMultiplier;
                        player->setBenis(player->getBenis()+shop->tapMultiplier);
                        if(!lowGraphics) {
                            QPixmap bpx = blus;
                            if(shop->chosenSkin!=23) {
                                if(shop->chosenSkin==14) bpx = minus;
                                blusse.append(new Blus(random(0,360),QRectF(x-20,y-20,40,40),bpx));
                            } else {
                                QString text;
                                switch(random(0,12)) {
                                case 0:
                                    text = "such wow";
                                    break;
                                case 1:
                                    text = "very touch";
                                    break;
                                case 2:
                                    text = "much flatter";
                                    break;
                                case 3:
                                    text = "such blus";
                                    break;
                                case 4:
                                    text = "very wow";
                                    break;
                                case 5:
                                    text = "such difficult";
                                    break;
                                case 6:
                                    text = "so hardcore";
                                    break;
                                case 7:
                                    text = "much tap";
                                    break;
                                case 8:
                                    text = "wow";
                                    break;
                                case 9:
                                    text = "so doge";
                                    break;
                                case 10:
                                    text = "very pr0gramm";
                                    break;
                                case 11:
                                    text = "such score";
                                    break;
                                }
                                blusse.append(new Blus(random(0,360),QRectF(x-20,y-20,40,40),text,random(35,46)));
                            }
                        }
                    }
                }
            }
        break;
        case 2:
            if(QRect(x,y,1,1).intersects(QRect(190,1300,300,150))) {
                radR = 350;
                moveAn = 1;
                for(int i=0;i<polyTop.size();i++) {
                    if(polyTop.at(i).x()<0) {
                        polyTop[i] = QPointF(0,polyTop.at(i).y());
                        polyTop[polyTop.size()-i-1] = QPointF(0,polyTop.at(polyTop.size()-i-1).y());
                    }
                }
                for(int i=0;i<polyBottom.size();i++) {
                    if(polyBottom.at(i).x()<0) {
                        polyBottom[i] = QPointF(0,polyBottom.at(i).y());
                        polyBottom[polyBottom.size()-i-1] = QPointF(0,polyBottom.at(polyBottom.size()-i-1).y());
                    }
                }
            } else if(QRect(x,y,1,1).intersects(QRect(590,1300,300,150))) {
                moveAn = -1;
            }
        break;
    }
}

void FrmMain::keyPressEvent(QKeyEvent *e)
{
    if(moveAn) return;
    write();
    if(e->key()==Qt::Key_Back) {
        if(crate) {
            crate=false;
            return;
        }
        if(shop->getActive()) {
            moveAn = 4;
        } else if(scoreboard->active){
            moveAn = 6;
        } else {
            workerThread->exit();
            animationThread->exit();
            blusThread->exit();
            QMetaObject::invokeMethod(t_blus,"stop");
            QMetaObject::invokeMethod(t_main,"stop");
            QApplication::quit();
        }
    } else {
        if(active==1) {
            if(!t_boost->isActive()&&!revive) pause = true;
        }
    }
}

void FrmMain::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    write();
    QMetaObject::invokeMethod(t_blus,"stop");
    QMetaObject::invokeMethod(t_main,"stop");
    QMetaObject::invokeMethod(t_animation,"stop");
    workerThread->exit();
    blusThread->exit();
    animationThread->exit();
}

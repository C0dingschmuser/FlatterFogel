#include "frmmain.h"
#include "ui_frmmain.h"

FrmMain::FrmMain(QOpenGLWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::FrmMain)
{
    ui->setupUi(this);
    mainX = 0;
    endX = 1080;
    event = 0;
    anDir = false;
    moveAn = false;
    version = "1.2r1";
    t_draw = new QTimer();
    t_main = new QTimer();
    t_obst = new QTimer();
    t_event = new QTimer();
    t_revive = new QTimer();
    t_boxDeathAn = new QTimer();
    t_boost = new QTimer();
    t_an = new QTimer();
    t_tilt = new QTimer();
    t_tchange = new QTimer();
    t_flag = new QTimer();
    t_star = new QTimer();
    t_resume = new QTimer();
    t_animation = new QTimer();
    flashOpacity = 0;
    pause = false;
    currentskin = 0;
    transl = new Translation();
    int id = QFontDatabase::addApplicationFont(":/font/PressStart2P.ttf");
    QString fam = QFontDatabase::applicationFontFamilies(id).at(0);
    font = QFont(fam);
    connect(t_event,SIGNAL(timeout()),this,SLOT(on_tEvent()));
    connect(t_main,SIGNAL(timeout()),this,SLOT(on_tmain()));
    connect(t_draw,SIGNAL(timeout()),this,SLOT(on_tdraw()));
    connect(t_obst,SIGNAL(timeout()),this,SLOT(on_tObst()));
    connect(t_revive,SIGNAL(timeout()),this,SLOT(on_trevive()));
    connect(t_boost,SIGNAL(timeout()),this,SLOT(on_tboost()));
    connect(t_an,SIGNAL(timeout()),this,SLOT(on_tAn()));
    connect(t_tilt,SIGNAL(timeout()),this,SLOT(on_tTilt()));
    connect(t_tchange,SIGNAL(timeout()),this,SLOT(on_tChange()));
    connect(t_flag,SIGNAL(timeout()),this,SLOT(on_tflag()));
    connect(t_star,SIGNAL(timeout()),this,SLOT(on_tstar()));
    connect(t_boxDeathAn,SIGNAL(timeout()),this,SLOT(on_tboxDeathAn()));
    connect(t_resume,SIGNAL(timeout()),this,SLOT(on_tresume()));
    connect(t_animation,SIGNAL(timeout()),this,SLOT(on_tAnimation()));
    //this->showMaximized();
    end = QPixmap(":/images/end.png");
    btnPx = QPixmap(":/images/button.png");
    blus = QPixmap(":/images/blus.png");
    minus = QPixmap(":/images/minus.png");
    schmuserkadser = QPixmap(":/images/schmuserkadser.png");
    maas = QPixmap(":/images/maas.png");
    ground = QPixmap(":/images/ground.png");
    bg = QPixmap(":/images/bg.png");
    medal_bronze = QPixmap(":/images/medals/bronze.png");
    medal_silver = QPixmap(":/images/medals/silber.png");
    medal_gold = QPixmap(":/images/medals/gold.png");
    medal_platin = QPixmap(":/images/medals/platin.png");
    QVector <QPixmap> medalsPx;
    medalsPx.append(medal_bronze);
    medalsPx.append(medal_silver);
    medalsPx.append(medal_gold);
    medalsPx.append(medal_platin);
    flag_de = QPixmap(":/images/flag/de.png");
    flag_en = QPixmap(":/images/flag/en.png");
    stats = QPixmap(":/images/stats.png");
    trainPx = QPixmap(":/images/train.png");
    train2Px = QPixmap(":/images/train2.png");
    boxPx = QPixmap(":/images/box/box.png");
    box2Px = QPixmap(":/images/box/box2.png");
    box3Px = QPixmap(":/images/box/box3.png");
    pause0 = QPixmap(":/images/pause0.png");
    pause1 = QPixmap(":/images/pause1.png");
    coinPx = QPixmap(":/images/coin.png");
    for(int i=0;i<10;i++) {
        skins.append(QPixmap(":/images/player/skins/"+QString::number(i)+".png"));
    }
    for(int i=0;i<3;i++) {
        boxPxAn.append(QPixmap(":/images/box/box_"+QString::number(i+1)+".png"));
    }
    for(int i=0;i<42;i++) {
        explosion.append(QPixmap(":/images/explosion/"+QString::number(i+1)+".png"));
    }
    player = new Player(QRectF(1080/2-40,1920/2-40,80,80));
    shop = new Shop(player,font,transl,coinPx);
    shop->skins = skins;
    shop->g2 = player->g2;
    scoreboard = new Scoreboard(shop->background,btnPx,font,transl);
    scoreboard->medals = medalsPx;
    connect(scoreboard,SIGNAL(connFail()),this,SLOT(on_sbConnFail()));
    connect(scoreboard,SIGNAL(wrongName()),this,SLOT(on_sbWrongName()));
    connect(scoreboard,SIGNAL(write()),this,SLOT(on_scoreWrite()));
    connect(scoreboard,SIGNAL(back()),this,SLOT(on_scoreBack()));
    connect(shop,SIGNAL(back()),this,SLOT(on_shopBack()));
    connect(shop,SIGNAL(msg(QString)),this,SLOT(on_shopMsg(QString)));
    connect(shop,SIGNAL(buy(int,bool,bool)),this,SLOT(on_shopBuy(int,bool,bool)));
    enemyRect = QRectF(-300,100,300,200);
    enemy = "Mieserkadser";
    enemylife = 10;
    boxDeath = 0;
    obsNum = 0;
    boxState = 0;
    resumeTime = 0;
    //window
    createWindows();
    //~Window
    flag = false;
    changelog = false;
    active = 0;
    enemydir = 1; //unten
    score = 0;
    schmuser = 0;
    highscore = 0;
    boost = 0;
    fastboost = false;
    medal = 0;
    g1x = 0;
    g2x = 1080;
    boxCount = 0;
    revive = false;
    loadData();
    workerThread = new QThread();
    t_main->start(5);
    t_draw->start(10);
    t_obst->start(100);
    t_event->start(2000);
    t_flag->start(750);
    t_star->start(125);
    t_an->start(250);
    t_animation->start(1);
    t_tchange->setSingleShot(true);
    t_animation->moveToThread(workerThread);
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
    workerThread->start();
}

FrmMain::~FrmMain()
{
    delete player;
    delete ui;
}

void FrmMain::on_tdraw()
{
    if(QGuiApplication::applicationState()==Qt::ApplicationSuspended) return;
    update();
}

void FrmMain::on_tmain()
{
    if(pause) return;
    //moveAn = 3;
    if(flashOpacity) {
        flashOpacity -= 0.0125;
    }
    for(int i=0;i<blusse.size();i++) {
        blusse[i]->move();
    }
    for(int i=0;i<blusse.size();i++) {
        if(!blusse[i]->getRect().intersects(QRectF(0,0,1080,1920))||!blusse[i]->getOpacity()) {
            delete blusse[i];
            blusse.removeAt(i);
            //break;
        }
    }
    if(active<1) return;
    if(active==1&&!boxDeath) {
        for(int i=0;i<obstacles.size();i++) {
            if(boost) {
                obstacles[i]->moveBy(-boost,0);
                moveGround(-boost);
            } else {
                obstacles[i]->moveBy(-1,0);
                moveGround(-1);
            }
            if((player->getRect().intersects(obstacles[i]->getBottom())||
                    player->getRect().intersects(obstacles[i]->getTop()))&&!boost) {
                active = 3;
                flashOpacity = 0.5;
            }
        }
    }
    if(player->getRect().y()<1600&&active>0) {
        double velD = player->getVelD();
        if(velD<10) velD += 0.1;
        player->setVelD(velD);
        QRectF r = player->getRect();
        if(r.y()+velD>1600) {
            velD = 1600-r.y();
        }
        player->setPos(r.x(),r.y()+velD);
    }
    if(player->getRect().y()>=1600) {
        if(!revive) {
            if(active==1) {
                flashOpacity = 0.5;
            }
            QMetaObject::invokeMethod(t_boost,"stop");
            QMetaObject::invokeMethod(t_tilt,"stop");
            active = 2;
        } else {
            active=-1;
            revive = false;
            reset(1);
            blusse.append(new Blus(270,QRect(260,850,1,1),"Revive!",88));
        }
        if(score>=175) {
            medal = 4;
        } else if(score>=100) {
            medal = 3;
        } else if(score>=60) {
            medal = 2;
        } else if(score>=30) {
            medal = 1;
        }
        if(score>highscore) {
            highscore = score;
            write();
        }
    }
    if(schmuser<4&&schmuser&&active==1) {
        if(enemyRect.y()>100&&enemydir==2) {
            enemyRect.moveTo(enemyRect.x(),enemyRect.y()-1);
            if(enemyRect.y()<=100) enemydir = 1;
        } else if(enemyRect.y()<1420&&enemydir==1) {
            enemyRect.moveTo(enemyRect.x(),enemyRect.y()+1);
            if(enemyRect.y()>=1420) enemydir = 2;
        }
        double s;
        if(enemyRect.x()<0) {
            s = 1;
        } else {
            s = 0.05;
        }
        if(enemyRect.x()+30<player->getRect().x()) enemyRect.moveTo(enemyRect.x()+s,enemyRect.y());
        if(enemyRect.intersects(player->getRect())) {
            active = 3;
            flashOpacity = 0.5;
        }
    } else if(schmuser==4&&active==1) {
        if(enemyRect.x()>-300) enemyRect.moveTo(enemyRect.x()-1,enemyRect.y());
        if(enemyRect.x()<=-300) {
            schmuser = 0;
            enemylife = 10;
            enemyRect.moveTo(-300,100);
        }
    }
    for(int i=0;i<obstacles.size();i++) {
        if(obstacles[i]->getTop().x()<-250) {
            delete obstacles[i];
            obstacles.removeAt(i);
            //qDebug()<<i;
            //break;
        } else if(obstacles[i]->getTop().x()<=player->getRect().x()&&active==1&&!obstacles[i]->type&&!obstacles[i]->approved) {
            obstacles[i]->approved = true;
            score++;
            int ok=-1;
            for(int a=0;a<windows.size();a++) {
                if(windows[a]->visible) {
                    ok = a;
                    break;
                }
            }
            if(ok!=-1) {
                windows[ok]->visible = false;
            }
            if(!boost) {
                if(score%100==0) {
                    on_shopBuy(1,false,true);
                    player->coins++;
                    write();
                } else {
                    player->setBenis(player->getBenis()+(score*shop->multiplier));
                    int b = score*shop->multiplier;
                    blusse.append(new Blus(90,QRectF(4,180,1,1),"+"+QString::number(b)));
                    for(int a=0;a<360;a+=12) {
                        blusse.append(new Blus(a,QRectF(player->getRect().center().x()-20,player->getRect().center().y()-20,40,40),blus));
                    }
                }
            }
        }
    }
}

void FrmMain::on_tObst()
{

    if(active!=1||schmuser||boxDeath) return;
    if(obstacles.size()<=3) {
        //diff 600
        int x = 1200;
        if(obstacles.size()) {
            x = obstacles[obstacles.size()-1]->getBottom().x()+600;
        }
        QPixmap p(":/images/pipe1.png");
        QRect top(x,0,100,random(300,1300));
        QRect bottom(x,top.height()+350,100,1920-top.height()+350);
        bool bA=false;
        bool type=false;
        if(active==1&&!boost) {
            bA = true;
            if(!random(0,6)) {
                type = true;
            }
        }
        obstacles.append(new Obstacle(top,bottom,p,0,bA,type));
    }
}

void FrmMain::on_tEvent()
{
    if(active!=1) return;
    if(((score%10==0)&&(score!=0)&&(!boost))||schmuser) {
        if(!schmuser) {
            enemytype = random(1,3);
            switch(enemytype) {
                case 1: //mieserkadser
                    enemyPixmap = schmuserkadser;
                    enemy = "Mieserkadser";
                    enemyRect = QRectF(-300,100,300,200);
                    maxX = 304;
                    maxY = 202;
                break;
                case 2: //maas
                    enemyPixmap = maas;
                    enemy = "Maas";
                    enemyRect = QRectF(-300,100,180,230);
                    maxX = 181;
                    maxY = 231;
                break;
            }
        }
        if(schmuser<3) schmuser++;
        for(int i=0;i<obstacles.size();i++) {
            if(obstacles[i]->getTop().x()>1280) {
                delete obstacles[i];
                obstacles.removeAt(i);
            }
        }
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

void FrmMain::on_shopBuy(int amount, bool buy, bool coin)
{
    QString a="+";
    if(buy) {
        a = "-";
    }
    write();
    blusse.append(new Blus(90,QRectF(4,180,1,1),a+QString::number(amount)));
    if(coin) {
        blusse.append(new Blus(90,QRectF(100,115,65,65),coinPx,16,16));
    }
}

void FrmMain::on_trevive()
{
    revive = false;
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
        for(int i=0;i<boost*2;i++) {
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
    if(flag) {
        flag = false;
    } else {
        flag = true;
    }
    if(obstacles.size()&&active==1&&random(0,2)) {
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
            blusse.append(spark);
        }
    }
}

void FrmMain::on_tstar()
{
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

void FrmMain::on_scoreWrite()
{
    if(scoreboard->active) {
        moveAn = 6;
    } else {
        moveAn = 5;
    }
    write();
}

void FrmMain::on_tAnimation()
{
    int speed = 2;
    if(moveAn) {
        switch (moveAn) {
            case 1: //end
                if(mainX<0) {
                    mainX += speed;
                    endX += speed;
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
        if(list.size()>1) {
            highscore = list.at(0).toInt();
            player->setBenis(list.at(1).toInt());
            shop->multiplier = list.at(3).toInt();
            shop->tapMultiplier = list.at(4).toInt();
            if(!shop->multiplier||!shop->tapMultiplier) {
                shop->multiplier = 10;
                shop->tapMultiplier = 1;
            }
            if(list.size()>8) {
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
                if(list.size()>12) {
                    player->coins = list.at(12).toInt();
                }
                if(list.size()>13) {
                    QStringList skinList = QString(list.at(13)).split("~");
                    for(int i=0;i<skinList.size()-1;i++) {
                        shop->ownedSkins.append(skinList.at(i).toInt());
                    }
                }
                if(list.size()>14) {
                    event = list.at(14).toInt();
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
    out << QString::number(highscore) << "#" << QString::number(player->getBenis()) << "#"
        << QString::number(shop->item1Count) << "#" << QString::number(shop->multiplier) << "#"
        << QString::number(shop->tapMultiplier) << "#" << QString::number(shop->item2Count) << "#"
        << transl->locale.bcp47Name() << "#" << QString::number(shop->item3Count) << "#"
        << scoreboard->name << "#" << QString::number(shop->item4Count) << "#"
        << QString::number(boxCount) << "#" << version << "#" << QString::number(player->coins) << "#"
        << shop->skinsToString() << "#" << QString::number(event) << "#";
    file.close();
}

void FrmMain::reset(int type)
{
    for(int i=0;i<obstacles.size();i++) {
        delete obstacles[i];
    }
    for(int i=0;i<blusse.size();i++) {
        delete blusse[i];
    }
    write();
    blusse.resize(0);
    obstacles.resize(0);
    if(!type) score = 0;
    QMetaObject::invokeMethod(t_boost,"stop");
    //QMetaObject::invokeMethod(t_an,"stop");
    QMetaObject::invokeMethod(t_tilt,"stop");
    enemylife = 10;
    medal = 0;
    boxDeath = 0;
    boxState = 0;
    schmuser = 0;
    enemydir = 1;
    boost = 0;
    player->tdir = 0;
    player->tilt = 45;
    player->setPos(1080/2-40,1920/2-40);
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
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(22,22,24));
    painter.drawRect(0,-2,1080,1922);
    painter.drawPixmap(0,0,1080,1660,bg);
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
    painter.setBrush(QColor(49,49,49));
    for(int i=0;i<windows.size();i++) {
        if(!windows[i]->visible) {
            painter.drawRect(windows[i]->rect);
        }
    }
    painter.setBrush(QColor(22,22,24));
    for(int i=0;i<stars.size();i++) {
        painter.setOpacity(stars[i]->opacity);
        painter.drawRect(stars[i]->rect);
    }
    painter.setOpacity(1);
    painter.setBrush(QColor(255,153,0));
    painter.save();
    painter.translate(mainX+1080,0);
    for(int i=0;i<obstacles.size();i++) {
        painter.drawPixmap(obstacles[i]->getTop(),obstacles[i]->px,QRectF(0,0,64,64));
        painter.drawPixmap(obstacles[i]->getBottom(),obstacles[i]->px,QRectF(0,0,64,64));
    }
    painter.restore();
    painter.drawPixmap(QRectF(g1x,1660,1080,260),ground,QRectF(0,0,108,25));
    painter.setBrush(QColor(0,143,255));
    //painter.drawRect(player->getRect());
    if(active>0||active==-1||moveAn==3||moveAn==1) {
        player->setPos((mainX+1080)+500,player->getRect().y());
        painter.save();
        painter.translate(player->getRect().center().x(),player->getRect().center().y());
        painter.rotate(player->tilt-45);
        painter.drawPixmap(QRectF(-player->getRect().width()/2,-player->getRect().height()/2,
                                  player->getRect().width(),player->getRect().height()),skins[shop->chosenSkin-1],QRectF(0,0,34,35));
        painter.drawPixmap(QRectF(-player->getRect().width()/2,-player->getRect().height()/2,
                                  player->getRect().width(),player->getRect().height()),player->getPx(),QRectF(0,0,34,35));
        painter.restore();
    }
    for(int i=0;i<obstacles.size();i++) {
        painter.save();
        painter.translate(mainX+1080,0);
        painter.drawPixmap(obstacles[i]->train,trainPx,QRectF(0,0,20,8));
        painter.drawPixmap(obstacles[i]->train2,train2Px,QRectF(0,0,20,8));
        if(obstacles[i]->hasBox) {
            switch(obstacles[i]->boxType) {
                case -1:
                    painter.drawPixmap(obstacles[i]->box,box3Px,QRectF(0,0,11,10));
                break;
                case 0:
                    painter.drawPixmap(obstacles[i]->box,box2Px,QRectF(0,0,11,10));
                break;
                case 1:
                    if(obstacles[i]->opacity<=1.0) {
                        painter.setOpacity(obstacles[i]->opacity);
                    }
                    painter.drawPixmap(obstacles[i]->box,boxPx,QRectF(0,0,11,10));
                    painter.setOpacity(1);
                break;
            }
        }
        painter.restore();
    }
    if(boxDeath>0) {
        QRectF area = obstacles[obsNum]->box;
        area.adjust(-100,-100,100,100);
        painter.drawPixmap(area,explosion[boxDeath],QRectF(0,0,130,130));
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
            a = (t_revive->remainingTime()/1000.0)*2;
        } else {
            a = 60;
        }
        painter.drawEllipse(QPointF(player->getRect().center()),40+a,40+a);
        pen.setWidth(2);
        painter.setPen(pen);
    }
    if(schmuser) {
        painter.drawPixmap(enemyRect,enemyPixmap,QRectF(0,0,maxX,maxY));
    }
    for(int i=0;i<blusse.size();i++) {
        if(!blusse[i]->isText()&&!blusse[i]->isRect) {
            painter.setOpacity((blusse[i]->getOpacity()/2.55)/100.0);
            painter.drawPixmap(blusse[i]->getRect(),blusse[i]->getPixmap(),QRectF(0,0,blusse[i]->width,blusse[i]->height));
            painter.setOpacity(1);
        } else if(blusse[i]->isRect) {
            painter.setOpacity((blusse[i]->getOpacity()/2.55)/100.0);
            painter.setBrush(blusse[i]->color);
            painter.drawRect(blusse[i]->getRect());
            painter.setOpacity(1);
        } else {
            f.setPixelSize(blusse[i]->size);
            painter.setFont(f);
            if(blusse[i]->getOpacity()>0) {
                painter.setPen(QPen(QColor(255,255,255,blusse[i]->getOpacity())));
                painter.drawText(blusse[i]->getRect().x(),blusse[i]->getRect().y(),blusse[i]->getText());
            }
        }
    }
    if(active==2) {
        f.setPixelSize(68);
        painter.setFont(f);
        //800*480
        painter.drawPixmap(endX+140,750,800,480,end);
        //300*150
        painter.drawPixmap(endX+390,1300,300,150,btnPx);
        painter.setPen(QColor(0,143,255));
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
        }
        painter.drawText(endX+720,970,QString::number(score));
        painter.drawText(endX+720,1175,QString::number(highscore));
        painter.drawText(endX+480,1410,"OK");
    }
    if(active>0||active==-1||moveAn==3) {
        f.setPixelSize(56);
        painter.setFont(f);
        painter.setPen(QColor(0,143,255));
        if(score<10) {
            painter.drawText((mainX+1080)+510,750,QString::number(score));
        } else if(score<100) {
            painter.drawText((mainX+1080)+490,750,QString::number(score));
        } else if(score<1000) {
            painter.drawText((mainX+1080)+470,750,QString::number(score));
        }
        if(schmuser) {
            Text t;
            switch(schmuser) {
                case 1:
                    t = transl->getText_Schmuser1();
                    painter.drawText(t.pos,t.text);
                break;
                case 2:
                    t = transl->getText_Schmuser2();
                    painter.drawText(t.pos,t.text+enemy);
                break;
                case 3:
                t = transl->getText_Schmuser3();
                painter.drawText(t.pos,t.text);
                break;
            }
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
        if(!shop->item2Count||active!=-1||(active==-1&&score)) {
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
        if(!shop->item4Count||active!=-1||(active==-1&&score)) {
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
            painter.drawPixmap((mainX+1080)+1005,0,75,75,pause0);
        } else {
            painter.drawPixmap((mainX+1080)+1005,0,75,75,pause1);
        }

    }
    if((!active&&!shop->getActive()&&!scoreboard->active)||moveAn) {
        Text go = transl->getBtn_Go();
        Text shop = transl->getBtn_Shop();
        f.setPixelSize(go.size);
        painter.setPen(Qt::NoPen);
        if(highscore>=175) {
            painter.drawPixmap(mainX+180,1538,150,150,medal_platin);
        } else if(highscore>=100) {
            painter.drawPixmap(mainX+180,1538,150,150,medal_gold);
        } else if(highscore>=60) {
            painter.drawPixmap(mainX+180,1538,150,150,medal_silver);
        } else if(highscore>=30) {
            painter.drawPixmap(mainX+180,1538,150,150,medal_bronze);
        }
        painter.setFont(f);
        painter.setPen(QColor(0,143,255));
        painter.drawPixmap(QRect(mainX+390,900,300,150),btnPx);
        painter.drawPixmap(QRect(mainX+390,1100,300,150),btnPx);
        painter.drawPixmap(QRect(mainX+390,1300,300,150),btnPx);
        painter.drawPixmap(QRect(mainX+439,1308,200,120),stats);
        painter.drawPixmap(QRect(mainX+10,1810,160,96),flag_de);
        painter.drawPixmap(QRect(mainX+175,1810,160,96),flag_en);
        painter.setBrush(QColor(22,22,24));
        painter.setOpacity(0.75);
        if(transl->locale.language()==QLocale::German) {
            painter.drawRect(mainX+175,1810,160,96);
        } else {
            painter.drawRect(mainX+10,1810,160,96);
        }
        painter.setOpacity(1);
        painter.drawText(QPoint(mainX+go.pos.x(),go.pos.y()),go.text);
        f.setPixelSize(shop.size);
        painter.setFont(f);
        painter.drawText(QPoint(mainX+shop.pos.x(),shop.pos.y()),shop.text);
        if(!boxState) {
            if(!boxCount) painter.setOpacity(0.5);
            painter.drawPixmap(QRectF(mainX+775,1550,150,135),boxPx,QRectF(0,0,11,10));
            painter.setOpacity(1);
        } else {
            painter.drawPixmap(QRectF(mainX+775,1550,150,135),boxPxAn[boxState-1],QRectF(0,0,11,10));
        }
        painter.setPen(QColor(238,77,46));
        painter.drawText(mainX+780,1755,QString::number(boxCount)+"x");
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
    Q_UNUSED(e)
    int x = e->pos().x()/scaleX;
    int y = e->pos().y()/scaleY;
    mousePos = QPoint(x,y);
    bool go = false;
    switch(active) {
    case 0:
        if(shop->getActive()) {
            shop->mousePress(QPoint(x,y));
        } else if(scoreboard->active) {
            scoreboard->mpress(QPoint(x,y));
        }
        break;
    }
    if(moveAn||shop->getActive()||scoreboard->active) return;
    switch(active) {
        case 0:
            if(QRect(x,y,1,1).intersects(QRect(50,1236,75,71))) {
                if(event<3) {
                    event++;
                    if(event==3) {
                        shop->ownedSkins.append(1);
                        player->coins++;
                        QMessageBox::information(this,"I bims der Schmuserkadser","Schmuserkadser hat dir einen Skin und einen Coin geschenkt!");
                        write();
                    }
                }
            } else if(QRect(x,y,1,1).intersects(QRect(390,900,300,150))) {
                //QMetaObject::invokeMethod(t_obst,"start");
                moveAn = 3;
            } else if(QRect(x,y,1,1).intersects(QRect(390,1100,300,150))) { //shop
                moveAn = 2;
            } else if(QRect(x,y,1,1).intersects(QRect(10,1810,160,96))) {
                transl->locale = QLocale("de");
                write();
            } else if(QRect(x,y,1,1).intersects(QRect(175,1810,160,96))) {
                transl->locale = QLocale("en");
                write();
            } else if(QRect(x,y,1,1).intersects(QRect(390,1300,300,150))) {
                bool ok=true;
                if(scoreboard->name=="") {
                    QGuiApplication::inputMethod()->show();
                    QString n = QInputDialog::getText(this,tr("Nickname"),transl->getText_Scoreboard_SetName().text,QLineEdit::Normal,"",&ok);
                    if(n.isEmpty()||n.contains("äüö#~ÄÖÜ"||n.length()>12||n.contains(" "))) {
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
                    scoreboard->setScore(highscore);
                    if(scoreboard->wasConnected) {
                        scoreboard->getScores();
                    }
                }
                if(ok&&scoreboard->wasConnected) scoreboard->active = true;
            } else if(QRect(x,y,1,1).intersects(QRect(775,1550,150,135))) {
                if(boxCount) {
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
                            blusse.append(new Blus(90,QRectF(4,180,1,1),"+ B "+QString::number(a)));
                        } else if(num<99) { //powerup
                            int x = 55;
                            int y = 75;
                            int w = 150;
                            int h = 150;
                            int pw = 100;
                            int ph = 100;
                            blusse.append(new Blus(90,QRectF(4,180,1,1),"+ "));
                            if(num<60) { //rel2
                                shop->item3Count++;
                                blusse.append(new Blus(90,QRectF(x,y,w,h),shop->getPixmap(3),pw,ph));
                            } else if(num<70) {//speed 2
                                shop->item4Count++;
                                blusse.append(new Blus(90,QRectF(x,y,w,h),shop->getPixmap(4),pw,ph));
                            } else if(num<85) {//rel 1
                                shop->item1Count++;
                                blusse.append(new Blus(90,QRectF(x,y,w,h),shop->getPixmap(1),pw,ph));
                            } else { //speed 1
                                shop->item2Count++;
                                blusse.append(new Blus(90,QRectF(x,y,w,h),shop->getPixmap(2),pw,ph));
                            }
                        } else {
                            player->coins++;
                            on_shopBuy(1,false,true);
                            write();
                        }
                        write();
                    } else {
                        boxState++;
                    }
                }
            }
        break;
        case -1:
            QMetaObject::invokeMethod(t_tilt,"start",Q_ARG(int,10));
            active = 1;
            go = true;
        case 1:
            if(player->getRect().y()-10>0) {
                bool buy = false;
                if(QRect(x,y,1,1).intersects(QRect(1005,0,75,75))) {
                    if(!t_resume->isActive()) {
                        if(pause) {
                            resumeTime = 3;
                            QMetaObject::invokeMethod(t_resume,"start",Q_ARG(int,1000));
                        } else {
                            if(!t_boost->isActive()&&!t_revive->isActive()) {
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
                        revive = true;
                        t_revive->start(30000);
                    }
                }
                if(QRectF(x,y,1,1).intersects(QRectF(250,1640,90,90))&&go) {  //item2
                    if(shop->item2Count&&!boost) {
                        shop->item2Count--;
                        boost=10;
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
                if(QRectF(x,y,1,1).intersects(QRectF(550,1640,90,90))&&go) {  //item4
                    if(shop->item4Count&&!boost) {
                        shop->item4Count--;
                        boost=14;
                        fastboost = true;
                        QMetaObject::invokeMethod(t_boost,"start",Q_ARG(int,50));
                    }
                }
                for(int i=0;i<obstacles.size();i++) {
                    if(obstacles[i]->hasBox) {
                        QRectF r = obstacles[i]->box;
                        if(QRectF(x,y,1,1).intersects(QRectF(r.x()-20,r.y()-20,r.width()+40,r.height()+40))) {
                            if(obstacles[i]->boxType&&obstacles[i]->opacity==1.1) {
                                obstacles[i]->opacity=1.0;
                                boxCount++;
                                write();
                            } else if(!boxDeath&&!obstacles[i]->boxType) {
                                QMetaObject::invokeMethod(t_boxDeathAn,"start",Q_ARG(int,10));
                                boxDeath = 0;
                                obsNum = i;
                                obstacles[obsNum]->boxType = -1;
                                active = 3;
                                flashOpacity = 0.5;
                            }
                            break;
                        }
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
                        if(schmuser<4) {
                            enemylife--;
                            if(!enemylife) {
                                schmuser = 4;
                                enemydir = 1;
                            }
                        }
                    } else {
                        player->setBenis(player->getBenis()+shop->tapMultiplier);
                        for(int i=0;i<shop->tapMultiplier;i++) {
                            blusse.append(new Blus(random(0,360),QRectF(x-20,y-20,40,40),blus));
                        }
                    }
                }
            }
        break;
        case 2:
            if(QRect(x,y,1,1).intersects(QRect(390,1300,300,150))) {
                moveAn = 1;
            }
        break;
    }
}

void FrmMain::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Back) {
        if(shop->getActive()) {
            moveAn = 4;
        } else if(scoreboard->active){
            moveAn = 6;
        } else {
            write();
            QApplication::quit();
        }
    }
}

void FrmMain::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    write();
}

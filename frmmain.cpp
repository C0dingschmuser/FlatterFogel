#include "frmmain.h"
#include "ui_frmmain.h"

FrmMain::FrmMain(QOpenGLWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::FrmMain)
{
    ui->setupUi(this);
    t_draw = new QTimer();
    t_main = new QTimer();
    t_obst = new QTimer();
    t_event = new QTimer();
    t_revive = new QTimer();
    t_boost = new QTimer();
    connect(t_event,SIGNAL(timeout()),this,SLOT(on_tEvent()));
    connect(t_main,SIGNAL(timeout()),this,SLOT(on_tmain()));
    connect(t_draw,SIGNAL(timeout()),this,SLOT(on_tdraw()));
    connect(t_obst,SIGNAL(timeout()),this,SLOT(on_tObst()));
    connect(t_revive,SIGNAL(timeout()),this,SLOT(on_trevive()));
    connect(t_boost,SIGNAL(timeout()),this,SLOT(on_tboost()));
    //this->showMaximized();
    end = QPixmap(":/images/end.png");
    btnPx = QPixmap(":/images/button.png");
    blus = QPixmap(":/images/blus.png");
    minus = QPixmap(":/images/minus.png");
    schmuserkadser = QPixmap(":/images/schmuserkadser.png");
    maas = QPixmap(":/images/maas.png");
    player = new Player(QRectF(1080/2-30,1920/2-30,60,60));
    shop = new Shop(player);
    connect(shop,SIGNAL(back()),this,SLOT(on_shopBack()));
    connect(shop,SIGNAL(msg(QString)),this,SLOT(on_shopMsg(QString)));
    connect(shop,SIGNAL(buy(int)),this,SLOT(on_shopBuy(int)));
    enemyRect = QRectF(-300,100,300,200);
    enemy = "Schmuserkadser";
    enemylife = 10;
    active = 0;
    enemydir = 1; //unten
    score = 0;
    schmuser = 0;
    highscore = 0;
    boost = 0;
    revive = false;
    loadData();
    workerThread = new QThread();
    t_main->start(5);
    t_draw->start(5);
    t_obst->start(100);
    t_event->start(2000);
    t_main->moveToThread(workerThread);
    t_obst->moveToThread(workerThread);
    t_boost->moveToThread(workerThread);
    workerThread->start();
}

FrmMain::~FrmMain()
{
    delete player;
    delete ui;
}

void FrmMain::on_tdraw()
{
    update();
}

void FrmMain::on_tmain()
{
    int start = QTime::currentTime().msec();
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
    if(active==1) {
        for(int i=0;i<obstacles.size();i++) {
            if(boost) {
                obstacles[i]->moveBy(-boost,0);
            } else {
                obstacles[i]->moveBy(-1,0);
            }
            if((player->getRect().intersects(obstacles[i]->getBottom())||
                    player->getRect().intersects(obstacles[i]->getTop()))&&!boost) {
                active = 3;
            }
        }
    }
    if(player->getRect().y()<1800&&active>0) {
        double velD = player->getVelD();
        if(velD<10) velD += 0.1;
        player->setVelD(velD);
        QRectF r = player->getRect();
        if(r.y()+velD>1800) {
            velD = 1800-r.y();
        }
        player->setPos(r.x(),r.y()+velD);
    }
    if(player->getRect().y()>=1800) {
        if(!revive) {
            QMetaObject::invokeMethod(t_boost,"stop");
            active = 2;
        } else {
            active=-1;
            revive = false;
            reset(1);
            blusse.append(new Blus(270,QRect(400,850,1,1),"Revive!",88));
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
        if(enemyRect.intersects(player->getRect())) active = 3;
    } else if(schmuser==4&&active==1) {
        if(enemyRect.x()>-300) enemyRect.moveTo(enemyRect.x()-1,enemyRect.y());
        if(enemyRect.x()<=-300) {
            schmuser = 0;
            enemylife = 10;
            enemyRect.moveTo(-300,100);
        }
    }
    for(int i=0;i<obstacles.size();i++) {
        if(obstacles[i]->getTop().x()<-110) {
            delete obstacles[i];
            obstacles.removeAt(i);
            //qDebug()<<i;
            //break;
        } else if(obstacles[i]->getTop().x()<=player->getRect().x()&&active==1&&!obstacles[i]->type&&!obstacles[i]->approved) {
            obstacles[i]->approved = true;
            score++;
            if(!boost) {
                player->setBenis(player->getBenis()+(score*shop->multiplier));
                int b = score*shop->multiplier;
                blusse.append(new Blus(90,QRectF(4,75,1,1),"+"+QString::number(b)));
                for(int a=0;a<360;a+=12) {
                    blusse.append(new Blus(a,QRectF(player->getRect().center().x()-40,player->getRect().center().y()-40,80,80),blus));
                }
            }
        }
    }
}

void FrmMain::on_tObst()
{

    if(active!=1||schmuser) return;
    if(obstacles.size()<=3) {
        //diff 600
        int x = 1200;
        if(obstacles.size()) {
            x = obstacles[obstacles.size()-1]->getBottom().x()+600;
        }
        switch(random(0,3)) {
            case 0: //oben
                obstacles.append(new Obstacle(QRect(x,0,100,400),QRect(x,700,100,1200)));
            break;
            case 1: //mitte
                obstacles.append(new Obstacle(QRect(x,0,100,810),QRect(x,1110,100,810)));
            break;
            case 2: //unten
                obstacles.append(new Obstacle(QRect(x,0,100,1200),QRect(x,1500,100,420)));
            break;
        }
    }
}

void FrmMain::on_tEvent()
{
    if(active!=1) return;
    if(score%10==0&&score!=0&&!boost||schmuser) {
        if(!schmuser) {
            enemytype = random(1,3);
            switch(enemytype) {
                case 1: //schmuserkadser
                    enemyPixmap = schmuserkadser;
                    enemy = "Schmuserkadser";
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
            if(obstacles[i]->getTop().x()>1080) {
                delete obstacles[i];
                obstacles.removeAt(i);
            }
        }
    }
}

void FrmMain::on_shopBack()
{
    shop->setActive(false);
}

void FrmMain::on_shopMsg(QString msg)
{
    QMessageBox::information(this,"Info",msg);
}

void FrmMain::on_shopBuy(int amount)
{
    write();
    blusse.append(new Blus(90,QRectF(4,75,1,1),"-"+QString::number(amount)));
}

void FrmMain::on_trevive()
{
    revive = false;
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
                b->color = QColor(238,77,46);
            }
            blusse.append(b);
        }
    } else {
        boost = 0;
        QMetaObject::invokeMethod(t_boost,"stop");
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
            shop->load(list.at(2).toInt(),list.at(5).toInt());
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
        << QString::number(shop->tapMultiplier) << "#" << QString::number(shop->item2Count) << "#";
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
    enemylife = 10;
    schmuser = 0;
    enemydir = 1;
    boost = 0;
    player->setPos(1080/2-30,1920/2-30);
    enemyRect.moveTo(-300,100);
}

void FrmMain::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    scaleX = double(this->geometry().width()/double(1080));
    scaleY = double(this->geometry().height()/double(1920));
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.scale(scaleX,scaleY);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(22,22,24));
    painter.drawRect(0,0,1080,1920);
    //painter.drawPixmap(0,0,2160,2160,bg);
    painter.setBrush(QColor(255,153,0));
    for(int i=0;i<obstacles.size();i++) {
        painter.drawRect(obstacles[i]->getTop());
        painter.drawRect(obstacles[i]->getBottom());
    }
    painter.setBrush(QColor(28,185,146));
    painter.drawRect(0,1860,1080,60);
    painter.setBrush(QColor(0,143,255));
    painter.drawRect(player->getRect());
    if(revive&&(active==1||active==-1)) {
        painter.setBrush(Qt::NoBrush);
        QPen pen(QColor(28,185,146));
        pen.setWidth(3);
        painter.save();
        painter.setPen(pen);
        painter.drawEllipse(player->getRect().center(),100,100);
        painter.restore();
    }
    if(schmuser) {
        painter.drawPixmap(enemyRect,enemyPixmap,QRectF(0,0,maxX,maxY));
    }
    for(int i=0;i<blusse.size();i++) {
        if(!blusse[i]->isText()&&!blusse[i]->isRect) {
            painter.setOpacity((blusse[i]->getOpacity()/2.55)/100.0);
            painter.drawPixmap(blusse[i]->getRect(),blusse[i]->getPixmap(),QRectF(0,0,40,40));
            painter.setOpacity(1);
        } else if(blusse[i]->isRect) {
            painter.setOpacity((blusse[i]->getOpacity()/2.55)/100.0);
            painter.setBrush(blusse[i]->color);
            painter.drawRect(blusse[i]->getRect());
            painter.setOpacity(1);
        } else {
            QFont f("Arial");
            f.setBold(true);
            f.setPixelSize(blusse[i]->size);
            painter.setFont(f);
            if(blusse[i]->getOpacity()>0) {
                painter.setPen(QPen(QColor(255,255,255,blusse[i]->getOpacity())));
                painter.drawText(blusse[i]->getRect().x(),blusse[i]->getRect().y(),blusse[i]->getText());
            }
        }
    }

    if(active==2) {
        QFont f("Arial");
        f.setBold(true);
        f.setPixelSize(88);
        painter.setFont(f);
        //800*480
        painter.drawPixmap(140,750,800,480,end);
        //300*150
        painter.drawPixmap(390,1300,300,150,btnPx);
        painter.setPen(QColor(108,67,43));
        painter.drawText(730,970,QString::number(score));
        painter.drawText(730,1175,QString::number(highscore));
        painter.drawText(480,1410,"OK");
    } else if(active>0||active==-1) {
        QFont f("Arial");
        f.setBold(true);
        f.setPixelSize(88);
        painter.setFont(f);
        painter.setPen(QColor(108,67,43));
        painter.drawText(510,750,QString::number(score));
        if(schmuser) {
            switch(schmuser) {
                case 1:
                    painter.drawText(350,450,"Oh Nein!");
                break;
                case 2:
                    painter.drawText(100,450,"Ein "+enemy+"!");
                break;
                case 3:
                    painter.drawText(250,450,"Schnell gib -");
                break;
            }
        }
        painter.save();
        if(!shop->item1Count||active==-1) {
            painter.setOpacity(0.5);
        }
        painter.drawPixmap(100,1700,125,125,shop->getPixmap(1)); //item1
        painter.restore();
        f.setPixelSize(44);
        painter.setFont(f);
        painter.drawText(100,1855,QString::number(shop->item1Count)+"x");
        painter.save();
        if(!shop->item2Count||active!=-1||active==-1&&score) {
            painter.setOpacity(0.5);
        }
        painter.drawPixmap(325,1700,125,125,shop->getPixmap(2)); //item2
        painter.restore();
        painter.drawText(325,1855,QString::number(shop->item2Count)+"x");
    } else if(!active&&!shop->getActive()) {
        QFont f("Arial");
        f.setBold(true);
        f.setPixelSize(88);
        painter.setFont(f);
        painter.setPen(QColor(108,67,43));
        painter.drawPixmap(QRect(390,900,300,150),btnPx);
        painter.drawPixmap(QRect(390,1100,300,150),btnPx);
        painter.drawText(465,1005,"Los");
        painter.drawText(435,1205,"Shop");
    } else if(!active&&shop->getActive()) {
        shop->draw(painter);
    }
    QFont f("Arial");
    f.setBold(true);
    f.setPixelSize(56);
    painter.setFont(f);
    painter.setPen(Qt::white);
    painter.drawText(4,45,"BENIS "+QString::number(player->getBenis()));
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
            } else {
                if(QRect(x,y,1,1).intersects(QRect(390,900,300,150))) {
                    QMetaObject::invokeMethod(t_obst,"start");
                    active = -1;
                } else if(QRect(x,y,1,1).intersects(QRect(390,1100,300,150))) {
                    shop->setActive(true);
                }
            }
        break;
        case -1:
            active = 1;
            go = true;
        case 1:
            if(player->getRect().y()-10>0) {
                bool buy = false;
                if(!go&&QRectF(x,y,1,1).intersects(QRectF(100,1700,125,125))) { //item1
                    buy = true;
                    if(shop->item1Count&&!revive) {
                        shop->item1Count--;
                        revive = true;
                        t_revive->start(30000);
                    }
                }
                if(QRectF(x,y,1,1).intersects(QRectF(325,1700,125,125))&&go) {  //item2
                    if(shop->item2Count&&!boost) {
                        shop->item2Count--;
                        boost=10;
                        QMetaObject::invokeMethod(t_boost,"start",Q_ARG(int,50));
                    }
                }
                if(!buy) {
                    player->setVelD(-5);
                    if(QRectF(x,y,1,1).intersects(enemyRect)) {
                        if(enemytype!=2) {
                            blusse.append(new Blus(random(0,360),QRectF(x-40,y-40,80,80),minus));
                        } else {
                            blusse.append(new Blus(random(0,360),QRectF(x-40,y-40,80,80),"██"));
                        }
                        blusse.append(new Blus(90,QRectF(4,75,1,1),"+"+QString::number(score*5)));
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
                            blusse.append(new Blus(random(0,360),QRectF(x-40,y-40,80,80),blus));
                        }
                    }
                }
            }
        break;
        case 2:
            if(QRect(x,y,1,1).intersects(QRect(390,1300,300,150))) {
                active = 0;
                reset();
            }
        break;
    }
}

void FrmMain::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Back) {
        if(shop->getActive()) {
            shop->setActive(false);
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

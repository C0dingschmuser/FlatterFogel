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
    t_reviveL = new QTimer();
    t_boost = new QTimer();
    t_an = new QTimer();
    t_tilt = new QTimer();
    t_tchange = new QTimer();
    t_flag = new QTimer();
    t_star = new QTimer();
    flashOpacity = 0;
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
    connect(t_reviveL,SIGNAL(timeout()),this,SLOT(on_treviveL()));
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
    flag_de = QPixmap(":/images/flag/de.png");
    flag_en = QPixmap(":/images/flag/en.png");
    player = new Player(QRectF(1080/2-40,1920/2-40,80,80));
    shop = new Shop(player,font,transl);
    connect(shop,SIGNAL(back()),this,SLOT(on_shopBack()));
    connect(shop,SIGNAL(msg(QString)),this,SLOT(on_shopMsg(QString)));
    connect(shop,SIGNAL(buy(int)),this,SLOT(on_shopBuy(int)));
    enemyRect = QRectF(-300,100,300,200);
    enemy = "Schmuserkadser";
    enemylife = 10;
    //window
    createWindows();
    //~Window
    flag = false;
    active = 0;
    enemydir = 1; //unten
    score = 0;
    schmuser = 0;
    highscore = 0;
    boost = 0;
    medal = 0;
    g1x = 0;
    g2x = 1080;
    revive = false;
    loadData();
    workerThread = new QThread();
    t_main->start(5);
    t_draw->start(15);
    t_obst->start(100);
    t_event->start(2000);
    t_flag->start(750);
    t_star->start(125);
    t_tchange->setSingleShot(true);
    t_an->moveToThread(workerThread);
    t_main->moveToThread(workerThread);
    t_obst->moveToThread(workerThread);
    t_boost->moveToThread(workerThread);
    t_tilt->moveToThread(workerThread);
    t_tchange->moveToThread(workerThread);
    t_flag->moveToThread(workerThread);
    t_star->moveToThread(workerThread);
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
    if(active==1) {
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
            QMetaObject::invokeMethod(t_an,"stop");
            QMetaObject::invokeMethod(t_tilt,"stop");
            active = 2;
        } else {
            active=-1;
            revive = false;
            reset(1);
            blusse.append(new Blus(270,QRect(260,850,1,1),"Revive!",88));
        }
        if(score>=100) {
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
        if(obstacles[i]->getTop().x()<-110) {
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
                player->setBenis(player->getBenis()+(score*shop->multiplier));
                int b = score*shop->multiplier;
                blusse.append(new Blus(90,QRectF(4,75,1,1),"+"+QString::number(b)));
                for(int a=0;a<360;a+=12) {
                    blusse.append(new Blus(a,QRectF(player->getRect().center().x()-20,player->getRect().center().y()-20,40,40),blus));
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
        QPixmap p(":/images/pipe1.png");
        QRect top(x,0,100,random(300,1300));
        QRect bottom(x,top.height()+300,100,1920-top.height()+300);
        /*switch(random(0,3)) {
            case 0: //oben
                obstacles.append(new Obstacle(QRect(x,0,100,400),QRect(x,700,100,1200),p));
            break;
            case 1: //mitte
                obstacles.append(new Obstacle(QRect(x,0,100,810),QRect(x,1110,100,810),p));
            break;
            case 2: //unten
                obstacles.append(new Obstacle(QRect(x,0,100,1200),QRect(x,1500,100,420),p));
            break;
        }*/
        obstacles.append(new Obstacle(top,bottom,p));
    }
}

void FrmMain::on_tEvent()
{
    if(active!=1) return;
    if(((score%10==0)&&(score!=0)&&(!boost))||schmuser) {
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
            if(obstacles[i]->getTop().x()>1280) {
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

void FrmMain::on_treviveL()
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

void FrmMain::on_tAn()
{
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
    player->tdir = false;
}

void FrmMain::on_tflag()
{
    if(flag) {
        flag = false;
    } else {
        flag = true;
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
            shop->load(list.at(2).toInt(),list.at(5).toInt(),list.at(7).toInt());
            if(list.at(6).size()>1) {
                transl->locale = QLocale(list.at(6));
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
        << transl->locale.bcp47Name() << "#" << QString::number(shop->item3Count) << "#";
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
    QMetaObject::invokeMethod(t_an,"stop");
    QMetaObject::invokeMethod(t_tilt,"stop");
    enemylife = 10;
    medal = 0;
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
    for(int i=0;i<obstacles.size();i++) {
        painter.drawPixmap(obstacles[i]->getTop(),obstacles[i]->px,QRectF(0,0,64,64));
        painter.drawPixmap(obstacles[i]->getBottom(),obstacles[i]->px,QRectF(0,0,64,64));
    }
    painter.drawPixmap(QRectF(g1x,1660,1080,260),ground,QRectF(0,0,27,7));
    painter.drawPixmap(QRectF(g2x,1660,1080,260),ground,QRectF(0,0,27,7));
    painter.setBrush(QColor(0,143,255));
    //painter.drawRect(player->getRect());
    painter.save();
    painter.translate(player->getRect().center());
    painter.rotate(player->tilt-45);
    painter.drawPixmap(QRectF(-player->getRect().width()/2,-player->getRect().height()/2,
                              player->getRect().width(),player->getRect().height()),player->getPx(),QRectF(0,0,34,35));
    painter.restore();
    if(revive&&(active==1||active==-1)) {
        painter.setBrush(Qt::NoBrush);
        if(revive>1) {
            pen.setColor(QColor(255,0,0));
        }
        pen.setWidth(3);
        painter.setPen(pen);
        painter.drawEllipse(player->getRect().center(),100,100);
        pen.setWidth(2);
        painter.setPen(pen);
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
        painter.drawPixmap(140,750,800,480,end);
        //300*150
        painter.drawPixmap(390,1300,300,150,btnPx);
        painter.setPen(QColor(0,143,255));
        switch(medal) {
            case 1:
                painter.drawPixmap(240,835,300,300,medal_bronze);
            break;
            case 2:
                painter.drawPixmap(240,835,300,300,medal_silver);
            break;
            case 3:
                painter.drawPixmap(240,835,300,300,medal_gold);
            break;
        }
        painter.drawText(730,970,QString::number(score));
        painter.drawText(730,1175,QString::number(highscore));
        painter.drawText(480,1410,"OK");
    } else if(active>0||active==-1) {
        f.setPixelSize(56);
        painter.setFont(f);
        painter.setPen(QColor(0,143,255));
        if(score<10) {
            painter.drawText(510,750,QString::number(score));
        } else if(score<100) {
            painter.drawText(490,750,QString::number(score));
        } else if(score<1000) {
            painter.drawText(470,750,QString::number(score));
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
        painter.drawPixmap(100,1700,125,125,shop->getPixmap(1)); //item1
        painter.setOpacity(1);
        f.setPixelSize(44);
        painter.setFont(f);
        painter.setPen(QColor(238,77,46));
        painter.drawText(100,1855,QString::number(shop->item1Count)+"x");
        if(!shop->item2Count||active!=-1||(active==-1&&score)) {
            painter.setOpacity(0.5);
        }
        painter.drawPixmap(300,1700,125,125,shop->getPixmap(2)); //item2
        painter.setOpacity(1);
        painter.drawText(300,1855,QString::number(shop->item2Count)+"x");
        if(!shop->item3Count||active==-1) {
            painter.setOpacity(0.5);
        }
        painter.drawPixmap(500,1700,125,125,shop->getPixmap(3)); //item3
        painter.setOpacity(1);
        painter.drawText(500,1855,QString::number(shop->item3Count)+"x");

    } else if(!active&&!shop->getActive()) {
        Text go = transl->getBtn_Go();
        Text shop = transl->getBtn_Shop();
        f.setPixelSize(go.size);
        painter.setFont(f);
        painter.setPen(QColor(0,143,255));
        painter.drawPixmap(QRect(390,900,300,150),btnPx);
        painter.drawPixmap(QRect(390,1100,300,150),btnPx);
        painter.drawPixmap(QRect(10,1810,160,96),flag_de);
        painter.drawPixmap(QRect(175,1810,160,96),flag_en);
        painter.setBrush(QColor(22,22,24));
        painter.setOpacity(0.75);
        if(transl->locale.language()==QLocale::German) {
            painter.drawRect(175,1810,160,96);
        } else {
            painter.drawRect(10,1810,160,96);
        }
        painter.setOpacity(1);
        painter.drawText(go.pos,go.text);
        f.setPixelSize(shop.size);
        painter.setFont(f);
        painter.drawText(shop.pos,shop.text);
    } else if(!active&&shop->getActive()) {
        shop->draw(painter);
    }
    f.setPixelSize(48);
    painter.setFont(f);
    painter.setPen(Qt::white);
    painter.drawText(4,50,"BENIS "+QString::number(player->getBenis()));
    if(flashOpacity) {
        painter.setBrush(Qt::white);
        painter.setOpacity(flashOpacity);
        painter.drawRect(0,0,1080,1920);
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
            } else {
                if(QRect(x,y,1,1).intersects(QRect(390,900,300,150))) {
                    //QMetaObject::invokeMethod(t_obst,"start");
                    QMetaObject::invokeMethod(t_an,"start",Q_ARG(int,250));
                    active = -1;
                } else if(QRect(x,y,1,1).intersects(QRect(390,1100,300,150))) {
                    shop->setActive(true);
                } else if(QRect(x,y,1,1).intersects(QRect(10,1810,160,96))) {
                    transl->locale = QLocale("de");
                    write();
                } else if(QRect(x,y,1,1).intersects(QRect(175,1810,160,96))) {
                    transl->locale = QLocale("en");
                    write();
                }
            }
        break;
        case -1:
            QMetaObject::invokeMethod(t_tilt,"start",Q_ARG(int,10));
            active = 1;
            go = true;
        case 1:
            player->tstep = (player->tilt/200)*10;
            player->tdir = true;
            QMetaObject::invokeMethod(t_tchange,"stop");
            QMetaObject::invokeMethod(t_tchange,"start",Q_ARG(int,200));
            if(player->getRect().y()-10>0) {
                bool buy = false;
                if(!go&&QRectF(x,y,1,1).intersects(QRectF(100,1700,125,125))) { //item1
                    if(shop->item1Count&&!revive&&!boost) {
                        buy = true;
                        shop->item1Count--;
                        revive = true;
                        t_revive->start(30000);
                    }
                }
                if(QRectF(x,y,1,1).intersects(QRectF(300,1700,125,125))&&go) {  //item2
                    if(shop->item2Count&&!boost) {
                        shop->item2Count--;
                        boost=10;
                        QMetaObject::invokeMethod(t_boost,"start",Q_ARG(int,50));
                    }
                }
                if(QRectF(x,y,1,1).intersects(QRectF(500,1700,125,125))) {  //item3
                    if(shop->item3Count&&!revive&&!boost) {
                        shop->item3Count--;
                        revive = 2;
                        buy = true;
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
                            blusse.append(new Blus(random(0,360),QRectF(x-20,y-20,40,40),blus));
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

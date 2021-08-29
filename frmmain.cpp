#include "frmmain.h"
#include "ui_frmmain.h"

FrmMain::FrmMain(QOpenGLWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::FrmMain)
{
    ui->setupUi(this);

    networkManager = new NetworkManager();

    connect(networkManager, SIGNAL(StatusDone(QString)), this, SLOT(HandleStatus(QString)));
    connect(networkManager, SIGNAL(AuthSave(QString)), this, SLOT(AuthSave(QString)));
    connect(networkManager, SIGNAL(DSGVODone(QString)), this, SLOT(DSGVODone(QString)));

#ifdef Q_OS_ANDROID
    setupIAP();
#elif Q_OS_IOS
    setupIAP()
#endif

    lastPost = "2561200";
    loading = true;
    mainX = 0;
    newHS = 0;
    caveSpawnCount = 0;
    schmuserWaveSize = 5;
    schmuserWave = 1;
    schmuserkills = 0;
    schmuserKillsneeded = 20;
    schmuserBaseHP = 1000;
    schmuserBaseMaxHP = 1000;
    schmuserRange = 600;
    schmuserDmg = 10;
    schmuserHP = 100;
    endX = 1080;
    closeSave = false;
    cloud1X = 0;
    cloud2X = 1079;
    event = 0;
    boostDisabled = false;
    donator = false;
    schmuserDefend = false;
    schmuserEnemy = true;
    playTime = 0;
    localPlayTime = 0;
    cBox = 0;
    cBTouch = 0;
    textFade = 1;
    cBPipe = 0;
    go = 1;
    rgb_red = 255, rgb_green = 0, rgb_blue = 0, rgb_mode = 0;
    hardcore = false;
    radR = 2700;
    anDir = false;
    moveAn = false;
    refActive = false;
    soundEnabled = false;
    soundEffectsEnabled = false;
    version = "1.3.4.r";
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
    t_rgb = new QTimer();
    t_backup = new QTimer();
    t_reload = new QTimer();
    t_regen = new QTimer();
    flashOpacity = 0;
    pause = false;
    ad = 0;
    transl = new Translation();
    int id = QFontDatabase::addApplicationFont(":/font/PressStart2P.ttf");
    QString fam = QFontDatabase::applicationFontFamilies(id).at(0);
    font = QFont(fam);
    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sound/pg.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    sound = new QMediaPlayer();
    connect(sound,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SLOT(on_mediastateChanged(QMediaPlayer::MediaStatus)));
    sound->setPlaylist(playlist);
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
    connect(t_rgb,SIGNAL(timeout()),this,SLOT(on_tRgb()));
    connect(t_backup,SIGNAL(timeout()),this,SLOT(on_tbackup()));
    connect(t_reload,SIGNAL(timeout()),this,SLOT(on_treload()));
    connect(t_regen,SIGNAL(timeout()),this,SLOT(on_tregen()));
    connect(qApp,SIGNAL(applicationStateChanged(Qt::ApplicationState)),this,SLOT(on_appStateChanged(Qt::ApplicationState)));
    //this->showMaximized();
    referrals = 3;
    invited = false;
    underwater = false;
    space = false;
    flip = false;
    gameSpeed = 1;
    schmuserKillsneeded = 20;
    schmuserReload = 100;
    schmuserRegen = 200;
    schmuserCredits = 0;
    schmuserCost.push_back(10);
    schmuserCost.push_back(5);
    schmuserCost.push_back(20);
    schmuserCost.push_back(10);
    lastbenpos = nullptr;
    btnup = QPixmap(":/images/buttons/up.png");
    btndown = QPixmap(":/images/buttons/down.png");
    end = QPixmap(":/images/end.png");
    btnPx = QPixmap(":/images/buttons/button.png");
    settingsBtn = QPixmap(":/images/buttons/buttonSettings.png");
    blus = QPixmap(":/images/blus.png");
    minus = QPixmap(":/images/minus.png");
    ground = QPixmap(":/images/backgrounds/ground/basic.png");
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
    vol0 = QPixmap(":/images/buttons/vol0.png");
    vol1 = QPixmap(":/images/buttons/vol1.png");
    coinPx = QPixmap(":/images/coin.png");
    referralPx1 = QPixmap(":/images/referral.png");
    referralPx2 = QPixmap(":/images/referral2.png");
    mieserkadserPx = QPixmap(":/images/mieserkadser.png");
    ad_px = QPixmap(":/images/ad.png");
    ad_px_eng = QPixmap(":/images/ad_eng.png");
    restorePx = QPixmap(":/images/buttons/restoreBtn.png");
    windowPx = QPixmap(":/images/shopM.png");
    dsgvoPx_de = QPixmap(":/images/dsgvo_de.png");
    dsgvoPx_en = QPixmap(":/images/dsgvo_en.png");

    for(int i=0;i<26;i++) {
        skins.push_back(QPixmap(":/images/player/skins/"+QString::number(i)+".png"));
    }
    for(int i=0;i<18;i++) {
        pipes.push_back(QPixmap(":/images/pipes/"+QString::number(i)+".png"));
    }
    for(int i=0;i<12;i++) {
        tails.push_back(QPixmap(":/images/tails/"+QString::number(i)+".png"));
    }
    for(int i=0;i<29;i++) {
        thumbs.append(QPixmap(":/images/pipes/thumbs/"+QString::number(i)+".jpg"));
    }
    for(int i=1;i<5;i++) {
        powerupPx.append(QPixmap(":/images/powerups/p"+QString::number(i)+".png"));
    }
    for(int i=0;i<5;i++) {
        planets.push_back(QPixmap(":/images/backgrounds/planets/"+QString::number(i)+".png"));
    }
    /*QFile f,f2;
    QString p = QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/flatter.wav";
    QString p2 = ":/sounds/flatter.wav";
    f.setFileName(p);
    f2.setFileName(p2);
    if(!f.exists()) {
       f2.copy(p);
    }
    qDebug()<<f2.errorString();*/
    backgrounds.push_back(new Background(1,QColor(22,22,24),true,false,true));
    backgrounds.push_back(new Background(2,QColor(0,143,255),false,true,true,false,true,true));
    backgrounds.push_back(new Background(3,QColor(95,95,95),true,false,false,false,false,true));
    backgrounds.push_back(new Background(4,QColor(95,95,95),false,false,false,true,false));
    backgrounds.push_back(new Background(5,QColor(255,207,43),false,false,false,false,false,true));
    backgrounds.push_back(new Background(6,QColor(22,22,24),true,false,false,false,false,true));
    backgrounds.push_back(new Background(7,QColor(22,22,24),true,false,true,false,true,false,1));
    backgrounds.push_back(new Background(8,QColor(22,22,24),false,true,false,false,true,false,0,false));
    backgrounds.push_back(new Background(9,QColor(22,22,24),false,false,false,false,false,true,0,false));
    backgrounds.push_back(new Background(10,QColor(22,22,24),false,false,false,false,false,true,0,false));
    backgrounds.push_back(new Background(11,QColor(22,22,24),false,false,false,false,false,true,0,false));
    for(int i=0;i<3;i++) {
        boxPxAn.append(QPixmap(":/images/box/box_"+QString::number(i+1)+".png"));
    }
    player = new Player(QRectF(1080/2-250,1920/2-40,80,80));
    shop = new Shop(player,font,transl,coinPx,cloudPx);

    shop->skins = skins;
    shop->pipes = pipes;
    shop->tails = tails;
    shop->g2 = player->g2;

    scoreboard = new Scoreboard(networkManager, shop->background,btnPx,font,transl);
    shop->backgrounds = backgrounds;
    scoreboard->medals = medalsPx;
    connect(scoreboard,SIGNAL(connFail()),this,SLOT(on_sbConnFail()));
    connect(scoreboard,SIGNAL(wrongName(int)),this,SLOT(on_sbWrongName(int)));
    connect(scoreboard,SIGNAL(write(int)),this,SLOT(on_scoreWrite(int)));
    connect(scoreboard,SIGNAL(back()),this,SLOT(on_scoreBack()));
    connect(scoreboard, SIGNAL(open()), this, SLOT(OpenScoreboard()));

    connect(networkManager, SIGNAL(GetScoreDone(QString)), scoreboard, SLOT(HandleGetScore(QString)));
    connect(networkManager, SIGNAL(SetScoreDone(QString)), scoreboard, SLOT(HandleSetScore(QString)));
    connect(networkManager, SIGNAL(ChangeNameDone(QString)), scoreboard, SLOT(HandleNameChange(QString)));

    connect(shop,SIGNAL(back()),this,SLOT(on_shopBack()));
    connect(shop,SIGNAL(msg(QString)),this,SLOT(on_shopMsg(QString)));
    connect(shop,SIGNAL(buy(int,bool,bool,bool)),this,SLOT(on_shopBuy(int,bool,bool,bool)));

    settings = new Settings(&shop->background,&btnPx,transl, scoreboard, networkManager);
    connect(settings, SIGNAL(updateFPS(FPSMode)), this, SLOT(UpdateFps(FPSMode)));
    connect(settings, SIGNAL(dsgvoCheck()), this, SLOT(DSGVOCheck()));

    connect(settings,SIGNAL(back()),this,SLOT(on_settingsBack()));
    connect(settings,SIGNAL(play()),this,SLOT(on_settingsPlay()));
    enemyRect = QRectF(-300,100,300,200);
    textColor = QColor(255,153,0);
    enemy = "Mieserkadser";
    enemylife = 10;
    boxDeath = 0;
    obsNum = 0;
    boxState = 0;
    resumeTime = 0;
    closing = false;
    planetX = 1080;
    planetY = 1000;
    chosenPlanet = 0;
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
    highscore_S = 0;
    highscore_UM = 0;
    boost = 0;
    crate = false;
    fastboost = false;
    lowGraphics = false;
    suspended = false;
    cave = false;
    outdated = false;
    medal = 0;
    g1x = 0;
    g2x = 1080;
    boxCount = 0;
    ad_active = false;
    unlockedSpeed = false;
    revive = false;
    boostused = false;
    QRandomGenerator(QDateTime::currentDateTimeUtc().toTime_t());
    //qsrand(QDateTime::currentDateTime().toTime_t());
    currentDateTime = QDateTime::currentDateTime();

    t_draw->setTimerType(Qt::PreciseTimer);
    //int aufgerundet für 60fps
    t_draw->start(17);

    loadData();

    workerThread = new QThread();
    blusThread = new QThread();
    animationThread = new QThread();
    musicThread = new QThread();
    t_main->start(5);
    t_rgb->start(10);
    t_obst->start(50);
    t_blus->start(5);
    t_event->start(500);
    t_flag->start(750);
    t_star->start(125);
    t_an->start(150);
    t_reload->start(schmuserReload);
    t_regen->start(schmuserRegen);
    //t_backup->start(10000);
    t_animation->setTimerType(Qt::PreciseTimer);
    t_animation->start(1);
    t_tchange->setSingleShot(true);
    t_backup->moveToThread(animationThread);
    t_animation->moveToThread(animationThread); //
    t_rgb->moveToThread(workerThread); //
    t_an->moveToThread(workerThread); //
    t_main->moveToThread(workerThread); //
    t_obst->moveToThread(workerThread); //
    t_boost->moveToThread(workerThread); //
    t_tilt->moveToThread(workerThread); //
    t_tchange->moveToThread(workerThread); //
    t_flag->moveToThread(workerThread); //
    t_star->moveToThread(workerThread); //
    t_boxDeathAn->moveToThread(workerThread);
    t_resume->moveToThread(workerThread);
    t_blus->moveToThread(blusThread); //
    t_tail->moveToThread(blusThread); //
    t_reload->moveToThread(blusThread);
    t_regen->moveToThread(blusThread);
    sound->moveToThread(blusThread);
    t_newHS->moveToThread(workerThread); //
    for(int i=0;i<10;i++) {
        QSoundEffect *effect = new QSoundEffect();
        effect->setSource(QUrl::fromLocalFile(":/sound/flatter.wav"));
        effect->setVolume(0.4);
        effect->moveToThread(musicThread);
        soundEffects.push_back(effect);
    }
    sound->moveToThread(musicThread);
    workerThread->start();
    blusThread->start();
    musicThread->start();
    animationThread->start();
    //startStop(true);
    qApp->setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; }");
}

FrmMain::~FrmMain()
{
    delete player;
    delete ui;
}


void FrmMain::setupIAP() {
    store = new QInAppStore(this);

    connect(store,SIGNAL(transactionReady(QInAppTransaction*)),this,SLOT(handleTransaction(QInAppTransaction*)));
    connect(store,SIGNAL(productRegistered(QInAppProduct*)),this,SLOT(productRegistered(QInAppProduct*)));
    connect(store,SIGNAL(productUnknown(QInAppProduct::ProductType,QString)),this,SLOT(productUnknown(QInAppProduct::ProductType,QString)));

    store->registerProduct(QInAppProduct::Unlockable, QStringLiteral("pack_small"));
    store->registerProduct(QInAppProduct::Unlockable, QStringLiteral("pack_medium"));
    store->registerProduct(QInAppProduct::Unlockable, QStringLiteral("pack_large"));
}

void FrmMain::handleTransaction(QInAppTransaction *transaction) {
    //Transaktion finalisieren

    if(!pInit) return;

    pInit = false;

    if(transaction->status() == QInAppTransaction::PurchaseApproved ||
            transaction->status() == QInAppTransaction::PurchaseRestored) {
        //erfolgreich / restored

        QString identifier = transaction->product()->identifier();
        QString orderID = transaction->orderId();

        //qDebug() << orderID;
        //qDebug() << identifier;

        int buyCode = -1;

        if(identifier == QStringLiteral("pack_small")) {
            buyCode = 0;
        } else if(identifier == QStringLiteral("pack_medium")) {
            buyCode = 1;
        } else if(identifier == QStringLiteral("pack_large")) {
            buyCode = 2;
        }

        switch(buyCode) {
        case 2:
            //packet large
            unlockedSpeed = true;
            if(!vContains(shop->ownedbackgrounds, 8))  {
                shop->ownedbackgrounds.push_back(8); //unterwasser
                boxCount += 25;
            }
        case 1:
            //packet medium
            if(!vContains(shop->ownedbackgrounds, 4))  {
                shop->ownedbackgrounds.push_back(4); //shekel bg
                if(donator == 1) boxCount += 10;
            }
            if(!vContains(shop->ownedPipes,8)) shop->ownedPipes.push_back(8); //shekel sskin
            if(!vContains(shop->ownedSkins,23)) shop->ownedSkins.push_back(23); //btc skin
        case 0:
            //packet small
            if(!vContains(shop->ownedbackgrounds, 7)) {
                shop->ownedbackgrounds.push_back(7); //skyline
                if(donator == 0) boxCount += 5;
            }
            if(!vContains(shop->ownedPipes, 11)) shop->ownedPipes.push_back(11); //skyline sskin
            break;
        }

        if(buyCode > -1) {
            //Speichern
            write();
            ad_active = false;

            if(transaction->status() == QInAppTransaction::PurchaseApproved) {

                QUrlQuery qry;
                qry.addQueryItem("code", "3");
                qry.addQueryItem("name", scoreboard->name);
                qry.addQueryItem("type", QString::number(buyCode));
                qry.addQueryItem("id", orderID);

                networkManager->PostData(qry, RequestCodes::Custom);

                if(transl->getLanguageCode() == 1) {
                    QMessageBox::information(this,"Danke!","Vielen Dank für deinen Kauf!\nDie exklusiven Inhalte wurden im Shop freigeschaltet!\n\nViel Spaß beim Spielen :D");
                } else {
                    QMessageBox::information(this,"Thank you!","Thank you for your Purchase!\nThe exclusive content has been unlocked in the shop!\n\nHave fun playing!");
                }
            } else {
                if(transl->getLanguageCode() == 1) {
                    QMessageBox::information(this,"Info","InGame käufe wiederhergestellt.");
                } else {
                    QMessageBox::information(this,"Info","InApp Purchases restored.");
                }
            }
        }
    }
}

void FrmMain::productRegistered(QInAppProduct *product)
{
    qDebug()<<"OK"<<product->identifier();
}

void FrmMain::productUnknown(QInAppProduct::ProductType ptype, QString id)
{
    Q_UNUSED(ptype)
    qDebug()<<"UNKNOWN"<<id;
}

void FrmMain::HandleStatus(QString response)
{
    QStringList list = response.split("~");

    if(list.length() <= 1) {
        //Error handling
        return;
    }

    switch(list[0].toInt()) {
    case 0:
        if(!vContains(shop->ownedbackgrounds,7)||
                !vContains(shop->ownedPipes,11)) donator = 1;
        break;
    case 1:
        if(!vContains(shop->ownedSkins,23)||
                !vContains(shop->ownedbackgrounds,4)||
                !vContains(shop->ownedPipes,8)||
                !vContains(shop->ownedbackgrounds,7)||
                !vContains(shop->ownedPipes,11)) donator = 2;
        break;
    case 2:
        if(!vContains(shop->ownedSkins,23)||
                !vContains(shop->ownedbackgrounds,4)||
                !vContains(shop->ownedPipes,8)||
                !vContains(shop->ownedbackgrounds,7)||
                !vContains(shop->ownedPipes,11)||
                !vContains(shop->ownedbackgrounds,8)||
                !unlockedSpeed) donator = 3;
        break;
    }

    if(list[1] != lastPost) {
        lastPost = list[1];
        newpost = true;
    }

    //version check
}

void FrmMain::AuthSave(QString auth)
{
    write();
}

void FrmMain::OpenScoreboard()
{
    moveAn = 5;
}

void FrmMain::UpdateFps(FPSMode newFps)
{
    int num = (int)newFps;

    t_draw->setInterval(1000.0 / num);
    write();
}

void FrmMain::DSGVOCheck()
{
    QString name = scoreboard->name;

    if(name.length() > 1) {

        QMessageBox::information(this, "Info", transl->getText_Options_DSGVO_EMail().text);

        bool ok = false;
        QGuiApplication::inputMethod()->show();
        QString n = QInputDialog::getText(this,tr("EMail"),"EMail: ",QLineEdit::Normal,"",&ok);

        if(ok) {
            if(n.length() > 4 && n.contains("@") && n.contains(".")) {
                //EMail "valid"

                QUrlQuery qry;
                qry.addQueryItem("code", "4");
                qry.addQueryItem("name", name);
                qry.addQueryItem("email", n);

                networkManager->PostData(qry, RequestCodes::DSGVO);
            } else {
                QMessageBox::critical(this, "Error", transl->getText_Options_WrongEMail().text);
            }
        }
    } else {
        QMessageBox::information(this, "Info", transl->getText_Options_DSGVO_None().text);
    }
}

void FrmMain::DSGVODone(QString response)
{
    if(response.contains("1")) {
        QMessageBox::information(this, "Info", transl->getText_Options_DSGVO_Success().text);
    } else if(response.contains("2")) {
        QMessageBox::information(this, "Info", transl->getText_Options_DSGVO_Time().text);
    }
}

void FrmMain::checkPost()
{
    QUrlQuery qry;
    qry.addQueryItem("code", "-1");
    qry.addQueryItem("name", scoreboard->name);

    networkManager->PostData(qry, RequestCodes::GetPost);

    return;

    /*QTcpSocket *socket = new QTcpSocket();
    socket->connectToHost("flatterfogel.ddns.net",38900);
    socket->waitForConnected(500);
    if(socket->state()==QTcpSocket::ConnectedState) {

        QString data = ".-1#"+lastPost+"#"+scoreboard->name+"#"+version+"#~";

        socket->write(data.toUtf8());
        socket->waitForBytesWritten(500);
        socket->waitForReadyRead(1000);

        QString input = socket->readAll();
        QStringList list = input.split("#");
        std::vector <QString> split;

        for(int i=0;i<list.size();i++) {
            split.push_back(list.at(i));
        }

        try {
            if(split.at(0)!=lastPost) {
                lastPost = split.at(0);
                newpost = true;
            }
            switch(split.at(1).toInt()) {
                case 1:
                    if(!vContains(shop->ownedbackgrounds,7)||
                            !vContains(shop->ownedPipes,11)) donator = 1;
                break;
                case 2:
                    if(!vContains(shop->ownedSkins,23)||
                            !vContains(shop->ownedbackgrounds,4)||
                            !vContains(shop->ownedPipes,8)||
                            !vContains(shop->ownedbackgrounds,7)||
                            !vContains(shop->ownedPipes,11)) donator = 2;
                break;
                case 3:
                    if(!vContains(shop->ownedSkins,23)||
                            !vContains(shop->ownedbackgrounds,4)||
                            !vContains(shop->ownedPipes,8)||
                            !vContains(shop->ownedbackgrounds,7)||
                            !vContains(shop->ownedPipes,11)||
                            !vContains(shop->ownedbackgrounds,8)||
                            !unlockedSpeed) donator = 3;
                break;
            }
            if(split.at(2)!=version) {
                //1.3.0.b
                if(version.contains("r")) {
                    QStringList vlocal = version.split(".");
                    QStringList vserver = split.at(2).split(".");
                    if(vlocal.at(0).toInt()<vserver.at(0).toInt()) {
                        outdated = true;
                    } else if(vlocal.at(1).toInt()<vserver.at(1).toInt()){
                        outdated = true;
                    } else if(vlocal.at(2).toInt()<vserver.at(2).toInt()){
                        outdated = true;
                    }
                }
            }
            if(split.at(3)=="WIN") {
                boxCount += 25;
                QMessageBox::information(this,"Info","Du hast gewonnen! Viel spaß mit den 25 Geschenken :D");
            }
        } catch(std::exception) {
            socket->close();
            delete socket;
            return;
        }
    }
    socket->close();
    delete socket;*/
}

void FrmMain::initSound()
{
    /*QtAndroid::PermissionResult cam = QtAndroid::checkPermission("android.permission.CAMERA");
    QtAndroid::PermissionResult mic = QtAndroid::checkPermission("android.permission.RECORD_AUDIO");
    QtAndroid::PermissionResult net = QtAndroid::checkPermission("android.permission.ACCESS_NETWORK_STATE");
    QtAndroid::PermissionResult sto = QtAndroid::checkPermission("android.permission.WRITE_EXTERNAL_STORAGE");
    QStringList request;
    if(cam==QtAndroid::PermissionResult::Denied) {
        request.append("android.permission.CAMERA");
    }
    if(mic==QtAndroid::PermissionResult::Denied) {
        request.append("android.permission.RECORD_AUDIO");
    }
    if(net==QtAndroid::PermissionResult::Denied) {
        request.append("android.permission.ACCESS_NETWORK_STATE");
    }
    if(sto==QtAndroid::PermissionResult::Denied) {
        request.append("android.permission.WRITE_EXTERNAL_STORAGE");
    }
    if(request.size()) {
        QtAndroid::requestPermissionsSync(request);
    }
    cam = QtAndroid::checkPermission("android.permission.CAMERA");
    mic = QtAndroid::checkPermission("android.permission.RECORD_AUDIO");
    net = QtAndroid::checkPermission("android.permission.ACCESS_NETWORK_STATE");
    sto = QtAndroid::checkPermission("android.permission.WRITE_EXTERNAL_STORAGE");
    if(cam!=QtAndroid::PermissionResult::Granted||
            mic!=QtAndroid::PermissionResult::Granted||
            net!=QtAndroid::PermissionResult::Granted||
            sto!=QtAndroid::PermissionResult::Granted) {
        soundEnabled = false;
        return;
    }
    sound = new QMediaPlayer();
    connect(sound,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SLOT(on_mediastateChanged(QMediaPlayer::MediaStatus)));
    sound->setMedia(QUrl("qrc:/sound/pg.mp3"));*/
    //play erst nachdem fertig geladen
}

void FrmMain::error(QString errorString)
{
    QMessageBox::critical(this,"FEHLER",errorString);
}

void FrmMain::startStop(bool start)
{
    if(start) {
        QMetaObject::invokeMethod(t_draw,"start",Q_ARG(int,10));
        QMetaObject::invokeMethod(t_main,"start",Q_ARG(int,5));
        QMetaObject::invokeMethod(t_blus,"start",Q_ARG(int,5));
        QMetaObject::invokeMethod(t_obst,"start",Q_ARG(int,50));
        QMetaObject::invokeMethod(t_star,"start",Q_ARG(int,125));
        QMetaObject::invokeMethod(t_an,"start",Q_ARG(int,150));
        suspended = false;
    } else {
        QMetaObject::invokeMethod(t_draw,"stop");
        QMetaObject::invokeMethod(t_main,"stop");
        QMetaObject::invokeMethod(t_blus,"stop");
        QMetaObject::invokeMethod(t_obst,"stop");
        QMetaObject::invokeMethod(t_star,"stop");
        QMetaObject::invokeMethod(t_an,"stop");
        suspended = true;
    }
}

void FrmMain::tap(int x, int y)
{
    cBTouch += shop->tapMultiplier;
    player->setBenis(player->getBenis()+shop->tapMultiplier);
    if(!lowGraphics) {
        QPixmap bpx = blus;
        if(shop->chosenSkin!=23&&shop->chosenSkin!=25&&shop->chosenSkin!=26) {
            if(shop->chosenSkin==14) bpx = minus;
            blusse.push_back(new Blus(random(0,360),QRectF(x-20,y-20,40,40),bpx));
        } else {
            QString text;
            switch(shop->chosenSkin) {
            case 23:
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
                break;
            case 25:
                switch(random(0,5)) {
                case 0:
                case 1:
                case 2:
                    text = "do you kno da wae";
                    break;
                case 3:
                case 4:
                    text = "*cluck*";
                    break;
                }
                break;
            case 26:
                switch(random(0,3)) {
                case 0:
                case 1:
                    text = "quak";
                    break;
                case 2:
                    text = "ban";
                    break;
                }
                break;
            }
            blusse.push_back(new Blus(random(0,360),QRectF(x-20,y-20,40,40),text,random(35,46)));
        }
    }
}

void FrmMain::changeSpeed(bool faster)
{
#ifdef QT_NO_DEBUG
    if(!unlockedSpeed) return;
#endif
    if(lastbenpos) {
        lastbenpos->move(-5000);
    }
    Blus *b = new Blus(0,QRect(200,500,10,10),"Geschw.: "+QString::number(gameSpeed,'f',2)+"x");
    b->vx = 0;
    b->speedDisplay = true;
    blusse.push_back(b);
    lastbenpos = b;
    if(faster) {
        if(gameSpeed<2.25) gameSpeed+=0.25;
    } else {
        if(gameSpeed>1) gameSpeed-=0.25;
    }
}

void FrmMain::initPurchase(int packageCode)
{
    //Kauf initialisieren

    QString paket = "pack_small";

    switch(packageCode) {
    case 1:
        paket = "pack_medium";
        break;
    case 2:
        paket = "pack_large";
        break;
    }

    QInAppProduct *product = store->registeredProduct(paket);

    if(!product) {
        //Fehlerhaftes Produkt
        return;
    }

    pInit = true;
    product->purchase();
}

double FrmMain::getDistance(QPointF p1, QPointF p2)
{
    return qSqrt(qPow(qFabs(p2.x()-(double)p1.x()),2)+qPow(qFabs(p2.y()-(double)p1.y()),2));
}

void FrmMain::on_tTail()
{
    if(boost||pause||suspended) return;
    switch(shop->chosenTail) {
    case 2: //blus
    case 3: //minus
    case 6: //coin
        {
        Blus *b = new Blus(0,QRect(player->getRect().x()-50,player->getRect().y()+player->getRect().height()/2-25,50,50),tails[shop->chosenTail-1],40,40,0,0);
        b->tail = true;
        blusse.push_back(b);
        break;
        }
    case 4: //nyan
    case 5: //de flag
    case 7: //re flag
    case 8: //au flag
    case 9: //orange
    case 10: //grün
    case 11: //blau
    case 12: //fliesentisch
        {
        Blus *b = new Blus(0,QRect(player->getRect().x()-10,player->getRect().y()+player->getRect().height()/2-40,5,80),tails[shop->chosenTail-1],5,60,0,0);
        b->tail = true;
        blusse.push_back(b);
        break;
        }
    }
}

void FrmMain::on_tRgb()
{
    if(suspended) return;
    if(active==1||active==-1||shop->getActive()) {
        switch(rgb_mode) {
        case 0: //rot- grün+
            rgb_red--;
            rgb_green++;
            if(!rgb_red) rgb_mode = 1;
            break;
        case 1: //grün- blau+
            rgb_green--;
            rgb_blue++;
            if(!rgb_green) rgb_mode = 2;
            break;
        case 2: //blau- rot+
            rgb_blue--;
            rgb_red++;
            if(!rgb_blue) rgb_mode = 0;
            break;
        }
//rgb-säulen
    }
}

void FrmMain::on_mediastateChanged(QMediaPlayer::MediaStatus status)
{
    if(status == QMediaPlayer::MediaStatus::LoadedMedia&&soundEnabled) {
        sound->setVolume(25);
        QMetaObject::invokeMethod(sound,"play");
    }
}

void FrmMain::on_appStateChanged(Qt::ApplicationState state)
{
    if(state==Qt::ApplicationActive) {
        if(soundEnabled) {
            if(sound->state()==QMediaPlayer::PausedState) {
                QMetaObject::invokeMethod(sound,"play");
            }
        }
        if(!suspended) return;
        QMetaObject::invokeMethod(t_draw,"start",Q_ARG(int,10));
        QMetaObject::invokeMethod(t_main,"start",Q_ARG(int,5));
        QMetaObject::invokeMethod(t_blus,"start",Q_ARG(int,5));
        QMetaObject::invokeMethod(t_obst,"start",Q_ARG(int,50));
        QMetaObject::invokeMethod(t_star,"start",Q_ARG(int,125));
        QMetaObject::invokeMethod(t_an,"start",Q_ARG(int,150));
        suspended = false;
    } else if(state==Qt::ApplicationInactive||
              state==Qt::ApplicationSuspended) {
        QMetaObject::invokeMethod(t_draw,"stop");
        QMetaObject::invokeMethod(t_main,"stop");
        QMetaObject::invokeMethod(t_blus,"stop");
        QMetaObject::invokeMethod(t_obst,"stop");
        QMetaObject::invokeMethod(t_star,"stop");
        QMetaObject::invokeMethod(t_an,"stop");
        if(!closing) write(false,score);
        suspended = true;
        if(active==1&&!pause) {
            pause = true;
        }
        if(soundEnabled) {
            if(sound->state()==QMediaPlayer::PlayingState) sound->pause();
        }
    }
//active
    //inactive
}

void FrmMain::on_test()
{
    qDebug()<<"finished";
}

void FrmMain::on_settingsBack()
{
    moveAn = 8;
}

void FrmMain::on_settingsPlay()
{
    if(soundEnabled) {
        sound->setVolume(25);
        QMetaObject::invokeMethod(sound,"play");
    } else {
        QMetaObject::invokeMethod(sound,"pause");
    }
}

void FrmMain::on_tbackup()
{
    if(suspended||pause||active!=1) return;
    qDebug()<<"save";
    write(false,score);
}

void FrmMain::on_treload()
{
    if(!schmuserDefend||active!=1||pause||!enemys.size()) return;
    double distance = schmuserRange;
    int minY = schmuserRange;
    int num = -1;
    for(uint i=0;i<enemys.size();i++) {
        if(!enemys[i]->dead&&enemys[i]->prehp>=0) {
            double tmpDistance = getDistance(player->getRect().center(),enemys[i]->rect.center());
            int tmpY = enemys[i]->rect.center().y();
            if(tmpDistance<distance&&tmpY>minY) {
                minY = tmpY;
                num = i;
            }
        }
    }
    if(num<0) return;
    //if(enemys[num]->prehp>=0) {
        double speed = 3;
        double enemyspeed = 1;
        int dmg = schmuserDmg;
        enemys[num]->prehp -= dmg;
        QRect er = enemys[num]->rect;
        QRectF pr = QRectF(player->getRect().x()+20,player->getRect().y()-25,20,20);
        double theta = atan2((er.y()+er.height()/2)-(player->getRect().y()-25),(er.x()+er.width()/2)-(player->getRect().x()+20));
        double angle = qRadiansToDegrees(theta);
        if(angle<0) angle+=360;
        double vy = qSin(qDegreesToRadians((double)angle))*2;
        //winkel zur aktuellen position berechnen
        double result = std::fabs((double)(er.y()+er.height()/2)-pr.y());
        result /= std::fabs(vy*speed); //anzahl der schritte von projektil zu ziel
        er.moveTo(er.x(),er.y()+(enemyspeed*result));
        aimingAt = er;
        theta = atan2((er.y()+er.height()/2)-(player->getRect().y()-25),(er.x()+er.width()/2)-(player->getRect().x()+20));
        angle = qRadiansToDegrees(theta);
        if(angle<0) angle+=360;
        //winkel zu zukünftiger position berechnen
        projectiles.push_back(new Projectile(QRectF(player->getRect().x()+20,player->getRect().y()-25,20,20),angle,speed,dmg));
    //}
}

void FrmMain::on_tregen()
{
    if(active!=1||!schmuserDefend||pause) return;
    if(schmuserBaseHP<schmuserBaseMaxHP) {
        schmuserBaseHP+=schmuserBaseMaxHP*0.001;
        if(schmuserBaseHP>schmuserBaseMaxHP) schmuserBaseHP = schmuserBaseMaxHP;
    }
}

void FrmMain::on_tdraw()
{
    //qDebug()<<QGuiApplication::applicationState();
    if(suspended) return;
    try {
        update();
    } catch(std::exception& e) {
        startStop(false);
        error("Bitte an Dev weiterleiten:\n"+QString(e.what()));
        QApplication::quit();
    }
}

void FrmMain::on_tblus()
{
    if(suspended||pause) return;
    QRectF field(0,0,1080,1920);
    for(uint i=0;i<projectiles.size();i++) {
        if(getDistance(player->getRect().center(),projectiles[i]->r.center())<schmuserRange&&!projectiles[i]->del) {
            projectiles[i]->move();
        } else {
            delete projectiles[i];
            projectiles.erase(projectiles.begin()+i);
        }
    }
    for(uint i=0;i<blusse.size();i++) {
        try {
            if(boost) {
                blusse[i]->move(-boost);
            } else {
                if(!blusse[i]->tail||(blusse[i]->tail&&active==1)) {
                    double s = 0;
                    if(active==1&&!schmuserDefend) s = -gameSpeed;
                    blusse[i]->move(s);
                }
                //if(blusse[i]->item) qDebug()<<blusse[i]->getRect();
            }
        } catch(std::out_of_range) {
            startStop(false);
            error("Bitte an Dev weiterleiten:\n"
                  "OOR - BLUS_TBLUS - MAX:"+QString::number(blusse.size())+" REQ:"+QString::number(i));
            QApplication::quit();
        } catch(std::exception) {
            startStop(false);
            error("Bitte an Dev weiterleiten:\n"
                  "NPE - BLUS_TBLUS - MAX:"+QString::number(blusse.size())+" REQ:"+QString::number(i));
            QApplication::quit();
        }
    }
    for(uint i=0;i<blusse.size();i++) {
        if((!blusse[i]->getRect().intersects(QRectF(0,0,1080,1920))&&!blusse[i]->isText())||blusse[i]->getOpacity()<=0) {
            if((!blusse[i]->snow&&!blusse[i]->item)||(blusse[i]->snow&&blusse[i]->getOpacity()<=0)||((blusse[i]->snow||blusse[i]->item)&&blusse[i]->getRect().x()<=0)||
                    (blusse[i]->item&&blusse[i]->getOpacity()<=0)) {
                delete blusse[i];
                blusse.erase(blusse.begin()+i);
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
    if(pause||suspended) return;
    //moveAn = 3;
    if(flashOpacity) {
        flashOpacity -= 0.0125;
    }
    if(textFade&&active==1) {
        textFade -= 0.005;
    }
    if(space) {
        if(planetX>-160) {
            if(active==1) {
                planetX -= 0.5;
            } else {
                planetX -= 0.25;
            }
        } else {
            planetX = 1080;
            planetY = random(200,1301);
            int np=chosenPlanet;
            do {
                np = random(0,5);
            } while(np==chosenPlanet);
            chosenPlanet = np;
        }
    }
    try {
        if(backgrounds.at(shop->chosenBackground-1)->cloud&&!lowGraphics) {
            cloud1X-=0.15;
            cloud2X-=0.15;
            if(cloud1X<=-1079) {
                cloud1X = 1079;
            } else if(cloud2X<=-1079) {
                cloud2X = 1079;
            }
        }
    } catch(std::out_of_range) {
        startStop(false);
        error("Bitte an Dev weiterleiten:\n"
              "OOR - BG_M - MAX:"+QString::number(backgrounds.size())+" REQ:"+QString::number(shop->chosenBackground-1));
        QApplication::quit();
    } catch(std::exception) {
        startStop(false);
        error("Bitte an Dev weiterleiten:\n"
              "OOR - BG_M_NP - MAX:"+QString::number(backgrounds.size())+" REQ:"+QString::number(shop->chosenBackground-1));
        QApplication::quit();
    }
    if(active<1) return;
    if(schmuserDefend) doSchmuserDefend();
    if(active==1) localPlayTime+=0.005;
    if(active==1&&!boxDeath&&!schmuserDefend) {
        if(revive==1) {
            reviveTime-=5;
            if(reviveTime<=0) {
                revive = 0;
                reviveTime = 0;
            }
        }
        for(uint i=0;i<obstacles.size();i++) {
            try {
                if(boost) {
                    obstacles.at(i)->moveBy(-boost,0);
                    moveGround(-boost);
                } else {
                    double speed=0.5;
                    if(hardcore) {
                        speed = 0.70;
                    }
                    obstacles.at(i)->moveBy(-gameSpeed,0,speed);
                    moveGround(-1);
                }
            } catch(std::out_of_range) {
                startStop(false);
                error("Bitte an Dev weiterleiten:\n"
                      "OOR - OB_M - MAX:"+QString::number(obstacles.size())+" REQ:"+QString::number(i));
                QApplication::quit();
            } catch(std::exception) {
                startStop(false);
                error("Bitte an Dev weiterleiten:\n"
                      "NPE - OB_M_NP - MAX:"+QString::number(obstacles.size())+" REQ:"+QString::number(i));
                QApplication::quit();
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
        if(((score>highscore&&!cave&&!hardcore&&!space&&!underwater)||
                (score>highscore_H&&!cave&&hardcore)||
                (score>highscore_C&&cave&&!hardcore)||
                (score>highscore_S&&space)||
                (score>highscore_UM&&underwater))&&
                !newHS&&highscore) {
            newHS = 1;
            Blus *b = new Blus(90,QRectF(4,180,1,1),transl->getText_NHS().text);
            b->color = QColor(255,0,130);
            blusse.push_back(b);
            QMetaObject::invokeMethod(t_newHS,"start",Q_ARG(int,250));
        }
        if(cave&&obstacles.size()) {
            QPolygonF poly;
            for(uint i=0;i<obstacles.size();i++) {
                QPointF oben(obstacles[i]->getBottom().x(),obstacles[i]->getBottom().y());
                poly.append(oben);
            }
            for(int i=obstacles.size()-1;i>0;i--) {
                QPointF unten(obstacles[i]->getBottom().x(),obstacles[i]->getBottom().y()+obstacles[i]->getBottom().height());
                poly.append(unten);
            }
            QPolygonF polyTop;
            for(uint i=0;i<obstacles.size();i++) {
                QPointF oben(obstacles[i]->getTop().x(),obstacles[i]->getTop().y());
                polyTop.append(oben);
            }
            for(uint i=obstacles.size()-1;i>0;i--) {
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
        for(uint i=0;i<blusse.size();i++) {
            try {
                if(blusse.at(i)->item) {
                    if(player->getCollRect().intersects(blusse[i]->getRect())) {
                        if(blusse[i]->item==1) {
                            score++;
                            blusse[i]->move(-5000);
                            if((score%200==0&&score!=0)||(score%30==0&&hardcore)) {
                                on_shopBuy(1,false,true);
                                player->coins++;
                            } else {
                                player->setBenis(player->getBenis()+(score*shop->multiplier));
                                int b = score*shop->multiplier;
                                cBPipe += b;
                                if(hardcore) b*=1.5;
                                player->setBenis(player->getBenis()+b);
                                blusse.push_back(new Blus(90,QRectF(4,180,1,1),"+"+QString::number(b)));
                                if(!lowGraphics) {
                                    QPixmap bpx = blus;
                                    if(shop->chosenSkin==14) bpx = minus;
                                    for(int a=0;a<360;a+=12) {
                                        blusse.push_back(new Blus(a,QRectF(player->getRect().center().x()-20,player->getRect().center().y()-20,40,40),bpx));
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
            } catch(std::out_of_range) {
                startStop(false);
                error("Bitte an Dev weiterleiten:\n"
                      "OOR - BLUS_M - MAX:"+QString::number(blusse.size())+" REQ:"+QString::number(i));
                QApplication::quit();
            } catch(std::exception) {
                startStop(false);
                error("Bitte an Dev weiterleiten:\n"
                      "NPE - BLUS_M_NP - MAX:"+QString::number(blusse.size())+" REQ:"+QString::number(i));
                QApplication::quit();
            }
        }
    }
    bool dead = false;
    if(player->getRect().y()<1600&&active>0&&!schmuserDefend) {
        double velD = player->getVelD();
        if(!space&&!underwater) {
            if(velD<8) velD += 0.075;
            player->setVelD(velD);
        } else if(underwater) {
            if(velD<8) velD += 0.035;
            player->setVelD(velD);
        }
        QRectF r = player->getCollRect();
        if(!cave) {
            if(r.y()+velD>1600) {
                velD = 1600-r.y();
            }
            bool ok=true;
            if(!boost) {
                QRectF newr = player->getCollRect();
                newr.moveTo(newr.x(),newr.y()+velD);
                for(uint i=0;i<obstacles.size();i++) {
                    if(newr.intersects(obstacles[i]->getBottom())||
                            newr.intersects(obstacles[i]->getTop())) {
                        ok = false;
                        dead = true;
                        break;
                    }
                }
            }
            if(ok) {
                if(player->getRect().y()>0||velD>0) {
                    player->setPos(r.x(),r.y()+velD);
                } else if(space) {
                    player->setVelD(velD*-1);
                }
            }
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
    if((player->getRect().y()>=1600&&!schmuserDefend)||dead) {
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
            blusse.push_back(new Blus(270,QRect(260,850,1,1),"Revive!",88));
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
        if(!cave&&!hardcore&&score>highscore&&!space) {
            highscore = score;
        } else if(hardcore&&!cave&&score>highscore_H&&!space) {
            highscore_H = score;
        } else if(!hardcore&&cave&&score>highscore_C&&!space) {
            highscore_C = score;
        } else if(!hardcore&&space&&score>highscore_S) {
            highscore_S = score;
        } else if(!hardcore&&underwater&&score>highscore_UM) {
            highscore_UM = score;
        }
    }
    if(!schmuserDefend) {
        for(uint i=0;i<obstacles.size();i++) {
            if((obstacles[i]->getTop().x()<-250&&!cave)||(obstacles[i]->getTop().x()<-700&&cave)||obstacles[i]->del) {
                delete obstacles[i];
                obstacles.erase(obstacles.begin()+i);
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
                if(score%200==0||(score%30==0&&hardcore)) {
                    on_shopBuy(1,false,true);
                    player->coins++;
                } else {
                    if(!boost) {
                        player->setBenis(player->getBenis()+(score*shop->multiplier));
                        unsigned long b = score*shop->multiplier;
                        if(hardcore) b*=1.5;
                        cBPipe += b;
                        blusse.push_back(new Blus(90,QRectF(4,180,1,1),"+"+QString::number(b)));
                        if(!lowGraphics) {
                            QPixmap bpx = blus;
                            if(shop->chosenSkin==14) bpx = minus;
                            for(int a=0;a<360;a+=12) {
                                blusse.push_back(new Blus(a,QRectF(player->getRect().center().x()-20,player->getRect().center().y()-20,40,40),bpx));
                            }
                        }
                    }
                }
            }
        }
    }
}

void FrmMain::on_tObst()
{
    if(pause||suspended) return;
    if(QGuiApplication::applicationState()==Qt::ApplicationSuspended) return;
    if(schmuserDefend&&active==1) {
        if(enemys.size()<schmuserWaveSize) {
            do {
                int x = random(0,980);
                int y = random(-600,-100);
                Enemy *e = new Enemy(QRect(x,y,100,100),0,schmuserHP);
                enemys.push_back(e);
            } while(enemys.size()<schmuserWaveSize);
        }
        return;
    }
    if(shop->chosenBackground==1&&!cave&&!lowGraphics) { //Schnee
        Blus *b = new Blus(random(55,125),QRectF(random(100,1500),-10,10,10),1,0.15,false);
        b->color = QColor(210,210,210);
        b->snow = true;
        blusse.push_back(b);//new Blus(random(55,125),QRectF(random(100,1500),-25,25,25),snowPx,25,25,0.15,1,true));
    } else if(shop->chosenBackground==5&&!lowGraphics) {//shekel
        for(int i=0;i<3;i++) {
            int y = random(600,680);
            int x = random(835,985);
            double os = 0.65;
            if(x>872) {
                os = 0.75;
            } else if(x>909) {
                os = 0.95;
            } else if(x>947) {
                os = 1.30;
            }
            Blus *b = new Blus(98,QRectF(x,y,10,10),1,os,false);
            QColor color(255,201,14);
            switch(random(0,3)) {
            case 1:
                color = QColor(223,173,0);
                break;
            case 2:
                color = QColor(255,221,102);
            }
            b->color = color;
            b->bg = true;
            b->snow = 2;
            blusse.push_back(b);
        }
    }
    if(newHS==1&&active==1&&!lowGraphics) {
        for(int a=0;a<360;a+=12) { //newhs
            blusse.push_back(new Blus(a,QRectF(player->getRect().center().x()-20,player->getRect().center().y()-20,40,40),blus,40,40,1.5));
        }
    }
    if(active!=1||schmuser||boxDeath) return;
    if((obstacles.size()<=3&&!cave)||(obstacles.size()<=6&&cave&&!boost)||(obstacles.size()<=7&&cave&&boost)||
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
                    x = obstacles.at(obstacles.size()-1)->getBottom().x()+diff2;
                }
                QPixmap p;
                if(!stationaryObstacles&&!hardcore) {
                    p = pipes.at(shop->chosenPipe-1);
                } else {
                    if(shop->chosenPipe==1) {
                        p = QPixmap(":/images/pipe2.png");
                    } else {
                        p = pipes.at(shop->chosenPipe-1);
                    }
                }
                if(cave&&obstacles.size()) {
                    int diff3 = 125; //max unterschied median
                    if(!random(0,10)) {
                        diff3*=2;
                    }
                    if(obstacles.size()>1) {
                        min = obstacles.at(obstacles.size()-1)->getTop().height()-diff3;
                        max = obstacles.at(obstacles.size()-1)->getTop().height()+diff3;
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
                        if((score+2)%200==0) {
                            px = coinPx;
                            w=16;
                            h=16;
                        }
                        caveSpawnCount = 0;
                        Blus *b = new Blus(0,QRectF(top.x(),(bottom.y()-diff/2)-30,60,60),px,w,h,0,0);
                        b->item = 1;
                        blusse.push_back(b);
                        //qDebug()<<"caveSpawnCount";
                    } else if(!random(0,10)&&!boost) {
                        w = 46;
                        h = 40;
                        Blus *b = new Blus(0,QRectF(top.x(),(bottom.y()-diff/2)-30,70,60),boxPx,w,h,0,0);
                        b->item = 2;
                        blusse.push_back(b);
                    }
                } else if(!random(0,9)&&!boost) {
                    QRect target;
                    int x = random(top.x()+top.width()+100,top.x()+top.width()+350);
                    int y = random(400,1200);
                    target = QRect(x,y,80,69);
                    Blus *b = new Blus(0,QRectF(target),boxPx,46,40,0,0);
                    b->item = 2;
                    blusse.push_back(b);
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
                obstacles.push_back(o);
            }
        } else { //stationary
            stationaryObstacles--;
            QRect top,bottom;
            bool ok=false;
            do {
                top = QRect(random(1500,3580),random(0,1300),200,200);
                ok = false;
                for(uint i=0;i<obstacles.size();i++) {
                    if(obstacles[i]->getTop().intersects(top)||
                            getDistance(obstacles[i]->getTop().center(),top.center())<500) ok = true;
                }
            } while(ok);
            Obstacle *o = new Obstacle(top,bottom,1);
            o->hasBox = false;
            obstacles.push_back(o);
        }
    }
}

void FrmMain::on_tEvent()
{
    if(suspended) return;
    if((cave||space||underwater)&&hardcore) {
        hardcore = false;
    }
    /*if(soundEffects.size()) {
        for(int i=0;i<soundEffects.size();i++) {
            if(soundEffects[i]->status()==QSoundEffect::Ready) {
                delete soundEffects[i];
                soundEffects.erase(soundEffects.begin()+i);
            }
        }
    }*/
    if(loading) {
        /*if(soundEnabled&&sound==NULL) {
            initSound();
        } else {
            sound = NULL;
        }*/
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
            switch(donator) {
            case 3:
                //packet large
                unlockedSpeed = true;
                if(!vContains(shop->ownedbackgrounds,8))  {
                    shop->ownedbackgrounds.push_back(8); //unterwasser
                    boxCount += 25;
                }
            case 2:
                //packet medium
                if(!vContains(shop->ownedbackgrounds,4))  {
                    shop->ownedbackgrounds.push_back(4); //shekel bg
                    if(donator==2) boxCount += 10;
                }
                if(!vContains(shop->ownedPipes,8)) shop->ownedPipes.push_back(8); //shekel sskin
                if(!vContains(shop->ownedSkins,23)) shop->ownedSkins.push_back(23); //btc skin
            case 1:
                //packet small
                if(!vContains(shop->ownedbackgrounds,7)) {
                    shop->ownedbackgrounds.push_back(7); //skyline
                    if(donator==1) boxCount += 5;
                }
                if(!vContains(shop->ownedPipes,11)) shop->ownedPipes.push_back(11); //skyline sskin
                break;
            }
            QMessageBox::information(this,"Danke!","Vielen Dank für deine Spende!\nDie exklusiven Inhalte wurden im Shop freigeschaltet!\n\nViel Spaß beim Spielen :D");
        }
        loading = false;
    }
    if(highscore>=10||highscore_H>=5||highscore_C>=10||highscore_S>=7||player->coins) {
        if((ad!=1&&!donator&&!ad_active&&!shop->getActive()&&active==0&&!scoreboard->active)||ad==-98) {
            if(!vContains(shop->ownedbackgrounds,4)||!vContains(shop->ownedPipes,8)||
                    !vContains(shop->ownedSkins,23)||!vContains(shop->ownedbackgrounds,7)||
                    !vContains(shop->ownedPipes,11)||ad==-98||!unlockedSpeed) {
                ad = 1;
                ad_active = true;
            }
        }
    }
    if(active!=1||cave||hardcore) return;
    if((((score+2)%30==0)&&(score!=0)&&(!boost))||schmuser) {
        for(uint i=0;i<obstacles.size();i++) {
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
    blusse.push_back(b);
    if(coin) {
        b = new Blus(angle,QRectF(x,y,w,h),coinPx,16,16);
        if(mid) b->gift = true;
        blusse.push_back(b);
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
            blusse.push_back(b);
        }
    } else {
        boost = 0;
        fastboost = false;
        QMetaObject::invokeMethod(t_boost,"stop");
    }
}

void FrmMain::on_tAn()
{
    if(suspended) return;
    /*---Raketen für Silvester---
    if(!lowGraphics&&!pause) {
        for(int i=0;i<2;i++) {
            int c = random(0,5);
            QColor color(Qt::red);
            switch(c) {
            case 1:
                color = QColor(Qt::green);
                break;
            case 2:
                color = QColor(Qt::blue);
                break;
            case 3:
                color = QColor(Qt::yellow);
                break;
            case 4:
                color = QColor(Qt::lightGray);
                break;
            case 5:
                color = QColor(Qt::magenta);
                break;
            case 6:
                color = QColor(Qt::cyan);
                break;
            }
            QRectF r = QRectF(random(100,950),random(900,1200),5,5);
            double v = random(10,100)/100.0;
            double o = random(100,200)/100.0;
            for(int a=0;a<360;a+=12) {
                Blus *b = new Blus(a,r,v,o);
                b->color = color;
                b->bg = true;
                blusse.push_back(b);
            }
        }
    }*/
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
    if(pause||space) return;
    if(player->tdir) {
        if(player->tilt-player->tstep>=0) {
            player->tilt-=player->tstep;
        }
    } else {
        if(player->tilt<135) {
            if(!underwater) {
                player->tilt+=1.5;
            } else {
                player->tilt+=1;
            }
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
    if(obstacles.size()&&backgrounds[shop->chosenBackground-1]->train) {
        if(active==1&&random(0,2)&&!lowGraphics) {
            bool ok=false;
            int num=0;
            for(uint i=0;i<obstacles.size();i++) {
                if(obstacles[i]->getTop().x()>100&&obstacles[i]->getTop().x()<900) {
                    num++;
                }
            }
            if(!num) ok = true;
            while(!ok) {
                num = random(0,obstacles.size());
                if(obstacles.at(num)->getTop().x()>100&&obstacles.at(num)->getTop().x()<900) {
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
                Blus *spark = new Blus(random(0,180),QRectF(obstacles.at(num)->train.x()+x,1780,5,5),0.5,7.5);
                spark->color = QColor(Qt::yellow);
                spark->spark = true;
                blusse.push_back(spark);
            }
        }
    }
}

void FrmMain::on_tstar()
{
    if(lowGraphics||suspended) return;
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

void FrmMain::on_sbWrongName(int type)
{
    if(type == -1 || type == 0) {
        Text t = transl->getText_Scoreboard_WrongName();
        QMessageBox::critical(this,"Error",t.text);
    } else if(type == 1) {
        Text t = transl->getText_Scoreboard_NameChanged();
        QMessageBox::information(this,"Info",t.text);
    }
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
        //zurück
        moveAn = 6;
    } else if(!type) {
        //scoreboard öffnen
        moveAn = 5;
    }
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
        case 7: //main-settings
            if(settings->settingsX<0) {
                settings->settingsX += speed;
                mainX += speed;
            } else {
                moveAn = 0;
                settings->active = true;
            }
            break;
        case 8: //settings-main
            if(settings->settingsX>-1080) {
                settings->settingsX -= speed;
                mainX -= speed;
            } else {
                moveAn = 0;
                settings->active = false;
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

bool FrmMain::vContains(std::vector<int> v, int value)
{
    bool ok=false;
    if (std::find(v.begin(), v.end(),value)!=v.end()) ok=true;
    return ok;
}

void FrmMain::loadData()
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#ifdef Q_OS_WIN
    if(!QDir(path).exists()) {
        QDir().mkdir(path);
    }
#endif
    QString pathR = path;
    QString pathE = path;
    QString dsgvoPath = path;

    QFile dsgvoFile;
    dsgvoFile.setFileName(path + "/dsgvo.dat");

    if(dsgvoFile.exists()) {
        dsgvo = true;
    } else {
        dsgvo = false;
    }

    QFile restore;
    restore.setFileName(path+"/restore.dat");
    pathE.append("/settings_e.dat");
    fileE.setFileName(pathE);
    pathR.append("/settings.dat");
    file.setFileName(pathR);
    if(file.exists()) {
        firstlaunch = false;

#ifdef QT_DEBUG
      //firstlaunch = true;
#endif

        QTextStream in;
        QString data;
        if(fileE.exists()) {
            fileE.open(QIODevice::ReadOnly);
            in.setDevice(&fileE);
            data = lucaAlgR(lucaAlgR(in.readLine()));
            eLoad = true;
        } else {
            fileE.open(QIODevice::ReadWrite);
            fileE.close();
            file.open(QIODevice::ReadOnly);
            in.setDevice(&file);
            data = in.readLine();
            eLoad = false;
        }
        //qDebug()<<lucaAlgR(lucaAlg(in.readLine()));
        QStringList list = data.split("#");
        QString a=QString::number(list.size())+"///";
        for(int i=0;i<list.size();i++) a.append(list.at(i)+"/");

        //Kp was das macht (lol)
        /*if(version.contains("bs")) {
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
        }*/
        if(list.size()>1) {
            if(list.at(0).contains("~")) {
                QStringList scores = QString(list.at(0)).split("~");
                highscore = scores.at(0).toInt();
                highscore_H = scores.at(1).toInt();
                highscore_C = scores.at(2).toInt();
                if(scores.size()>3) {
                    highscore_S = scores.at(3).toInt();
                }
                if(scores.size()>4) {
                    highscore_UM = scores.at(4).toInt();
                }
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
                } else if(list.at(11).mid(0,6)!=version.mid(0,6)) {
                    changelog = true;
                }
                if(list.size()>13) {
                    player->coins = list.at(12).toInt();
#ifdef QT_DEBUG
    player->coins=999;
#endif
                }
                if(list.size()>14) {
                    QStringList skinList = QString(list.at(13)).split("~");
                    for(int i=0;i<skinList.size()-1;i++) {
                        shop->ownedSkins.push_back(skinList.at(i).toInt());
                    }
                }
                if(list.size()>15) {
                    event = 0;//list.at(14).toInt();
                }
                if(list.size()>16) {
                    QStringList bgList = QString(list.at(15)).split("~");
                    for(int i=0;i<bgList.size()-1;i++) {
                        shop->ownedbackgrounds.push_back(bgList.at(i).toInt());
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
                    switch(shop->chosenBackground) {
                    case 4:
                        cave = true;
                        break;
                    case 6:
                        space = true;
                        break;
                    case 7:
                        flip = true;
                        break;
                    case 9:
                    case 10:
                        underwater = true;
                        break;
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
                        shop->ownedPipes.push_back(pipeList.at(i).toInt());
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
                    settings->lowGraphics = lowGraphics;
                }
                if(list.size()>25) {
                    QStringList tailList = QString(list.at(24)).split("~");
                    for(int i=0;i<tailList.size()-1;i++) {
                        shop->ownedTails.push_back(tailList.at(i).toInt());
                    }
                }
                if(list.size()>26) {
                    shop->chosenTail = list.at(25).toInt();
                }
                if(list.size()>27) {
                    if(list.at(26).toInt()) {
                        soundEnabled = true;
                    } else {
                        soundEnabled = false;
                    }
                    settings->music = soundEnabled;
                }
                if(list.size()>28) {
                    ad = list.at(27).toInt();
                    if(ad==1) ad = 0;
                }
                if(list.size()>29) {
                    if(list.at(28).toInt()) {
                        soundEffectsEnabled = true;
                    } else {
                        soundEffectsEnabled = false;
                    }
                    settings->soundEffects = soundEffectsEnabled;
                }
                if(list.size()>30) {
                    if(list.at(29).toInt()) {
                        unlockedSpeed = true;
                    }
                }
                if(restore.exists()) {
                    QTextStream rin;
                    restore.open(QIODevice::ReadOnly);
                    rin.setDevice(&restore);
                    QString data = rin.readLine();
                    restore.close();
                    moveAn = 3;
                    boostDisabled = true;
                    score = data.toInt();
                    restore.remove();
                }
                if(list.size()>33) {
                    if(list.at(32).toInt()) {
                        schmuserEnemy = true;
                    } else {
                        schmuserEnemy = false;
                    }
                }
                if(list.size() > 34) {
                    //user auth
                    networkManager->SetAuth(list.at(33), false);
                }
                if(list.size() > 35) {
                    FPSMode newFPS = (FPSMode)list.at(34).toInt();
                    settings->changeFPS(newFPS);
                }
                /*if(list.at(8)=="restore2002"&&shop->multiplier<200) {
                    scoreboard->name = "Dolllaaar";
                    shop->multiplier = 1397;
                    shop->tapMultiplier = 60;
                    highscore = 3172;
                    highscore_C = 35;
                    highscore_H = 141;
                    highscore_S = 2;
                    highscore_UM = 3172;
                    boxCount = 25;
                    player->coins = 50;
                    player->setBenis(6999999999);
                }*/
            }

        }
        file.close();
        fileE.close();
        if(!eLoad) {
            eLoad = true;
            write();
        }
    } else {
        file.open(QIODevice::ReadWrite);
        fileE.open(QIODevice::ReadWrite);
        eLoad = true;
        file.close();
        fileE.close();
    }
}

void FrmMain::write(bool normal, int bscore)
{
    qDebug()<<normal;
    QString exit;
    if(!normal && !schmuserDefend && active==-1 && active==1) {
        exit.append("NOTOK");
        QFile restore;
        QString path = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
        restore.setFileName(path+"/restore.dat");
        restore.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
        QTextStream rout(&restore);
        rout << QString::number(bscore);
        restore.close();
        return;
    } else {
        exit.append("OK");
        file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
        fileE.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
        QTextStream out(&file);
        QTextStream outE(&fileE);
        QString data = QString::number(highscore) + "~" + QString::number(highscore_H) + "~"
            + QString::number(highscore_C) + "~"+ QString::number(highscore_S) + "~" + QString::number(highscore_UM) + "~#"
            + QString::number(player->getBenis()) + "#"
            + QString::number(shop->item1Count) + "#" + QString::number(shop->multiplier) + "#"
            + QString::number(shop->tapMultiplier) + "#" + QString::number(shop->item2Count) + "#"
            + transl->locale.bcp47Name() + "#" + QString::number(shop->item3Count) + "#"
            + scoreboard->name + "#" + QString::number(shop->item4Count) + "#"
            + QString::number(boxCount) + "#" + version + "#" + QString::number(player->coins) + "#"
            + shop->skinsToString() + "#" + QString::number(event) + "#" + shop->bgsToString() + "#"
            + QString::number(shop->chosenSkin) + "#" + QString::number(shop->chosenBackground) + "#"
            + QString::number(referrals) + "~" + QString::number(invited) + "#"
            + QString::number(playTime,'f',3) + "#" + shop->pipesToString() + "#"
            + QString::number(shop->chosenPipe) + "#" + lastPost + "#" + QString::number(lowGraphics) + "#"
            + shop->tailsToString() + "#" + QString::number(shop->chosenTail) + "#"
            + QString::number(soundEnabled) + "#" + QString::number(ad) + "#" + QString::number(soundEffectsEnabled) +"#"
            + QString::number(unlockedSpeed) + "#" + exit + "#" + QString::number(bscore) + "#" + QString::number(schmuserEnemy) + "#"
            + networkManager->GetAuth() + "#" + QString::number((int)settings->fps) + "#";

        if(eLoad) {
            outE << lucaAlg(lucaAlg(data));
            out << "Immer han du die bech :(";
        } else {
            out << data;
        }
        fileE.close();
        file.close();
    }
}

void FrmMain::reset(int type)
{
    //qsrand(QTime::currentTime().)
    for(uint i=0;i<obstacles.size();i++) {
        delete obstacles[i];
    }
    for(uint i=0;i<blusse.size();i++) {
        if(!blusse[i]->snow) {
            blusse[i]->move(-5000);
        }
    }
    write();
    //blusse.resize(0);
    obstacles.resize(0);
    if(!type) {
        boostused = false;
        go = 1;
        score = 0;
        gameSpeed = 1;
        textFade = 1;
        cBox = 0;
        cBTouch = 0;
        cBPipe = 0;
    } else {
        go = 2;
    }
    for(uint i=0;i<enemys.size();i++) {
        delete enemys[i];
    }
    for(uint i=0;i<projectiles.size();i++) {
        projectiles[i]->del = true;
    }
    schmuserCost[0] = 10;
    schmuserCost[1] = 5;
    schmuserCost[2] = 20;
    schmuserCost[3] = 10;
    enemys.resize(0);
    schmuserBaseHP = 1000;
    schmuserBaseMaxHP = 1000;
    schmuserkills = 0;
    schmuserWave = 1;
    schmuserHP = 100;
    schmuserWaveSize = 5;
    schmuserKillsneeded = 20;
    schmuserRange = 600;
    schmuserCredits = 0;
    schmuserReload = 100;
    schmuserDmg = 10;
    player->fin = false;
    QMetaObject::invokeMethod(t_boost,"stop");
    //QMetaObject::invokeMethod(t_an,"stop");
    QMetaObject::invokeMethod(t_tilt,"stop");
    QMetaObject::invokeMethod(t_tail,"stop");
    QMetaObject::invokeMethod(t_reload,"start",Q_ARG(int,100));
    enemylife = 10;
    caveSpawnCount = 0;
    medal = 0;
    boostDisabled = false;
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
    if(!schmuserDefend) {
        player->setPos(1080/2-250,1920/2-40);
    }
    player->setVelD(0);
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
            blusse.push_back(b);
        } else if(num<99) { //powerup
            int x = 500;
            int y = 750;
            int w = 150;
            int h = 150;
            int pw = 100;
            int ph = 100;
            Blus *b = new Blus(angle,QRectF(x-75,y+100,1,1),"+ ");
            b->gift = true;
            blusse.push_back(b);
            if(num<60) { //rel2
                shop->item3Count++;
                Blus *b = new Blus(angle,QRectF(x,y,w,h),shop->getPixmap(3),pw,ph);
                b->gift = true;
                blusse.push_back(b);
            } else if(num<70) {//speed 2
                shop->item4Count++;
                Blus *b = new Blus(angle,QRectF(x,y,w,h),shop->getPixmap(4),pw,ph);
                b->gift = true;
                blusse.push_back(b);
            } else if(num<85) {//rel 1
                shop->item1Count++;
                Blus *b = new Blus(angle,QRectF(x,y,w,h),shop->getPixmap(1),pw,ph);
                b->gift = true;
                blusse.push_back(b);
            } else { //speed 1
                shop->item2Count++;
                Blus *b = new Blus(angle,QRectF(x,y,w,h),shop->getPixmap(2),pw,ph);
                b->gift = true;
                blusse.push_back(b);
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
                        if(!vContains(shop->ownedSkins,num)) ok=false;
                    }
                    shop->ownedSkins.push_back(num);
                    Blus *b = new Blus(angle,QRectF(x-75,y+100,1,1),"+ ");
                    b->gift = true;
                    blusse.push_back(b);
                    b = new Blus(angle,QRectF(x,y,w,h),skins[num]);
                    b->gift = true;
                    blusse.push_back(b);
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
                        if(!vContains(shop->ownedPipes,num)) ok=false;
                    }
                    shop->ownedPipes.push_back(num);
                    Blus *b = new Blus(angle,QRectF(x-75,y+100,1,1),"+ ");
                    b->gift = true;
                    blusse.push_back(b);
                    b = new Blus(angle,QRectF(x,y,w,h),pipes[num]);
                    b->gift = true;
                    blusse.push_back(b);
                    done = true;
                }
            }
            if(type==2) { //bg
                if((uint)shop->ownedbackgrounds.size()!=backgrounds.size()) {
                    bool ok=true;
                    int num;
                    while(ok) {
                        num = random(1,backgrounds.size());
                        if(!vContains(shop->ownedbackgrounds,num)) ok=false;
                    }
                    shop->ownedbackgrounds.push_back(num);
                    Blus *b = new Blus(angle,QRectF(x-75,y+100,1,1),"+ ");
                    b->gift = true;
                    blusse.push_back(b);
                    b = new Blus(angle,QRectF(x,y,w,h),backgrounds[num]->background);
                    b->gift = true;
                    blusse.push_back(b);
                    done = true;
                }
            }
            if(type==3) { //tail
                if(shop->ownedTails.size()!=tails.size()) {
                    bool ok=true;
                    int num;
                    while(ok) {
                        num = random(1,tails.size());
                        if(!vContains(shop->ownedTails,num)) ok=false;
                    }
                    shop->ownedTails.push_back(num);
                    Blus *b = new Blus(angle,QRectF(x-75,y+100,1,1),"+ ");
                    b->gift = true;
                    blusse.push_back(b);
                    b = new Blus(angle,QRectF(x,y,w,h),tails[num]);
                    b->gift = true;
                    blusse.push_back(b);
                    done = true;
                }
            }
            if(!done) {
                player->coins+=2;
                on_shopBuy(2,false,true,true);
            }
        }
    } else {
        boxState++;
    }
}

void FrmMain::playFlatter()
{
    if(!soundEffectsEnabled) return;
    for(int i=0;i<10;i++) {
        if(!soundEffects[i]->isPlaying()&&soundEffects[i]->status()==QSoundEffect::Ready) {
            QMetaObject::invokeMethod(soundEffects[i],"play");
            //soundEffects[i]->play();
            break;
        }
    }
}

void FrmMain::doSchmuserDefend()
{
    //wavecheck
    if(schmuserkills>=schmuserKillsneeded) {
        schmuserkills = 0;
        if((schmuserWave+1)%10==0) {
            player->coins++;
        }
        schmuserWave++;
        if(schmuserWaveSize<20) {
            schmuserWaveSize*=1.25;
        } else {
            schmuserHP*=1.25;
        }
        schmuserKillsneeded*=1.2;
    }
    //del
    for(uint i=0;i<enemys.size();i++) {
        bool del=false;
        if(enemys[i]->showhp) enemys[i]->showhp -= 5;
        for(uint a=0;a<projectiles.size();a++) {
            if(!enemys[i]->dead) {
                if(projectiles[a]->r.intersects(QRectF(enemys[i]->rect))) {
                    enemys[i]->hp-=projectiles[a]->damage;
                    projectiles[a]->del = true;
                    if(enemys[i]->hp<=0) {
                        enemys[i]->hp = 0;
                        enemys[i]->dead = true;
                    } else {
                        enemys[i]->showhp = 200;
                    }
                }
            }
        }
        if(enemys[i]->dead) {
            if(enemys[i]->opacity>0) {
                enemys[i]->opacity -= 0.025;
            } else {
                del = true;
            }
        }
        if(enemys[i]->rect.y()<1500&&!del) {
            if(!enemys[i]->dead) {
                enemys[i]->moveTo(enemys[i]->rect.x(),enemys[i]->rect.y()+1);
                if(enemys[i]->showhp>5) enemys[i]->showhp-=5;
            }
        } else {
            if(del) {
                schmuserCredits++;
                schmuserkills++;
                //qDebug()<<"WAVE: "<<schmuserWave<<" KILLS: "<<schmuserkills<<" FROM "<<schmuserKillsneeded;
            } else {
                schmuserBaseHP -= enemys[i]->hp;
                if(schmuserBaseHP<=0) {
                    schmuserBaseHP = 0;
                    active=2;
                }
            }
            delete enemys[i];
            enemys.erase(enemys.begin()+i);
        }
    }
}

void FrmMain::drawSchmuserDefend(QPainter &painter, QFont f)
{
    if(!active&&moveAn!=3&&moveAn!=1) return;
    QPixmap schmuserPixmap = skins[14];
    if(!schmuserEnemy) schmuserPixmap = mieserkadserPx;
    for(uint i=0;i<enemys.size();i++) {
        QRect er = enemys[i]->rect;
        if(er.y()>-100) {
            painter.setOpacity(enemys[i]->opacity);
            painter.drawPixmap(er,schmuserPixmap);
        }
        painter.setOpacity(1);
    }
    for(uint i=0;i<enemys.size();i++) {
        QRect er = enemys[i]->rect;
        if(enemys[i]->hp<enemys[i]->maxhp) {
            int health = enemys[i]->hp;
            int maxHealth = enemys[i]->maxhp;
            if(health>maxHealth*0.8) {
                painter.setBrush(QColor(34,177,76));
            } else if(health>maxHealth*0.6) {
                painter.setBrush(QColor(181,230,29));
            } else if(health>maxHealth*0.4) {
                painter.setBrush(QColor(255,242,0));
            } else if(health>maxHealth*0.2) {
                painter.setBrush(QColor(223,89,0));
            } else if(health>0) {
                painter.setBrush(QColor(237,28,36));
            }
            painter.drawRect(er.x(),er.y()-30,er.width()*((double)enemys[i]->hp/enemys[i]->maxhp),10);
        }
    }
    for(uint i=0;i<projectiles.size();i++) {
        painter.drawPixmap(projectiles[i]->r,minus,QRectF(0,0,40,40));
    }
    /*painter.setBrush(Qt::red);
    painter.drawRect(aimingAt);*/
    painter.setBrush(Qt::black);
    painter.drawRect((mainX+1080)+19,1679,1042,42);
    int health = schmuserBaseHP;
    int maxHealth = schmuserBaseMaxHP;
    if(health>maxHealth*0.8) {
        painter.setBrush(QColor(34,177,76));
    } else if(health>maxHealth*0.6) {
        painter.setBrush(QColor(181,230,29));
    } else if(health>maxHealth*0.4) {
        painter.setBrush(QColor(255,242,0));
    } else if(health>maxHealth*0.2) {
        painter.setBrush(QColor(223,89,0));
    } else if(health>0) {
        painter.setBrush(QColor(237,28,36));
    }
    painter.drawRect((mainX+1080)+20,1680,1040*((double)schmuserBaseHP/schmuserBaseMaxHP),40);
    f.setPixelSize(25);
    painter.setFont(f);
    painter.setPen(Qt::white);
    painter.drawText(QRect((mainX+1080)+19,1679,1042,42),Qt::AlignCenter,QString::number(schmuserBaseHP)+" / "+QString::number(schmuserBaseMaxHP));
    QPen p;
    p.setWidth(3);
    p.setColor(Qt::red);
    painter.setPen(p);
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(player->getRect().center(),schmuserRange,schmuserRange);
    painter.setPen(Qt::NoPen);
    painter.drawPixmap((mainX+1080)+10,1730,250,90,btnPx);
    if(schmuserRange>=1300) painter.setOpacity(0.4);
    painter.drawPixmap((mainX+1080)+280,1730,250,90,btnPx);
    painter.setOpacity(1);
    painter.drawPixmap((mainX+1080)+550,1730,250,90,btnPx);
    painter.drawPixmap((mainX+1080)+820,1730,250,90,btnPx);
    painter.setPen(Qt::white);
    painter.drawText((mainX+1080)+10,1730,250,90,Qt::AlignCenter,"DMG\nCost:"+QString::number(schmuserCost[0]));
    if(schmuserRange>=1300) painter.setOpacity(0.4);
    painter.drawText((mainX+1080)+280,1730,250,90,Qt::AlignCenter,"RANGE\nCost:"+QString::number(schmuserCost[1]));
    painter.setOpacity(1);
    painter.drawText((mainX+1080)+550,1730,250,90,Qt::AlignCenter,"RELOAD\nCost:"+QString::number(schmuserCost[2]));
    painter.drawText((mainX+1080)+820,1730,250,90,Qt::AlignCenter,"MAX HP\nCost:"+QString::number(schmuserCost[3]));
    f.setPixelSize(30);
    painter.setFont(f);
    painter.drawText((mainX+1080)+10,1750,1060,250,Qt::AlignCenter,"WAVE "+QString::number(schmuserWave)+" KILLS "+QString::number(schmuserkills)+"/"+QString::number(schmuserKillsneeded));
    if(active==-1||moveAn==3||(active==1&&textFade)) {
        painter.setOpacity(textFade);
        painter.setPen(Qt::white);
        f.setPixelSize(48);
        painter.setFont(f);
        Text t = transl->getText_AOTS();
        painter.drawText(QRect((mainX+1080)+0,1000,1080,200),Qt::AlignCenter,t.text);
        painter.setOpacity(1);
    }
}

void FrmMain::drawSchmuserDefendEnd(QPainter &painter, QFont f)
{
    painter.drawPixmap(endX+190,1300,300,150,btnPx);
    painter.drawPixmap(endX+590,1300,300,150,btnPx);
    painter.setPen(textColor);
    f.setPixelSize(72);
    painter.setFont(f);
    painter.drawText(QRect(0,500,1080,400),Qt::AlignCenter,"Game Over");
    f.setPixelSize(56);
    painter.setFont(f);
    painter.drawText(QRect(0,700,1080,400),Qt::AlignCenter,"Wave "+QString::number(schmuserWave));
    f.setPixelSize(48);
    painter.setFont(f);
    painter.drawText(QRect(endX+190,1300,300,150),Qt::AlignCenter,"Ok");
    painter.drawText(QRect(endX+590,1300,300,150),Qt::AlignCenter,transl->getBtn_Go().text);
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

QString FrmMain::lucaAlgR(QString text)
{
    QString output,tmp;
    for(int i=0;i<text.size();i++) {
        if(QString(text.at(i)).toInt()<5) {
            tmp.append("0");
        } else {
            tmp.append("1");
        }
        if(tmp.size()==8) {
            char c=0;
            for(int a=0;a<8;a++) {
                if(tmp[a]=='1') {
                    c += pow(2,7-a);
                }
            }
            tmp.resize(0);
            output.append(c);
        }
    }
    return output;
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

bool FrmMain::intersectsWithCircle2(QRectF rect, int radius, QPoint center)
{
    bool coll=false;
    double distX = abs(center.x()-rect.center().x());
    double distY = abs(center.y()-rect.center().y());
    if((distX>(rect.width()/2+radius))||
            (distY>(rect.height()/2+radius))) return false;
    if((distX<=(rect.width()/2))||
            (distY<=(rect.height()/2))) return true;
    double dx=distX-rect.width()/2;
    double dy=distY-rect.height()/2;
    if(dx*dx+dy*dy<=(radius*radius)) return true;
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

    if(!dsgvo) {
        //DSGVO anzeige

        if(transl->getLanguageCode() == 1) {
            //Deutsch
            painter.drawPixmap(115, 750, 850, 850, dsgvoPx_de);
        } else {
            painter.drawPixmap(115, 750, 850, 850, dsgvoPx_en);
        }

        painter.drawPixmap(115,1650,400,150, btnPx); //exit btn
        painter.drawPixmap(565,1650,400,150, btnPx); //continue btn

        f.setPixelSize(48);
        painter.setFont(f);
        painter.setPen(Qt::black);
        painter.drawText(QRect(115,1650,400,150),Qt::AlignCenter,"Exit");
        painter.drawText(QRect(565,1650,400,150),Qt::AlignCenter,transl->getText_Continue().text);

        return;
    }

    if(flip) {
        painter.translate(1080/2,1920/2);
        painter.scale(1,-1);
        painter.translate(-1080/2,-1920/2);
    }
    /*painter.translate(1080/2,1920/2);
    painter.scale(1,-1);
    painter.translate(-1080/2,-1920/2);*/
    painter.setPen(Qt::NoPen);
    painter.setBrush(backgrounds[shop->chosenBackground-1]->bColor);
    //painter.setBrush(QColor(0,143,255));
    //painter.drawRect(0,-2,1080,1922);
    painter.drawPixmap(0,0,1080,1660,backgrounds[shop->chosenBackground-1]->background);
    if(!cave&&!space&&backgrounds[shop->chosenBackground-1]->flag) {
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
            if(space) {
                QRect off = stars[i]->rect;
                off.moveTo(off.x(),off.y()+870);
                painter.setOpacity(stars[stars.size()-1-i]->opacity);
                painter.drawRect(off);
            }
        }
    }
    painter.setOpacity(1);
    int scb = shop->chosenBackground;
    if(scb!=2&&scb!=4) {
        for(uint i=0;i<blusse.size();i++) {
            if(blusse[i]->bg) {
                if(blusse[i]->getRect().intersects(QRectF(0,0,1080,1920))) {
                    painter.setOpacity((blusse[i]->getOpacity()/2.55)/100.0);
                    painter.setBrush(blusse[i]->color);
                    painter.drawRect(blusse[i]->getRect());
                    painter.setOpacity(1);
                }
            }
        }
    }
    if(flip&&active!=1&&active!=-1) {
        painter.translate(1080/2,1920/2);
        painter.scale(1,-1);
        painter.translate(-1080/2,-1920/2);
    }
    if(backgrounds[shop->chosenBackground-1]->cloud) {
        int y = 800;
        if(shop->chosenBackground==8) {
            y = 100;
        }
        painter.drawPixmap(QRectF(cloud1X,y,1080,280),cloudPx,QRectF(0,0,108,28));
        painter.drawPixmap(QRectF(cloud2X,y,1080,280),cloudPx,QRectF(0,0,108,28));
    }
    if(space) {
        painter.drawPixmap(QRectF(planetX,planetY,160,160),planets[chosenPlanet],QRectF(0,0,16,16));
    }
    painter.setBrush(QColor(255,153,0));
    painter.save();
    painter.translate(mainX+1080,0);
    if(!cave) {
        for(uint i=0;i<obstacles.size();i++) {
            if(obstacles[i]->getTop().intersects(QRectF(0,0,1080,1920))) {
                if(!obstacles[i]->type) {
                    if(shop->chosenPipe>pipes.size()) {
                        startStop(false);
                        error("Bitte an Dev weiterleiten:\n"
                              "OOR - PIPE_DRAW - MAX:"+QString::number(pipes.size())+" REQ:"+QString::number(shop->chosenPipe));
                        QApplication::quit();
                    }
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
                    case 12:
                    case 18:
                        for(uint i=0;i<obstacles.size();i++) {
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
                    case 10:
                        painter.drawPixmap(obstacles[i]->getTop(),pipes[shop->chosenPipe-1],QRectF(0,0,100,100));
                        painter.drawPixmap(obstacles[i]->getBottom(),pipes[shop->chosenPipe-1],QRectF(0,0,100,100));
                        painter.setBrush(QColor(rgb_red,rgb_green,rgb_blue,100));
                        painter.drawRect(obstacles[i]->getTop());
                        painter.drawRect(obstacles[i]->getBottom());
                        break;
                    case 11:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    {
                        QPen p(QColor(0,143,255));
                        switch(shop->chosenPipe) {
                        case 13:
                            p = QPen(QColor(255,153,0));
                            break;
                        case 14:
                            p = QPen(QColor(108,67,43));
                            break;
                        case 15:
                            p = QPen(QColor(225,8,233));
                            break;
                        case 16:
                            p = QPen(QColor(255,255,255));
                            break;
                        case 17:
                            p = QPen(QColor(91,185,28));
                            break;
                        }
                        p.setWidth(6);
                        painter.setPen(p);
                        painter.setBrush(Qt::transparent);
                        painter.translate(0,-5);
                        painter.drawRect(obstacles[i]->getTop());
                        painter.translate(0,5);
                        painter.drawRect(obstacles[i]->getBottom());
                        break;
                    }
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
    if(flip&&active!=-1&&active!=1) {
        painter.translate(1080/2,1920/2);
        painter.scale(1,-1);
        painter.translate(-1080/2,-1920/2);
    }
    if(!backgrounds[shop->chosenBackground-1]->custombg&&!cave&&!space) {
        painter.drawPixmap(QRectF(g1x,1660,1080,260),ground,QRectF(0,0,108,25));
    } else if(cave) {
        painter.setBrush(QColor(68,68,68));
        painter.drawRect(g1x,1660,1080,260);
    } else {
        painter.drawPixmap(QRectF(g1x,1660,1080,260),backgrounds[shop->chosenBackground-1]->ground,QRectF(0,0,108,25));
    }
    if(flip&&active!=-1&&active!=1) {
        painter.translate(1080/2,1920/2);
        painter.scale(1,-1);
        painter.translate(-1080/2,-1920/2);
    }
    painter.setBrush(QColor(0,143,255));
    //painter.drawRect(player->getRect());
    if(flip&&active!=-1&&active!=1) {
        painter.translate(1080/2,1920/2);
        painter.scale(1,-1);
        painter.translate(-1080/2,-1920/2);
    }
    if(active>0||active==-1||moveAn==3||moveAn==1||moveAn==-1) {
        if(!schmuserDefend) player->setPos((mainX+1080)+250,player->getRect().y());
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
    if(!cave&&backgrounds[shop->chosenBackground-1]->train) {
        for(uint i=0;i<obstacles.size();i++) {
            if(!obstacles[i]->type) {
                painter.save();
                painter.translate(mainX+1080,0);
                painter.drawPixmap(obstacles[i]->train,trainPx,QRectF(0,0,20,8));
                painter.drawPixmap(obstacles[i]->train2,trainPx,QRectF(0,0,20,8));
                painter.restore();
            }
        }
    }
    if(flip&&active!=-1&&active!=1) {
        painter.translate(1080/2,1920/2);
        painter.scale(1,-1);
        painter.translate(-1080/2,-1920/2);
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
    for(uint i=0;i<blusse.size();i++) {
        if(!blusse[i]->gift&&!blusse[i]->bg) {
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
    for(uint i=0;i<blusse.size();i++) {
        if(!blusse[i]->gift&&!blusse[i]->bg) {
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
    if(schmuserDefend) {
        drawSchmuserDefend(painter,f);
    }
    if(active==2&&!schmuserDefend) {
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
        painter.setPen(textColor);
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
        } else if(space&&!hardcore) {
            hs = highscore_S;
        } else if(underwater&&!hardcore) {
            hs = highscore_UM;
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
    } else if(active==2&&schmuserDefend) {
        drawSchmuserDefendEnd(painter,f);
    }
    if((active==1||active==-1||moveAn==3||moveAn==-1)) {
        if(!schmuserDefend) {
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
            painter.setPen(Qt::NoPen);
            painter.drawPixmap((mainX+1080)+10,1680,250,90,powerupPx[0]); //item1
            painter.setOpacity(1);
            f.setPixelSize(44);
            painter.setFont(f);
            painter.setPen(QColor(238,77,46));
            painter.drawText((mainX+1080)+120,1750,shop->getItemCount(1)+"x");
            if(!shop->item2Count||active!=-1||(active==-1&&score)||hardcore||cave) {
                painter.setOpacity(0.5);
            }
            painter.setPen(Qt::NoPen);
            painter.drawPixmap((mainX+1080)+280,1680,250,90,powerupPx[1]); //item2
            painter.setOpacity(1);
            painter.setPen(QColor(238,77,46));
            painter.drawText((mainX+1080)+390,1750,shop->getItemCount(2)+"x");
            if(!shop->item3Count||active==-1) {
                painter.setOpacity(0.5);
            }
            painter.setPen(Qt::NoPen);
            painter.drawPixmap((mainX+1080)+550,1680,250,90,powerupPx[2]); //item3
            painter.setOpacity(1);
            painter.setPen(QColor(238,77,46));
            painter.drawText((mainX+1080)+660,1750,shop->getItemCount(3)+"x");
            if(!shop->item4Count||active!=-1||(active==-1&&score)||hardcore||cave) {
                painter.setOpacity(0.5);
            }
            painter.setPen(Qt::NoPen);
            painter.drawPixmap((mainX+1080)+820,1680,250,90,powerupPx[3]); //item4
            painter.setOpacity(1);
            painter.setPen(QColor(238,77,46));
            painter.drawText((mainX+1080)+930,1750,shop->getItemCount(4)+"x");
            painter.setPen(Qt::NoPen);
            if(space) {
                painter.drawPixmap((mainX+1080)+10,1790,520,120,btndown);
                painter.drawPixmap((mainX+1080)+550,1790,520,120,btnup);
            }
            if(active==-1||moveAn==3||(active==1&&textFade)) {
                painter.setOpacity(textFade);
                if(!space){
                    painter.setPen(Qt::white);
                    f.setPixelSize(48);
                    painter.setFont(f);
                    Text t = transl->getText_Begin();
                    painter.drawText(QRect((mainX+1080)+0,1000,1080,200),Qt::AlignCenter,t.text);
                } else {
                    painter.setBrush(Qt::white);
                    for(int i=0;i<20;i+=3) {
                        painter.drawRect((mainX+1080)+25+i*54,player->getRect().center().y()-10,54,20);
                    }
                    painter.setPen(Qt::white);
                    f.setPixelSize(40);
                    painter.setFont(f);
                    painter.drawText(QRect((mainX+1080)+0,player->getRect().center().y()-200,1080,200),Qt::AlignCenter,transl->getText_BeginSpaceTop().text);
                    painter.drawText(QRect((mainX+1080)+0,player->getRect().center().y()+0,1080,200),Qt::AlignCenter,transl->getText_BeginSpaceBottom().text);

                }
            }
            if(!shop->item4Count||active==-1) {
                painter.setOpacity(0.5);
            }
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

        //Zeichne Buttons

        painter.drawPixmap(QRect(mainX+228,900,300,150),btnPx); //los
        painter.drawPixmap(QRect(mainX+553,900,300,150),btnPx); //aots

        painter.drawPixmap(QRect(mainX+390,1100,300,150),btnPx); //shop
        painter.drawPixmap(QRect(mainX+390,1300,300,150),btnPx); //hs
        painter.drawPixmap(QRect(mainX+390,1500,300,150),settingsBtn); //neue settings
        //painter.drawPixmap(QRect(mainX+350,1810,360,96),btnPx); //alte settings
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
        painter.setPen(textColor);
        f.setPixelSize(23);
        painter.setFont(f);
        //painter.drawText(QRect(mainX+350,1810,360,96),Qt::AlignCenter,"Einstellungen");
        f.setPixelSize(32);
        painter.setFont(f);
        if(hardcore) {
            painter.drawText(QRect(mainX+23,900,75,325),Qt::AlignCenter,"H\nA\nR\nD\nC\nO\nR\nE");
        } else {
            painter.drawText(QRect(mainX+23,900,75,325),Qt::AlignCenter,"N\nO\nR\nM\nA\nL");
        }

        f.setPixelSize(42);
        painter.setFont(f);
        painter.drawText(QRect(mainX+725,1810,180,96),Qt::AlignCenter,"$$$");

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
        //"Los"
        painter.drawText(QRect(mainX+228,900,300,150), Qt::AlignCenter,go.text);
        f.setPixelSize(shopT.size);
        painter.setFont(f);
        painter.drawText(QPoint(mainX+shopT.pos.x(),shopT.pos.y()),shopT.text);
        painter.drawText(QRect(mainX+553,900,300,150),Qt::AlignCenter,"AotS");
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
            for(uint i=0;i<blusse.size();i++) {
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
            painter.setPen(textColor);
            painter.drawText(QRect(170,1460,300,130),Qt::AlignCenter,transl->getText_Referral_btnConfirm().text);
            painter.drawText(QRect(455,1460,300,130),Qt::AlignCenter,transl->getText_Referral_btnInvite().text);
            painter.drawText(QRect(750,1460,160,130),Qt::AlignCenter,"Ok");
        }
        f.setPixelSize(42);
        painter.setFont(f);
        if(outdated) painter.drawText(mainX+25,200,"Ein Update ist verfügbar!");
        if(soundEnabled) {
            painter.drawPixmap(mainX+955,0,125,125,vol0);
        } else {
            painter.drawPixmap(mainX+955,0,125,125,vol1);
        }
    }
    if((!active&&shop->getActive())||(moveAn==2||moveAn==4)) {
        shop->draw(painter,rgb_red,rgb_green,rgb_blue,textColor);
    } else if((!active&&scoreboard->active)||(moveAn==5||moveAn==6)) {
        scoreboard->draw(painter,highscore,textColor);
    } else if((!active&&settings->active)||(moveAn==7||moveAn==8)) {
        settings->draw(painter,textColor,schmuserEnemy);
    }
    f.setPixelSize(48);
    painter.setFont(f);
    painter.setPen(Qt::white);
    if(!schmuserDefend||!active) {
        painter.drawText(4,50,"BENIS "+QString::number(player->getBenis()));
    } else {
        painter.drawText(4,50,"CREDITS "+QString::number(schmuserCredits));
    }
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
    if(ad_active) {
        painter.setBrush(QColor(22,22,24));
        painter.setOpacity(0.7);
        painter.drawRect(0,0,1080,1920);
        painter.setOpacity(1);

        if(transl->getLanguageCode() == 1) {
            //Deutsch
            painter.drawPixmap(65,150,950,1413,ad_px); //ad image
        } else {
            //Englisch
            painter.drawPixmap(65,150,950,1413,ad_px_eng); //ad image eng
        }

        //painter.drawPixmap(165,1345,750,150,btnPx); //jetzt spenden

        painter.drawPixmap(65, 1650, 150, 150, restorePx); //restore btn
        painter.drawPixmap(265,1650,750,150, btnPx); //vllt später btn

        //f.setPixelSize(48);
        //painter.setFont(f);
        painter.setPen(textColor);
        //painter.drawText(QRect(165,1345,750,150),Qt::AlignCenter,"Jetzt Spenden");
        //f.setPixelSize(20);
        //painter.setFont(f);
        //painter.drawText(QPoint(205,1475),"(Ab 1.5€. Weiterleitung zu Paypal)");
        f.setPixelSize(40);
        painter.setFont(f);
        painter.drawText(QRect(265,1650,750,150),Qt::AlignCenter,transl->getText_MaybeLater().text);
    }
}

void FrmMain::mousePressEvent(QMouseEvent *e)
{
    int x = e->pos().x()/scaleX;
    int y = e->pos().y()/scaleY;
    mouseX = x;
    mouseY = y;
    mousePressed = true;
    QRect collRect = QRect(x,y,1,1);
    QRectF collRectF = QRectF(collRect);
    //delete e;
    mousePos = QPoint(x,y);

    //qDebug() << mousePos;

    switch(active) {
    case 0:
        if(shop->getActive()) {
            shop->mousePress(QPoint(x,y),cave,space,flip,underwater);
        } else if(scoreboard->active) {
            scoreboard->mpress(QPoint(x,y), this);
        } else if(settings->active) {
            settings->mousePress(x,y,soundEnabled,soundEffectsEnabled,lowGraphics,schmuserEnemy);
        }
        break;
    }
    if(moveAn||shop->getActive()||scoreboard->active||settings->active||loading) return;
    switch(active) {
        case 0:

            if(!dsgvo) {
                //DSGVO check

                if(collRect.intersects(QRect(115,1650,400,150))) {
                    //Exit App
                    QApplication::quit();
                } else if(collRect.intersects(QRect(565,1650,400,150))) {
                    //Continue
                    firstlaunch = false;
                    dsgvo = true;

                    //Speichern
                    QFile dsgvoFile;
                    QString path = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
                    dsgvoFile.setFileName(path+"/dsgvo.dat");
                    dsgvoFile.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
                    QTextStream dout(&dsgvoFile);
                    dout << QString::number(1);
                    dsgvoFile.close();

                } else if(collRect.intersects(QRect(115, 750, 850, 850))) {
                    //Datenschutzerklärung öffnen
                    QUrl link("https://pastebin.com/kiHSKVV2");
                    QDesktopServices::openUrl(link);
                }

                return;
            }

            if(ad_active) {
                //Ad Aktiv -> Prüfen ob auf Paket getippt

                int packageCode = -1;

                if(collRect.intersects(QRect(100, 264, 900, 350))) {
                    //Kleines Paket
                    packageCode = 0;
                } else if(collRect.intersects(QRect(100, 622, 900, 350))) {
                    //Mittleres Paket
                    packageCode = 1;
                } else if(collRect.intersects(QRect(100, 999, 900, 350))) {
                    //Großes Paket
                    packageCode = 2;
                }

                if(packageCode > -1) {
                    //Kauf initialisieren
                    initPurchase(packageCode);
                } else if(collRect.intersects(QRect(265,1650,750,150))) {
                    //Auf "Vielleicht später" getippt -> exit ad
                    ad_active = 0;
                } else if(collRect.intersects(QRect(65, 1650, 150, 150))) {
                    //Auf Restore getippt
                    store->restorePurchases();
                }

                /*if(collRect.intersects(QRect(165,1345,750,150))) { //jetzt spenden
                    QUrl link("https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=LNQX9P7KSG6NY");
                    QMessageBox::information(this,"Info","Vergiss nicht deinen Namen anzugeben!");
                    QDesktopServices::openUrl(link);
                    ad_active = 0;
                }*/
                return;
            }
            if(crate) {
                if(collRect.intersects(QRect(340,760,400,453))) {
                    handleBox();
                } else {
                    crate = false;
                }
                return;
            }
            if(refActive) {
                if(collRect.intersects(QRect(165,1460,300,130))&&referrals) { //btnconfirm
                    bool ok=false;
                    QGuiApplication::inputMethod()->show();
                    QString n = QInputDialog::getText(this,tr("Key"),"Key: ",QLineEdit::Normal,"",&ok);
                    if(ok) {
                        if(checkConfirm(n)&&n!=confirmkey) {
                            player->setBenis(player->getBenis()+250000);
                            on_shopBuy(250000,false);
                            referrals--;
                            QMessageBox::information(this,"Info",transl->getText_Referral_Confirmed2().text);
                        } else {
                            QMessageBox::information(this,"Info",transl->getText_Referral_WrongKey().text);
                        }
                    }
                    refActive = false;
                } else if(collRect.intersects(QRect(455,1460,300,130))&&!invited) { //btnwurde
                    bool ok=false;
                    QGuiApplication::inputMethod()->show();
                    QString n = QInputDialog::getText(this,tr("Key"),"Key: ",QLineEdit::Normal,"",&ok);
                    if(ok) {
                        if(checkKey(n)&&n!=refkey) {
                            player->setBenis(player->getBenis()+100000);
                            on_shopBuy(100000,false);
                            invited = 1;
                            confirmkey = lucaAlg("d");
                            QMessageBox::information(this,tr("Info"),transl->getText_Referral_Confirmed().text+confirmkey);
                        } else {
                            QMessageBox::information(this,tr("Info"),transl->getText_Referral_WrongKey().text);
                        }
                    }
                    refActive = false;
                } else if(collRect.intersects(QRect(750,1460,160,130))) { //btnok
                    refActive = false;
                }
                return;
            }
            if(collRect.intersects(QRect(50,1236,75,71))) {
                /*if(event<3) {
                    event++;
                    if(event==3) {
                        boxCount += 25;
                        QMessageBox::information(this,"I bims der Schmuserkadser","Schmuserkadser hat dir 25 Geschenke gegeben!\nFrohe Weihnachten!");
                        write();
                    }
                }*/
            } else if(collRect.intersects(QRect(228,900,300,150))) { //los
                radR = 1700;
                moveAn = 3;
                schmuserDefend = false;
                player->setPos(1080/2-250,1920/2-40);
            } else if(collRect.intersects(QRect(390,1500,300,150))) { //öffne settings
                if(!settings->active) {
                    moveAn = 7;
                }
            } else if(collRect.intersects(QRect(390,1100,300,150))) { //shop
                moveAn = 2;
            } else if(collRect.intersects(QRect(10,1810,160,96))) {
                transl->locale = QLocale("de");
            } else if(collRect.intersects(QRect(175,1810,160,96))) {
                transl->locale = QLocale("en");
            } else if(collRect.intersects(QRect(390,1300,300,150))) { //scoreboard

                //qDebug() << "hit1";

                bool ok = true;
                if(scoreboard->name == "") {
                    //Wenn Name noch nicht gesetzt

                    //qDebug() << "hit2";

                    QGuiApplication::inputMethod()->show();
                    QString n = QInputDialog::getText(this,tr("Nickname"),transl->getText_Scoreboard_SetName().text, QLineEdit::Normal, "", &ok);

                    if(ok) {
                        //In Dialogbox auf ok geklickt

                        ok = scoreboard->checkName(n);

                        if(!ok) {
                            //Name falsch

                            Text t = transl->gettext_Scoreboard_Falsch();
                            QMessageBox::critical(this,"Error",t.text);
                        } else {
                            scoreboard->name = n;
                            scoreboard->first = "1";
                        }
                    }
                } else {
                    //qDebug() << "hit3";
                    scoreboard->first = "0";
                }

                if(ok) {
                    //qDebug() << "hit4";
                    //if(highscore*3>playTime) num = -1;
                    scoreboard->setScore(highscore,highscore_H,highscore_C,highscore_S,highscore_UM);

                    /*if(scoreboard->wasConnected==1) {
                        if(scoreboard->first=="1") scoreboard->first="0";
                        scoreboard->getScores();
                    }*/
                }
                //if(ok && scoreboard->wasConnected==1) scoreboard->active = true;
            } else if(collRect.intersects(QRect(775,1550,150,135))&&!crate) { //kiste
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
            } else if(collRect.intersects(QRect(910,1810,160,100))) { //ref
                refActive = true;
                if(refkey!="") return;
                for(int i=0;i<10;i++) refkey = genKey();
            } else if(collRect.intersects(QRect(mainX+725,1810,180,96))) {//spenden
                /*QUrl link("https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=LNQX9P7KSG6NY");
                QMessageBox boxMsg;
                boxMsg.setWindowTitle("Info");
                boxMsg.setText(transl->getText_Donate().text);
                boxMsg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                boxMsg.setDefaultButton(QMessageBox::Yes);
                int ret = boxMsg.exec();
                if(ret==QMessageBox::Yes) {
                    QMessageBox::information(this,"Info","Vergiss nicht deinen Namen anzugeben!");
                    QDesktopServices::openUrl(link);
                }*/
                ad_active = 1;
            } else if(collRect.intersects(QRect(20,900,75,325))) { //hardcore
                if(!cave&&shop->chosenPipe!=2&&!space&&!underwater) {
                    if(hardcore) {
                        hardcore = false;
                    } else {
                        hardcore = true;
                    }
                }
            } else if(collRect.intersects(QRect(553,900,300,150))) {//öffne aots
                radR = 1700;
                moveAn = 3;
                schmuserDefend = true;
                player->setPos(1080/2-40,1600);
            } else if(collRect.intersects(QRect(955,0,125,125))) { //sound
                if(soundEnabled) {
                    QMetaObject::invokeMethod(sound,"pause");
                    soundEnabled = false;
                    soundEffectsEnabled = false;
                } else {
                    sound->setVolume(25);
                    QMetaObject::invokeMethod(sound,"play");
                    soundEnabled = true;
                    soundEffectsEnabled = true;
                }
                settings->music = soundEnabled;
                settings->soundEffects = soundEffectsEnabled;
            }
        break;
        case -1:
            {
                if(!schmuserDefend) {
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
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                        interval = 15;
                        break;
                    }
                    //if(lowGraphics) interval = 0;
                    if(interval) QMetaObject::invokeMethod(t_tail,"start",Q_ARG(int,interval));
                }
                active = 1;
            }
        case 1:
            //for(int i=0;i<40000;i++) blusse.push_back(new Blus(90,QRectF(4,180,1,1),"+"+QString::number(10)));
            if(player->getRect().y()-10>0) {
                bool buy = false;
                if(collRect.intersects(QRect(955,0,125,125))) {
                    if(!t_resume->isActive()) {
                        if(pause) {
                            resumeTime = 3;
                            QMetaObject::invokeMethod(t_resume,"start",Q_ARG(int,1000));
                        } else {
                            if(!t_boost->isActive()&&!revive) {
                                pause = true;
                            } else {
                                blusse.push_back(new Blus(90,QRectF(4,180,1,1),transl->getText_PauseError().text,30));
                            }
                        }
                    }
                    return;
                }
                if(schmuserDefend) {
                    /*painter.drawText((mainX+1080)+10,1730,250,90,Qt::AlignCenter,"DMG\nCost:"+QString::number(schmuserCost[0]));
                    painter.drawText((mainX+1080)+280,1730,250,90,Qt::AlignCenter,"RANGE\nCost:"+QString::number(schmuserCost[1]));
                    painter.drawText((mainX+1080)+550,1730,250,90,Qt::AlignCenter,"RELOAD\nCost:"+QString::number(schmuserCost[2]));
                    painter.drawText((mainX+1080)+820,1730,250,90,Qt::AlignCenter,"MAX HP\nCost:"+QString::number(schmuserCost[3]));*/
                    if(collRect.intersects(QRect(10,1730,250,90))) { //dmg
                        if(schmuserCredits>=schmuserCost[0]) {
                            schmuserCredits -= schmuserCost[0];
                            schmuserCost[0] *= 2;
                            schmuserDmg *= 1.5;
                        }
                    } else if(collRect.intersects(QRect(280,1730,250,90))) { //range
                        if(schmuserCredits>=schmuserCost[1]&&schmuserRange<1300) {
                            schmuserCredits -= schmuserCost[1];
                            schmuserCost[1] *= 2;
                            schmuserRange *= 1.1;
                        }
                    } else if(collRect.intersects(QRect(550,1730,250,90))) { //reload
                        if(schmuserCredits>=schmuserCost[2]&&schmuserReload>10) {
                            schmuserCredits -= schmuserCost[2];
                            schmuserCost[2] *= 2;
                            schmuserReload *= 0.8;
                            QMetaObject::invokeMethod(t_reload,"start",Q_ARG(int,schmuserReload));
                        }
                    } else if(collRect.intersects(QRect(820,1730,250,90))) { //maxhp
                        if(schmuserCredits>=schmuserCost[3]) {
                            schmuserCredits -= schmuserCost[3];
                            schmuserCost[3] *= 2;
                            schmuserBaseMaxHP *= 1.5;
                        }
                    }
                }
                if(pause||schmuserDefend) return;
                player->tstep = (player->tilt/200)*10;
                player->tdir = true;
                QMetaObject::invokeMethod(t_tchange,"stop");
                QMetaObject::invokeMethod(t_tchange,"start",Q_ARG(int,200));
                if(active==1&&collRectF.intersects(QRectF(10,1680,250,90))) { //item1
                    if(shop->item1Count&&!revive&&!boost&&!boostDisabled) {
                        buy = true;
                        shop->item1Count--;
                        revive = 1;
                        reviveTime = 30000;
                    }
                } else if(collRectF.intersects(QRectF(280,1680,250,90))&&go==1&&!boostused) {  //item2
                    if(shop->item2Count&&!boost&&!hardcore&&!cave) {
                        shop->item2Count--;
                        boost=11;
                        boostused = true;
                        localPlayTime+=60;
                        fastboost = false;
                        QMetaObject::invokeMethod(t_boost,"start",Q_ARG(int,50));
                    }
                } else if(active==1&&collRectF.intersects(QRectF(550,1680,250,90))) {  //item3
                    if(shop->item3Count&&!revive&&!boost&&!boostDisabled) {
                        shop->item3Count--;
                        revive = 2;
                        buy = true;
                    }
                } else if(collRectF.intersects(QRectF(820,1680,250,90))&&go==1&&!boostused) {  //item4
                    if(shop->item4Count&&!boost&&!hardcore&&!cave) {
                        shop->item4Count--;
                        boost=20;
                        boostused = true;
                        localPlayTime+=120;
                        fastboost = true;
                        QMetaObject::invokeMethod(t_boost,"start",Q_ARG(int,50));
                    }
                } else if(collRectF.intersects(QRectF(550,1790,520,120))) { //btnup
                    double velD = player->getVelD();
                    velD -= 1;
                    if(!velD) velD = -1;
                    if(velD>5) velD = 5;
                    if(velD<-5) velD = -5;
                    buy = true;
                    player->setVelD(velD);
                    playFlatter();
                    tap(player->getRect().center().x(),player->getRect().center().y());
                } else if(collRectF.intersects(QRectF(10,1790,520,120))) { //btndown
                    double velD = player->getVelD();
                    velD += 1;
                    if(!velD) velD = 1;
                    if(velD>5) velD = 5;
                    if(velD<-5) velD = -5;
                    buy = true;
                    player->setVelD(velD);
                    playFlatter();
                    tap(player->getRect().center().x(),player->getRect().center().y());
                }
                if(!buy) {
                    playFlatter();
                    double velD = player->getVelD();
                    if(!space&&!underwater) {
                        velD = -4;
                    } else if(underwater) {
                        velD = -3;
                    } else {
                        QRectF r = player->getRect();
                        if(collRectF.y()<r.y()) { //runter | velD -1
                            velD -= 1;
                            if(!velD) velD = -1;
                        } else { //hoch | velD +1
                            velD += 1;
                            if(!velD) velD = 1;
                        }
                        if(velD>5) velD = 5;
                        if(velD<-5) velD = -5;
                    }
                    player->setVelD(velD);
                    if(collRectF.intersects(enemyRect)) {
                        if(enemytype!=2) {
                            blusse.push_back(new Blus(random(0,360),QRectF(x-20,y-20,40,40),minus));
                        } else {
                            blusse.push_back(new Blus(random(0,360),QRectF(x-20,y-20,40,40),"██",36));
                        }
                        blusse.push_back(new Blus(90,QRectF(4,180,1,1),"+"+QString::number(score*5)));
                        player->setBenis(player->getBenis()+score*(shop->multiplier/2));
                    } else {
                       tap(x,y);
                    }
                }
            } else if(schmuserDefend) {

            }
        break;
        case 2:
            if(collRect.intersects(QRect(190,1300,300,150))) {
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
            } else if(collRect.intersects(QRect(590,1300,300,150))) {
                moveAn = -1;
                textFade = 1;
            }
        break;
    }
}

void FrmMain::mouseReleaseEvent(QMouseEvent *e)
{
    mousePressed = false;
    int newX = e->pos().x()/scaleX;
    //int newY = e->pos().y()/scaleY;
    if(schmuserDefend) return;
    if(abs(mouseX-newX)<300) return;
    if(newX>mouseX) {//links->rechts
        if(active==1) {
            changeSpeed(true);
        }
    } else { //rechts->links
        if(active==1) {
            changeSpeed(false);
        }
    }
}

void FrmMain::keyPressEvent(QKeyEvent *e)
{
    if(moveAn) return;
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
            /*workerThread->exit();
            animationThread->exit();
            blusThread->exit();*/
            startStop(false);
            this->close();
        }
    } else {
        if(active==1) {
            if(!t_boost->isActive()&&!revive) pause = true;
        }
    }
}

void FrmMain::closeEvent(QCloseEvent *event)
{
    closing = true;
    Q_UNUSED(event)
    if((suspended||pause)&&active==1) {
        write(false,score);
    } else {
        write();
    }
    startStop(false);
    workerThread->quit();
    blusThread->quit();
    animationThread->quit();
    QApplication::quit();
}

#include "scoreboard.h"

void Scoreboard::on_tcpRecv()
{

}

QString Scoreboard::maas(QString n)
{
    return n;
}

Scoreboard::Scoreboard(QPixmap bg, QPixmap btnPx, QFont f, Translation *transl, QObject *parent) : QObject(parent)
{
    scoreX = -1080;
    this->bg = bg;
    this->btnPx = btnPx;
    this->transl = transl;
    this->btnNormal = QPixmap(":/images/buttons/btnNormal.png");
    this->btnCave = QPixmap(":/images/buttons/btnCave.png");
    this->btnHardcore = QPixmap(":/images/buttons/btnHardcore.png");
    this->btnSpace = QPixmap(":/images/buttons/btnSpace.png");
    this->btnUM = QPixmap(":/images/buttons/btnUM.png");
    hs=0;
    hs_H=0;
    hs_C=0;
    active = false;
    socket = new QTcpSocket();
    font = f;
    first="0";
    wasConnected = 0;
    page = 0;
    connect(socket,SIGNAL(readyRead()),this,SLOT(on_tcpRecv()));
}

void Scoreboard::draw(QPainter &painter, int highscore, QColor textColor)
{
    highscore = hs;
    if(page==1) {
        highscore = hs_H;
    } else if(page==2) {
        highscore = hs_C;
    } else if(page==3) {
        highscore = hs_S;
    } else if(page==4) {
        highscore = hs_UM;
    }
    painter.drawPixmap(scoreX+20,460,1040,1000,bg);
    if(page) painter.setOpacity(0.4);
    painter.drawPixmap(scoreX+30,473,160,160,btnNormal);
    painter.setOpacity(1);
    if(page!=1) painter.setOpacity(0.4);
    painter.drawPixmap(scoreX+190,473,160,160,btnHardcore);
    painter.setOpacity(1);
    if(page!=2) painter.setOpacity(0.4);
    painter.drawPixmap(scoreX+350,473,160,160,btnCave);
    painter.setOpacity(1);
    if(page!=3) painter.setOpacity(0.4);
    painter.drawPixmap(scoreX+510,473,160,160,btnSpace);
    painter.setOpacity(1);
    if(page!=4) painter.setOpacity(0.4);
    painter.drawPixmap(scoreX+670,473,160,160,btnUM);
    painter.setOpacity(1);
    QFont f = font;
    f.setPixelSize(40);
    painter.setFont(f);
    painter.setPen(Qt::white);
    int own = -1;
    for(int i=0;i<players.size();i++) {
        QString name = players[i].split("#").at(0);
        QString score = players[i].split("#").at(1);
        QString score2 = score;
        if(score.contains("-")) {
            score2.replace("-","");
        }
        if(name==this->name&&score2.toInt()==highscore&&own==-1) {
            own = i;
        }
        if(own==i) {
            painter.setPen(Qt::red);
        } else {
            painter.setPen(Qt::white);
        }
        if(score.contains("-")) {
            painter.setPen(QColor(28,185,146));
        }
        painter.drawText(scoreX+45,700+(i*60),name);
        painter.drawText(scoreX+845,700+(i*60),score2);
        int scoreI = score2.toInt();
        int medal=0;
        if(scoreI>=1000) {
            medal = 5;
        } else if(scoreI>=300) {
            medal = 4;
        } else if(scoreI>=175) {
            medal = 3;
        } else if(scoreI>=100) {
            medal = 2;
        } else if(scoreI>=60) {
            medal = 1;
        } else if(scoreI>=30) {
            medal = 0;
        }
        painter.drawPixmap(scoreX+785,647+(i*60),50,50,medals[medal]);
    }
    if(own==-1) {
        painter.setPen(Qt::red);
        painter.drawText(scoreX+50,700+10*60,name);
        painter.drawText(scoreX+850,700+10*60,QString::number(highscore));
    }
    painter.setPen(Qt::magenta);
    f.setPixelSize(36);
    painter.setFont(f);
    //painter.drawText(scoreX+50,550+12*60,"Server ist instabil. WIP.");
    painter.drawPixmap(scoreX+24,1324,300,130,btnPx);
    painter.drawPixmap(scoreX+500,1324,560,130,btnPx);
    painter.setPen(textColor);
    Text t = transl->getBtn_Scoreboard_Back();
    f.setPixelSize(t.size);
    painter.setFont(f);
    painter.drawText(QPoint(scoreX+t.pos.x(),t.pos.y()),t.text);
    t = transl->getBtn_Scoreboard_Change();
    f.setPixelSize(t.size);
    painter.setFont(f);
    painter.drawText(QPoint(scoreX+t.pos.x(),t.pos.y()),t.text);
}

void Scoreboard::setScore(int his, int his_H, int his_C, int his_S, int his_UM)
{
    bool ok=true;
    if(his||his_H||his_C||his_S||his_UM) {
        this->hs = his;
        this->hs_H = his_H;
        this->hs_C = his_C;
        this->hs_S = his_S;
        this->hs_UM = his_UM;
        ok=false;
    }
    int score = hs;
    if(page==1) {
        score = hs_H;
    } else if(page==2) {
        score = hs_C;
    } else if(page==3) {
        score = hs_S;
    } else if(page==4) {
        score = hs_UM;
    }
    socket->connectToHost("flatterfogel.ddns.net",38900);
    socket->waitForConnected(1000);
    if(socket->state()==QTcpSocket::ConnectedState) {
        QString data = ".0#"+name+"#"+QString::number(score)+"#"+first+"#"+QString::number(page)+"#~";
        socket->write(data.toUtf8());
        socket->waitForBytesWritten(2000);
        socket->waitForReadyRead(2000);
        QString input = socket->readAll();
        if(input.size()) {
            if(input.at(0)=="0") {
                active = false;
                wasConnected = false;
                socket->close();
                this->name=="";
                emit wrongName();
                return;
            }
        }
        first="0";
        emit write(ok);
        wasConnected = true;
    } else {
        emit connFail();
    }
    socket->close();
}

void Scoreboard::getScores()
{
    if(!wasConnected) return;
    socket->connectToHost("flatterfogel.ddns.net",38900);
    socket->waitForConnected(2000);
    if(socket->state()==QTcpSocket::ConnectedState) {
        QString data = ".1#"+name+"#"+QString::number(page)+"#~";
        socket->write(data.toUtf8());
        socket->waitForBytesWritten(1000);
        socket->waitForReadyRead(1000);
        QString input = socket->readAll();
        if(input.size()) {
            players.resize(0);
            input.replace("~","");
            QStringList split = input.split("#");
            for(int i=0;i<split.size()-1;i+=2) {
                QString n = maas(split[i]);
                players.append(n+"#"+split[i+1]);
            }
        }
    }
    socket->close();
}

void Scoreboard::mpress(QPoint pos)
{
    if(scoreX!=0) return;
    if(QRect(pos.x(),pos.y(),1,1).intersects(QRect(24,1324,300,130))) {
        emit back();
    }
    if(!players.size()) return;
    if(QRect(pos.x(),pos.y(),1,1).intersects(QRect(30,473,160,160))) { //normal
        if(page>0) {
            page = 0;
            setScore();
            getScores();
        }
    } else if(QRect(pos.x(),pos.y(),1,1).intersects(QRect(190,473,160,160))) { //hardcore
        if(page!=1) {
            page = 1;
            setScore();
            getScores();
        }
    } else if(QRect(pos.x(),pos.y(),1,1).intersects(QRect(350,473,160,160))) { //cave
        if(page!=2) {
            page = 2;
            setScore();
            getScores();
        }
    } else if(QRect(pos.x(),pos.y(),1,1).intersects(QRect(510,473,160,160))) { //space
        if(page!=3) {
            page = 3;
            setScore();
            getScores();
        }
    } else if(QRect(pos.x(),pos.y(),1,1).intersects(QRect(670,473,160,160))) {
        if(page!=4) {
            page = 4;
            setScore();
            getScores();
        }
    }
    if(QRect(pos.x(),pos.y(),1,1).intersects(QRect(500,1324,560,130))) {
        QMessageBox boxMsg;
        boxMsg.setWindowTitle("Info");
        boxMsg.setText(transl->getText_CN().text);
        boxMsg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        boxMsg.setDefaultButton(QMessageBox::No);
        int ret = boxMsg.exec();
        if(ret==QMessageBox::Yes) {
            socket->connectToHost("flatterfogel.ddns.net",38900);
            socket->waitForConnected(1000);
            if(socket->state()==QTcpSocket::ConnectedState) {
                QString data = ".2#"+name+"#~";
                socket->write(data.toUtf8());
                socket->waitForBytesWritten(2000);
            }
            socket->close();
            wasConnected = false;
            this->name = "";
            this->first = "0";
            emit write(0);
            this->active = false;
        }
    }
}

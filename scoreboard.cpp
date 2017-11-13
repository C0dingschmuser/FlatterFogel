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
    active = false;
    socket = new QTcpSocket();
    font = f;
    first="0";
    connect(socket,SIGNAL(readyRead()),this,SLOT(on_tcpRecv()));
}

void Scoreboard::draw(QPainter &painter,int highscore)
{
    painter.drawPixmap(scoreX+20,460,1040,1000,bg);
    QFont f = font;
    f.setPixelSize(56);
    painter.setFont(f);
    painter.setPen(Qt::white);
    int own = -1;
    for(int i=0;i<players.size();i++) {
        QString name = players[i].split("#").at(0);
        QString score = players[i].split("#").at(1);
        if(name==this->name&&score.toInt()==highscore&&own==-1) {
            own = i;
        }
        if(own==i) {
            painter.setPen(Qt::red);
        } else {
            painter.setPen(Qt::white);
        }
        painter.drawText(scoreX+50,550+(i*60),name);
        painter.drawText(scoreX+850,550+(i*60),score);
        int scoreI = score.toInt();
        int medal;
        if(scoreI>=175) {
            medal = 3;
        } else if(scoreI>=100) {
            medal = 2;
        } else if(scoreI>=60) {
            medal = 1;
        } else if(scoreI>=30) {
            medal = 0;
        }
        painter.drawPixmap(scoreX+790,490+(i*60),55,55,medals[medal]);
    }
    if(own==-1) {
        painter.setPen(Qt::red);
        painter.drawText(scoreX+50,550+10*60,name);
        painter.drawText(scoreX+850,550+10*60,QString::number(highscore));
    }
    painter.drawPixmap(scoreX+24,1324,300,130,btnPx);
    painter.drawPixmap(scoreX+500,1324,560,130,btnPx);
    painter.setPen(QColor(0,143,255));
    Text t = transl->getBtn_Scoreboard_Back();
    f.setPixelSize(t.size);
    painter.setFont(f);
    painter.drawText(QPoint(scoreX+t.pos.x(),t.pos.y()),t.text);
    t = transl->getBtn_Scoreboard_Change();
    f.setPixelSize(t.size);
    painter.setFont(f);
    painter.drawText(QPoint(scoreX+t.pos.x(),t.pos.y()),t.text);
}

void Scoreboard::setScore(int score)
{
    socket->connectToHost("37.120.177.121",38900);
    socket->waitForConnected(1000);
    if(socket->state()==QTcpSocket::ConnectedState) {
        QString data = ".0#"+name+"#"+QString::number(score)+"#"+first+"#~";
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
        emit write();
        wasConnected = true;
    } else {
        wasConnected = false;
        emit connFail();
    }
    socket->close();
}

void Scoreboard::getScores()
{
    if(!wasConnected) return;
    socket->connectToHost("37.120.177.121",38900);
    socket->waitForConnected(2000);
    if(socket->state()==QTcpSocket::ConnectedState) {
        QString data = ".1#"+name+"#~";
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
    } else {

    }
    socket->close();
}

void Scoreboard::mpress(QPoint pos)
{
    if(scoreX!=0) return;
    if(QRect(pos.x(),pos.y(),1,1).intersects(QRect(24,1324,300,130))) {
        emit back();
    }
    if(QRect(pos.x(),pos.y(),1,1).intersects(QRect(500,1324,560,130))) {
        socket->connectToHost("37.120.177.121",38900);
        socket->waitForConnected(1000);
        if(socket->state()==QTcpSocket::ConnectedState) {
            QString data = ".2#"+name+"#~";
            socket->write(data.toUtf8());
            socket->waitForBytesWritten(2000);
        } else {
            emit connFail();
            return;
        }
        socket->close();
        wasConnected = false;
        this->name = "";
        this->first = "0";
        emit write();
        this->active = false;
    }
}

#include "scoreboard.h"

void Scoreboard::on_tcpRecv()
{

}

Scoreboard::Scoreboard(QPixmap bg, QPixmap btnPx, QFont f, Translation *transl, QObject *parent) : QObject(parent)
{
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
    painter.drawPixmap(70,460,940,1000,bg);
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
        painter.drawText(100,550+(i*60),name);
        painter.drawText(790,550+(i*60),score);
    }
    if(own==-1) {
        painter.setPen(Qt::red);
        painter.drawText(100,550+10*60,name);
        painter.drawText(790,550+10*60,QString::number(highscore));
    }
    painter.drawPixmap(104,1324,300,130,btnPx);
    Text t = transl->getBtn_Scoreboard_Back();
    f.setPixelSize(t.size);
    painter.setFont(f);
    painter.drawText(t.pos,t.text);
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
                emit wrongName();
            }
        }
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
                players.append(split[i]+"#"+split[i+1]);
            }
        }
    } else {

    }
    socket->close();
}

void Scoreboard::mpress(QPoint pos)
{
    if(QRect(pos.x(),pos.y(),1,1).intersects(QRect(104,1324,300,130))) {
        this->active = false;
    }
}

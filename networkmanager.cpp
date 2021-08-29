#include "networkmanager.h"

void NetworkManager::on_finished(QNetworkReply *reply)
{ //Abfrage fertig
    QByteArray rawResponse = reply->readAll();
    QString response = QString(rawResponse);

#ifdef Q_OS_WIN
    qDebug() << "NRESPONSE " << response;
#endif

    running = false;

    switch(type) {
    case RequestCodes::GetPost:
        emit StatusDone(response);
        break;
    case RequestCodes::SetScore:
        emit SetScoreDone(response);
        break;
    case RequestCodes::GetScore:
        emit GetScoreDone(response);
        break;
    case RequestCodes::ChangeName:
        emit ChangeNameDone(response);
        break;
    case RequestCodes::DSGVO:
        emit DSGVODone(response);
        break;
    }
}

NetworkManager::NetworkManager(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(on_finished(QNetworkReply*)));

    mainUrl = QUrl("https://bruh.games/api/ff1/server.php");
}

void NetworkManager::PostData(QUrlQuery data, RequestCodes type)
{ //Post
    //qDebug() << "RUNNING " << running;

    if(running) return;

    //disconnect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(on_finished(QNetworkReply*)));
    //delete manager;



    //manager = new QNetworkAccessManager(this);

    //connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(on_finished(QNetworkReply*)));

    running = true;

    if(userAuth.length() > 0) {
        data.addQueryItem("k", userAuth);
    }

    this->type = type;

    QNetworkRequest request(mainUrl);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QByteArray byteData;
    byteData.append(data.toString());

    manager->post(request, byteData);
}

void NetworkManager::SetAuth(QString auth, bool save)
{
    userAuth = auth;

    if(save) {
        emit AuthSave(userAuth);
    }
}

QString NetworkManager::GetAuth()
{
    return userAuth;
}

#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>

enum class RequestCodes {
    GetPost,
    SetScore,
    GetScore,
    ChangeName,
    Custom,
    DSGVO,
};

class NetworkManager : public QObject
{
    Q_OBJECT

private:
    QNetworkAccessManager* manager;
    QUrl mainUrl;
    QString userAuth = "";
private slots:
    void on_finished(QNetworkReply *reply);
public:
    explicit NetworkManager(QObject *parent = nullptr);
    void PostData(QUrlQuery data, RequestCodes type);
    void SetAuth(QString auth, bool save);
    QString GetAuth();
    bool running = false;
    RequestCodes type;

signals:
    void AuthSave(QString auth);
    void StatusDone(QString response);
    void SetScoreDone(QString response);
    void GetScoreDone(QString response);
    void ChangeNameDone(QString response);
    void DSGVODone(QString response);
};

#endif // NETWORKMANAGER_H

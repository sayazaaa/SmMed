#ifndef NETCLIENT_H
#define NETCLIENT_H

#include <QObject>
#include <QSharedPointer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>

class NetClient : QObject {
    Q_OBJECT
private:
    QSharedPointer<QNetworkAccessManager> manager;
public:
    NetClient();

    void send_request(const QUrl &url);
signals:
    void received_json(const QJsonObject &json);

private slots:
    void handle_reply_json();
};

#endif // NETCLIENT_H

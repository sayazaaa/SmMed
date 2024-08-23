#ifndef NETCLIENT_H
#define NETCLIENT_H

#include <QObject>
#include <QSharedPointer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>

class NetClient : public QObject {
    Q_OBJECT
private:
    QSharedPointer<QNetworkAccessManager> manager;
public:
    NetClient();

    void send_get_request
        (const QUrl &url) const;
    void send_post_request
        (const QUrl &url, const QJsonObject &json) const;
    void send_put_request
        (const QUrl &url,const QJsonObject &json) const;
    void send_delete_request
        (const QUrl &url) const;
signals:
    void received_json(const QJsonObject &json);

private slots:
    void handle_reply_json();
};

#endif // NETCLIENT_H

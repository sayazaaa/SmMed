#ifndef NETCLIENT_H
#define NETCLIENT_H

#include <QObject>
#include <QSharedPointer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTcpSocket>
#include <QDialog>
#include <QMessageBox>
#include "messages.h"
#include "apikey.h"

#define SERVER_URL "http://62.234.161.235:8080"

class NetClient : public QObject {
    Q_OBJECT
private:
    QSharedPointer<QNetworkAccessManager> manager;
    QSharedPointer<QTcpSocket> socket;
public:
    NetClient();
    static NetClient& getInstance() {
        static NetClient instance;
        return instance;
    }

    void send_get_request
    (const QUrl& url) const;
    void send_post_request
    (const QUrl& url, const QJsonObject& json) const;
    void send_put_request
    (const QUrl& url, const QJsonObject& json) const;
    void send_delete_request
    (const QUrl& url) const;
    void send_socket_apikey_request(QString apikey) const;

    void send_socket_request(Message& msg,std::function<void(bool)> callback) const;
signals:
    void received_json(const QJsonObject& json);
    void write_msg(std::function<void(bool)> callback) const;
    void received_msg(QSharedPointer<Message> msg);

private slots:
    void handle_reply_json();
    void handle_socket_read();
};

#endif // NETCLIENT_H

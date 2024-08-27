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

    void send_socket_request(QString msg) const;
    void send_socket_request(QByteArray msg) const;
signals:
    void received_json(const QJsonObject& json);

private slots:
    void handle_reply_json();
};

#endif // NETCLIENT_H

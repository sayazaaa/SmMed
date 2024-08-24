#include "netclient.h"

#include <QDebug>
NetClient::NetClient() {
    manager = QSharedPointer<QNetworkAccessManager>::create();
}

void NetClient::send_get_request(const QUrl& url) const{
    QNetworkRequest request(url);
    QNetworkReply* reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &NetClient::handle_reply_json);
}

void NetClient::send_post_request(const QUrl& url, const QJsonObject& json) const{
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply* reply = manager->post(request, QJsonDocument(json).toJson());
    qDebug() << "sendpostrequest : " << url;
    connect(reply, &QNetworkReply::finished, this, &NetClient::handle_reply_json);
}

void NetClient::send_put_request(const QUrl& url, const QJsonObject& json) const{
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply* reply = manager->put(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, &NetClient::handle_reply_json);
}

void NetClient::send_delete_request(const QUrl& url) const{
    QNetworkRequest request(url);
    QNetworkReply* reply = manager->deleteResource(request);
    connect(reply, &QNetworkReply::finished, this, &NetClient::handle_reply_json);
}

// slot
void NetClient::handle_reply_json() {
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (reply) {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "handle reply json";
            QByteArray response = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
            if (jsonDoc.isObject()) {
                QJsonObject jsonObj = jsonDoc.object();
                emit received_json(jsonObj);
            }
        }
    }
}

#include "net_client.h"


NetClient::NetClient() {
    manager = QSharedPointer<QNetworkAccessManager>::create();
}

void NetClient::send_request(const QUrl& url) {
    QNetworkRequest request(url);
    QNetworkReply* reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &NetClient::handle_reply_json);
}

void NetClient::handle_reply_json() {
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (reply) {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
            if (jsonDoc.isObject()) {
                QJsonObject jsonObj = jsonDoc.object();
                emit received_json(jsonObj);
            }
        }
    }
}
#include "netclient.h"

#include <QDebug>
NetClient::NetClient() {
    manager = QSharedPointer<QNetworkAccessManager>::create();
    socket = QSharedPointer<QTcpSocket>::create();
    socket->connectToHost("localhost", 8080);

}

void NetClient::send_get_request(const QUrl& url) const {
    QNetworkRequest request(url);
    QNetworkReply* reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &NetClient::handle_reply_json);
}

void NetClient::send_post_request(const QUrl& url, const QJsonObject& json) const {
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Accept", "*/*");
    request.setRawHeader("Connection", "close");
    //request.setRawHeader("Host", "62.234.161.235:8080");
    qDebug() << "sendpostrequest : " << json;
    qDebug() << QJsonDocument(json).toJson();
    QNetworkReply* reply = manager->post(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, &NetClient::handle_reply_json);
    qDebug() << "sendpostrequest : " << url;
}

void NetClient::send_put_request(const QUrl& url, const QJsonObject& json) const {
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply* reply = manager->put(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, &NetClient::handle_reply_json);
}

void NetClient::send_delete_request(const QUrl& url) const {
    QNetworkRequest request(url);
    QNetworkReply* reply = manager->deleteResource(request);
    connect(reply, &QNetworkReply::finished, this, &NetClient::handle_reply_json);
}

void NetClient::send_socket_request(QString msg) const {
    socket->write(msg.toUtf8());
}

void NetClient::send_socket_request(QByteArray msg) const {
    socket->write(msg);
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
        else {
            qDebug() << reply->error();
            qDebug() << reply->errorString();

            QMessageBox msgBox;
            msgBox.setText("失败" + reply->errorString());
            msgBox.exec();
        }
    }
}

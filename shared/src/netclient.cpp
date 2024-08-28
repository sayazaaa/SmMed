#include "netclient.h"

#include <QDebug>
NetClient::NetClient() {
    manager = QSharedPointer<QNetworkAccessManager>::create();
    socket = QSharedPointer<QTcpSocket>::create();

    connect(socket.get(), &QTcpSocket::readyRead, this, &NetClient::handle_socket_read);
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

void NetClient::send_socket_request(Message& msg, std::function<void(bool)> callback) const{
    send_message(*socket, msg);
    emit write_msg(callback);
    connect(this, &NetClient::write_msg, this, [this, callback]() {
        callback(true);
    });
    
}

void NetClient::send_socket_apikey_request(QString apikey) const{

        socket->connectToHost("0.0.0.0", 8081);
        qDebug() << API_KEY;
        socket->write(API_KEY.toStdString().c_str());
        socket->write("\n");
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



void NetClient::handle_socket_read() {
    qDebug() << "socket read";
    QByteArray response = socket->readAll();
    qDebug() << "socket res:" <<response;
}

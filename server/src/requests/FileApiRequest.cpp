/**
 * SmMed
 * No description provided (generated by Openapi Generator https://github.com/openapitools/openapi-generator)
 *
 * The version of the OpenAPI document: 1.0.0
 *
 * NOTE: This class is auto generated by OpenAPI Generator (https://openapi-generator.tech).
 * https://openapi-generator.tech
 * Do not edit the class manually.
 */

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QDebug>

#include "Helpers.h"
#include "FileApiRequest.h"

namespace HttpServer {

    FileApiRequest::FileApiRequest(QHttpEngine::Socket* s, QSharedPointer<FileApiHandler> hdl) : QObject(s), socket(s), handler(hdl) {
        auto headers = s->headers();
        for (auto itr = headers.begin(); itr != headers.end(); itr++) {
            requestHeaders.insert(QString(itr.key()), QString(itr.value()));
        }
    }

    FileApiRequest::~FileApiRequest() {
        disconnect(this, nullptr, nullptr, nullptr);
        qDebug() << "FileApiRequest::~FileApiRequest()";
    }

    QMap<QString, QString>
        FileApiRequest::getRequestHeaders() const {
        return requestHeaders;
    }

    void FileApiRequest::setResponseHeaders(const QMultiMap<QString, QString>& headers) {
        for (auto itr = headers.begin(); itr != headers.end(); ++itr) {
            responseHeaders.insert(itr.key(), itr.value());
        }
    }


    QHttpEngine::Socket* FileApiRequest::getRawSocket() {
        return socket;
    }


    void FileApiRequest::fileGetRequest() {
        qDebug() << "/file";
        connect(this, &FileApiRequest::fileGet, handler.data(), &FileApiHandler::fileGet);


        QString uuid;
        if (socket->queryString().keys().contains("uuid")) {
            fromStringValue(socket->queryString().value("uuid"), uuid);
        }

        QString apikey;
        if (socket->queryString().keys().contains("apikey")) {
            fromStringValue(socket->queryString().value("apikey"), apikey);
        }



        emit fileGet(uuid, apikey);
    }


    void FileApiRequest::filePostRequest() {
        qDebug() << "/file";
        connect(this, &FileApiRequest::filePost, handler.data(), &FileApiHandler::filePost);


        QString name;
        if (socket->queryString().keys().contains("name")) {
            fromStringValue(socket->queryString().value("name"), name);
        }

        QString doctor_id;
        if (socket->queryString().keys().contains("doctor_id")) {
            fromStringValue(socket->queryString().value("doctor_id"), doctor_id);
        }

        QString patient_id;
        if (socket->queryString().keys().contains("patient_id")) {
            fromStringValue(socket->queryString().value("patient_id"), patient_id);
        }

        QString type;
        if (socket->queryString().keys().contains("type")) {
            fromStringValue(socket->queryString().value("type"), type);
        }

        QString apikey;
        if (socket->queryString().keys().contains("apikey")) {
            fromStringValue(socket->queryString().value("apikey"), apikey);
        }

        QString appointment_id;
        if (socket->queryString().keys().contains("appointment_id")) {
            fromStringValue(socket->queryString().value("appointment_id"), appointment_id);
        }


        connect(socket, &QHttpEngine::Socket::readChannelFinished, this, [name, doctor_id, patient_id, type, apikey, appointment_id, this]() {
            // // 检查是否有数据可读
            // qint64 bytesAvailable = socket->bytesAvailable();
            // qDebug() << "Bytes available to read:" << bytesAvailable;

            // // 读取并解析请求头
            // qint64 contentLength = 0;
            // contentLength = socket->contentLength();

            // qDebug() << "Content-Length:" << contentLength;

            // // 读取指定数量的字节
            // QByteArray bodyData;
            // while (bodyData.size() < contentLength) {
            //     if (socket->bytesAvailable() > 0) {
            //         bodyData.append(socket->read(contentLength - bodyData.size()));
            //         qDebug() << "Read bytes:" << bodyData.size();
            //     }
            //     else {
            //         socket->waitForReadyRead(100);
            //         qDebug() << "Wait for ready read";
            //     }
            //     QThread::msleep(1000);
            // }
            QByteArray bodyData = socket->readAll();

            qDebug() << "Read all bytes, size:" << bodyData.size();

            // 创建 HttpFileElement 并设置数据
            auto body = new HttpFileElement();
            body->bytearray = bodyData;

            // 发送信号
            emit filePost(name, doctor_id, patient_id, type, apikey, appointment_id, *body);
            });

        // HttpFileElement body;
        // // ::HttpServer::fromStringValue(QString(socket->readAll()), body);
        // body.bytearray = socket->readAll();



        // emit filePost(name, doctor_id, patient_id, type, apikey, appointment_id, body);
    }



    void FileApiRequest::fileGetResponse(const QByteArray& res) {
        writeResponseHeaders();
        // QJsonDocument resDoc(::HttpServer::toJsonValue(res).toObject());
        // socket->writeJson(resDoc);
        socket->write(res);
        connect(socket, &QIODevice::bytesWritten, this, [this](qint64 bytes) {
        qDebug() << "Bytes written:" << bytes;
        if (socket->bytesToWrite() == 0) {
            qDebug() << "Write complete";
            if (socket->isOpen()) {
                socket->close();
            }
        }
    });
    }

    void FileApiRequest::filePostResponse(const Inline_response_200_3& res) {
        writeResponseHeaders();
        QJsonDocument resDoc(::HttpServer::toJsonValue(res).toObject());
        socket->writeJson(resDoc);
        if (socket->isOpen()) {
            socket->close();
        }
    }


    void FileApiRequest::fileGetError(const Object& res, QNetworkReply::NetworkError error_type, QString& error_str) {
        Q_UNUSED(error_type);
        Q_UNUSED(res);
        socket->writeError(404, error_str.toStdString().c_str());
        if (socket->isOpen()) {
            socket->close();
        }
    }

    void FileApiRequest::filePostError(const Inline_response_200_3& res, QNetworkReply::NetworkError error_type, QString& error_str) {
        Q_UNUSED(error_type);
        Q_UNUSED(res);
        socket->writeError(404, error_str.toStdString().c_str());
        if (socket->isOpen()) {
            socket->close();
        }
    }


    void FileApiRequest::sendCustomResponse(QByteArray& res, QNetworkReply::NetworkError error_type) {
        Q_UNUSED(error_type); // TODO
        socket->write(res);
        if (socket->isOpen()) {
            socket->close();
        }
    }

    void FileApiRequest::sendCustomResponse(QIODevice* res, QNetworkReply::NetworkError error_type) {
        Q_UNUSED(error_type);  // TODO
        socket->write(res->readAll());
        if (socket->isOpen()) {
            socket->close();
        }
    }

}

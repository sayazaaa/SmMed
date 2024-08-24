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

#ifndef _FileApiRequest_H
#define _FileApiRequest_H

#include <QObject>
#include <QStringList>
#include <QMultiMap>
#include <QNetworkReply>
#include <QSharedPointer>

#include <qhttpengine/socket.h>
#include "HttpFileElement.h"
#include "Inline_response_200_10.h"
#include "Inline_response_200_9.h"
#include "Object.h"
#include <QString>
#include "FileApiHandler.h"

namespace HttpServer {

class FileApiRequest : public QObject
{
    Q_OBJECT

public:
    FileApiRequest(QHttpEngine::Socket *s, QSharedPointer<FileApiHandler> handler);
    virtual ~FileApiRequest();

    void fileDocterGetRequest();
    void fileGetRequest();
    void filePatientGetRequest();
    void filePostRequest();
    

    void fileDocterGetResponse(const Inline_response_200_10& res);
    void fileGetResponse(const Object& res);
    void filePatientGetResponse(const Inline_response_200_10& res);
    void filePostResponse(const Inline_response_200_9& res);
    

    void fileDocterGetError(const Inline_response_200_10& res, QNetworkReply::NetworkError error_type, QString& error_str);
    void fileGetError(const Object& res, QNetworkReply::NetworkError error_type, QString& error_str);
    void filePatientGetError(const Inline_response_200_10& res, QNetworkReply::NetworkError error_type, QString& error_str);
    void filePostError(const Inline_response_200_9& res, QNetworkReply::NetworkError error_type, QString& error_str);
    

    void sendCustomResponse(QByteArray & res, QNetworkReply::NetworkError error_type);

    void sendCustomResponse(QIODevice *res, QNetworkReply::NetworkError error_type);

    QMap<QString, QString> getRequestHeaders() const;

    QHttpEngine::Socket* getRawSocket();

    void setResponseHeaders(const QMultiMap<QString,QString>& headers);

signals:
    void fileDocterGet(QString doctor_id, qint32 type);
    void fileGet(qint32 id, QString doctor_id, qint32 patient_id);
    void filePatientGet(qint32 patient_id, qint32 type);
    void filePost(qint32 id, QString name, QString doctor_id, QString patient_id, qint32 type, HttpFileElement body);
    

private:
    QMap<QString, QString> requestHeaders;
    QMap<QString, QString> responseHeaders;
    QHttpEngine::Socket  *socket;
    QSharedPointer<FileApiHandler> handler;

    inline void writeResponseHeaders(){
        QHttpEngine::Socket::HeaderMap resHeaders;
        for(auto itr = responseHeaders.begin(); itr != responseHeaders.end(); ++itr) {
            resHeaders.insert(itr.key().toUtf8(), itr.value().toUtf8());
        }
        socket->setHeaders(resHeaders);
        socket->writeHeaders();
    }
};

}

#endif // _FileApiRequest_H

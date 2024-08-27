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

#ifndef _DocterApiRequest_H
#define _DocterApiRequest_H

#include <QObject>
#include <QStringList>
#include <QMultiMap>
#include <QNetworkReply>
#include <QSharedPointer>

#include <qhttpengine/socket.h>
#include "Inline_object_1.h"
#include "Inline_response_200_2.h"
#include "Object.h"
#include <QString>
#include "DocterApiHandler.h"

namespace HttpServer {

class DocterApiRequest : public QObject
{
    Q_OBJECT

public:
    DocterApiRequest(QHttpEngine::Socket *s, QSharedPointer<DocterApiHandler> handler);
    virtual ~DocterApiRequest();

    void doctorPostRequest();
    

    void doctorPostResponse(const Inline_response_200_2& res);
    

    void doctorPostError(const Inline_response_200_2& res, QNetworkReply::NetworkError error_type, QString& error_str);
    

    void sendCustomResponse(QByteArray & res, QNetworkReply::NetworkError error_type);

    void sendCustomResponse(QIODevice *res, QNetworkReply::NetworkError error_type);

    QMap<QString, QString> getRequestHeaders() const;

    QHttpEngine::Socket* getRawSocket();

    void setResponseHeaders(const QMultiMap<QString,QString>& headers);

signals:
    void doctorPost(QString apikey, Inline_object_1 inline_object_1);
    

private:
    QMap<QString, QString> requestHeaders;
    QMap<QString, QString> responseHeaders;
    QHttpEngine::Socket  *socket;
    QSharedPointer<DocterApiHandler> handler;

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

#endif // _DocterApiRequest_H

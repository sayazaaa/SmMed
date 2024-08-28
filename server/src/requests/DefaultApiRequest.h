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

#ifndef _DefaultApiRequest_H
#define _DefaultApiRequest_H

#include <QObject>
#include <QStringList>
#include <QMultiMap>
#include <QNetworkReply>
#include <QSharedPointer>

#include <qhttpengine/socket.h>
#include "Inline_response_200.h"
#include "Inline_response_404.h"
#include "Object.h"
#include <QString>
#include "DefaultApiHandler.h"

namespace HttpServer {

class DefaultApiRequest : public QObject
{
    Q_OBJECT

public:
    DefaultApiRequest(QHttpEngine::Socket *s, QSharedPointer<DefaultApiHandler> handler);
    virtual ~DefaultApiRequest();

    void loginPostRequest();
    void sqlGetRequest();
    

    void loginPostResponse(const Inline_response_200& res);
    void sqlGetResponse(const QJsonDocument& jsondoc);
    

    void loginPostError(const Inline_response_200& res, QNetworkReply::NetworkError error_type, QString& error_str);
    void sqlGetError(const Object& res, QNetworkReply::NetworkError error_type, QString& error_str);
    

    void sendCustomResponse(QByteArray & res, QNetworkReply::NetworkError error_type);

    void sendCustomResponse(QIODevice *res, QNetworkReply::NetworkError error_type);

    QMap<QString, QString> getRequestHeaders() const;

    QHttpEngine::Socket* getRawSocket();

    void setResponseHeaders(const QMultiMap<QString,QString>& headers);

signals:
    void loginPost(QString id, QString password, bool usertype, QString apikey, Object body);
    void sqlGet(QString sql, QString apikey, QString id, bool usertype);
    

private:
    QMap<QString, QString> requestHeaders;
    QMap<QString, QString> responseHeaders;
    QHttpEngine::Socket  *socket;
    QSharedPointer<DefaultApiHandler> handler;

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

#endif // _DefaultApiRequest_H

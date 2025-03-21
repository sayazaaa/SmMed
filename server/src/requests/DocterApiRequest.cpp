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
#include "DocterApiRequest.h"

namespace HttpServer {

DocterApiRequest::DocterApiRequest(QHttpEngine::Socket *s, QSharedPointer<DocterApiHandler> hdl) : QObject(s), socket(s), handler(hdl) {
    auto headers = s->headers();
    for(auto itr = headers.begin(); itr != headers.end(); itr++) {
        requestHeaders.insert(QString(itr.key()), QString(itr.value()));
    }
}

DocterApiRequest::~DocterApiRequest(){
    disconnect(this, nullptr, nullptr, nullptr);
    qDebug() << "DocterApiRequest::~DocterApiRequest()";
}

QMap<QString, QString>
DocterApiRequest::getRequestHeaders() const {
    return requestHeaders;
}

void DocterApiRequest::setResponseHeaders(const QMultiMap<QString, QString>& headers){
    for(auto itr = headers.begin(); itr != headers.end(); ++itr) {
        responseHeaders.insert(itr.key(), itr.value());
    }
}


QHttpEngine::Socket* DocterApiRequest::getRawSocket(){
    return socket;
}


void DocterApiRequest::doctorPostRequest(){
    qDebug() << "/doctor";
    connect(this, &DocterApiRequest::doctorPost, handler.data(), &DocterApiHandler::doctorPost);

    
    QString apikey;
    if(socket->queryString().keys().contains("apikey")){
        fromStringValue(socket->queryString().value("apikey"), apikey);
    }
    

    connect(socket,&QHttpEngine::Socket::readChannelFinished,this,[=](){
        QJsonDocument doc;
        socket->readJson(doc);
        QJsonObject obj = doc.object();
        Inline_object_1 inline_object_1;
        ::HttpServer::fromJsonValue(inline_object_1, obj);


        emit doctorPost(apikey, inline_object_1);
    });

}



void DocterApiRequest::doctorPostResponse(const Inline_response_200_2& res){
    writeResponseHeaders();
    QJsonDocument resDoc(::HttpServer::toJsonValue(res).toObject());
    socket->writeJson(resDoc);
    if(socket->isOpen()){
        socket->close();
    }
}


void DocterApiRequest::doctorPostError(const Inline_response_200_2& res, QNetworkReply::NetworkError error_type, QString& error_str){
    Q_UNUSED(error_type);
    Q_UNUSED(res);
    socket->writeError(404,error_str.toStdString().c_str());
    if(socket->isOpen()){
        socket->close();
    }
}


void DocterApiRequest::sendCustomResponse(QByteArray & res, QNetworkReply::NetworkError error_type){
    Q_UNUSED(error_type); // TODO
    socket->write(res);
    if(socket->isOpen()){
        socket->close();
    }    
}

void DocterApiRequest::sendCustomResponse(QIODevice *res, QNetworkReply::NetworkError error_type){
    Q_UNUSED(error_type);  // TODO
    socket->write(res->readAll());
    if(socket->isOpen()){
        socket->close();
    }
}

}

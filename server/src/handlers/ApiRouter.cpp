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


#include "ApiRouter.h"
#include "DefaultApiRequest.h"
#include "DocterApiRequest.h"
#include "FileApiRequest.h"
#include "UserApiRequest.h"


namespace HttpServer {

ApiRouter::ApiRouter() {
    createApiHandlers();
}

ApiRouter::~ApiRouter(){

}

void ApiRouter::createApiHandlers() { 
    mDefaultApiHandler = QSharedPointer<DefaultApiHandler>::create();
    mDocterApiHandler = QSharedPointer<DocterApiHandler>::create();
    mFileApiHandler = QSharedPointer<FileApiHandler>::create();
    mUserApiHandler = QSharedPointer<UserApiHandler>::create();
}


void ApiRouter::setDefaultApiHandler(QSharedPointer<DefaultApiHandler> handler){
    mDefaultApiHandler = handler;
}
void ApiRouter::setDocterApiHandler(QSharedPointer<DocterApiHandler> handler){
    mDocterApiHandler = handler;
}
void ApiRouter::setFileApiHandler(QSharedPointer<FileApiHandler> handler){
    mFileApiHandler = handler;
}
void ApiRouter::setUserApiHandler(QSharedPointer<UserApiHandler> handler){
    mUserApiHandler = handler;
}

void ApiRouter::setUpRoutes() {
    
    Routes.insert(QString("%1 %2").arg("POST").arg("/login").toLower(), [this](QHttpEngine::Socket *socket) {
            auto reqObj = new DefaultApiRequest(socket, mDefaultApiHandler);
            reqObj->loginPostRequest();
    });
    Routes.insert(QString("%1 %2").arg("GET").arg("/sql").toLower(), [this](QHttpEngine::Socket *socket) {
            auto reqObj = new DefaultApiRequest(socket, mDefaultApiHandler);
            reqObj->sqlGetRequest();
    });
    Routes.insert(QString("%1 %2").arg("POST").arg("/doctor").toLower(), [this](QHttpEngine::Socket *socket) {
            auto reqObj = new DocterApiRequest(socket, mDocterApiHandler);
            reqObj->doctorPostRequest();
    });
    Routes.insert(QString("%1 %2").arg("GET").arg("/file").toLower(), [this](QHttpEngine::Socket *socket) {
            auto reqObj = new FileApiRequest(socket, mFileApiHandler);
            reqObj->fileGetRequest();
    });
    Routes.insert(QString("%1 %2").arg("POST").arg("/file").toLower(), [this](QHttpEngine::Socket *socket) {
            auto reqObj = new FileApiRequest(socket, mFileApiHandler);
            reqObj->filePostRequest();
    });
    Routes.insert(QString("%1 %2").arg("POST").arg("/user").toLower(), [this](QHttpEngine::Socket *socket) {
            auto reqObj = new UserApiRequest(socket, mUserApiHandler);
            reqObj->userPostRequest();
    });
}

void ApiRouter::processRequest(QHttpEngine::Socket *socket){
    qDebug() << "processing...";
    if( handleRequest(socket) ){
        return;
    }
    if( handleRequestAndExtractPathParam(socket) ){
        return;
    }
    qDebug() << "closing";
    socket->setStatusCode(QHttpEngine::Socket::NotFound);
    if(socket->isOpen()){
        socket->writeHeaders();
        socket->close();
    }
}

bool ApiRouter::handleRequest(QHttpEngine::Socket *socket){
    auto reqPath = QString("%1 %2").arg(fromQHttpEngineMethod(socket->method())).arg(socket->path()).toLower();
    if ( Routes.contains(reqPath) ) {
        Routes.value(reqPath).operator()(socket);
        return true;
    }
    return false;
}

bool ApiRouter::handleRequestAndExtractPathParam(QHttpEngine::Socket *socket){
    auto reqPath = QString("%1 %2").arg(fromQHttpEngineMethod(socket->method())).arg(socket->path()).toLower();
    return false;
}

}

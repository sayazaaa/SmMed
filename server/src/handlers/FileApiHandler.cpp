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

#include "FileApiHandler.h"
#include "FileApiRequest.h"

namespace HttpServer {

FileApiHandler::FileApiHandler(){

}

FileApiHandler::~FileApiHandler(){

}

void FileApiHandler::fileDocterGet(QString doctor_id, qint32 type) {
    Q_UNUSED(doctor_id);
    Q_UNUSED(type);
    auto reqObj = qobject_cast<FileApiRequest*>(sender());
    if( reqObj != nullptr ) 
    { 
        Inline_response_200_10 res;
        reqObj->fileDocterGetResponse(res);
    }    
}
void FileApiHandler::fileGet(qint32 id, QString doctor_id, qint32 patient_id) {
    Q_UNUSED(id);
    Q_UNUSED(doctor_id);
    Q_UNUSED(patient_id);
    auto reqObj = qobject_cast<FileApiRequest*>(sender());
    if( reqObj != nullptr ) 
    { 
        Object res;
        reqObj->fileGetResponse(res);
    }    
}
void FileApiHandler::filePatientGet(qint32 patient_id, qint32 type) {
    Q_UNUSED(patient_id);
    Q_UNUSED(type);
    auto reqObj = qobject_cast<FileApiRequest*>(sender());
    if( reqObj != nullptr ) 
    { 
        Inline_response_200_10 res;
        reqObj->filePatientGetResponse(res);
    }    
}
void FileApiHandler::filePost(qint32 id, QString name, QString doctor_id, QString patient_id, qint32 type, HttpFileElement body) {
    Q_UNUSED(id);
    Q_UNUSED(name);
    Q_UNUSED(doctor_id);
    Q_UNUSED(patient_id);
    Q_UNUSED(type);
    Q_UNUSED(body);
    auto reqObj = qobject_cast<FileApiRequest*>(sender());
    if( reqObj != nullptr ) 
    { 
        Inline_response_200_9 res;
        reqObj->filePostResponse(res);
    }    
}


}

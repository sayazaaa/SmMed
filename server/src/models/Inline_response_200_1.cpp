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

#include "Inline_response_200_1.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QObject>

#include "Helpers.h"

namespace HttpServer {

Inline_response_200_1::Inline_response_200_1(QString json) {
    this->initializeModel();
    this->fromJson(json);
}

Inline_response_200_1::Inline_response_200_1() {
    this->initializeModel();
}

Inline_response_200_1::~Inline_response_200_1() {}

void Inline_response_200_1::initializeModel() {

    m_apikey_isSet = false;
    m_apikey_isValid = false;

    m_id_isSet = false;
    m_id_isValid = false;

    m_date_isSet = false;
    m_date_isValid = false;
}

void Inline_response_200_1::fromJson(QString jsonString) {
    QByteArray array(jsonString.toStdString().c_str());
    QJsonDocument doc = QJsonDocument::fromJson(array);
    QJsonObject jsonObject = doc.object();
    this->fromJsonObject(jsonObject);
}

void Inline_response_200_1::fromJsonObject(QJsonObject json) {

    m_apikey_isValid = ::HttpServer::fromJsonValue(apikey, json[QString("apikey")]);
    m_apikey_isSet = !json[QString("apikey")].isNull() && m_apikey_isValid;

    m_id_isValid = ::HttpServer::fromJsonValue(id, json[QString("id")]);
    m_id_isSet = !json[QString("id")].isNull() && m_id_isValid;

    m_date_isValid = ::HttpServer::fromJsonValue(date, json[QString("date")]);
    m_date_isSet = !json[QString("date")].isNull() && m_date_isValid;
}

QString Inline_response_200_1::asJson() const {
    QJsonObject obj = this->asJsonObject();
    QJsonDocument doc(obj);
    QByteArray bytes = doc.toJson();
    return QString(bytes);
}

QJsonObject Inline_response_200_1::asJsonObject() const {
    QJsonObject obj;
    if (m_apikey_isSet) {
        obj.insert(QString("apikey"), ::HttpServer::toJsonValue(apikey));
    }
    if (m_id_isSet) {
        obj.insert(QString("id"), ::HttpServer::toJsonValue(id));
    }
    if (m_date_isSet) {
        obj.insert(QString("date"), ::HttpServer::toJsonValue(date));
    }
    return obj;
}

QString Inline_response_200_1::getApikey() const {
    return apikey;
}
void Inline_response_200_1::setApikey(const QString &apikey) {
    this->apikey = apikey;
    this->m_apikey_isSet = true;
}

bool Inline_response_200_1::is_apikey_Set() const{
    return m_apikey_isSet;
}

bool Inline_response_200_1::is_apikey_Valid() const{
    return m_apikey_isValid;
}

QString Inline_response_200_1::getId() const {
    return id;
}
void Inline_response_200_1::setId(const QString &id) {
    this->id = id;
    this->m_id_isSet = true;
}

bool Inline_response_200_1::is_id_Set() const{
    return m_id_isSet;
}

bool Inline_response_200_1::is_id_Valid() const{
    return m_id_isValid;
}

QString Inline_response_200_1::getDate() const {
    return date;
}
void Inline_response_200_1::setDate(const QString &date) {
    this->date = date;
    this->m_date_isSet = true;
}

bool Inline_response_200_1::is_date_Set() const{
    return m_date_isSet;
}

bool Inline_response_200_1::is_date_Valid() const{
    return m_date_isValid;
}

bool Inline_response_200_1::isSet() const {
    bool isObjectUpdated = false;
    do {
        if (m_apikey_isSet) {
            isObjectUpdated = true;
            break;
        }

        if (m_id_isSet) {
            isObjectUpdated = true;
            break;
        }

        if (m_date_isSet) {
            isObjectUpdated = true;
            break;
        }
    } while (false);
    return isObjectUpdated;
}

bool Inline_response_200_1::isValid() const {
    // only required properties are required for the object to be considered valid
    return m_apikey_isValid && m_id_isValid && m_date_isValid && true;
}

} // namespace HttpServer

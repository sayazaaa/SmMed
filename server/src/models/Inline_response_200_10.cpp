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

#include "Inline_response_200_10.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QObject>

#include "Helpers.h"

namespace HttpServer {

Inline_response_200_10::Inline_response_200_10(QString json) {
    this->initializeModel();
    this->fromJson(json);
}

Inline_response_200_10::Inline_response_200_10() {
    this->initializeModel();
}

Inline_response_200_10::~Inline_response_200_10() {}

void Inline_response_200_10::initializeModel() {

    m_total_isSet = false;
    m_total_isValid = false;

    m_data_isSet = false;
    m_data_isValid = false;
}

void Inline_response_200_10::fromJson(QString jsonString) {
    QByteArray array(jsonString.toStdString().c_str());
    QJsonDocument doc = QJsonDocument::fromJson(array);
    QJsonObject jsonObject = doc.object();
    this->fromJsonObject(jsonObject);
}

void Inline_response_200_10::fromJsonObject(QJsonObject json) {

    m_total_isValid = ::HttpServer::fromJsonValue(total, json[QString("total")]);
    m_total_isSet = !json[QString("total")].isNull() && m_total_isValid;

    m_data_isValid = ::HttpServer::fromJsonValue(data, json[QString("data")]);
    m_data_isSet = !json[QString("data")].isNull() && m_data_isValid;
}

QString Inline_response_200_10::asJson() const {
    QJsonObject obj = this->asJsonObject();
    QJsonDocument doc(obj);
    QByteArray bytes = doc.toJson();
    return QString(bytes);
}

QJsonObject Inline_response_200_10::asJsonObject() const {
    QJsonObject obj;
    if (m_total_isSet) {
        obj.insert(QString("total"), ::HttpServer::toJsonValue(total));
    }
    if (data.size() > 0) {
        obj.insert(QString("data"), ::HttpServer::toJsonValue(data));
    }
    return obj;
}

qint32 Inline_response_200_10::getTotal() const {
    return total;
}
void Inline_response_200_10::setTotal(const qint32 &total) {
    this->total = total;
    this->m_total_isSet = true;
}

bool Inline_response_200_10::is_total_Set() const{
    return m_total_isSet;
}

bool Inline_response_200_10::is_total_Valid() const{
    return m_total_isValid;
}

QList<Inline_response_200_10_data> Inline_response_200_10::getData() const {
    return data;
}
void Inline_response_200_10::setData(const QList<Inline_response_200_10_data> &data) {
    this->data = data;
    this->m_data_isSet = true;
}

bool Inline_response_200_10::is_data_Set() const{
    return m_data_isSet;
}

bool Inline_response_200_10::is_data_Valid() const{
    return m_data_isValid;
}

bool Inline_response_200_10::isSet() const {
    bool isObjectUpdated = false;
    do {
        if (m_total_isSet) {
            isObjectUpdated = true;
            break;
        }

        if (data.size() > 0) {
            isObjectUpdated = true;
            break;
        }
    } while (false);
    return isObjectUpdated;
}

bool Inline_response_200_10::isValid() const {
    // only required properties are required for the object to be considered valid
    return m_total_isValid && m_data_isValid && true;
}

} // namespace HttpServer

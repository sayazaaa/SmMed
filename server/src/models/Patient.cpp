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

#include "Patient.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QObject>

#include "Helpers.h"

namespace HttpServer {

Patient::Patient(QString json) {
    this->initializeModel();
    this->fromJson(json);
}

Patient::Patient() {
    this->initializeModel();
}

Patient::~Patient() {}

void Patient::initializeModel() {

    m_id_isSet = false;
    m_id_isValid = false;

    m_name_isSet = false;
    m_name_isValid = false;

    m_gender_isSet = false;
    m_gender_isValid = false;

    m_phone_isSet = false;
    m_phone_isValid = false;
}

void Patient::fromJson(QString jsonString) {
    QByteArray array(jsonString.toStdString().c_str());
    QJsonDocument doc = QJsonDocument::fromJson(array);
    QJsonObject jsonObject = doc.object();
    this->fromJsonObject(jsonObject);
}

void Patient::fromJsonObject(QJsonObject json) {

    m_id_isValid = ::HttpServer::fromJsonValue(id, json[QString("id")]);
    m_id_isSet = !json[QString("id")].isNull() && m_id_isValid;

    m_name_isValid = ::HttpServer::fromJsonValue(name, json[QString("name")]);
    m_name_isSet = !json[QString("name")].isNull() && m_name_isValid;

    m_gender_isValid = ::HttpServer::fromJsonValue(gender, json[QString("gender")]);
    m_gender_isSet = !json[QString("gender")].isNull() && m_gender_isValid;

    m_phone_isValid = ::HttpServer::fromJsonValue(phone, json[QString("phone")]);
    m_phone_isSet = !json[QString("phone")].isNull() && m_phone_isValid;
}

QString Patient::asJson() const {
    QJsonObject obj = this->asJsonObject();
    QJsonDocument doc(obj);
    QByteArray bytes = doc.toJson();
    return QString(bytes);
}

QJsonObject Patient::asJsonObject() const {
    QJsonObject obj;
    if (m_id_isSet) {
        obj.insert(QString("id"), ::HttpServer::toJsonValue(id));
    }
    if (m_name_isSet) {
        obj.insert(QString("name"), ::HttpServer::toJsonValue(name));
    }
    if (m_gender_isSet) {
        obj.insert(QString("gender"), ::HttpServer::toJsonValue(gender));
    }
    if (m_phone_isSet) {
        obj.insert(QString("phone"), ::HttpServer::toJsonValue(phone));
    }
    return obj;
}

QString Patient::getId() const {
    return id;
}
void Patient::setId(const QString &id) {
    this->id = id;
    this->m_id_isSet = true;
}

bool Patient::is_id_Set() const{
    return m_id_isSet;
}

bool Patient::is_id_Valid() const{
    return m_id_isValid;
}

QString Patient::getName() const {
    return name;
}
void Patient::setName(const QString &name) {
    this->name = name;
    this->m_name_isSet = true;
}

bool Patient::is_name_Set() const{
    return m_name_isSet;
}

bool Patient::is_name_Valid() const{
    return m_name_isValid;
}

QString Patient::getGender() const {
    return gender;
}
void Patient::setGender(const QString &gender) {
    this->gender = gender;
    this->m_gender_isSet = true;
}

bool Patient::is_gender_Set() const{
    return m_gender_isSet;
}

bool Patient::is_gender_Valid() const{
    return m_gender_isValid;
}

QString Patient::getPhone() const {
    return phone;
}
void Patient::setPhone(const QString &phone) {
    this->phone = phone;
    this->m_phone_isSet = true;
}

bool Patient::is_phone_Set() const{
    return m_phone_isSet;
}

bool Patient::is_phone_Valid() const{
    return m_phone_isValid;
}

bool Patient::isSet() const {
    bool isObjectUpdated = false;
    do {
        if (m_id_isSet) {
            isObjectUpdated = true;
            break;
        }

        if (m_name_isSet) {
            isObjectUpdated = true;
            break;
        }

        if (m_gender_isSet) {
            isObjectUpdated = true;
            break;
        }

        if (m_phone_isSet) {
            isObjectUpdated = true;
            break;
        }
    } while (false);
    return isObjectUpdated;
}

bool Patient::isValid() const {
    // only required properties are required for the object to be considered valid
    return m_id_isValid && m_name_isValid && m_gender_isValid && m_phone_isValid && true;
}

} // namespace HttpServer

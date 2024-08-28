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

#include "Inline_object.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QObject>

#include "Helpers.h"

namespace HttpServer {

Inline_object::Inline_object(QString json) {
    this->initializeModel();
    this->fromJson(json);
}

Inline_object::Inline_object() {
    this->initializeModel();
}

Inline_object::~Inline_object() {}

void Inline_object::initializeModel() {

    m_id_isSet = true;
    m_id_isValid = true;

    m_password_isSet = true;
    m_password_isValid = true;

    m_name_isSet = true;
    m_name_isValid = true;

    m_age_isSet = true;
    m_age_isValid = true;

    m_gender_isSet = true;
    m_gender_isValid = true;

    m_phone_isSet = true;
    m_phone_isValid = true;

    m_address_isSet = true;
    m_address_isValid = true;
}

void Inline_object::fromJson(QString jsonString) {
    QByteArray array(jsonString.toStdString().c_str());
    QJsonDocument doc = QJsonDocument::fromJson(array);
    QJsonObject jsonObject = doc.object();
    this->fromJsonObject(jsonObject);
}

void Inline_object::fromJsonObject(QJsonObject json) {

    m_id_isValid = ::HttpServer::fromJsonValue(id, json[QString("id")]);
    m_id_isSet = !json[QString("id")].isNull() && m_id_isValid;

    m_password_isValid = ::HttpServer::fromJsonValue(password, json[QString("password")]);
    m_password_isSet = !json[QString("password")].isNull() && m_password_isValid;

    m_name_isValid = ::HttpServer::fromJsonValue(name, json[QString("name")]);
    m_name_isSet = !json[QString("name")].isNull() && m_name_isValid;

    m_age_isValid = ::HttpServer::fromJsonValue(age, json[QString("age")]);
    m_age_isSet = !json[QString("age")].isNull() && m_age_isValid;

    m_gender_isValid = ::HttpServer::fromJsonValue(gender, json[QString("gender")]);
    m_gender_isSet = !json[QString("gender")].isNull() && m_gender_isValid;

    m_phone_isValid = ::HttpServer::fromJsonValue(phone, json[QString("phone")]);
    m_phone_isSet = !json[QString("phone")].isNull() && m_phone_isValid;

    m_address_isValid = ::HttpServer::fromJsonValue(address, json[QString("address")]);
    m_address_isSet = !json[QString("address")].isNull() && m_address_isValid;
}

QString Inline_object::asJson() const {
    QJsonObject obj = this->asJsonObject();
    QJsonDocument doc(obj);
    QByteArray bytes = doc.toJson();
    return QString(bytes);
}

QJsonObject Inline_object::asJsonObject() const {
    QJsonObject obj;
    if (m_id_isSet) {
        obj.insert(QString("id"), ::HttpServer::toJsonValue(id));
    }
    if (m_password_isSet) {
        obj.insert(QString("password"), ::HttpServer::toJsonValue(password));
    }
    if (m_name_isSet) {
        obj.insert(QString("name"), ::HttpServer::toJsonValue(name));
    }
    if (m_age_isSet) {
        obj.insert(QString("age"), ::HttpServer::toJsonValue(age));
    }
    if (m_gender_isSet) {
        obj.insert(QString("gender"), ::HttpServer::toJsonValue(gender));
    }
    if (m_phone_isSet) {
        obj.insert(QString("phone"), ::HttpServer::toJsonValue(phone));
    }
    if (m_address_isSet) {
        obj.insert(QString("address"), ::HttpServer::toJsonValue(address));
    }
    return obj;
}

QString Inline_object::getId() const {
    return id;
}
void Inline_object::setId(const QString &id) {
    this->id = id;
    this->m_id_isSet = true;
}

bool Inline_object::is_id_Set() const{
    return m_id_isSet;
}

bool Inline_object::is_id_Valid() const{
    return m_id_isValid;
}

QString Inline_object::getPassword() const {
    return password;
}
void Inline_object::setPassword(const QString &password) {
    this->password = password;
    this->m_password_isSet = true;
}

bool Inline_object::is_password_Set() const{
    return m_password_isSet;
}

bool Inline_object::is_password_Valid() const{
    return m_password_isValid;
}

QString Inline_object::getName() const {
    return name;
}
void Inline_object::setName(const QString &name) {
    this->name = name;
    this->m_name_isSet = true;
}

bool Inline_object::is_name_Set() const{
    return m_name_isSet;
}

bool Inline_object::is_name_Valid() const{
    return m_name_isValid;
}

QString Inline_object::getAge() const {
    return age;
}
void Inline_object::setAge(const QString &age) {
    this->age = age;
    this->m_age_isSet = true;
}

bool Inline_object::is_age_Set() const{
    return m_age_isSet;
}

bool Inline_object::is_age_Valid() const{
    return m_age_isValid;
}

QString Inline_object::getGender() const {
    return gender;
}
void Inline_object::setGender(const QString &gender) {
    this->gender = gender;
    this->m_gender_isSet = true;
}

bool Inline_object::is_gender_Set() const{
    return m_gender_isSet;
}

bool Inline_object::is_gender_Valid() const{
    return m_gender_isValid;
}

QString Inline_object::getPhone() const {
    return phone;
}
void Inline_object::setPhone(const QString &phone) {
    this->phone = phone;
    this->m_phone_isSet = true;
}

bool Inline_object::is_phone_Set() const{
    return m_phone_isSet;
}

bool Inline_object::is_phone_Valid() const{
    return m_phone_isValid;
}

QString Inline_object::getAddress() const {
    return address;
}
void Inline_object::setAddress(const QString &address) {
    this->address = address;
    this->m_address_isSet = true;
}

bool Inline_object::is_address_Set() const{
    return m_address_isSet;
}

bool Inline_object::is_address_Valid() const{
    return m_address_isValid;
}

bool Inline_object::isSet() const {
    bool isObjectUpdated = false;
    do {
        if (m_id_isSet) {
            isObjectUpdated = true;
            break;
        }

        if (m_password_isSet) {
            isObjectUpdated = true;
            break;
        }

        if (m_name_isSet) {
            isObjectUpdated = true;
            break;
        }

        if (m_age_isSet) {
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

        if (m_address_isSet) {
            isObjectUpdated = true;
            break;
        }
    } while (false);
    return isObjectUpdated;
}

bool Inline_object::isValid() const {
    // only required properties are required for the object to be considered valid
    return m_id_isValid && m_password_isValid && true;
}

} // namespace HttpServer

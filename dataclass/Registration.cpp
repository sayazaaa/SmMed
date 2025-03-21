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

#include "Registration.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QObject>

#include "Helpers.h"

namespace HttpServer {

Registration::Registration(QString json) {
    this->initializeModel();
    this->fromJson(json);
}

Registration::Registration() {
    this->initializeModel();
}

Registration::~Registration() {}

void Registration::initializeModel() {

    m_id_isSet = false;
    m_id_isValid = false;

    m_appoint_date_isSet = false;
    m_appoint_date_isValid = false;

    m_office_isSet = false;
    m_office_isValid = false;

    m_doctor_isSet = false;
    m_doctor_isValid = false;

    m_number_isSet = false;
    m_number_isValid = false;
}

void Registration::fromJson(QString jsonString) {
    QByteArray array(jsonString.toStdString().c_str());
    QJsonDocument doc = QJsonDocument::fromJson(array);
    QJsonObject jsonObject = doc.object();
    this->fromJsonObject(jsonObject);
}

void Registration::fromJsonObject(QJsonObject json) {

    m_id_isValid = ::HttpServer::fromJsonValue(id, json[QString("id")]);
    m_id_isSet = !json[QString("id")].isNull() && m_id_isValid;

    m_appoint_date_isValid = ::HttpServer::fromJsonValue(appoint_date, json[QString("appoint_date")]);
    m_appoint_date_isSet = !json[QString("appoint_date")].isNull() && m_appoint_date_isValid;

    m_office_isValid = ::HttpServer::fromJsonValue(office, json[QString("office")]);
    m_office_isSet = !json[QString("office")].isNull() && m_office_isValid;

    m_doctor_isValid = ::HttpServer::fromJsonValue(doctor, json[QString("doctor")]);
    m_doctor_isSet = !json[QString("doctor")].isNull() && m_doctor_isValid;

    m_number_isValid = ::HttpServer::fromJsonValue(number, json[QString("number")]);
    m_number_isSet = !json[QString("number")].isNull() && m_number_isValid;
}

QString Registration::asJson() const {
    QJsonObject obj = this->asJsonObject();
    QJsonDocument doc(obj);
    QByteArray bytes = doc.toJson();
    return QString(bytes);
}

QJsonObject Registration::asJsonObject() const {
    QJsonObject obj;
    if (m_id_isSet) {
        obj.insert(QString("id"), ::HttpServer::toJsonValue(id));
    }
    if (m_appoint_date_isSet) {
        obj.insert(QString("appoint_date"), ::HttpServer::toJsonValue(appoint_date));
    }
    if (m_office_isSet) {
        obj.insert(QString("office"), ::HttpServer::toJsonValue(office));
    }
    if (m_doctor_isSet) {
        obj.insert(QString("doctor"), ::HttpServer::toJsonValue(doctor));
    }
    if (m_number_isSet) {
        obj.insert(QString("number"), ::HttpServer::toJsonValue(number));
    }
    return obj;
}

qint32 Registration::getId() const {
    return id;
}
void Registration::setId(const qint32 &id) {
    this->id = id;
    this->m_id_isSet = true;
}

bool Registration::is_id_Set() const{
    return m_id_isSet;
}

bool Registration::is_id_Valid() const{
    return m_id_isValid;
}

QString Registration::getAppointDate() const {
    return appoint_date;
}
void Registration::setAppointDate(const QString &appoint_date) {
    this->appoint_date = appoint_date;
    this->m_appoint_date_isSet = true;
}

bool Registration::is_appoint_date_Set() const{
    return m_appoint_date_isSet;
}

bool Registration::is_appoint_date_Valid() const{
    return m_appoint_date_isValid;
}

QString Registration::getOffice() const {
    return office;
}
void Registration::setOffice(const QString &office) {
    this->office = office;
    this->m_office_isSet = true;
}

bool Registration::is_office_Set() const{
    return m_office_isSet;
}

bool Registration::is_office_Valid() const{
    return m_office_isValid;
}

QString Registration::getDoctor() const {
    return doctor;
}
void Registration::setDoctor(const QString &doctor) {
    this->doctor = doctor;
    this->m_doctor_isSet = true;
}

bool Registration::is_doctor_Set() const{
    return m_doctor_isSet;
}

bool Registration::is_doctor_Valid() const{
    return m_doctor_isValid;
}

qint32 Registration::getNumber() const {
    return number;
}
void Registration::setNumber(const qint32 &number) {
    this->number = number;
    this->m_number_isSet = true;
}

bool Registration::is_number_Set() const{
    return m_number_isSet;
}

bool Registration::is_number_Valid() const{
    return m_number_isValid;
}

bool Registration::isSet() const {
    bool isObjectUpdated = false;
    do {
        if (m_id_isSet) {
            isObjectUpdated = true;
            break;
        }

        if (m_appoint_date_isSet) {
            isObjectUpdated = true;
            break;
        }

        if (m_office_isSet) {
            isObjectUpdated = true;
            break;
        }

        if (m_doctor_isSet) {
            isObjectUpdated = true;
            break;
        }

        if (m_number_isSet) {
            isObjectUpdated = true;
            break;
        }
    } while (false);
    return isObjectUpdated;
}

bool Registration::isValid() const {
    // only required properties are required for the object to be considered valid
    return m_id_isValid && m_appoint_date_isValid && m_office_isValid && m_doctor_isValid && true;
}

} // namespace HttpServer

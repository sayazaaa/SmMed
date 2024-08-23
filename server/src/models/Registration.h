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

/*
 * Registration.h
 *
 * 
 */

#ifndef Registration_H
#define Registration_H

#include <QJsonObject>

#include <QString>

#include "Enum.h"
#include "Object.h"

namespace HttpServer {

class Registration : public Object {
public:
    Registration();
    Registration(QString json);
    ~Registration() override;

    QString asJson() const override;
    QJsonObject asJsonObject() const override;
    void fromJsonObject(QJsonObject json) override;
    void fromJson(QString jsonString) override;

    qint32 getId() const;
    void setId(const qint32 &id);
    bool is_id_Set() const;
    bool is_id_Valid() const;

    QString getAppointDate() const;
    void setAppointDate(const QString &appoint_date);
    bool is_appoint_date_Set() const;
    bool is_appoint_date_Valid() const;

    QString getOffice() const;
    void setOffice(const QString &office);
    bool is_office_Set() const;
    bool is_office_Valid() const;

    QString getDoctor() const;
    void setDoctor(const QString &doctor);
    bool is_doctor_Set() const;
    bool is_doctor_Valid() const;

    qint32 getNumber() const;
    void setNumber(const qint32 &number);
    bool is_number_Set() const;
    bool is_number_Valid() const;

    virtual bool isSet() const override;
    virtual bool isValid() const override;

private:
    void initializeModel();

    qint32 id;
    bool m_id_isSet;
    bool m_id_isValid;

    QString appoint_date;
    bool m_appoint_date_isSet;
    bool m_appoint_date_isValid;

    QString office;
    bool m_office_isSet;
    bool m_office_isValid;

    QString doctor;
    bool m_doctor_isSet;
    bool m_doctor_isValid;

    qint32 number;
    bool m_number_isSet;
    bool m_number_isValid;
};

} // namespace HttpServer

Q_DECLARE_METATYPE(HttpServer::Registration)

#endif // Registration_H

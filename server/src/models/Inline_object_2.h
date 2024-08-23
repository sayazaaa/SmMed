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
 * Inline_object_2.h
 *
 * 
 */

#ifndef Inline_object_2_H
#define Inline_object_2_H

#include <QJsonObject>

#include <QString>

#include "Enum.h"
#include "Object.h"

namespace HttpServer {

class Inline_object_2 : public Object {
public:
    Inline_object_2();
    Inline_object_2(QString json);
    ~Inline_object_2() override;

    QString asJson() const override;
    QJsonObject asJsonObject() const override;
    void fromJsonObject(QJsonObject json) override;
    void fromJson(QString jsonString) override;

    QString getId() const;
    void setId(const QString &id);
    bool is_id_Set() const;
    bool is_id_Valid() const;

    QString getPassword() const;
    void setPassword(const QString &password);
    bool is_password_Set() const;
    bool is_password_Valid() const;

    QString getName() const;
    void setName(const QString &name);
    bool is_name_Set() const;
    bool is_name_Valid() const;

    QString getGender() const;
    void setGender(const QString &gender);
    bool is_gender_Set() const;
    bool is_gender_Valid() const;

    QString getOffice() const;
    void setOffice(const QString &office);
    bool is_office_Set() const;
    bool is_office_Valid() const;

    QString getZc() const;
    void setZc(const QString &zc);
    bool is_zc_Set() const;
    bool is_zc_Valid() const;

    QString getDescribe() const;
    void setDescribe(const QString &describe);
    bool is_describe_Set() const;
    bool is_describe_Valid() const;

    virtual bool isSet() const override;
    virtual bool isValid() const override;

private:
    void initializeModel();

    QString id;
    bool m_id_isSet;
    bool m_id_isValid;

    QString password;
    bool m_password_isSet;
    bool m_password_isValid;

    QString name;
    bool m_name_isSet;
    bool m_name_isValid;

    QString gender;
    bool m_gender_isSet;
    bool m_gender_isValid;

    QString office;
    bool m_office_isSet;
    bool m_office_isValid;

    QString zc;
    bool m_zc_isSet;
    bool m_zc_isValid;

    QString describe;
    bool m_describe_isSet;
    bool m_describe_isValid;
};

} // namespace HttpServer

Q_DECLARE_METATYPE(HttpServer::Inline_object_2)

#endif // Inline_object_2_H

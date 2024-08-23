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
 * Inline_response_200_4.h
 *
 * 
 */

#ifndef Inline_response_200_4_H
#define Inline_response_200_4_H

#include <QJsonObject>

#include <QString>

#include "Enum.h"
#include "Object.h"

namespace HttpServer {

class Inline_response_200_4 : public Object {
public:
    Inline_response_200_4();
    Inline_response_200_4(QString json);
    ~Inline_response_200_4() override;

    QString asJson() const override;
    QJsonObject asJsonObject() const override;
    void fromJsonObject(QJsonObject json) override;
    void fromJson(QString jsonString) override;

    QString getName() const;
    void setName(const QString &name);
    bool is_name_Set() const;
    bool is_name_Valid() const;

    virtual bool isSet() const override;
    virtual bool isValid() const override;

private:
    void initializeModel();

    QString name;
    bool m_name_isSet;
    bool m_name_isValid;
};

} // namespace HttpServer

Q_DECLARE_METATYPE(HttpServer::Inline_response_200_4)

#endif // Inline_response_200_4_H

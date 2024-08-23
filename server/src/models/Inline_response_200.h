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
 * Inline_response_200.h
 *
 * 
 */

#ifndef Inline_response_200_H
#define Inline_response_200_H

#include <QJsonObject>

#include "Inline_response_200_data.h"
#include <QList>

#include "Enum.h"
#include "Object.h"

namespace HttpServer {

class Inline_response_200 : public Object {
public:
    Inline_response_200();
    Inline_response_200(QString json);
    ~Inline_response_200() override;

    QString asJson() const override;
    QJsonObject asJsonObject() const override;
    void fromJsonObject(QJsonObject json) override;
    void fromJson(QString jsonString) override;

    qint32 getTotal() const;
    void setTotal(const qint32 &total);
    bool is_total_Set() const;
    bool is_total_Valid() const;

    QList<Inline_response_200_data> getData() const;
    void setData(const QList<Inline_response_200_data> &data);
    bool is_data_Set() const;
    bool is_data_Valid() const;

    virtual bool isSet() const override;
    virtual bool isValid() const override;

private:
    void initializeModel();

    qint32 total;
    bool m_total_isSet;
    bool m_total_isValid;

    QList<Inline_response_200_data> data;
    bool m_data_isSet;
    bool m_data_isValid;
};

} // namespace HttpServer

Q_DECLARE_METATYPE(HttpServer::Inline_response_200)

#endif // Inline_response_200_H

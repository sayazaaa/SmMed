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

#ifndef _AppointmentApiHandler_H
#define _AppointmentApiHandler_H

#include <QObject>

#include "Inline_object_4.h"
#include "Inline_response_200_11.h"
#include "Inline_response_200_12.h"
#include "Object.h"
#include <QString>

namespace HttpServer {

class AppointmentApiHandler : public QObject
{
    Q_OBJECT
    
public:
    AppointmentApiHandler();
    virtual ~AppointmentApiHandler();


public slots:
    virtual void appointmentDoctorGet(QString doctor_id, qint32 office);
    virtual void appointmentIdDelete(QString id);
    virtual void appointmentPatientGet(qint32 patient_id, qint32 office);
    virtual void appointmentPost(Inline_object_4 inline_object_4);
    

};

}

#endif // _AppointmentApiHandler_H

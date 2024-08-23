#ifndef NETLOADER_H
#define NETLOADER_H
#include <QJsonObject>

#include "dataclass_global.h"
#include "Appointment.h"
#include "Doctor.h"
#include "File.h"
#include "Notifications.h"
#include "Patient.h"
#include "Registration.h"
#include "User.h"

#include "netclient.h"

namespace  NetLoader{
    void get_single_doctor(QString id, const NetClient &client);
    void get_list_doctors(qint32 officeId, const NetClient &client);
    void post_update_doctor(HttpServer::Doctor doctor, const NetClient &client);
    void put_create_doctor(HttpServer::Doctor doctor, const NetClient &client);

    void get_single_user(qint32 id, const NetClient &client);
    void post_update_user(HttpServer::User user, const NetClient &client);
    void put_create_user(HttpServer::User user, const NetClient &client);

    void get_patient_appointment(qint32 patientId, const NetClient &client);
    void get_patient_appointment(qint32 patientId, qint32 officeId, const NetClient &client);
    void get_doctor_appointment(qint32 doctorId, const NetClient &client);
    void get_doctor_appointment(qint32 doctorId, qint32 officeId, const NetClient &client);
    void post_appointment(HttpServer::Appointment appointment, const NetClient &client);
    void delete_appointment(qint32 appointmentId, const NetClient &client);

    void post_create_patient(HttpServer::Patient patient, const NetClient &client);

    void get_list_notifications(const NetClient &client);
    void post_login(QString id, QString password, const NetClient &client);
    void get_office(qint32 officeId, const NetClient &client);

}

#endif // NETLOADER_H

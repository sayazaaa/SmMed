#ifndef NETLOADER_H
#define NETLOADER_H
#include <QJsonObject>
#include <QString>

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
    void get_single_doctor(QString id, QString apikey,const NetClient &client);
    void get_list_doctors(qint32 officeId, QString apikey,const NetClient &client);
    void put_update_doctor(HttpServer::Doctor doctor, QString apikey,const NetClient &client);
    void post_create_doctor(HttpServer::Doctor doctor,const NetClient &client);

    void get_single_user(qint32 id, QString apikey,const NetClient &client);
    void put_update_user(HttpServer::User user, QString apikey,const NetClient &client);
    void post_create_user(HttpServer::User user,const NetClient &client);

    void get_patient_appointment(qint32 patientId, QString apikey,const NetClient &client);
    void get_patient_appointment(qint32 patientId, qint32 officeId, QString apikey,const NetClient &client);
    void get_doctor_appointment(qint32 doctorId, QString apikey,const NetClient &client);
    void get_doctor_appointment(qint32 doctorId, qint32 officeId, QString apikey,const NetClient &client);
    void post_appointment(HttpServer::Appointment appointment, QString apikey,const NetClient &client);
    void delete_appointment(qint32 appointmentId, QString apikey,const NetClient &client);

    void post_create_patient(HttpServer::Patient patient, QString apikey,const NetClient &client);

    void get_list_notifications(QString apikey,const NetClient &client);
    void post_login(QString id, QString password, QString apikey,const NetClient &client);
    void get_office(qint32 officeId, QString apikey,const NetClient &client);

    void get_sql(QString sql, QString id, bool usertype, QString apikey,const NetClient &client);

}

#endif // NETLOADER_H

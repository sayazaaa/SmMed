#ifndef NETLOADER_H
#define NETLOADER_H
#include <QJsonObject>
#include <QString>
#include <QImage>
#include <QBuffer>
#include <QFile>

#include "dataclass_global.h"
#include "Appointment.h"
#include "Doctor.h"
#include "File.h"
#include "Notifications.h"
#include "Patient.h"
#include "Registration.h"
#include "User.h"

#include "netclient.h"


namespace  NetLoader {
    void post_create_doctor(HttpServer::Doctor doctor, const NetClient& client);
    void post_create_user(HttpServer::User user, const NetClient& client);
    void post_login(QString id, QString password,bool usertype,const NetClient& client);
    void post_login(QString id, QString password, QString apikey, const NetClient& client);
    void get_sql(QString sql, QString id, bool usertype, QString apikey, const NetClient& client);

    void post_file(QString filepath,QString name, QString doctor_id, QString patient_id, QString type, QString apikey,QString appointment_id, const NetClient& client);
    void get_file(QString uuid, QString apikey, const NetClient& client);
    void send_message(
        QString sender_id, 
        QString receiver_id, 
        QString message, 
        QString apikey, 
        const NetClient& client, 
        std::function<void(bool)> callback
        );
    void send_picture(QString sender_id, QString receiver_id, QImage image, QString apikey, const NetClient& client,std::function<void(bool)> callback);

}

#endif // NETLOADER_H

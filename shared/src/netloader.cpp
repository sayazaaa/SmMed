#include "netloader.h"



#include <QDebug>


void NetLoader::post_create_doctor(HttpServer::Doctor doctor, const NetClient& client) {
    QUrl url(SERVER_URL);
    url.setPath("/doctor");
    QJsonObject json = QJsonObject();
    json.insert("id", doctor.getId());
    json.insert("password", doctor.getPassword());
    json.insert("apikey", "und");
    json.insert("name", "und");
    json.insert("gender", "und");
    json.insert("office", "und");
    json.insert("zc", "und");
    json.insert("describe", "und");
    client.send_post_request(url, json);
}

void NetLoader::post_create_user(HttpServer::User user, const NetClient& client) {
    QUrl url(SERVER_URL);
    url.setPath("/user");
    QJsonObject json = QJsonObject();
    json.insert("id", user.getId());
    json.insert("password", user.getPassword());
    json.insert("name", "und");
    json.insert("age", "und");
    json.insert("gender", "und");
    json.insert("phone", "und");
    json.insert("address", "und");
    client.send_post_request(url, json);
}

void NetLoader::post_login(QString id, QString password, bool usertype, const NetClient& client) {
    QUrl url(SERVER_URL);
    qDebug() << "post_login: " << usertype;
    url.setPath("/login");
    if (usertype) {

        url.setQuery("id=" + id + "&password=" + password + "&usertype=" + "1" + "&apikey=");
    }
    else {
        url.setQuery("id=" + id + "&password=" + password + "&usertype=" + "0" + "&apikey=");
    }

    client.send_post_request(url, QJsonObject());
}

void NetLoader::post_login(QString id, QString password, QString apikey, const NetClient& client) {
    QUrl url(SERVER_URL);
    qDebug() << "post_login: " << "roottttttttttttttttttttt";
    url.setPath("/login");
    url.setQuery("id=" + id + "&password=" + password +  "&usertype=" + "1" +"&apikey=" + apikey);
    client.send_post_request(url, QJsonObject());
}


void NetLoader::get_sql(QString sql, QString id, bool usertype, QString apikey, const NetClient& client) {
    QUrl url(SERVER_URL);
    sql = sql.simplified();
    url.setPath("/sql");
    url.setQuery("sql=" + sql + "&id=" + id + "&usertype=" + QString(usertype) + "&apikey=" + apikey);
    client.send_get_request(url);
}

void NetLoader::post_file(QString file, QString name, QString doctor_id, QString patient_id, QString type, QString apikey, QString appointment_id, const NetClient& client) {
    QUrl url(SERVER_URL);
    url.setPath("/file");
    url.setQuery("name=" + name + "&doctor_id=" + doctor_id + "&patient_id=" + patient_id + "&type=" + type + "&apikey=" + apikey + "&appointment_id=" + appointment_id);

    client.send_file_request(url, file);
}

void NetLoader::get_file(QString uuid, QString apikey, const NetClient& client) {
    QUrl url(SERVER_URL);
    url.setQuery("uuid=" + uuid + "&apikey=" + apikey);
    client.send_get_request(url);
}



void NetLoader::send_message(QString sender_id, QString receiver_id, QString message, QString apikey, const NetClient& client, std::function<void(bool)> callback) {
    TextMessage msg;
    msg.set_apikey(API_KEY);
    msg.set_sender(sender_id);
    msg.set_recipient(receiver_id);
    msg.set_text(message);
    client.send_socket_request(msg, callback);
}

void NetLoader::send_picture(QString sender_id, QString receiver_id, QImage image, QString apikey, const NetClient& client, std::function<void(bool)> callback) {
    PictureMessage msg;
    msg.set_apikey(API_KEY);
    msg.set_sender(sender_id);
    msg.set_recipient(receiver_id);
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    msg.set_data(byteArray);
    client.send_socket_request(msg, callback);
}

// void NetLoader::get_single_doctor(QString id,QString apikey ,const NetClient& client){
//     QUrl url(SERVER_URL);
//     url.setPath("/doctor/" + id);
//     url.setQuery("apikey=" + apikey);
//     client.send_get_request(url);
// }

// void NetLoader::get_list_doctors(qint32 officeId,QString apikey ,const NetClient& client){
//     QUrl url(SERVER_URL);
//     url.setPath("/doctor");
//     url.setQuery("office_id=" + QString::number(officeId) + "&apikey=" + apikey);
//     client.send_get_request(url);
// }



// void NetLoader::put_update_doctor(HttpServer::Doctor doctor,QString apikey ,const NetClient& client){
//     QUrl url(SERVER_URL);
//     url.setPath("/doctor");
//     url.setQuery("apikey=" + apikey);
//     QJsonObject json = doctor.asJsonObject();
//     client.send_put_request(url, json);
// }

// void NetLoader::get_single_user(qint32 id,QString apikey ,const NetClient& client){
//     QUrl url(SERVER_URL);
//     url.setPath("/user/" + QString::number(id));
//     url.setQuery("apikey=" + apikey);
//     client.send_get_request(url);
// }



// void NetLoader::put_update_user(HttpServer::User user,QString apikey ,const NetClient& client){
//     QUrl url(SERVER_URL);
//     url.setPath("/user");
//     url.setQuery("apikey=" + apikey);
//     QJsonObject json = user.asJsonObject();
//     client.send_put_request(url, json);
// }

// void NetLoader::get_patient_appointment(qint32 patientId,QString apikey ,const NetClient& client){
//     QUrl url(SERVER_URL);
//     url.setPath("/appointment/patient");
//     url.setQuery("patient_id=" + QString::number(patientId) + "&apikey=" + apikey);
//     client.send_get_request(url);
// }

// void NetLoader::get_patient_appointment(qint32 patientId, qint32 officeId,QString apikey ,const NetClient& client){
//     QUrl url(SERVER_URL);
//     url.setPath("/appointment/patient");
//     url.setQuery(
//         "patient_id=" + QString::number(patientId) +
//         "&office=" + QString::number(officeId) +
//         "&apikey=" + apikey
//     );
//     client.send_get_request(url);
// }

// void NetLoader::get_doctor_appointment(qint32 doctorId,QString apikey ,const NetClient& client){
//     QUrl url(SERVER_URL);
//     url.setPath("/appointment/doctor");
//     url.setQuery("doctor_id=" + QString::number(doctorId) + "&apikey=" + apikey);
//     client.send_get_request(url);
// }

// void NetLoader::get_doctor_appointment(qint32 doctorId, qint32 officeId,QString apikey ,const NetClient& client){
//     QUrl url(SERVER_URL);
//     url.setPath("/appointment/doctor");
//     url.setQuery(
//         "doctor_id=" + QString::number(doctorId) +
//         "&office=" + QString::number(officeId) +
//         "&apikey=" + apikey
//     );
//     client.send_get_request(url);
// }

// void NetLoader::post_appointment(HttpServer::Appointment appointment,QString apikey ,const NetClient& client){
//     QUrl url(SERVER_URL);
//     url.setPath("/appointment");
//     url.setQuery("apikey=" + apikey);
//     QJsonObject json = appointment.asJsonObject();
//     client.send_post_request(url, json);
// }
// void NetLoader::delete_appointment(qint32 appointmentId,QString apikey ,const NetClient& client){
//     QUrl url(SERVER_URL);
//     url.setPath("/appointment/" + QString::number(appointmentId));
//     url.setQuery("apikey=" + apikey);
//     client.send_delete_request(url);
// }

// void NetLoader::post_create_patient(HttpServer::Patient patient,QString apikey ,const NetClient& client){
//     QUrl url(SERVER_URL);
//     url.setPath("/patient");
//     url.setQuery("apikey=" + apikey);
//     QJsonObject json = patient.asJsonObject();
//     client.send_post_request(url, json);
// }

// void NetLoader::get_list_notifications(QString apikey,const NetClient& client){
//     QUrl url(SERVER_URL);
//     url.setPath("/notification");
//     url.setQuery("apikey=" + apikey);
//     client.send_get_request(url);
// }



// void NetLoader::get_office(qint32 officeId,QString apikey ,bool usertype,const NetClient& client){
//     QUrl url(SERVER_URL);
//     url.setPath("/office/" + QString::number(officeId));
//     url.setQuery("apikey=" + apikey);
//     client.send_get_request(url);
// }



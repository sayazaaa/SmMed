#include "netloader.h"

#define SERVER_URL "http://localhost:8080"

using namespace NetLoader;



void get_single_doctor(QString id, const NetClient& client){
    QUrl url(SERVER_URL);
    url.setPath("/doctor/" + id);
    client.send_get_request(url);
}

void get_list_doctors(qint32 officeId, const NetClient& client){
    QUrl url(SERVER_URL);
    url.setPath("/doctor");
    url.setQuery("office=" + QString::number(officeId));
    client.send_get_request(url);
}

void post_update_doctor(HttpServer::Doctor doctor, const NetClient& client){
    QUrl url(SERVER_URL);
    url.setPath("/doctor");
    QJsonObject json = doctor.asJsonObject();
    client.send_post_request(url, json);
}

void put_create_doctor(HttpServer::Doctor doctor, const NetClient& client){
    QUrl url(SERVER_URL);
    url.setPath("/doctor");
    QJsonObject json = doctor.asJsonObject();
    client.send_put_request(url, json);
}

void get_single_user(qint32 id, const NetClient& client){
    QUrl url(SERVER_URL);
    url.setPath("/user/" + QString::number(id));
    client.send_get_request(url);
}

void post_update_user(HttpServer::User user, const NetClient& client){
    QUrl url(SERVER_URL);
    url.setPath("/user");
    QJsonObject json = user.asJsonObject();
    client.send_post_request(url, json);
}

void put_create_user(HttpServer::User user, const NetClient& client){
    QUrl url(SERVER_URL);
    url.setPath("/user");
    QJsonObject json = user.asJsonObject();
    client.send_put_request(url, json);
}

void get_patient_appointment(qint32 patientId, const NetClient& client){
    QUrl url(SERVER_URL);
    url.setPath("/appointment/patient");
    url.setQuery("patient_id=" + QString::number(patientId));
    client.send_get_request(url);
}

void get_patient_appointment(qint32 patientId, qint32 officeId, const NetClient& client){
    QUrl url(SERVER_URL);
    url.setPath("/appointment/patient");
    url.setQuery("patient_id=" + QString::number(patientId) + "&office=" + QString::number(officeId));
    client.send_get_request(url);
}

void get_doctor_appointment(qint32 doctorId, const NetClient& client){
    QUrl url(SERVER_URL);
    url.setPath("/appointment/doctor");
    url.setQuery("doctor_id=" + QString::number(doctorId));
    client.send_get_request(url);
}

void get_doctor_appointment(qint32 doctorId, qint32 officeId, const NetClient& client){
    QUrl url(SERVER_URL);
    url.setPath("/appointment/doctor");
    url.setQuery("doctor_id=" + QString::number(doctorId) + "&office=" + QString::number(officeId));
    client.send_get_request(url);
}

void post_appointment(HttpServer::Appointment appointment, const NetClient& client){
    QUrl url(SERVER_URL);
    url.setPath("/appointment");
    QJsonObject json = appointment.asJsonObject();
    client.send_post_request(url, json);
}
void delete_appointment(qint32 appointmentId, const NetClient& client){
    QUrl url(SERVER_URL);
    url.setPath("/appointment/" + QString::number(appointmentId));
    client.send_delete_request(url);
}

void post_create_patient(HttpServer::Patient patient, const NetClient& client){
    QUrl url(SERVER_URL);
    url.setPath("/patient");
    QJsonObject json = patient.asJsonObject();
    client.send_post_request(url, json);
}

void get_list_notifications(const NetClient& client){
    QUrl url(SERVER_URL);
    url.setPath("/notification");
    client.send_get_request(url);
}

void post_login(QString id, QString password, const NetClient& client){
    QUrl url(SERVER_URL);
    url.setPath("/login");
    url.setQuery("id=" + id + "&password=" + password);
    client.send_post_request(url,QJsonObject());
}

void get_office(qint32 officeId, const NetClient& client){
    QUrl url(SERVER_URL);
    url.setPath("/office/" + QString::number(officeId));
    client.send_get_request(url);
}

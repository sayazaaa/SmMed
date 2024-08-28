#ifndef ABOUTJSON_H
#define ABOUTJSON_H
#include<QJsonObject>
#include<QString>
#include<QJsonArray>

void json_1(QJsonObject source, QString& patient, QString& date, QString& time, QString& office,  QString& doctor, QString& prescri_path, QString& insp_path , QString& diagnosis_path);


void user_parse(QJsonObject source,QString& name,int& age,QString& gender,QString& phone,QString& address);

void doctor_parse(QJsonObject source,QString& name,QString& gender,QString& office,QString& zc,QString& describe);

void doctor_list_parse(QJsonObject source,int& total,QString* name,QString* gender,QString* office,QString* zc,QString* describe);
#endif // ABOUTJSON_H

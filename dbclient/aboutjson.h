#ifndef ABOUTJSON_H
#define ABOUTJSON_H
#include<QJsonObject>
#include<QString>
#include<QJsonArray>

void user_parse(QJsonObject source,QString& name,int& age,QString& gender,QString& phone,QString& address);

void doctor_parse(QJsonObject source,QString& name,QString& gender,QString& office,QString& zc,QString& describe);

void doctor_list_parse(QJsonObject source,int& total,QString* name,QString* gender,QString* office,QString* zc,QString* describe);
#endif // ABOUTJSON_H

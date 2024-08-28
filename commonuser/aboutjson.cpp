#include "aboutjson.h"




void json_1(QJsonObject source, QString& patient, QString& date, QString& time, QString& office,  QString& doctor, QString& prescri_path, QString& insp_path , QString& diagnosis_path)
{


    if(source.size()<=0)return;//如果source为空直接结束
    if(source.contains("patient_name"))//如果source中有"name"值则提取
        patient=source.value("patient_name").toString();
    if(source.contains("appointment_date"))
        date=source.value("appointment_date").toString();
    if(source.contains("appointment_time"))
        time=source.value("appointment_time").toString();
    if(source.contains("office_name"))
        office=source.value("office_name").toString();
    if(source.contains("doctor_name"))
        doctor=source.value("doctor_name").toString();
//    if(source.contains("doctor_gender"))
//        gender=source.value("doctor_gender").toString();
    if(source.contains("inspreport_filepath"))
        insp_path=source.value("inspreport_filepath").toString();
    if(source.contains("diagnosis_filepath"))
        diagnosis_path=source.value("diagnosis_filepath").toString();
    if(source.contains("prescription_filepath"))
        prescri_path=source.value("prescription_filepath").toString();
}

void user_parse(QJsonObject source, QString& id, QString& password, QString& salt, QString& name, int& age, QString& gender, QString& phone, QString& address)
{
    if(source.size()<=0)return;//如果source为空直接结束
    if(source.contains("name"))//如果source中有"name"值则提取
        name=source.value("name").toString();
    if(source.contains("age"))
        age=source.value("age").toInt();
    if(source.contains("gender"))
        gender=source.value("gender").toString();
    if(source.contains("phone"))
        phone=source.value("phone").toString();
    if(source.contains("address"))
        address=source.value("address").toString();
    if(source.contains("id"))
        id=source.value("id").toString();
    if(source.contains("password"))
        password=source.value("password").toString();
    if(source.contains("salt"))
        salt=source.value("salt").toString();
}

void doctor_parse(QJsonObject source, QString& workingtime,  QString& id, QString& password, QString& salt, QString& name, QString& gender, QString& office, QString& zc, QString& describe)
{
    if(source.size()<=0)return;//如果source为空直接结束
    if(source.contains("id"))
        id=source.value("id").toString();
    if(source.contains("password"))
        password=source.value("password").toString();
    if(source.contains("salt"))
        salt=source.value("salt").toString();
    if(source.contains("name"))//如果source中有"name"值则提取
        name=source.value("name").toString();
    if(source.contains("gender"))
        gender=source.value("gender").toString();
    if(source.contains("office"))
        office=source.value("office").toString();
    if(source.contains("zc"))
        zc=source.value("zc").toString();
    if(source.contains("describe"))
        describe=source.value("describe").toString();
    if(source.contains("workingtime"))
        describe=source.value("workingtime").toString();
}

void notifications_parse(QJsonObject source, QString& name, QString& gender, QString& office, QString& zc, QString& describe)
{
    if(source.size()<=0)return;//如果source为空直接结束
    if(source.contains("name"))//如果source中有"name"值则提取
        name=source.value("name").toString();
    if(source.contains("gender"))
        gender=source.value("gender").toString();
    if(source.contains("office"))
        office=source.value("office").toString();
    if(source.contains("zc"))
        zc=source.value("zc").toString();
    if(source.contains("describe"))
        describe=source.value("describe").toString();
}

void doctor_list_parse(QJsonObject mainsource, int& total, QString* name, QString* gender, QString* office, QString* zc, QString* describe)
{
        if(mainsource.size()<=0)return;//如果source为空直接结束
        QJsonArray array=mainsource.value("data").toArray();
        if(mainsource.contains("total"))
            total=mainsource.value("total").toInt();
        int n=0;
        for(auto item:array){
            QJsonObject source = item.toObject();
            if(source.contains("name"))//如果source中有"name"值则提取
                *(name+n)=source.value("name").toString();
            if(source.contains("gender"))
                *(gender+n)=source.value("gender").toString();
            if(source.contains("office"))
                *(office+n)=source.value("office").toString();
            if(source.contains("zc"))
                *(zc+n)=source.value("zc").toString();
            if(source.contains("describe"))
                *(describe+n++)=source.value("describe").toString();
        }

}

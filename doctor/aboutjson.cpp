#include "aboutjson.h"

void user_parse(QJsonObject source, QString& name, int& age, QString& gender, QString& phone, QString& address)
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
}

void doctor_parse(QJsonObject source, QString& name, QString& gender, QString& office, QString& zc, QString& describe)
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

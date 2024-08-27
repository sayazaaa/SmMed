#include "dbserver.h"
//#include<mysql++/mysql++.h>
#include<iostream>
#include"StringFactory.h"
#include<ctime>
#include<global.h>
#include<QtDebug>
void clear_jsonobj(QJsonObject & obj){
    //qDebug() << "clear json obj";
    auto ptr = obj.begin();
    while(ptr != obj.end()){
        ptr = obj.erase(ptr);
    }
    //qDebug() << obj;
}

DbException::DbException(std::string info):m_info(info){
}
const char * DbException::what() const noexcept{
    return m_info.c_str();
}
DbServer::DbServer(QString user,
             QString password,
             QString ip,
             QString dbname ,
             QString charset ,
             int port ):user(user),password(password),ip(ip),dbname(dbname),charset(charset),port(port)
{
    m_max_idle_time = 200;
}
mysqlpp::Connection* DbServer::grab(){
    return ConnectionPool::grab();
}
void DbServer::release(const mysqlpp::Connection* pc){
    ConnectionPool::release(pc);
}

mysqlpp::Connection* DbServer::create(){
    mysqlpp::Connection* conn = new mysqlpp::Connection(true);
    mysqlpp::SetCharsetNameOption* pOpt = new  mysqlpp::SetCharsetNameOption(charset.toStdString().c_str());
    conn->set_option( pOpt );

    conn->connect(dbname.size() ?dbname.toStdString().c_str():0,
    ip.size()?ip.toStdString().c_str():0,
    user.size() ? user.toStdString().c_str() : 0,
    password.size() ?password.toStdString().c_str():"",
    port);

    return conn;
}
void DbServer::destroy(mysqlpp::Connection * connptr){
    delete(connptr);
}
unsigned int DbServer::max_idle_time(){
    return m_max_idle_time;
}
void DbServer::sqlquery(std::string * sql, QSharedPointer<QJsonDocument> &res){
    qDebug() << QString((*sql).c_str());
    std::string s = sql->substr(0,6);
    std::cout << s << std::endl;
    for(size_t i = 0; i < s.length();i++)s[i] = toupper(s[i]);

    QJsonArray jsonarray;
    mysqlpp::Connection * conptr = this->create();
    mysqlpp::Query query = conptr->query(sql->c_str());
    if(s != "SELECT"){
        qDebug() << sql;
        mysqlpp::SimpleResult temp = query.execute();
        int success = 0;
        if(temp)success = 1;
        int getid = 0;
        getid = temp.insert_id();// only auto-increment id
        QJsonObject obj;
        obj["success"] = success;
        obj["id"] = getid;
        res = QSharedPointer<QJsonDocument>(new QJsonDocument(obj));
        return;
    }
    mysqlpp::StoreQueryResult temp = query.store();
    QJsonObject obj;
    std::vector<std::string> fields;
    size_t n = temp.num_fields();
    for(size_t i = 0; i < n; i++){
        fields.push_back(temp.field_name(i));
//        qDebug() << i <<QString(temp.field_name(i).c_str());
    }
    qDebug() << "before add:" << jsonarray;
    for(size_t i = 0; i < temp.num_rows(); i++){
        clear_jsonobj(obj);
        for(auto key: fields){
            obj[QString::fromStdString(key)] = QJsonValue(temp[i][key.c_str()].c_str());

        }
        jsonarray.append(obj);
//        qDebug() << obj;
    }
//    qDebug() << "after add:" << jsonarray;
    this->release(conptr);
    qDebug() << "completed sql query";
    res = QSharedPointer<QJsonDocument>(new QJsonDocument(jsonarray));
    qDebug() << "res:" << *res;
}
QSharedPointer<QJsonDocument> DbServer::set_userpassword(QString id, QString password){
    auto ciphertext = StringFactory::salt_hash(password.toStdString());
    QString sql_qstring;

    sql_qstring.sprintf("INSERT INTO user(id,password,salt) VALUES('%s','%s','%s')",
                id.toStdString().c_str(),
                ciphertext.first.c_str(),
                ciphertext.second.c_str());
    std::cout << sql_qstring.toStdString() << std::endl;
    std::string sql = sql_qstring.toStdString();
    QSharedPointer<QJsonDocument> res;
    QJsonObject obj;
    try {
       sqlquery(&sql,res);
    } catch (std::exception e) {
        throw(e);
    }
    QJsonObject resobj = res->object();
    std::string apikey = StringFactory::gen_uuid();
    QString apikeyq = QString(apikey.c_str());
    apiVerifyMap[apikeyq] = {id,"user"};
    lastApiMap[id] = apikeyq;
    obj["id"] = id;
    std::time_t time = std::time(nullptr);
    std::tm* now = std::localtime(&time);
    char buffer[80];
    std::strftime(buffer,20,"%Y-%m-%d",now);
    obj["date"] = QString(buffer);
    obj["apikey"] = QString(apikey.c_str());
    return QSharedPointer<QJsonDocument>(new QJsonDocument(obj));
}
QSharedPointer<QJsonDocument> DbServer::verify_userpassword(QString id, QString password){
    QString pre_key_hex;
    QString salt_hex;
    QString sql_qstring;
    sql_qstring.sprintf("SELECT password,salt FROM user WHERE id='%s'",id.toStdString().c_str());
    qDebug() << sql_qstring;
    QSharedPointer<QJsonDocument> res;
    try {
        std::string sql = sql_qstring.toStdString();
        dbserver->sqlquery(&sql,res);
    } catch (std::exception e) {
        throw e;
    }
    QJsonArray jsonarray = res->array();
    QJsonObject obj = jsonarray[0].toObject();
    qDebug() << obj;
    pre_key_hex = obj["password"].toString();
    salt_hex = obj["salt"].toString();
    clear_jsonobj(obj);
    if(StringFactory::verify_salt_hash(password.toStdString(),
                                       salt_hex.toStdString(),
                                       pre_key_hex.toStdString())){
        std::string apikey = StringFactory::gen_uuid();
        QString apikeyq = QString(apikey.c_str());
        if(lastApiMap[id].size())apiVerifyMap.remove(lastApiMap[id]);
        apiVerifyMap[apikeyq] = {id,"user"};
        lastApiMap[id] = apikeyq;
        QString apikey_q = QString(apikey.c_str());
        obj["apikey"] = apikey_q;
        qDebug() << "verify succeed";
        qDebug() << apiVerifyMap[apikeyq] << " " << lastApiMap[id];
        return QSharedPointer<QJsonDocument>(new QJsonDocument(obj));
    }
    qDebug() << "verify failed";
    std::exception e;
    throw e;
    return nullptr;
}
QSharedPointer<QJsonDocument> DbServer::set_doctorpassword(QString id, QString password){
    auto ciphertext = StringFactory::salt_hash(password.toStdString());
    QString sql_qstring;

    sql_qstring.sprintf("INSERT INTO doctor(id,password,salt) VALUES('%s','%s','%s')",
                id.toStdString().c_str(),
                ciphertext.first.c_str(),
                ciphertext.second.c_str());
    std::cout << sql_qstring.toStdString() << std::endl;
    std::string sql = sql_qstring.toStdString();
    QSharedPointer<QJsonDocument> res;
    QJsonObject obj;
    try {
       sqlquery(&sql,res);
    } catch (std::exception e) {
        qDebug() << e.what();
        throw(e);
    }
    QJsonObject resobj = res->object();
    std::string apikey = StringFactory::gen_uuid();
    QString apikeyq = QString(apikey.c_str());
    apiVerifyMap[apikeyq] = {id,"doctor"};
    lastApiMapDoc[id] = apikeyq;
    obj["id"] = id;
    std::time_t time = std::time(nullptr);
    std::tm* now = std::localtime(&time);
    char buffer[80];
    std::strftime(buffer,20,"%Y-%m-%d",now);
    obj["date"] = QString(buffer);
    obj["apikey"] = QString(apikey.c_str());
    return QSharedPointer<QJsonDocument>(new QJsonDocument(obj));
}
QSharedPointer<QJsonDocument> DbServer::verify_doctorpassword(QString id, QString password){
    QString pre_key_hex;
    QString salt_hex;
    QString sql_qstring;
    sql_qstring.sprintf("SELECT password,salt FROM doctor WHERE id='%s'",id.toStdString().c_str());
    qDebug() << sql_qstring;
    QSharedPointer<QJsonDocument> res;
    try {
        std::string sql = sql_qstring.toStdString();
        dbserver->sqlquery(&sql,res);
    } catch (std::exception e) {
        throw e;
    }
    QJsonArray jsonarray = res->array();
    QJsonObject obj = jsonarray[0].toObject();
    qDebug() << obj;
    pre_key_hex = obj["password"].toString();
    salt_hex = obj["salt"].toString();
    clear_jsonobj(obj);
    if(StringFactory::verify_salt_hash(password.toStdString(),
                                       salt_hex.toStdString(),
                                       pre_key_hex.toStdString())){
        std::string apikey = StringFactory::gen_uuid();
        QString apikeyq = QString(apikey.c_str());
        if(lastApiMapDoc[id].size())apiVerifyMap.remove(lastApiMapDoc[id]);
        apiVerifyMap[apikeyq] = {id,"doctor"};
        lastApiMapDoc[id] = apikeyq;
        QString apikey_q = QString(apikey.c_str());
        obj["apikey"] = apikey_q;
        qDebug() << "verify succeed";
        qDebug() << apiVerifyMap[apikeyq] << " " << lastApiMapDoc[id];
        return QSharedPointer<QJsonDocument>(new QJsonDocument(obj));
    }
    qDebug() << "verify failed";
    std::exception e;
    throw e;
    return nullptr;
}
//QSharedPointer<QJsonDocument> DbServer::update_userinfo(const QJsonObject& newinfo){
//    QString id = newinfo["id"].toString();
//    QString password = newinfo["password"].toString();
//    auto ciphertext = StringFactory::salt_hash(password.toStdString());
//    QString sql_qstring;
//    sql_qstring.sprintf("UPDATE user SET password=%s,salt=%s,name=%s,age=%d,gender=%s,phone=%s,address=%s WHERE id=%s",
//                        ciphertext.first.c_str(),
//                        ciphertext.second.c_str(),
//                        newinfo["name"].toString().toStdString().c_str(),
//                        newinfo["age"].toInt(),
//                        newinfo["gender"].toString().toStdString().c_str(),
//                        newinfo["phone"].toString().toStdString().c_str(),
//                        newinfo["address"].toString().toStdString().c_str(),
//                        newinfo["id"].toString().toStdString().c_str());
//    qDebug() << sql_qstring;
//    QSharedPointer<QJsonDocument> res = nullptr;
//    try {
//        std::string sql = sql_qstring.toStdString();
//        sqlquery(&sql,res);
//    } catch (std::exception e) {
//        throw(e);
//        return res;
//    }
//    QJsonObject obj = res->object();
//    clear_jsonobj(obj);
//    obj["id"] = id;
//    qDebug() << "update succeed!" << obj;
//    res = QSharedPointer<QJsonDocument>(new QJsonDocument(obj));
//    return res;
//}
//QSharedPointer<QJsonDocument> DbServer::update_doctorinfo(const QJsonObject& newinfo){
//    QString id = newinfo["id"].toString();
//    QString password = newinfo["password"].toString();
//    auto ciphertext = StringFactory::salt_hash(password.toStdString());
//    QString sql_qstring;
//    sql_qstring.sprintf("UPDATE doctor SET password=%s,salt=%s,name=%s,gender=%s,office=%s,zc=%s,describe=%s WHERE id=%s",
//                        ciphertext.first.c_str(),
//                        ciphertext.second.c_str(),
//                        newinfo["name"].toString().toStdString().c_str(),
//                        newinfo["gender"].toString().toStdString().c_str(),
//                        newinfo["office"].toString().toStdString().c_str(),
//                        newinfo["zc"].toString().toStdString().c_str(),
//                        newinfo["describe"].toString().toStdString().c_str(),
//                        newinfo["id"].toString().toStdString().c_str());
//    qDebug() << sql_qstring;
//    QSharedPointer<QJsonDocument> res = nullptr;
//    try {
//        std::string sql = sql_qstring.toStdString();
//        sqlquery(&sql,res);
//    } catch (std::exception e) {
//        throw(e);
//        return res;
//    }
//    QJsonObject obj = res->object();
//    clear_jsonobj(obj);
//    obj["id"] = id;
//    qDebug() << "update succeed!" << obj;
//    res = QSharedPointer<QJsonDocument>(new QJsonDocument(obj));
//    return res;
//}
//QSharedPointer<QJsonDocument> DbServer::update_patientinfo(const QJsonObject& newinfo){
//    QString id = newinfo["id"].toString();
//    QString password = newinfo["password"].toString();
//    auto ciphertext = StringFactory::salt_hash(password.toStdString());
//    QString sql_qstring;
//    sql_qstring.sprintf("UPDATE doctor SET password=%s,salt=%s,name=%s,gender=%s,office=%s,zc=%s,describe=%s WHERE id=%s",
//                        ciphertext.first.c_str(),
//                        ciphertext.second.c_str(),
//                        newinfo["name"].toString().toStdString().c_str(),
//                        newinfo["gender"].toString().toStdString().c_str(),
//                        newinfo["office"].toString().toStdString().c_str(),
//                        newinfo["zc"].toString().toStdString().c_str(),
//                        newinfo["describe"].toString().toStdString().c_str(),
//                        newinfo["id"].toString().toStdString().c_str());
//    qDebug() << sql_qstring;
//    QSharedPointer<QJsonDocument> res = nullptr;
//    try {
//        std::string sql = sql_qstring.toStdString();
//        sqlquery(&sql,res);
//    } catch (std::exception e) {
//        throw(e);
//        return res;
//    }
//    QJsonObject obj = res->object();
//    clear_jsonobj(obj);
//    obj["id"] = id;
//    qDebug() << "update succeed!" << obj;
//    res = QSharedPointer<QJsonDocument>(new QJsonDocument(obj));
//    return res;
//}
const QString & DbServer::get_user(){
    return this->user;
}
const QString & DbServer::get_password(){
    return this->password;
}
const QString & DbServer::get_ip(){
    return this->ip;
}
const QString & DbServer::get_dbname(){
    return this->dbname;
}
const QString & DbServer::get_charset(){
    return this->charset;
}
const int & DbServer::get_port(){
    return this->port;
}

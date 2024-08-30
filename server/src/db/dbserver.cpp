#include "dbserver.h"
//#include<mysql++/mysql++.h>
#include<iostream>
#include"StringFactory.h"
#include<ctime>
#include<global.h>
#include<QtDebug>
#include"qdir.h"
#include"qtimer.h"
#include"qdatetime.h"
#include"qdatastream.h"
#include"qjsondocument.h"
#include"qurl.h"
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
    m_max_idle_time = 28800;
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
    mysqlpp::Connection * conptr = this->create();


    while(!conptr->connected()){
        std::cout << "released one bad connection!" << std::endl;
        qDebug() << "bad connection released";
        release(conptr);
        conptr = new mysqlpp::Connection();
        conptr->connect("database_name", "server_ip", "user", "password");

    }
    mysqlpp::Transaction trans(*conptr);
    try {
        std::string s = sql->substr(0,6);
        for(size_t i = 0; i < s.length();i++)s[i] = toupper(s[i]);

        QJsonArray jsonarray;
        QString sqlq = QString(sql->c_str());
        sqlq = QUrl::fromPercentEncoding(sqlq.toUtf8());
        //std::cout << sqlq.toStdString() << std::endl;
       qDebug() << sqlq;

        mysqlpp::Query query = conptr->query(sqlq.toUtf8());
        qDebug() << "going to query...";
        if(s != "SELECT"){
            mysqlpp::SimpleResult temp = query.execute();
            int success = 0;
            if(temp)success = 1;
            int getid = 0;
            getid = temp.insert_id();// only auto-increment id
            QJsonObject obj;
            if(success) qDebug() << "succeed";
            obj["success"] = success;
            obj["id"] = getid;
            res = QSharedPointer<QJsonDocument>(new QJsonDocument(obj));
            trans.commit();
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
       qDebug() << "after add:" << jsonarray;
        this->release(conptr);
        qDebug() << "completed sql query";
        res = QSharedPointer<QJsonDocument>(new QJsonDocument(jsonarray));
        qDebug() << "res:" << *res;
        trans.commit();
    } catch (std::exception e) {
        trans.rollback();
        throw e;
    }
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
QSharedPointer<QJsonDocument> DbServer::store_file(QString doctorname,
                                         QString patient,
                                         QString oname,
                                         QString type,
                                         const QByteArray& file,
                                         qint32 appointment_id){
    std::string uuidstd = StringFactory::gen_uuid();
    QString sqlq;
    QDateTime currentTime = QDateTime::currentDateTime();
    QString formattedTime = currentTime.toString("yyyy-MM-dd HH:mm:ss");
    sqlq.sprintf("INSERT INTO %s(doctor_id,patient_id,filepath,title,date,appointment_id) VALUES('%s','%s','%s','%s','%s',%d)",
                 type.toStdString().c_str(),
                 doctorname.toStdString().c_str(),
                 patient.toStdString().c_str(),
                 uuidstd.c_str(),
                 oname.toStdString().c_str(),
                 formattedTime.toStdString().c_str(),
                 appointment_id);
    std::string sql = sqlq.toStdString();
    QSharedPointer<QJsonDocument> res;
    try {
        dbserver->sqlquery(&sql,res);
        saveDataToFile(file,"userfile",uuidstd.c_str());
    } catch (std::exception e) {
        throw(e);
        return res;
    }

    return res;
}
QSharedPointer<QByteArray> DbServer::get_file(QString uuidq){
    return getDataFromFile("userfile",uuidq);
}
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
void saveDataToFile(const QByteArray &data, const QString &relativeFilePath, const QString & realFileName) {
    QString currentPath = QDir::currentPath();
    qDebug() << "relativefilepath:" << relativeFilePath;
    QDir dir;
    QString fullFilePath = currentPath + "/" + relativeFilePath ;
    qDebug() << "path:"<< fullFilePath;
    if (!dir.exists(fullFilePath)) {
        dir.mkpath(fullFilePath);
    }
    fullFilePath = fullFilePath + "/" + realFileName;
    QFile file(fullFilePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "write: open file failed!" << file.errorString();
        return;
    }
    qint64 bytesWritten = file.write(data);
    if (bytesWritten == -1) {
        qDebug() << "write: write data failed!" << file.errorString();
    } else if (bytesWritten != data.size()) {
        qDebug() << "write: not all data written!" << bytesWritten << "of" << data.size();
    } else {
        qDebug() << "file write succeed!" << fullFilePath;
    }
    file.close();
    // QDataStream out(&file);
    // out << data;
    // file.close();
}
QSharedPointer<QByteArray> getDataFromFile(const QString &relativeFilePath, const QString realFileName){
    QSharedPointer<QByteArray> data = QSharedPointer<QByteArray>(new QByteArray());
    QString currentPath = QDir::currentPath();
    QDir dir;
    QString filepath = currentPath + "/" + relativeFilePath ;
    if(!dir.exists(filepath)){
        dir.mkpath(filepath);
    }
    filepath = filepath + "/" + realFileName;
    QFile file(filepath);
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "read: open file failed!" << file.errorString();
      ////////////////////////////////////////////////////////////////
        return nullptr;
    }
    *data = file.readAll();
    file.close();
    qDebug() <<  filepath << "file read succeed! : " << data->size();

    

    // QDataStream in(&file);
    // in >> (*data);
    // qDebug() <<  filepath << "file read succeed! : " << data->size();

    return data;
}

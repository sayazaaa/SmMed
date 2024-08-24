#include <dbserver.h>
//#include<mysql++/mysql++.h>
#include<iostream>
#include"StringFactory.h"
#include<ctime>

void clear_jsonobj(QJsonObject & obj){
    auto ptr = obj.begin();
    while(ptr != obj.end()){
        ptr = obj.erase(ptr);
    }
}

DbException::DbException(std::string info):m_info(info){
}
const char * DbException::what() const noexcept{
    return m_info.c_str();
}
DbServer::DbServer(QString user,
                   QString host,
                   QString password,
                   QString ip,
                   QString dbname,
                   QString charset,
                   int port):user(user),host(host),password(password),ip(ip),dbname(dbname),charset(charset),port(port)
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

    conn->connect(dbname.size() ? 0 : dbname.toStdString().c_str(),
    ip.size() ? 0 : ip.toStdString().c_str(),
    user.size() ? 0 : user.toStdString().c_str(),
    password.size() ? "" : password.toStdString().c_str(),
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
    std::string s = sql->substr(0,6);
    for(size_t i = 0; i < s.length();i++)s[i] = toupper(s[i]);

    QJsonArray jsonarray;
    mysqlpp::Connection * conptr = this->create();
    mysqlpp::Query query = conptr->query(sql->c_str());
    if(s != "SELECT"){
        mysqlpp::SimpleResult temp = query.execute();
        int success = 0;
        if(temp)success = 1;
        int getid = 0;
        getid = temp.insert_id();
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
    }
    for(size_t i = 0; i < temp.num_rows(); i++){
        clear_jsonobj(obj);
        for(auto key: fields){
            obj[QString::fromStdString(key)] = QJsonValue(temp[i][key.c_str()].c_str());
            jsonarray.append(obj);
        }
    }
    this->release(conptr);
    res = QSharedPointer<QJsonDocument>(new QJsonDocument(jsonarray));
}
QSharedPointer<QJsonDocument> DbServer::set_userpassword(QString id, QString password){
    auto ciphertext = StringFactory::salt_hash(password.toStdString());
    QString sql_qstring;
    sql_qstring.sprintf("INSERT INTO user(id,password,salt) VALUES(%s,%s,%s)",
                id.toStdString().c_str(),
                ciphertext.first.c_str(),
                ciphertext.second.c_str());
    std::string sql = sql_qstring.toStdString();
    QSharedPointer<QJsonDocument> res;
    sqlquery(&sql,res);
    QJsonObject obj;
    QJsonObject resobj = res->object();
    if(!resobj["success"].toInt()){
        obj["id"] = 0;
        obj["date"] = 0;
        return QSharedPointer<QJsonDocument>(new QJsonDocument(obj));
    }
    obj["id"] = resobj["id"];
    std::time_t time = std::time(nullptr);
    std::tm* now = std::localtime(&time);
    char buffer[80];
    std::strftime(buffer,20,"%Y-%m-%d",now);
    obj["date"] = QString(buffer);
    return QSharedPointer<QJsonDocument>(new QJsonDocument(obj));
}

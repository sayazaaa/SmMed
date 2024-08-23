#include <dbserver.h>
//#include<mysql++/mysql++.h>
#include<iostream>
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
void DbServer::sqlquery(QString *sql, QJsonDocument res, int col){

    QJsonArray jsonarray;
}

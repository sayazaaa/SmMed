#ifndef DBSERVER_H
#define DBSERVER_H
#include<mysql++/mysql++.h>
#include<string>
#include<QSharedPointer>
#include<QScopedPointer>
#include<QJsonDocument>
#include<QJsonArray>
#include<QJsonObject>
class DbServer: public mysqlpp::ConnectionPool {
public:
    DbServer(QString user,
             QString host,
             QString password,
             QString ip,
             QString dbname = "hospitaldb",
             QString charset = "utf-8",
             int port = 80);
    virtual mysqlpp::Connection* grab();
    virtual void release(const mysqlpp::Connection* pc);
    /****************************************************/
    QSharedPointer<QJsonDocument> set_userpassword(QString id , QString password);
    QSharedPointer<QJsonDocument> verify_userpassword(QString id, QString password);
    QSharedPointer<QJsonDocument> set_doctorpassword(QString id, QString password);
    QSharedPointer<QJsonDocument> verify_doctorpassword(QString id, QString password);
    QSharedPointer<QJsonDocument> store_file(QString doctorname, QString patient, QString oname, QByteArray& file);
    QSharedPointer<QJsonDocument> query_doctorinfo(QString id);
    QSharedPointer<QJsonDocument> query_userinfo(QString id);
    QSharedPointer<QJsonDocument> query_patientinfo(QString id);
    QSharedPointer<QJsonDocument> list_doctorinfo(unsigned int officeid);
//    QSharedPointer<QJsonDocument>
    /****************************************************/
    void sqlquery(std::string * sql, QSharedPointer<QJsonDocument> &res);
    bool store_message(QString fromid, QString toid, QString text);
protected:
    virtual mysqlpp::Connection* create();
    virtual void destroy(mysqlpp::Connection *);
    virtual unsigned int max_idle_time();
    size_t size() const;
private:
    const QString user;
    const QString host;
    const QString password;
    const QString ip;
    const QString dbname;
    const QString charset;
    const int port;
    unsigned int m_max_idle_time;
};
class DbException: public std::exception{
public:
    DbException(std::string info = "DATABASE::ERROR");
    const char * what() const noexcept override;
private:
   std::string m_info;

};

#endif

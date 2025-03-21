/**
 * SmMed
 * No description provided (generated by Openapi Generator https://github.com/openapitools/openapi-generator)
 *
 * The version of the OpenAPI document: 1.0.0
 *
 * NOTE: This class is auto generated by OpenAPI Generator (https://openapi-generator.tech).
 * https://openapi-generator.tech
 * Do not edit the class manually.
 */


#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QHostAddress>
#include <QRegExp>
#include<QtDebug>
#include <QStringList>
#include <QSharedPointer>
#include <QObject>
#ifdef __linux__
#include <signal.h>
#include <unistd.h>
#endif
#include <qhttpengine/server.h>
#include "ApiRouter.h"
#include "db/dbserver.h"
#include "global.h"
#include "talkserver.h"
#ifdef __linux__

DbServer * dbserver = nullptr;
QMap<QString,QPair<QString,QString>> apiVerifyMap;
QMap<QString,QString> lastApiMap;
QMap<QString,QString> lastApiMapDoc;
QMap<QString,QTcpSocket*> api_socket;
QString get_api(QString id, QString type){
    if(type == "doctor")return lastApiMapDoc[id];
    else return lastApiMap[id];
}
void catchUnixSignals(QList<int> quitSignals) {
    auto handler = [](int sig) -> void {
        // blocking and not aysnc-signal-safe func are valid
        qDebug() << "\nquit the application by signal " << sig;
        QCoreApplication::quit();
    };

    sigset_t blocking_mask;
    sigemptyset(&blocking_mask);
    for (auto sig : quitSignals)
        sigaddset(&blocking_mask, sig);

    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_mask    = blocking_mask;
    sa.sa_flags   = 0;

    for (auto sig : quitSignals)
        sigaction(sig, &sa, nullptr);
}
#endif

int main(int argc, char * argv[])
{
    QCoreApplication a(argc, argv);
#ifdef __linux__
    QList<int> sigs({SIGQUIT, SIGINT, SIGTERM, SIGHUP});
    catchUnixSignals(sigs);
#endif
    // Build the command-line options
    QCommandLineParser parser;
    QCommandLineOption addressOption(
        QStringList() << "a" << "address",
        "address to bind to",
        "address",
        "0.0.0.0"
    );
    parser.addOption(addressOption);
    QCommandLineOption portOption(
        QStringList() << "p" << "port",
        "port to listen on",
        "port",
        "8080"
    );
    parser.addOption(portOption);
    QCommandLineOption usernameOption(
                QStringList() << "u" << "username",
                "database's username",
                "user",
                "root"
                );

    parser.addOption(usernameOption);
    QCommandLineOption keyOption(
                QStringList() << "k" << "key",
                "database's password",
                "key",
                ""
                );
    parser.addOption(keyOption);
    QCommandLineOption databaseOption(
                QStringList() << "d" << "database",
                "database name",
                "db",
                "hospitaldb"
                );
    parser.addOption(databaseOption);
    QCommandLineOption databasePort(
                QStringList() << "dp" << "databaseport",
                "database port",
                "dp",
                "3306");
    parser.addOption(databasePort);
    QCommandLineOption databaseIp(
                QStringList() << "ip" << "databaseIp",
                "database ip",
                "ip",
                "0.0.0.0"
                );
    parser.addOption(databaseIp);
    QCommandLineOption charset(
                QStringList() << "ch" << "charset",
                "database charset",
                "charset",
                "utf8mb3"
                );
    parser.addOption(charset);
    parser.addHelpOption();

    // Parse the options that were provided
    parser.process(a);
    dbserver = new DbServer(parser.value(usernameOption),
                            parser.value(keyOption),
                            parser.value(databaseIp),
                            parser.value(databaseOption),
                            parser.value(charset),
                            parser.value(databasePort).toInt());
    // Obtain the values
    qDebug() << dbserver->get_user() << " " << dbserver->get_password() <<" " <<  dbserver->get_ip() << " " << dbserver->get_dbname() << " " << dbserver->get_port();
    QString sqlq;


    sqlq.sprintf("USE %s",parser.value(databaseOption).toStdString().c_str());
    QSharedPointer<QJsonDocument> ptr;
    std::string sql = sqlq.toStdString();
    dbserver->sqlquery(&sql,ptr);

    QHostAddress address = QHostAddress(parser.value(addressOption));
    quint16 port = static_cast<quint16>(parser.value(portOption).toInt());

    QSharedPointer<HttpServer::ApiRequestHandler> handler(new HttpServer::ApiRequestHandler());
    auto router = QSharedPointer<HttpServer::ApiRouter>::create();
    router->setUpRoutes();
    QObject::connect(handler.data(), &HttpServer::ApiRequestHandler::requestReceived, [&](QHttpEngine::Socket *socket) {
        router->processRequest(socket);
    });

    QHttpEngine::Server server(handler.data());
    qDebug() << "Serving on " << address.toString() << ":" << port;
    // Attempt to listen on the specified port
    if (!server.listen(address, port)) {
        qCritical("Unable to listen on the specified port.");
        return 1;
    }
   TServer talkserver;
   if (!talkserver.listen(address,8081)) {
       qDebug() << "talk Server could not start!";
       return 1;
   }

   qDebug() << "talk Server started on port" << talkserver.serverPort();
    return a.exec();
}

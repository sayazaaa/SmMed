#ifndef GLOBAL_H
#define GLOBAL_H
#include"db/dbserver.h"
#include<map>
#include<QTcpSocket>
extern DbServer * dbserver;
extern QMap<QString,QPair<QString,QString>> apiVerifyMap;
extern QMap<QString,QString> lastApiMap;
extern QMap<QString,QString> lastApiMapDoc;
extern QMap<QString,QTcpSocket *> api_socket;

QString get_api(QString id, QString type);
#endif

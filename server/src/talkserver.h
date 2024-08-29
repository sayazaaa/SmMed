#ifndef TALKSERVER_H
#define TALKSERVER_H

#include <QTcpServer>
#include <QThreadPool>
#include "usertalkthread.h"
#include <QTcpServer>
#include <QThread>
#include <QMap>
#include "usertalkthread.h"
#include"global.h"
#include"messages.h"
class TServer : public QTcpServer {
    Q_OBJECT
public:
    explicit TServer(QObject* parent = nullptr) : QTcpServer(parent) {}

protected:
    void incomingConnection(qintptr socketDescriptor) override;
private slots:
    void handleForwardMessage(Message& msg);
signals:
    void sendDataToClient(Message& msg, QTcpSocket* recipientSocket);
    void Errorsignal(QString info);
};


#endif// TALKSERVER_H

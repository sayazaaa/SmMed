#ifndef TALKSERVER_H
#define TALKSERVER_H

#include <QTcpServer>
#include <QThreadPool>
#include "usertalkthread.h"
class MyServer : public QTcpServer {
    Q_OBJECT

public:
    explicit MyServer(QObject *parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor) override;
};

#endif // TALKSERVER_H

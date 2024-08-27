#include "talkserver.h"

MyServer::MyServer(QObject *parent): QTcpServer(parent) {
    QThreadPool::globalInstance()->setMaxThreadCount(10);
}
void MyServer::incomingConnection(qintptr socketDescriptor)
{

    ClientTask *task = new ClientTask(socketDescriptor);


    QThreadPool::globalInstance()->start(task);
}

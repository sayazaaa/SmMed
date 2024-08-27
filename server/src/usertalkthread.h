#ifndef USERTALKTHREAD_H
#define USERTALKTHREAD_H
#include<qthread.h>
#include<qtcpsocket.h>
#include<qrunnable.h>
#include <QRunnable>
#include <QTcpSocket>
#include <QDebug>

class ClientTask : public QRunnable {
public:
    explicit ClientTask(qintptr socketDescriptor);

    void run() override;
private:
    qintptr m_socketDescriptor;
};

#endif // USERTALKTHREAD_H

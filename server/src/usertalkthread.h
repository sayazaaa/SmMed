#ifndef USERTALKTHREAD_H
#define USERTALKTHREAD_H
#include<qthread.h>
#include<qtcpsocket.h>
#include<qrunnable.h>
#include <QRunnable>
#include <QTcpSocket>
#include <QDebug>

#include <QTcpSocket>
#include <QThread>
#include <QDataStream>
#include "messages.h"
#include"global.h"
class ClientTask : public QThread {
    Q_OBJECT
public:
    explicit ClientTask(qintptr socketDescriptor, QObject* parent = nullptr);

protected:
    void run() override;

signals:
    void forwardMessage(Message& msg);
    void error(QTcpSocket::SocketError socketError);

public slots:
    void sendMessage(Message& msg, QTcpSocket* recipientSocket);

private slots:
    void handleReadyRead();

    void handleDisconnected();

private:
    qintptr m_socketDescriptor;
};

#endif // USERTALKTHREAD_H

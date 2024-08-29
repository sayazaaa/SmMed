#include "usertalkthread.h"
#include "messages.h"
#include "global.h"
#include"QDataStream"
#include"messages.h"
ClientTask::ClientTask(qintptr socketDescriptor, QObject* parent)
        : QThread(parent), m_socketDescriptor(socketDescriptor) {}

void ClientTask::run(){
    try {
        QTcpSocket* socket = new QTcpSocket();
        qDebug() << "running";
        if (!socket->setSocketDescriptor(m_socketDescriptor)) {
            emit error(socket->error());
            return;
        }
        if(socket->waitForReadyRead(3000)){
            qDebug()<<"getapikey";
            QString apikey;
            apikey = socket->readLine();
            apikey = apikey.trimmed();
            if(!apiVerifyMap.contains(apikey)){
                emit error(QTcpSocket::SocketError::ProxyProtocolError);
                return;
            }
            api_socket[apikey] = socket;
            qDebug() << "api <-> socket:" << socket << endl;
        }else{
            emit error(QTcpSocket::SocketError::ProxyProtocolError);
            return;
        }
        connect(socket, &QTcpSocket::readyRead, this, &ClientTask::handleReadyRead);
        connect(socket, &QTcpSocket::disconnected, this, &ClientTask::handleDisconnected);

        exec();
    } catch (std::exception e) {
        qDebug() << "socket init failed!";
    }
}


void ClientTask::sendMessage(Message& msg, QTcpSocket* recipientSocket) {
    if(recipientSocket->socketDescriptor() != m_socketDescriptor)return;
    if (recipientSocket && recipientSocket->state() == QTcpSocket::ConnectedState) {
        QByteArray block;
        QDataStream out(&block,QIODevice::WriteOnly);
        out << msg;
        qDebug() << recipientSocket->socketDescriptor();
        recipientSocket->write(block);
        recipientSocket->flush();
        qDebug() << "send succeed!";
    }
}

void ClientTask::handleReadyRead(){
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    QSharedPointer<Message> msg = receive_message(*socket);
    qDebug() << "get messsage!!!!!!!!!!!!!!!!!!"<<msg->get_apikey();

    if (msg) {
        QString recipientId = msg->get_recipient();
        emit forwardMessage(*msg);
    }
}

void ClientTask::handleDisconnected() {
    quit();
}

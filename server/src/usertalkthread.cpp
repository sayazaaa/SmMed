#include "usertalkthread.h"
#include "messages.h"
#include "global.h"
#include"QDataStream"
#include"messages.h"
////ClientTask::ClientTask(qintptr socketDescriptor):m_socketDescriptor(socketDescriptor){}
////void ClientTask::run(){
////    QTcpSocket socket;
////    bool verified = 0;
////    if (!socket.setSocketDescriptor(m_socketDescriptor)) {
////        qDebug() << "Failed to set socket descriptor";
////        return;
////    }

////    // 处理客户端请求
////    while (socket.state() == QTcpSocket::ConnectedState) {
////        if (socket.isReadable()) {
////            if(!verified){
////                qDebug() << "Client connected" << "isnt verified";
////                QString apikey;
////                QByteArray block = socket.readLine();
////                QDataStream in(&block,QIODevice::ReadOnly);
////                in >> apikey;
////                apikey = apikey.trimmed();

////                 api_socket[apikey] = QSharedPointer<QTcpSocket>(&socket);
////                verified = 1;
////            }else{
////                 qDebug() << "Client connected" << "is verified";
////                QSharedPointer<Message> ptr = receive_message(socket);
////                if (ptr == nullptr)
////                {
////                    continue;
////                }

////                qDebug() << ptr->get_sender();
////                qDebug() << ptr->get_recipient();
////                QString apikey = ptr->get_apikey();
////                if(api_socket[apikey] == (&socket)){
////                    QSharedPointer<QTcpSocket> tosocket = nullptr;
////                    QString recipient;
////                    if(apiVerifyMap[apikey].first.size()){
////                        if(apiVerifyMap[apikey].second == "user"){
////                            recipient = lastApiMapDoc[ptr->get_recipient()];
////                            tosocket = api_socket[lastApiMapDoc[ptr->get_recipient()]];
////                        }else{
////                            recipient = ptr->get_recipient();
////                            tosocket = api_socket[lastApiMap[ptr->get_recipient()]];
////                        }
////                        qDebug() << recipient;
////                        if(tosocket != nullptr){
////                            QMetaObject::invokeMethod(tosocket.data(), [tosocket,ptr]() {
////                                if (tosocket->state() == QTcpSocket::ConnectedState) {
////                                    // 在这里执行发送消息的逻辑
////                                    send_message(*tosocket, *ptr);
////                                }
////                            }, Qt::QueuedConnection);
////                        }else{
////                        //    QString sqlq;
////                        //    sqlq.sprintf("INSERT INTO messages(sender,recipient,content,sendertype,content_type) VALUES(%s,%s,%s,%s,%s)",
////                        //                 ptr->get_sender(),
////                        //                 ptr->get_recipient(),
////                        //                 ptr->)
////                        //    dbserver->sqlquery()
////                        }
////                   }
////               }
////            }
////        }
////    }

////    socket.disconnectFromHost();
////    socket.waitForDisconnected();
////    qDebug() << "Client disconnected";
////}
//void ClientTask::run(){
//    QTcpSocket socket;
//    if (!socket.setSocketDescriptor(m_socketDescriptor)) {
//        emit error(socket.error());
//        return;
//    }

//    connect(&socket, &QTcpSocket::readyRead, this, &ClientTask::handleReadyRead);
//    connect(&socket, &QTcpSocket::disconnected, this, &ClientTask::handleDisconnected);

//    exec();
//}

ClientTask::ClientTask(qintptr socketDescriptor, QObject* parent)
        : QThread(parent), m_socketDescriptor(socketDescriptor) {}

void ClientTask::run(){
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
}


void ClientTask::sendMessage(Message& msg, QTcpSocket* recipientSocket) {
    if (recipientSocket && recipientSocket->state() == QTcpSocket::ConnectedState) {
        QByteArray block;
        QDataStream out(&block,QIODevice::WriteOnly);
        out << msg;
        recipientSocket->write(block);
        recipientSocket->flush();
        qDebug() << "send succeed!";
    }
}

void ClientTask::handleReadyRead(){
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    QSharedPointer<Message> msg = receive_message(*socket);
    qDebug() << msg->get_apikey();

    if (msg) {
        QString recipientId = msg->get_recipient();
        emit forwardMessage(*msg);
    }
}

void ClientTask::handleDisconnected() {
    quit();
}

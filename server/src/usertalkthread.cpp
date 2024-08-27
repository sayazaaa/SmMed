#include "usertalkthread.h"
#include "messages.h"
#include "global.h"
#include"QDataStream"
#include"messages.h"

ClientTask::ClientTask(qintptr socketDescriptor):m_socketDescriptor(socketDescriptor){}
void ClientTask::run(){
    QTcpSocket socket;
    bool verified = 0;
    if (!socket.setSocketDescriptor(m_socketDescriptor)) {
        qDebug() << "Failed to set socket descriptor";
        return;
    }

    // 处理客户端请求
    while (socket.state() == QTcpSocket::ConnectedState) {
        if (socket.isReadable()) {
            if(!verified){
                qDebug() << "Client connected" << "isnt verified";
                QString apikey;
                QByteArray block = socket.readLine();
                QDataStream in(&block,QIODevice::ReadOnly);
                in >> apikey;
                apikey = apikey.trimmed();

            //     api_socket[apikey] = QSharedPointer<QTcpSocket>(&socket);
                verified = 1;
            }else{
                 qDebug() << "Client connected" << "is verified";
                QSharedPointer<Message> ptr = receive_message(socket);
                if (ptr == nullptr)
                {
                 continue;
                }

                qDebug() << ptr->get_sender();
                qDebug() << ptr->get_recipient();
               // QString apikey = ptr->get_apikey();
               // if(api_socket[apikey] == (&socket)){
               //     QSharedPointer<QTcpSocket> tosocket = nullptr;
               //     QString recipient;
               //     if(apiVerifyMap[apikey].first.size()){
               //         if(apiVerifyMap[apikey].second == "user"){
               //             recipient = lastApiMapDoc[ptr->get_recipient()];
               //             tosocket = api_socket[lastApiMapDoc[ptr->get_recipient()]];
               //         }else{
               //             recipient = ptr->get_recipient();
               //             tosocket = api_socket[lastApiMap[ptr->get_recipient()]];
               //         }
               //         qDebug() << recipient;
               //         if(tosocket != nullptr && tosocket->state() == QTcpSocket::ConnectedState){
               //          qDebug() << tosocket;
               //             send_message(*tosocket,*ptr);
               //         }else{
                        //    QString sqlq;
                        //    sqlq.sprintf("INSERT INTO messages(sender,recipient,content,sendertype,content_type) VALUES(%s,%s,%s,%s,%s)",
                        //                 ptr->get_sender(),
                        //                 ptr->get_recipient(),
                        //                 ptr->)
                        //    dbserver->sqlquery()
                 //      }
                   //}
               //}
            }
        }
    }

    socket.disconnectFromHost();
    socket.waitForDisconnected();
    qDebug() << "Client disconnected";
}

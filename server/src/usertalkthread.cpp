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
        if (socket.waitForReadyRead(3000)) {
            if(!verified){
                QString apikey;
                QByteArray block = socket.readLine();
                QDataStream in(&block,QIODevice::ReadOnly);
                in >> apikey;
                apikey = apikey.trimmed();
                api_socket[apikey] = QSharedPointer<QTcpSocket>(&socket);
            }else{
//                QSharedPointer<Message> ptr = receive_message(socket);
//                QString apikey = ptr->get_apikey();
//                if(api_socket[apikey] == (&socket)){
//                    QSharedPointer<QTcpSocket> tosocket = nullptr;
//                    if(apiVerifyMap[apikey].first.size()){
//                        if(apiVerifyMap[apikey].second == "user"){
//                            tosocket = api_socket[lastApiMapDoc[ptr->get_recipient()]];
//                        }else{
//                            tosocket = api_socket[lastApiMap[ptr->get_sender()]];
//                        }
//                        if(tosocket != nullptr){
//                            send_message(*tosocket,*ptr);
//                        }else{
//                            QString sqlq;
//                            sqlq.sprintf("INSERT INTO messages(sender,recipient,content,sendertype,content_type) VALUES(%s,%s,%s,%s,%s)",
//                                         ptr->get_sender(),
//                                         ptr->get_recipient(),
//                                         ptr->)
//                            dbserver->sqlquery()
//                        }
//                    }
//                }
            }
            socket.waitForBytesWritten(3000);
        }
    }

    socket.disconnectFromHost();
    socket.waitForDisconnected();
    qDebug() << "Client disconnected";
}

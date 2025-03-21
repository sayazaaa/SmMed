#include "talkserver.h"


void TServer::incomingConnection(qintptr socketDescriptor) {
    ClientTask* task = new ClientTask(socketDescriptor);
    qDebug() << "new user...";
    connect(task, &ClientTask::forwardMessage, this, &TServer::handleForwardMessage);
    connect(this, &TServer::sendDataToClient, task, &ClientTask::sendMessage);

    task->start();
}

void TServer::handleForwardMessage(Message& msg) {
    try {
        QString sendertype = apiVerifyMap[msg.get_apikey()].second;
        QString recapi;
        qDebug() <<"sendertype:" <<sendertype;
        if(sendertype == "user"){
            recapi = lastApiMapDoc[msg.get_recipient()];
        }else {
            recapi = lastApiMap[msg.get_recipient()];
        }
        if (api_socket.contains(recapi)) {
            qDebug() << recapi;
            emit sendDataToClient(msg, api_socket.value(recapi));
        } else {
                QString sqlq;
                sqlq.sprintf("INSERT INTO messages(sender,recipient,content,sendertype,content_type) VALUES('%s','%s','%s','%s','%s')",
                            msg.get_sender().toStdString().c_str(),
                            msg.get_recipient().toStdString().c_str(),
                            msg.get_data()->data(),
                            msg.get_sender().toStdString().c_str(),
                            msg.get_type().toStdString().c_str());
                std::string sql = sqlq.toStdString();
                QSharedPointer<QJsonDocument> resdoc;
                dbserver->sqlquery(&sql,resdoc);
        }
    } catch (std::exception e) {
        emit Errorsignal("send into database failed!");
    }
}

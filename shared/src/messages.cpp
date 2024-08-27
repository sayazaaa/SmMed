#include "messages.h"
#include<qiodevice.h>
#include<qdatastream.h>
Message::Message(QString apikey,QString sender, QString recipient):
apikey(apikey),sender(sender),recipient(recipient){}

QString Message::get_sender() const{
    return sender;
}
void Message::set_sender(QString sender){
    this->sender = sender;
}
QString Message::get_recipient() const{
    return recipient;
}
void Message::set_recipient(QString recipient){
    this->recipient = recipient;
}
QString Message::get_apikey() const{
    return apikey;
}
void Message::set_apikey(QString apikey){
    this->apikey = apikey;
}

TextMessage::TextMessage(QString apikey,
                         QString sender,
                         QString recipient,
                         QString text):Message(apikey,sender,recipient),text(text){}
QString TextMessage::get_type() const{
    return "text";
}
void TextMessage::serialize(QDataStream &out) const{
    out << apikey <<"\n"<< sender <<"\n"<< recipient <<"\n"<< text << "\n";
}
void TextMessage::deserialize(QDataStream &in){
    in >> apikey >> sender >> recipient >> text;
}
QString TextMessage::get_text() const{
    return text;
}
void TextMessage::set_text(QString text){
    this->text = text;
}
QByteArray* TextMessage::get_data(){
    return new QByteArray(text.toUtf8());
}
PictureMessage::PictureMessage(QString apikey,
                               QString sender,
                               QString recipient,
                               QByteArray binary_data):Message(apikey,sender,recipient),data(binary_data){}
QString PictureMessage::get_type() const{
    return "picture";
}
void PictureMessage::serialize(QDataStream &out) const{
    out << apikey << sender << recipient << data;
}
void PictureMessage::deserialize(QDataStream &in){
    in >> apikey >> sender >> recipient >> data;
}
QByteArray* PictureMessage::get_data(){
    return (&data);
}
void PictureMessage::set_data(QByteArray& newdata){
    data = newdata;
}

void send_message(QTcpSocket& socket, Message& mes){
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    mes.serialize(out);
    if(mes.get_type() == "picture"){
        PictureMessage* picMsg = static_cast<PictureMessage*>(&mes);
        const QByteArray* imageData = picMsg->get_data();
        sendLargeData(&socket, *imageData);
    }else{
        socket.write(block);
        socket.flush();
    }
}
QSharedPointer<Message> receive_message(QTcpSocket& socket){
    static QByteArray buffer;
        static quint32 expectedSize = 0;
        static QSharedPointer<Message> currentMessage;

        if (!socket.waitForReadyRead(3000)) {
            qDebug() << "Failed to wait for ready read:" << socket.errorString();
            return nullptr;
        }

        buffer.append(socket.readAll());

        // 如果还未接收到完整的数据
        if (expectedSize == 0) {
            if (size_t(buffer.size()) < sizeof(QString)) {
                return nullptr;  // 数据不足，等待更多数据
            }

            QDataStream in(buffer);
            QString type;
            in >> type;

            if (type == "text") {
                currentMessage = QSharedPointer<Message>(new TextMessage());
            } else if (type == "picture") {
                currentMessage = QSharedPointer<Message>(new PictureMessage());
            } else {
                return nullptr;  // 未知消息类型
            }

            // 开始读取消息内容的长度
            buffer.remove(0, sizeof(QString));
        }

        // 处理大数据块
        if (currentMessage && currentMessage->get_type() == "picture") {
            while (buffer.size() > 0) {
                if (expectedSize == 0) {
                    if (size_t(buffer.size()) < sizeof(quint32)) {
                        return nullptr;  // 数据不足，等待更多数据
                    }

                    QDataStream in(buffer);
                    in >> expectedSize;
                    buffer.remove(0, sizeof(quint32));
                }

                if (size_t(buffer.size()) < expectedSize) {
                    return nullptr;  // 数据不足，等待更多数据
                }

                QByteArray chunkData = buffer.left(expectedSize);
                buffer.remove(0, expectedSize);
                expectedSize = 0;

                // 将数据块合并到当前消息
                PictureMessage* picMsg = static_cast<PictureMessage*>(currentMessage.data());
                QByteArray *currentData = picMsg->get_data();
                currentData->append(chunkData);
                picMsg->set_data(*currentData);

                // 完成接收
                if (buffer.isEmpty()) {
                    return currentMessage;
                }
            }
        } else {
            // 处理其他消息类型
            if (size_t(buffer.size()) >= sizeof(QString)) {
                QDataStream in(buffer);
                in >> (*currentMessage);
                return currentMessage;
            }
        }

        return nullptr;
}
void sendLargeData(QTcpSocket *socket, const QByteArray &data) {
    const quint32 chunkSize = 1024 * 1024; // 每块数据大小为 1 MB
    quint32 offset = 0;
    quint32 dataSize = data.size();

    while (offset < dataSize) {
        QByteArray chunk;
        QDataStream out(&chunk, QIODevice::WriteOnly);

        // 计算当前块的大小
        quint32 remainingSize = dataSize - offset;
        quint32 currentChunkSize = qMin(chunkSize, remainingSize);

        // 写入块大小和数据
        out << currentChunkSize;
        out.writeRawData(data.constData() + offset, currentChunkSize);

        // 发送数据块
        socket->write(chunk);
        socket->waitForBytesWritten(3000);

        // 更新偏移量
        offset += currentChunkSize;
    }
}
#include <QTcpSocket>
#include <QDebug>

// 接收数据的函数
void receiveLargeData(QTcpSocket *socket) {
    static QByteArray buffer;
    static quint32 expectedSize = 0;

    if (!socket->waitForReadyRead(3000)) {
        qDebug() << "Failed to wait for ready read:" << socket->errorString();
        return;
    }

    buffer.append(socket->readAll());

    while (buffer.size() > 0) {
        if (expectedSize == 0) {
            if (size_t(buffer.size()) < sizeof(quint32)) {
                return;  // 数据不足，等待更多数据
            }

            QDataStream in(buffer);
            in >> expectedSize;
            buffer.remove(0, sizeof(quint32));
        }

        if (quint32(buffer.size()) < expectedSize) {
            return;  // 数据不足，等待更多数据
        }

        QByteArray chunkData = buffer.left(expectedSize);
        buffer.remove(0, expectedSize);
        expectedSize = 0;

        // 处理接收到的块数据
        qDebug() << "Received data chunk size:" << chunkData.size();
        // 你可以将接收到的数据块合并起来
    }
}

#ifndef MESSAGES_H
#define MESSAGES_H
#include<qstring.h>
#include"qtcpsocket.h"
#include"qdatastream.h"
#include<qsharedpointer.h>
class Message
{
public:
    Message(QString apikey = "",QString sender = "", QString recipient = "");
    virtual QString get_type() const = 0;
    virtual void serialize(QDataStream &out) const = 0;
    virtual void deserialize(QDataStream &in) = 0;
    virtual QByteArray* get_data() = 0;

    QString get_sender() const;
    void set_sender(QString sender);
    QString get_recipient() const;
    void set_recipient(QString recipient);
    QString get_apikey() const;
    void set_apikey(QString apikey);

    friend QDataStream &operator<<(QDataStream &out, const Message &obj) {
        out << obj.get_type();
        obj.serialize(out);
        return out;
    }

    friend QDataStream &operator>>(QDataStream &in, Message &obj) {
        obj.deserialize(in);
        return in;
    }
protected:
    QString apikey;
    QString sender;
    QString recipient;
};

class TextMessage: public Message
{
public:
    TextMessage(QString apikey = "",
                QString sender = "",
                QString recipient = "",
                QString text="");
    virtual QString get_type() const override;
    virtual void serialize(QDataStream &out) const override;
    virtual void deserialize(QDataStream &in) override;
    virtual QByteArray* get_data() override;
    QString get_text() const;
    void set_text(QString text);
private:
    QString text;
};

class PictureMessage: public Message
{
public:
    PictureMessage(QString apikey = "",
                   QString sender = "",
                   QString recipient = "",
                   QByteArray binary_data = QByteArray());
    virtual QString get_type() const override;
    virtual void serialize(QDataStream &out) const override;
    virtual void deserialize(QDataStream &in) override;
    virtual QByteArray* get_data() override;
    void set_data(QByteArray& newdata);
private:
    QByteArray data;
};

//void send_message(QTcpSocket& socket, Message& mes);
//QSharedPointer<Message> receive_message(QTcpSocket& socket);
//void sendLargeData(QTcpSocket *socket, const QByteArray &data);
//void receiveLargeData(QTcpSocket *socket);
void send_message(QTcpSocket& socket, Message& mes);

QSharedPointer<Message> receive_message(QTcpSocket& socket);
#endif // MESSAGES_H

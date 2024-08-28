#ifndef CHAT_BOX_H
#define CHAT_BOX_H

#include<QPainter>
#include<QFileDialog>
#include<QImageReader>
#include <QListWidgetItem>
#include <QWidget>
#include<qnchatmessage.h>
#include <QDateTime>
#include "netclient.h"
#include "netloader.h"
#include "DBManager.h"
#include "apikey.h"

namespace Ui {
class chat_box;
}

class chat_box : public QWidget
{
    Q_OBJECT

public:
    explicit chat_box(QWidget* parent = nullptr);
    chat_box( QString sender_id, QString receiver_id,QWidget *parent = nullptr);
    ~chat_box();
    QNChatMessage* dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time, QNChatMessage::User_Type type);
    void dealMessageTime(QString curMsgTime);
protected:
    void resizeEvent(QResizeEvent *event);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    void net_send_msg(const QString &msg, std::function<void(bool)> callback);
    void net_send_pic(QImage image, std::function<void(bool)> callback);
    Ui::chat_box *ui;
    QSqlDatabase& db;
    NetClient& netClient;
    QString sender_id;
    QString receiver_id;
};

#endif // CHAT_BOX_H

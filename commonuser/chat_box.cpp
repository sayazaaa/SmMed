#include "chat_box.h"
#include "ui_chat_box.h"

#include <QDebug>

chat_box::chat_box(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::chat_box),
    db(DatabaseManager::getInstance().getDatabase()),
    netClient(NetClient::getInstance()),
    sender_id(""),
    receiver_id("") {
    ui->setupUi(this);
    resize(600, 800);
}
chat_box::chat_box(QString sender_id, QString receiver_id, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::chat_box),
    db(DatabaseManager::getInstance().getDatabase()),
    netClient(NetClient::getInstance()),
    sender_id(sender_id),
    receiver_id(receiver_id) {
    ui->setupUi(this);
    resize(600, 800);
}

chat_box::~chat_box() {
    delete ui;
}



void chat_box::on_pushButton_clicked() {
    QString msg = ui->textEdit->toPlainText();
    ui->textEdit->setText("");
    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳
    dealMessageTime(time);
    QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
    QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
    dealMessage(messageW, item, msg, time, QNChatMessage::User_Me);
    net_send_msg(msg, [this, messageW](bool success) {
        if (success) {
            messageW->setTextSuccess();
        }
        else {
            qDebug() << "发送失败";
        }
        });
    qDebug() << "addMessage" << msg << time << ui->listWidget->count();

    ui->listWidget->setCurrentRow(ui->listWidget->count() - 1);
}

QNChatMessage* chat_box::dealMessage(QNChatMessage* messageW, QListWidgetItem* item, QString text, QString time, QNChatMessage::User_Type type) {
    messageW->setFixedWidth(this->width());
    QSize size = messageW->fontRect(text);
    item->setSizeHint(size);
    messageW->setText(text, time, size, type);
    ui->listWidget->setItemWidget(item, messageW);
    return messageW;
}

void chat_box::dealMessageTime(QString curMsgTime) {
    bool isShowTime = false;
    if (ui->listWidget->count() > 0) {
        QListWidgetItem* lastItem = ui->listWidget->item(ui->listWidget->count() - 1);
        QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(lastItem);
        int lastTime = messageW->time().toInt();
        int curTime = curMsgTime.toInt();
        qDebug() << "curTime lastTime:" << curTime - lastTime;
        isShowTime = ((curTime - lastTime) > 60); // 两个消息相差一分钟
        //        isShowTime = true;
    }
    else {
        isShowTime = true;
    }
    if (isShowTime) {
        QNChatMessage* messageTime = new QNChatMessage(ui->listWidget->parentWidget());
        QListWidgetItem* itemTime = new QListWidgetItem(ui->listWidget);

        QSize size = QSize(this->width(), 40);
        messageTime->resize(size);
        itemTime->setSizeHint(size);
        messageTime->setText(curMsgTime, curMsgTime, size, QNChatMessage::User_Time);
        ui->listWidget->setItemWidget(itemTime, messageTime);
    }
}

void chat_box::resizeEvent(QResizeEvent* event) {
    Q_UNUSED(event);


    ui->textEdit->resize(this->width() - 20, ui->widget->height() - 20);
    ui->textEdit->move(10, 10);

    ui->pushButton->move(ui->textEdit->width() + ui->textEdit->x() - ui->pushButton->width() - 10,
        ui->textEdit->height() + ui->textEdit->y() - ui->pushButton->height() - 10);
    ui->pushButton_2->move(ui->textEdit->width() + ui->textEdit->x() - ui->pushButton_2->width() - 90,
        ui->textEdit->height() + ui->textEdit->y() - ui->pushButton_2->height() - 10);


    for (int i = 0; i < ui->listWidget->count(); i++) {
        QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(ui->listWidget->item(i));
        QListWidgetItem* item = ui->listWidget->item(i);

        dealMessage(messageW, item, messageW->text(), messageW->time(), messageW->userType());
    }
}

void chat_box::on_pushButton_2_clicked() {

    QString file = QFileDialog::getOpenFileName(
        this,
        tr("Select an image"),
        ".", // 默认打开的目录
        tr("Image Files (*.bmp *.jpg *.jpeg *.gif *.png)"));
    QImage image = QImageReader(file).read();

    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳

    QString msg = "";
    bool isSending = true; // 发送中
    qDebug() << ui->listWidget->count();
    if (ui->listWidget->count() % 2) {
        if (isSending) {
            dealMessageTime(time);

            QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
            messageW->Message_image = image;
            messageW->setFixedWidth(this->width());
            messageW->setlogoposi();
            item->setSizeHint(QSize(image.width() + 50, image.height() + 50));
            messageW->setText(msg, time, QSize(image.width() + 50, image.height() + 50), QNChatMessage::User_Me);
            ui->listWidget->setItemWidget(item, messageW);
        }
        else {
            bool isOver = true;
            for (int i = ui->listWidget->count() - 1; i > 0; i--) {
                QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(ui->listWidget->item(i));
                if (messageW->text() == msg) {
                    isOver = false;
                    messageW->setTextSuccess();
                }
            }
            if (isOver) {
                dealMessageTime(time);

                QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
                QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
                messageW->Message_image = image;
                messageW->setFixedWidth(this->width());
                messageW->setlogoposi();
                item->setSizeHint(QSize(image.width() + 50, image.height() + 50));
                messageW->setText(msg, time, QSize(image.width() + 50, image.height() + 50), QNChatMessage::User_Me);
                ui->listWidget->setItemWidget(item, messageW);
                messageW->setTextSuccess();
            }
        }
    }
    else {
        if (msg != "" || !image.isNull()) {
            dealMessageTime(time);

            QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
            messageW->Message_image = image;
            messageW->setFixedWidth(this->width());
            messageW->setlogoposi();
            item->setSizeHint(QSize(image.width() + 50, image.height() + 50));
            messageW->setText(msg, time, QSize(image.width() + 50, image.height() + 50), QNChatMessage::User_She);
            ui->listWidget->setItemWidget(item, messageW);
        }
    }
    ui->listWidget->setCurrentRow(ui->listWidget->count() - 1);
}

void chat_box::net_send_msg(const QString& msg, std::function<void(bool)> callback) {
    NetLoader::send_message(sender_id, receiver_id, msg, API_KEY, netClient, callback);
}

void chat_box::net_send_pic(QImage image) {
    //TODO APIKEY
    NetLoader::send_picture(sender_id, receiver_id, image, API_KEY, netClient);
}


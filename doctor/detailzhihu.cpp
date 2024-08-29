/*-------------------------------------------------
#
# Project created by QtCreator
# Author: 沙振宇
# CreateTime: 2018-07-23
# UpdateTime: 2019-12-27
# Info: Qt5气泡式聊天框——QListWidget+QPainter实现
# Url:https://shazhenyu.blog.csdn.net/article/details/81505832
# Github:https://github.com/ShaShiDiZhuanLan/Demo_MessageChat_Qt
#
#-------------------------------------------------*/
#include "detailzhihu.h"
#include "ui_detailzhihu.h"
#include <QDateTime>
#include <QDebug>
#include "apikey.h"
#include "netloader.h"
#include "netclient.h"
#include <qjsonarray.h>

void detailZhihu::setquestion(const QString text)
{
    ui->label->setText(text);
}


detailZhihu::detailZhihu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::detailZhihu)
{
    ui->setupUi(this);

//    ui->pushButton->setDisabled(true);
    resize(600,700);

//    QString sql= R"(
//    SELECT
//        huifu.text AS huifu_text,
//        doctor.name AS doctor_name,
//        huifu.time AS huifu_time
//    FROM
//        user , tiezi , doctor , huifu
//    WHERE
//        tiezi.id = '%)"+ tiez_id +R"(%'
//    )";

//    NetClient &client = NetClient::getInstance();
//    connect(&client, &NetClient::received_json, this, &detailZhihu::handleJsonReceived);
//    NetLoader::get_sql(sql , USER_ID , 0 , API_KEY , client );

    for(now=0;now<allnum;now++)
    {
//        QString msg = ui->textEdit->toPlainText();
//        ui->textEdit->setText("");
//        QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳

        bool isSending = true; // 发送中


        QNChatMessage_zhihu* messageW = new QNChatMessage_zhihu(ui->listWidget->parentWidget());
        QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
        dealMessage(messageW, item, huifutext, huifutime, QNChatMessage_zhihu::User_She);
        ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
    }

}

detailZhihu::~detailZhihu()
{
    delete ui;
}

void detailZhihu::on_pushButton_clicked()
{
    QString msg = ui->textEdit->toPlainText();
    ui->textEdit->setText("");
    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳

    bool isSending = true; // 发送中

    // QString sql = "INSERT INTO huifu (text, tiezi_id, doctor_id, time) VALUES ('"+ msg +"', '"+ tiez_id +"', '" + USER_ID + "', '"+ time +"');";
    // NetClient &client = NetClient::getInstance();
    // NetLoader::get_sql(sql , USER_ID , 0 , API_KEY , client );

    // sql = "UPDATE tiezi  SET num=num+1  WHERE id = '"+tiez_id+"'; ";
    // NetLoader::get_sql(sql , USER_ID , 0 , API_KEY , client );

    QNChatMessage_zhihu* messageW = new QNChatMessage_zhihu(ui->listWidget->parentWidget());
    QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
    dealMessage(messageW, item, msg, time, QNChatMessage_zhihu::User_She);
    ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
}

void detailZhihu::dealMessage(QNChatMessage_zhihu *messageW, QListWidgetItem *item, QString text, QString time,  QNChatMessage_zhihu::User_Type type)
{
    messageW->setFixedWidth(this->width());
    QSize size = messageW->fontRect(text);
    item->setSizeHint(size);

    //    QString sql= R"(
    //    SELECT
    //        doctor.name AS doctor_name
    //    FROM
    //        doctor
    //    WHERE
    //        doctor.id = '%)"+ USER_ID +R"(%'
    //    )";

    //    NetClient &client = NetClient::getInstance();
    //    NetLoader::get_sql(sql , USER_ID , 0 , API_KEY , client );

    messageW->setText(doctorname,text, time, size, type);
    ui->listWidget->setItemWidget(item, messageW);
}



void detailZhihu::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);


    ui->Question->resize(this->width(),(this->height())/7);
    ui->listWidget->resize(this->width(),4*(this->height())/7);
    ui->widget->resize(this->width(),2*(this->height())/7);
    ui->widget->move(0,5*(this->height())/7);
    ui->listWidget->move(0,(this->height())/7);
    ui->textEdit->resize(this->width() - 20, ui->widget->height() - 20);
    ui->textEdit->move(10, 10);

    ui->pushButton->move(ui->textEdit->width()+ui->textEdit->x() - ui->pushButton->width() - 10,
                         ui->textEdit->height()+ui->textEdit->y() - ui->pushButton->height() - 10);


    for(int i = 0; i < ui->listWidget->count(); i++) {
        QNChatMessage_zhihu* messageW = (QNChatMessage_zhihu*)ui->listWidget->itemWidget(ui->listWidget->item(i));
        QListWidgetItem* item = ui->listWidget->item(i);

        dealMessage(messageW, item, messageW->text(), messageW->time(), messageW->userType());
    }
}

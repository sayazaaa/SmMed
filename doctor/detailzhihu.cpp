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

detailZhihu::detailZhihu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::detailZhihu)
{
    ui->setupUi(this);
    resize(600,700);
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
    messageW->setText("李时珍",text, time, size, type);
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

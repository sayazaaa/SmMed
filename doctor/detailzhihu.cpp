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

QVector<QString> doctorid ,doctorname;
QVector<QString> userid ,username ;
QVector<QString> tieziid ,tiezitext,tiezidate ,tiezinum;
QVector<QString> huifuid , huifutext,huifutime ;
int allnum=0;
int pagenow=0;
int searchstate=0;

void detailZhihu::setquestion(const QString text)
{
    ui->label->setText(text);
}


detailZhihu::detailZhihu(QWidget *parent ,QString tzid) :
    QMainWindow(parent),
    tiez_id(tzid),
    ui(new Ui::detailZhihu)
{
    ui->setupUi(this);
    NetClient &client = NetClient::getInstance();

    connect(&client, &NetClient::received_json, this, &detailZhihu::handleJsonReceived_zhihu);

    resize(600,700);

    qDebug()<<"tytytytytytytytytytytytytytytyt";
    qDebug()<<"tiez_id";

    search_901();
}

detailZhihu::~detailZhihu()
{

    qDebug()<<"888                     77777436y45ygertevsd";
    delete ui;
}

void detailZhihu::closeEvent(QCloseEvent *event)
{
    this->~detailZhihu();
    QWidget::closeEvent(event);
}


void detailZhihu::handleJsonReceived_zhihu(const QJsonObject &mainsource)
{
    qDebug()<<"888" << mainsource;

    if(mainsource.size()<=0)return;//如果source为空直接结束
    QJsonArray array=mainsource.value("array").toArray();
    int n=0;
    for(auto item:array){
        QJsonObject source = item.toObject();
        qDebug()<<"777"<<source;
        if(source.contains("doctorid"))//如果source中有"name"值则提取
            doctorid.push_back(source.value("doctorid").toString());
        else doctorid.clear();

        if(source.contains("doctorname"))
            doctorname.push_back(source.value("doctorname").toString());
       else doctorname.clear();

        if(source.contains("userid"))
            userid.push_back(source.value("userid").toString());
       else userid.clear();

        if(source.contains("username"))
            username.push_back(source.value("username").toString());
       else username.clear();

        if(source.contains("tieziid"))
            tieziid.push_back(source.value("tieziid").toString());
       else tieziid.clear();

        if(source.contains("tiezitext"))
            tiezitext.push_back(source.value("tiezitext").toString());
       else tiezitext.clear();

        if(source.contains("tiezidate"))
            tiezidate.push_back(source.value("tiezidate").toString());
       else tiezidate.clear();

        if(source.contains("tiezinum"))
            tiezinum.push_back(source.value("tiezinum").toString());
       else tiezinum.clear();

        if(source.contains("huifuid"))
            huifuid.push_back(source.value("huifuid").toString());
       else huifuid.clear();

        if(source.contains("huifutime"))
            huifutime.push_back(source.value("huifutime").toString());
       else huifutime.clear();

        if(source.contains("huifutext"))
            huifutext.push_back(source.value("huifutext").toString());
       else huifutext.clear();
//        qDebug()<<"111111111111111";
        n++;
    }
    allnum=n;
    pagenow=0;

    if(searchstate==901)
    {
        for(int i=0;i<allnum;i++)
        {
            putin_901();
            pagenow++;
        }
        search_902();
    }



}

void detailZhihu::search_901()
{
    searchstate=901;
    qDebug()<<"9090909090909090909090";
    QString sql=R"(
        SELECT
            huifu.text AS huifutext,
            doctor.name AS doctorname,
            huifu.time AS huifutime,
            doctor.id AS doctorid
        FROM
            huifu, doctor
        WHERE
            huifu.doctor_id = doctor.id AND
            huifu.tiezi_id = ')"+ tiez_id +R"('
    )";
    NetClient &client = NetClient::getInstance();

    NetLoader::get_sql(sql , USER_ID , 0 , API_KEY , client );
}
void detailZhihu::putin_901()
{
    searchstate=901;
    QString msg = huifutext[pagenow];
    ui->textEdit->setText("");
    QString time = QString::number(QDateTime::fromString(huifutime[pagenow]).toTime_t()); //时间戳
//    QString time = QDateTime::fromString(huifutime[pagenow]).toString("yyyy-MM-dd");
    bool isSending = true; // 发送中
    QNChatMessage_zhihu* messageW = new QNChatMessage_zhihu(ui->listWidget->parentWidget());
    QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
//    dealMessage(messageW, item, msg, time, QNChatMessage_zhihu::User_She);
    messageW->setFixedWidth(this->width());
    QSize size = messageW->fontRect(msg);
    item->setSizeHint(size);
    messageW->setText(doctorname[pagenow],msg, time, size, QNChatMessage_zhihu::User_She);
    ui->listWidget->setItemWidget(item, messageW);
    ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
}

void detailZhihu::search_902()
{
    searchstate=902;
    QString sql=R"(
        SELECT
            doctor.name AS doctorname
        FROM
            doctor
        WHERE
            doctor.id = ')"+ USER_ID +R"('
    )";
    NetClient &client = NetClient::getInstance();


    NetLoader::get_sql(sql , USER_ID , 0 , API_KEY , client );
}




void detailZhihu::on_pushButton_clicked()
{
    QString msg = ui->textEdit->toPlainText();
    ui->textEdit->setText("");
    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳
//    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString m_Time = QDateTime::fromTime_t(time.toInt()).toString("yyyy-MM-dd");

    bool isSending = true; // 发送中

    QString sql = "INSERT INTO huifu (text, tiezi_id, doctor_id, time) VALUES ('"+ msg +"', '"+ tiez_id +"', '" + USER_ID + "', '"+ m_Time +"');";
    NetClient &client = NetClient::getInstance();
    NetLoader::get_sql(sql , USER_ID , 0 , API_KEY , client );

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
    messageW->setText(doctorname[0],text, time, size, type);
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

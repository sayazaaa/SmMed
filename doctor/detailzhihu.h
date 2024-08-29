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
#ifndef DETAILZHIHU_H
#define DETAILZHIHU_H

#include<QPainter>
#include<QFileDialog>
#include<QImageReader>
#include <QMainWindow>
#include <QListWidgetItem>
#include "qnchatmessage_zhihu.h"









//QString* doctorid =0, *doctorpassword =0,* doctorsalt =0, *doctorname=0 , *doctorgender=0 , *doctorzc =0, *doctordescribe=0 ,* doctorworkingtime=0;
//QString* userid=0 , *userpassword =0, *usersalt =0, *userage =0, *username =0, *usergender=0 , *userphone =0, *useraddress=0;
//QString* tieziid =0,* tiezitext=0 , *tiezidate =0 , *tiezinum=0;
//QString* huifuid =0,* huifutext=0 , *huifutime =0;

//int allnum=0;
//int now=0;



namespace Ui {
class detailZhihu;
}

class detailZhihu : public QMainWindow
{
    Q_OBJECT

public:
    explicit detailZhihu(QWidget *parent = 0);
    ~detailZhihu();


    int allnum=0;
    int now=0;
    QVector<QString> huifutext;
    QVector<QString> huifutime;
    QVector<QString> doctorname;
//    QString tiez_id;
    QString tiez_id;
//    void setquestion(const QString text);
    void setquestion(const QString text);
    void dealMessage(QNChatMessage_zhihu *messageW, QListWidgetItem *item, QString text, QString time, QNChatMessage_zhihu::User_Type type);
    void dealMessageTime(QString curMsgTime);
protected:
    void resizeEvent(QResizeEvent *event);
private slots:
    void on_pushButton_clicked();


private:
    Ui::detailZhihu *ui;
};

#endif // DETAILZHIHU_H

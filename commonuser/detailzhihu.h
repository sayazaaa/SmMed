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

namespace Ui {
class detailZhihu;
}

class detailZhihu : public QMainWindow
{
    Q_OBJECT

public:
    explicit detailZhihu(QWidget *parent = 0);
    ~detailZhihu();

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

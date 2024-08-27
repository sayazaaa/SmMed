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
#ifndef QNCHATMESSAGE_ZHIHU_H
#define QNCHATMESSAGE_ZHIHU_H

#include <QWidget>
#include<QPushButton>

class QPaintEvent;
class QPainter;
class QLabel;
class QMovie;

class QNChatMessage_zhihu : public QWidget
{
    Q_OBJECT
public:
    explicit QNChatMessage_zhihu(QWidget *parent = nullptr);
    QImage Message_image;

    enum User_Type{
        User_System,//系统
        User_Me,    //自己
        User_She,   //用户
        User_Time,  //时间
    };
    void setTextSuccess();
    void setText(QString name, QString text, QString time, QSize allSize, User_Type userType);
    void setlogoposi();
    QSize getRealString(QString src);
    QSize fontRect(QString str);

    inline QString text() {return m_msg;}
    inline QString time() {return m_time;}
    inline User_Type userType() {return m_userType;}
    void onPushButtonClicked();
    void initPushButton();
protected:
    void paintEvent(QPaintEvent *event);
private:
    QPushButton *m_pushButton = nullptr;
    QString username;
    QString m_title;
    QString m_msg;
    QString m_time;
    QString m_curTime;

    QSize m_allSize;
    User_Type m_userType = User_System;

    int m_kuangWidth;
    int m_textWidth;
    int m_spaceWid;
    int m_lineHeight;

    QRect m_nameRect;
    QRect m_timeRect;
    QRect m_iconLeftRect;

    QRect m_sanjiaoLeftRect;

    QRect m_kuangLeftRect;

    QRect m_textLeftRect;

    QPixmap m_leftPixmap;
    QPixmap m_rightPixmap;
    QLabel* m_loading = Q_NULLPTR;
    QMovie* m_loadingMovie = Q_NULLPTR;
    bool m_isSending = false;
};

#endif // QNCHATMESSAGE_ZHIHU_H

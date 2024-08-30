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
#include "qnchatmessage_zhihu.h"
#include <QFontMetrics>
#include <QPaintEvent>
#include <QDateTime>
#include <QPainter>
#include <QMovie>
#include <QLabel>
#include <QDebug>

QNChatMessage_zhihu::QNChatMessage_zhihu(QWidget *parent) : QWidget(parent)
{
    QFont te_font = this->font();
    te_font.setFamily("MicrosoftYaHei");
    te_font.setPointSize(12);
//    te_font.setWordSpacing(0);
//    te_font.setLetterSpacing(QFont::PercentageSpacing,0);
//    te_font.setLetterSpacing(QFont::PercentageSpacing, 100);          //300%,100为默认  //设置字间距%
//    te_font.setLetterSpacing(QFont::AbsoluteSpacing, 0);             //设置字间距为3像素 //设置字间距像素值
    this->setFont(te_font);
    m_leftPixmap = QPixmap(":/img/Customer Copy.png");
    m_rightPixmap = QPixmap(":/img/CustomerService.png");
//    initPushButton();
    m_loadingMovie = new QMovie(this);
    m_loadingMovie->setFileName(":/img/loading4.gif");
    m_loading = new QLabel(this);
    m_loading->setMovie(m_loadingMovie);
    m_loading->resize(16,16);
    m_loading->setAttribute(Qt::WA_TranslucentBackground , true);
    m_loading->setAutoFillBackground(false);
}

void QNChatMessage_zhihu::setTextSuccess()
{
    m_loading->hide();
    m_loadingMovie->stop();
    m_isSending = true;
}

void QNChatMessage_zhihu::setText(QString name,QString text, QString time, QSize allSize, QNChatMessage_zhihu::User_Type userType)
{
    username = name;
    m_msg = text;
    m_userType = userType;
    m_time = time;
    m_curTime = QDateTime::fromTime_t(time.toInt()).toString("yyyy-MM-dd hh:mm");
    m_allSize = allSize;
    this->update();
}

QSize QNChatMessage_zhihu::fontRect(QString str)
{
    m_msg = str;
    int minHei = 30;
    int iconWH = 40;
    int iconSpaceW = 20;
    int iconRectW = 5;
    int iconTMPH = 10;
    int sanJiaoW = 6;
    int kuangTMP = 20;
    int textSpaceRect = 12;
    m_kuangWidth = this->width() - kuangTMP - 2*(iconWH+iconSpaceW+iconRectW);
    m_textWidth = m_kuangWidth - 2*textSpaceRect;
    m_spaceWid = this->width() - m_textWidth;
    m_iconLeftRect = QRect(iconSpaceW, iconTMPH, iconWH, iconWH);
    m_nameRect = QRect(iconWH+iconSpaceW+iconRectW+25, 0, this->width()-25, 32);
    m_timeRect = QRect(iconWH+iconSpaceW+iconRectW+25, 12, this->width()-25, 48);
    QSize size = getRealString(m_msg); // 整个的size

    qDebug() << "fontRect Size:" << size;
    int hei = size.height() < minHei ? minHei : size.height();

    m_sanjiaoLeftRect = QRect(iconWH+iconSpaceW+iconRectW, m_lineHeight/2, sanJiaoW, hei - m_lineHeight);

    if(size.width() < (m_textWidth+m_spaceWid))
        m_kuangLeftRect.setRect(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), m_lineHeight/4*3, size.width()-m_spaceWid+2*textSpaceRect, hei-m_lineHeight);
    else
        m_kuangLeftRect.setRect(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), m_lineHeight/4*3, m_kuangWidth, hei-m_lineHeight);
        m_textLeftRect.setRect(iconWH+iconSpaceW+iconRectW+25,48,this->width()-150,m_kuangLeftRect.height()-2*iconTMPH);
    return QSize(size.width(), hei+25);
}

QSize QNChatMessage_zhihu::getRealString(QString src)
{
    QFontMetricsF fm(this->font());
    m_lineHeight = fm.lineSpacing();
    int nCount = src.count("\n");
    int nMaxWidth = 0;
    if(nCount == 0) {
        nMaxWidth = fm.width(src);
        QString value = src;
        if(nMaxWidth > m_textWidth) {
            nMaxWidth = m_textWidth;
            int size = m_textWidth / fm.width(" ");
            int num = fm.width(value) / m_textWidth;
            num = ( fm.width(value) ) / m_textWidth;
            nCount += num;
            QString temp = "";
            for(int i = 0; i < num; i++) {
                temp += value.mid(i*size, (i+1)*size) + "\n";
            }
            src.replace(value, temp);
        }
    } else {
        for(int i = 0; i < (nCount + 1); i++) {
            QString value = src.split("\n").at(i);
            nMaxWidth = fm.width(value) > nMaxWidth ? fm.width(value) : nMaxWidth;
            if(fm.width(value) > m_textWidth) {
                nMaxWidth = m_textWidth;
                int size = m_textWidth / fm.width(" ");
                int num = fm.width(value) / m_textWidth;
                num = ((i+num)*fm.width(" ") + fm.width(value)) / m_textWidth;
                nCount += num;
                QString temp = "";
                for(int i = 0; i < num; i++) {
                    temp += value.mid(i*size, (i+1)*size) + "\n";
                }
                src.replace(value, temp);
            }
        }
    }
    return QSize(nMaxWidth+m_spaceWid+1, (nCount + 1) * m_lineHeight+2*m_lineHeight);
}

void QNChatMessage_zhihu::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);//消锯齿
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::gray));

    /*if(m_userType == User_Type::User_She) {*/ // 用户
        //头像
//        painter.drawRoundedRect(m_iconLeftRect,m_iconLeftRect.width(),m_iconLeftRect.height());



        //框加边
        QColor col_KuangB(234, 234, 234);
        painter.setBrush(QBrush(col_KuangB));

        painter.drawRect(0,5,this->width(),20000);
        painter.drawPixmap(m_iconLeftRect, m_leftPixmap);




        QPen penText;
        penText.setColor(QColor(51,51,51));
        painter.setPen(penText);
        QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
        option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        painter.setFont(this->font());
        painter.drawText(m_nameRect,username,option);
        painter.drawText(m_textLeftRect, m_msg,option);
        penText.setColor(QColor(153,153,153));
        painter.setPen(penText);



        painter.drawText(m_timeRect,m_curTime,option);

}
void QNChatMessage_zhihu::setlogoposi()
{
    m_iconLeftRect = QRect(20, 10, 40, 40);
}

void QNChatMessage_zhihu::onPushButtonClicked()
{

}

void QNChatMessage_zhihu::initPushButton()
{
    m_pushButton = new QPushButton(this);
            m_pushButton->setText("联系医生");
            m_pushButton->setFixedSize(75, 30); // 设置按钮的固定尺寸
            m_pushButton->move(0,60);
            connect(m_pushButton, &QPushButton::clicked, this, &QNChatMessage_zhihu::onPushButtonClicked);
}

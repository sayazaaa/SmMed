#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
//最小化相关
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QMenu>
// #include <QAction>
#include<QTimer>
#include<QDateTime>
//自定义弹窗
#include "mymessagebox.h"
#include "framelesswidget.h"
#include "information.h"
#include "little_appointment.h"
#include "chart_create.h"

namespace Ui {
class Widget;
}
class Widget : public FramelessWidget
{
    Q_OBJECT

public slots:
    void handleJsonReceived(const QJsonObject &mainsource);  // 槽函数

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void closeEvent(QCloseEvent *event);

    void changeMboxReturn(int num);

    void on_btn_logout_clicked();

    void on_btn_littleshow_clicked();


    void timerUpdate(void);

    void on_btn_home_clicked();

    void on_btn_menu_item_1_clicked();

    void on_btn_menu_item_3_clicked();

    void on_btn_menu_item_2_clicked();

    void on_btn_menu_item_4_clicked();


    void on_btn_confirm_3_clicked();


    void on_btn_page_left_3_clicked();

    void on_btn_page_right_3_clicked();


    void on_btn_page_1_3_clicked();

    void on_btn_page_2_3_clicked();

    void on_btn_page_3_3_clicked();

    void on_btn_page_4_3_clicked();

    void on_btn_confirm_1_clicked();

    void on_btn_page_left_1_clicked();

    void on_btn_page_1_1_clicked();

    void on_btn_page_2_1_clicked();



    void on_btn_page_3_1_clicked();

    void on_btn_page_4_1_clicked();

    void on_btn_page_right_1_clicked();

    void on_btn_confirm_2_clicked();

    void on_btn_page_left_2_clicked();

    void on_btn_page_1_2_clicked();

    void on_btn_page_2_2_clicked();

    void on_btn_page_3_2_clicked();

    void on_btn_page_4_2_clicked();

    void on_btn_page_right_2_clicked();

    void on_btn_page_left_4_clicked();

    void on_btn_page_1_4_clicked();

    void on_btn_page_2_4_clicked();

    void on_btn_page_3_4_clicked();

    void on_btn_page_4_4_clicked();

    void on_btn_page_right_4_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Widget *ui;

    MyMessageBox *myMbox;
    //自定义窗口通信参数
    int mbox_return;

    //最小化到托盘
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    //窗口管理动作
    QAction *returnNormal;
    QAction *quitAction;

    void initUi();          //Ui界面初始化函数
    void initMember();      //成员变量初始化函数
    void littleShow();      //最小化显示函数

    void search_1();
    void putin_1();
    void delete_1();
    void page_hide_1();

    void search_2();
    void putin_2();
    void delete_2();
    void page_hide_2();

    void search_3();
    void putin_3();
    void delete_3();
    void page_hide_3();

    void search_4();
    void putin_4();
    void delete_4();
    void page_hide_4();
};
QString convertDayToChinese(const QString& day);
#endif // WIDGET_H

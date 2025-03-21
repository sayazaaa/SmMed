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
#include<QListWidgetItem>
//自定义弹窗
#include "mymessagebox.h"
#include "framelesswidget.h"
#include "information.h"
#include "little_appointment.h"

#include<QJsonObject>
#include<QString>
#include<QJsonArray>

namespace Ui {
class Widget;
}
class Widget : public FramelessWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void handleJsonReceived(const QJsonObject &mainsource);  // 槽函数

private slots:
    void closeEvent(QCloseEvent *event);

    void changeMboxReturn(int num);

    void on_btn_main_item_1_clicked();

    void on_btn_main_item_2_clicked();

    void on_btn_main_item_3_clicked();

    void on_btn_main_item_4_clicked();

    void on_btn_logout_clicked();

    void on_btn_littleshow_clicked();

    void on_btn_mine_clicked(bool checked);

    void on_btn_mine_clicked();

    void timerUpdate(void);

    void on_btn_home_clicked();

    void btn_hide();

    void on_btn_menu_item_1_clicked();

    void on_btn_menu_item_3_clicked();

    void on_btn_menu_item_2_clicked();

    void on_btn_menu_item_4_clicked();

    void on_btn_menu_item_5_clicked();

    void on_btn_menu_item_6_clicked();

    void on_btn_report_1_clicked();

    void on_btn_prescription_1_clicked();

    void on_btn_diagnosis_1_clicked();

    void on_btn_page_left_1_clicked();

    void on_btn_page_right_1_clicked();

    void page_hide_1();

    void on_btn_page_1_1_clicked();

    void on_btn_page_2_1_clicked();

    void on_btn_page_3_1_clicked();

    void on_btn_page_4_1_clicked();


    void on_btn_page_right_3_clicked();

    void on_btn_confirm_4_clicked();

    void on_btn_page_left_4_clicked();

    void on_btn_page_right_4_clicked();

    void page_hide_4();

    void on_btn_page_1_4_clicked();

    void on_btn_page_2_4_clicked();

    void on_btn_page_3_4_clicked();

    void on_btn_page_4_4_clicked();


    void on_btn_confirm_8_clicked();

    void on_btn_confirm_9_clicked();

    void onItemClicked_8(QListWidgetItem *item);

    void on_date_1_userDateChanged(const QDate &date);

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

    void search_101();
    void putin_101(int i);
    void delete_101();

    void search_1();
    void putin_1();
    void delete_1();

    void search_3();
    void putin_3();
    void delete_3();

    void search_mine();
    void putin_mine();

    void search_4();
    void putin_4();
    void delete_4();

    void search_8();
//    void putin_8();
    void delete_8();

    void search_801();
    void putin_801();

    void search_802(QString qi);
    void putin_802();


    void search_9();
    void putin_9();
    void delete_9();

};
QString convertDayToChinese(const QString& day);
#endif // WIDGET_H

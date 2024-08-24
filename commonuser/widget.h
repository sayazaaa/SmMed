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
#include"information.h"

namespace Ui {
class Widget;
}

class Widget : public FramelessWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

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


    void on_combo_depart_3_activated(const QString &arg1);

    void on_table_3_cellClicked(int row, int column);

    void on_date_3_userDateChanged(const QDate &date);

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
};
QString convertDayToChinese(const QString& day);
#endif // WIDGET_H

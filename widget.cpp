#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsDropShadowEffect>
int choice_state=0;
Widget::Widget(QWidget *parent) :
    FramelessWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);
    this->initUi();
    this->initMember();
}

Widget::~Widget()
{
    delete ui;
}

/**********************************************************初始化函数****************************************************************/

void Widget::initUi()
{
    //初始化窗口边框
    //this->setAttribute(Qt::WA_StyledBackground);
    //this->setAttribute(Qt::WA_TranslucentBackground, true);
    //this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_Hover);
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setColor(QColor("#444444"));
    shadow->setBlurRadius(16);
    ui->w_bg->setGraphicsEffect(shadow);
    ui->lay_bg->setMargin(12);

    //Logo
    QPixmap logo(":/icons/logo.png");
    ui->lab_logo->setPixmap(logo);

    btn_hide();
    ui->sw_main->setCurrentIndex(0);

}

void Widget::initMember()
{
    this->myMbox = new MyMessageBox();
    connect(myMbox,SIGNAL(btnchicked(int)),this,SLOT(changeMboxReturn(int)));

    //最小化到托盘
    QIcon icon = QIcon(":/icons/logo.png");//设置最小图标
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(icon);
    trayIcon->setToolTip("BIT SMS"); //提示文字
    //添加托盘列表项(还原与退出)
    returnNormal = new QAction(" 打开", this);
    returnNormal->setFont(QFont("Arial", 9));
    returnNormal->setObjectName("returnNormal");
    returnNormal->setIcon(QIcon(":/icons/show.png"));
    quitAction = new QAction(" 关闭", this);
    quitAction->setFont(QFont("Arial", 9));
    quitAction->setObjectName("quitAction");
    quitAction->setIcon(QIcon(":/icons/out.png"));
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));           //绑定槽函数退出
    connect(returnNormal, SIGNAL(triggered()), this, SLOT(showNormal()));   //绑定槽函数还原界面

    //创建托盘菜单(必须先创建动作，后添加菜单项，还可以加入菜单项图标美化)
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(returnNormal);
    trayIconMenu->addAction(quitAction);
    trayIcon->setContextMenu(trayIconMenu);
}

/**********************************************************自定义函数****************************************************************/

void Widget::littleShow()
{
    this->hide();//隐藏主窗口
    trayIcon->show();//显示托盘

    //显示到系统提示框的信息
    QString title="BIT SMS";
    QString text="正自动在后台运行";
    trayIcon->showMessage(title,text,QSystemTrayIcon::Information,3000); //此参数为提示时长
}

/**********************************************************控件槽函数****************************************************************/

void Widget::closeEvent(QCloseEvent *event)
{
    myMbox->setIcon("question");
    myMbox->setBodyText("退出提示              ");
    myMbox->setButtonText("最小化到托盘","直接关闭应用");
    myMbox->exec();
    if(mbox_return == 0) {
        event->ignore();
    }else if(mbox_return == 1){
        event->ignore();
        littleShow();
    }
}

void Widget::changeMboxReturn(int num)
{
    this->mbox_return = num;
}

void Widget::on_btn_main_item_1_clicked()
{
    ui->sw_main->setCurrentIndex(2*choice_state-1);
}

void Widget::on_btn_main_item_2_clicked()
{
    ui->sw_main->setCurrentIndex(2*choice_state);
}

void Widget::on_btn_main_item_3_clicked()
{
    ui->sw_main->setCurrentIndex(2*choice_state+1);
}

void Widget::on_btn_main_item_4_clicked()
{
    ui->sw_main->setCurrentIndex(3);
}

void Widget::on_btn_logout_clicked()
{
    close();
}

void Widget::on_btn_littleshow_clicked()
{
    showMinimized();
}

void Widget::on_btn_mine_clicked(bool checked)
{

}


void Widget::on_btn_mine_clicked()
{
    information *me=new information;
    me->show();
}


void Widget::on_btn_menu_item_1_clicked()
{
    ui->sw_main->setCurrentIndex(1);
    choice_state=1;
    btn_hide();
    ui->btn_main_item_1->setText("最近一年");
    ui->btn_main_item_2->setText("更早");
    ui->btn_main_item_1->show();
    ui->btn_main_item_2->show();
}

void Widget::timerUpdate(void)
{
    QDateTime time = QDateTime::currentDateTime();
    QString timeStr=time.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->time_block->setText(timeStr);
}


void Widget::on_btn_home_clicked()
{
    choice_state=0;
    ui->sw_main->setCurrentIndex(0);
    btn_hide();
}

void Widget::btn_hide()
{
    ui->btn_main_item_1->hide();
    ui->btn_main_item_2->hide();
    ui->btn_main_item_3->hide();
    ui->btn_main_item_4->hide();
}

void Widget::on_btn_menu_item_3_clicked()
{
    ui->sw_main->setCurrentIndex(3);
    choice_state=2;
    btn_hide();
    ui->btn_main_item_1->setText("挂号预约");
    ui->btn_main_item_2->setText("预约信息");
    ui->btn_main_item_1->show();
    ui->btn_main_item_2->show();
}


void Widget::on_btn_menu_item_2_clicked()
{
    ui->sw_main->setCurrentIndex(5);
    choice_state=3;
    btn_hide();
    ui->btn_main_item_1->setText("当日在班医生");
    ui->btn_main_item_2->setText("本周可预约医生");
    ui->btn_main_item_1->show();
    ui->btn_main_item_2->show();
}


void Widget::on_btn_menu_item_4_clicked()
{
    ui->sw_main->setCurrentIndex(7);
    choice_state=4;
    btn_hide();
    ui->btn_main_item_1->setText("医生列表");
    ui->btn_main_item_2->setText("询问历史");
    ui->btn_main_item_1->show();
    ui->btn_main_item_2->show();
}


void Widget::on_btn_menu_item_5_clicked()
{
    ui->sw_main->setCurrentIndex(9);
    choice_state=5;
    btn_hide();
    ui->btn_main_item_1->setText("研发人员");
    ui->btn_main_item_2->setText("意见反馈");
    ui->btn_main_item_3->setText("联系我们");
    ui->btn_main_item_1->show();
    ui->btn_main_item_2->show();
    ui->btn_main_item_3->show();
}


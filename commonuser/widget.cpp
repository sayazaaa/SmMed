#include "widget.h"
#include "ui_widget.h"
#include "newappointment.h"
#include <QGraphicsDropShadowEffect>
#include <QString>
#include <QDebug>
int choice_state=0;
int page_now=0;
int page_max=0;
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
    // this->setAttribute(Qt::WA_StyledBackground);
    // this->setAttribute(Qt::WA_TranslucentBackground, true);
    // this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
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

void Widget::page_hide_3()
{
    ui->btn_page_1_3->hide();
    ui->btn_page_2_3->hide();
    ui->btn_page_3_3->hide();
    ui->btn_page_4_3->hide();
}

void Widget::delete_3()
{
    //清空QlistWidget
    int n=ui->listWidget_3->count();//获取item的总数
//    删去所有item
    for(int i=0;i<n;i++)
    {
        QListWidgetItem *item = ui->listWidget_3->takeItem(0);
        delete item;
    }
}


void Widget::putin_3()
{
    //通过 医生序号doc_id[] 当前页数 page_now
    //获得 姓名doc_name[] 性别doc_gender[] 科室doc_apartment[]
    //填写QlistWidget

    //假定数据
    QString doc_name="abcdefghijskdscsdfacs";

    page_hide_3();
    //填写页数
    ui->btn_page_now_3->setText(QString::number(page_now));
    ui->btn_page_now_3->setEnabled(false);
    if(page_now>3)
    {
        ui->btn_page_2_3->setText("...");
        ui->btn_page_2_3->show();
        ui->btn_page_2_3->setEnabled(false);
        ui->btn_page_1_3->setText("1");
        ui->btn_page_1_3->show();
    }
    else if(page_now==3)
    {
        ui->btn_page_2_3->setText("2");
        ui->btn_page_2_3->show();
        ui->btn_page_1_3->setText("1");
        ui->btn_page_1_3->show();
    }
    else if(page_now==2)
    {
        ui->btn_page_2_3->setText("1");
        ui->btn_page_2_3->show();
    }
    if(page_max-page_now>2)
    {
        ui->btn_page_3_3->setText("...");
        ui->btn_page_3_3->setEnabled(false);
        ui->btn_page_3_3->show();
        ui->btn_page_4_3->setText(QString::number(page_max));
        ui->btn_page_4_3->show();
    }
    else if(page_max-page_now==2)
    {
        ui->btn_page_3_3->setText(QString::number(page_max-1));
        ui->btn_page_3_3->show();
        ui->btn_page_4_3->setText(QString::number(page_max));
        ui->btn_page_4_3->show();
    }
    else if(page_max-page_now==1)
    {
        ui->btn_page_3_3->setText(QString::number(page_max));
        ui->btn_page_3_3->show();
    }

    //创建item
    little_appointment *w = new little_appointment;
    QListWidgetItem* pItem = new QListWidgetItem;
    //填入数据
    w->set_label_doc_name(  doc_name.mid(2,3)  );
    w->set_label_gender("girl");
    w->set_label_apartment("酱油部");

//    pItem->setBackground(QColor("green"));
    //设置item大小
    pItem->setSizeHint(QSize(ui->listWidget_3->width()/3-10,ui->listWidget_3->height()/3 ));
    //添加进QlistWidget
    ui->listWidget_3->addItem(pItem);
    ui->listWidget_3->setItemWidget(pItem, w);
    //不可被选中
    pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
}
void Widget::search_3()
{
    //get data()
    //通过 科室apartment 日期date 姓名searched_name 性别doc_gender
    //得到 数据总量data_num 总页数page_num 医生序号doc_id[] 当前页数page_now
    int data_num=9456;
    page_max=data_num/9+1;
    page_now=1;
    int doc_id[6]={1,2,3,4,5,6};

    //填写总数据量
    ui->label_data_num_text_3->setText("共有"+QString::number(data_num)+"项数据");
    //删除数据
    delete_3();
    //填入数据
    for(int i=0;i<9;i++)
    {
        putin_3();//缺少参数
    }



}
void Widget::on_btn_main_item_1_clicked()
{
    //显示page
    ui->sw_main->setCurrentIndex(2*choice_state-1);
    //预约挂号
    if(choice_state == 2)
    {
        //初始化日期
        ui->date_3->setDisplayFormat("yyyy/MM/dd");
        ui->date_3->setDate(QDate::currentDate());
        ui->date_3->setMinimumDate(QDate::currentDate());
        ui->date_3->setMaximumDate(QDate::currentDate().addDays(10));
        ui->date_3->setCalendarPopup(true);

        search_3();
    }
}

void Widget::on_btn_main_item_2_clicked()
{
    ui->sw_main->setCurrentIndex(2*choice_state);

    //我的预约
    if(choice_state == 2)
    {

        ui->listWidget_4->setWrapping(true);						//自动换行
        ui->listWidget_4->setFlow(QListView::LeftToRight);

        little_appointment *w = new little_appointment[9];
        QListWidgetItem* pItem = new QListWidgetItem[9];

        for(int i=0;i<9;i++)
        {

            (pItem+i)->setSizeHint(QSize(ui->listWidget_4->width()/3-10,ui->listWidget_4->height()/3 ));
            (pItem+i)->setFlags(Qt::ItemIsEnabled);//双击可选中
            (pItem+i)->setCheckState(Qt::Unchecked);//默认 不选中状态
            ui->listWidget_4->addItem(pItem+i);
            ui->listWidget_4->setItemWidget(pItem+i, w+i);
        }

        ui->listWidget_4->setDragEnabled(false);
        //设置每个子项的大小固定
        ui->listWidget_4->setUniformItemSizes(true);
        //设置QLisView大小改变时，图标的调整模式，默认是固定的，可以改成自动调整
        ui->listWidget_4->setResizeMode(QListView::Adjust);
        //设置每个子项之间的间距
        ui->listWidget_4->setSpacing(0);


        //填写日期
        ui->date_3->setDisplayFormat("yyyy/MM/dd");
        ui->date_3->setDate(QDate::currentDate());
        ui->date_3->setCalendarPopup(true);

    }

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

// 映射表：英文星期名称到中文星期名称
QMap<QString, QString> dayMap = {
    {"Sunday", "星期日"},
    {"Monday", "星期一"},
    {"Tuesday", "星期二"},
    {"Wednesday", "星期三"},
    {"Thursday", "星期四"},
    {"Friday", "星期五"},
    {"Saturday", "星期六"}
};

// 将英文星期名称转换为中文星期名称
QString convertDayToChinese(const QString& day)
{
    auto it = dayMap.find(day);
    if (it != dayMap.end())
    {
        return it.value();
    }
    else
    {
        // 如果找不到对应的星期名称，返回原字符串
        return day;
    }
}

void Widget::timerUpdate(void)
{
    QDateTime time = QDateTime::currentDateTime();
    QString timeStr=time.toString("yyyy-MM-dd hh:mm:ss ");
    QString day=time.toString("dddd");
    ui->time_block->setText(timeStr+convertDayToChinese(day));
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

void Widget::on_btn_menu_item_1_clicked()
{
    choice_state=1;
    ui->sw_main->setCurrentIndex(0);
    btn_hide();
    ui->btn_main_item_1->setText("最近一年");
    ui->btn_main_item_2->setText("更早");
    ui->btn_main_item_1->show();
    ui->btn_main_item_2->show();
}

void Widget::on_btn_menu_item_2_clicked()
{
    choice_state=2;
    ui->sw_main->setCurrentIndex(0);
    btn_hide();
    ui->btn_main_item_1->setText("预约挂号");
    ui->btn_main_item_2->setText("我的预约");
    ui->btn_main_item_1->show();
    ui->btn_main_item_2->show();
}

void Widget::on_btn_menu_item_3_clicked()
{
    choice_state=3;
    ui->sw_main->setCurrentIndex(0);
    btn_hide();
    ui->btn_main_item_1->setText("当日在班医生");
    ui->btn_main_item_2->setText("本周可预约医生");
    ui->btn_main_item_1->show();
    ui->btn_main_item_2->show();
}

void Widget::on_btn_menu_item_4_clicked()
{
    choice_state=4;
    ui->sw_main->setCurrentIndex(0);
    btn_hide();
    ui->btn_main_item_1->setText("医生列表");
    ui->btn_main_item_2->setText("询问历史");
    ui->btn_main_item_1->show();
    ui->btn_main_item_2->show();
}

void Widget::on_btn_menu_item_5_clicked()
{
    choice_state=5;
    ui->sw_main->setCurrentIndex(0);
    btn_hide();
    ui->btn_main_item_1->setText("健康评估");
    ui->btn_main_item_2->setText("评估历史");
    ui->btn_main_item_1->show();
    ui->btn_main_item_2->show();
}

void Widget::on_btn_menu_item_6_clicked()
{
    choice_state=6;
    ui->sw_main->setCurrentIndex(0);
    btn_hide();
    ui->btn_main_item_1->setText("研发人员");
    ui->btn_main_item_2->setText("意见反馈");
    ui->btn_main_item_3->setText("联系我们");
    ui->btn_main_item_1->show();
    ui->btn_main_item_2->show();
    ui->btn_main_item_3->show();
}

void Widget::on_btn_confirm_3_clicked()
{
//    获取需要查询的 科室apartment 日期date 姓名doc_name 性别gender
    QString apartment = ui->combo_depart_3->currentText();
    QDate date = ui->date_3->date();
    QString doc_name = ui->lineEdit_docname_3->text();
    QString gender =  ui->combo_gender_3->currentText();

//    查询
    search_3();//参数未填充

}





void Widget::on_btn_page_left_3_clicked()
{
    if(page_now!=1)
    {
        page_now--;
        delete_3();
        for(int i=0;i<9;i++)
        {
            putin_3();//缺少参数
        }
    }
}


void Widget::on_btn_page_right_3_clicked()
{
    if(page_now!=page_max)
    {
        page_now++;
        delete_3();
        for(int i=0;i<9;i++)
        {
            putin_3();//缺少参数
        }
    }
}


void Widget::on_btn_page_1_3_clicked()
{
    page_now=1;
    delete_3();
    for(int i=0;i<9;i++)
    {
        putin_3();//缺少参数
    }
}


void Widget::on_btn_page_2_3_clicked()
{
    page_now--;
    delete_3();
    for(int i=0;i<9;i++)
    {
        putin_3();//缺少参数
    }

}


void Widget::on_btn_page_3_3_clicked()
{
    page_now++;
    delete_3();
    for(int i=0;i<9;i++)
    {
        putin_3();//缺少参数
    }
}


void Widget::on_btn_page_4_3_clicked()
{
    page_now=page_max;
    delete_3();
    for(int i=0;i<9;i++)
    {
        putin_3();//缺少参数
    }
}


#include "widget.h"
#include "ui_widget.h"
#include "newappointment.h"
#include "myappointment.h"
#include "little_doctor.h"
#include "little_history.h"
#include "nowdiagnose.h"
#include "little_zhihu.h"
#include "netclient.h"
#include "netloader.h"
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QString>
#include <QDebug>
int choice_state=0;
int page_now=0;
int page_max=0;

int three_which=0;

QString* doctor_id =0, *doctor_password =0,* doctor_salt =0, *doctor_name=0 , *doctor_gender=0 , *doctor_zc =0, *doctor_describe=0 ,* doctor_workingtime=0;
QString* office_name=0 ,  *office_id =0;
QString* user_id=0 , *user_password =0, *user_salt =0, *user_age =0, *user_name =0, *user_gender=0 , *user_phone =0, *user_address=0;
QString* inspreport_id=0 , *inspreport_filepath=0 ,* inspreport_title =0, *inspreport_date=0;
QString* patient_id =0,* patient_name =0, *patient_gender=0 , *patient_phone=0 ;
QString* appointment_id =0, *appointment_date =0, *appointment_num=0 , *appointment_time=0;
QString* notifications_id =0,* notifications_title =0,* notifications_time=0 ,* notifications_enddate=0 , *notifications_content=0;
QString* diagnosis_id =0, *diagnosis_title=0 , *diagnosis_filepath=0 , *diagnosis_date=0;
QString* prescription_id =0,* prescription_title=0 , *prescription_filepath =0, *prescription_date=0;
int all_num=0;

int page_state=1;
QString  my_id="666";
//QString apikey="";
NetClient &client = NetClient::getInstance();



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

    // 将 QListWidget 的 itemClicked 信号连接到槽函数
    connect(ui->listWidget_8, &QListWidget::itemClicked, this, &Widget::onItemClicked_8);

    connect(&client, &NetClient::received_json, this, &Widget::handleJsonReceived);

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


void Widget::handleJsonReceived(const QJsonObject &mainsource)
{

    if(mainsource.size()<=0)return;//如果source为空直接结束
    QJsonArray array=mainsource.value("data").toArray();
    int n=0;
    for(auto item:array){
        QJsonObject source = item.toObject();
        if(source.contains("doctor_id"))//如果source中有"name"值则提取
            *(doctor_id+n)=source.value("doctor_id").toString();
//        else doctor_id=0;

        if(source.contains("doctor_password"))
            *(doctor_password+n)=source.value("doctor_password").toString();
//        else doctor_password=0;

        if(source.contains("doctor_salt"))
            *(doctor_salt+n)=source.value("doctor_salt").toString();
//        else doctor_salt=0;

        if(source.contains("doctor_name"))
            *(doctor_name+n)=source.value("doctor_name").toString();
//        else doctor_name=0;

        if(source.contains("doctor_gender"))
            *(doctor_gender+n)=source.value("doctor_gender").toString();
//        else doctor_gender=0;

        if(source.contains("doctor_describe"))
            *(doctor_describe+n)=source.value("doctor_describe").toString();
//        else doctor_describe=0;

        if(source.contains("doctor_workingtime"))
            *(doctor_workingtime+n)=source.value("doctor_workingtime").toString();
//        else doctor_workingtime=0;

        if(source.contains("doctor_zc"))
            *(doctor_zc+n)=source.value("doctor_zc").toString();
//        else doctor_zc=0;

        if(source.contains("office_name"))
            *(office_name+n)=source.value("office_name").toString();
//        else office_name=0;

        if(source.contains("office_id"))
            *(office_id+n)=source.value("office_id").toString();
//        else office_id=0;

        if(source.contains("user_id"))
            *(user_id+n)=source.value("user_id").toString();
//        else user_id=0;

        if(source.contains("user_password"))
            *(user_password+n)=source.value("user_password").toString();
//        else user_password=0;

        if(source.contains("user_salt"))
            *(user_salt+n)=source.value("user_salt").toString();
//        else user_salt=0;

        if(source.contains("user_age"))
            *(user_age+n)=source.value("user_age").toString();
//        else user_age=0;

        if(source.contains("user_name"))
            *(user_name+n)=source.value("user_name").toString();
//        else user_name=0;

        if(source.contains("user_gender"))
            *(user_gender+n)=source.value("user_gender").toString();
//        else user_gender=0;

        if(source.contains("user_phone"))
            *(user_phone+n)=source.value("user_phone").toString();
//        else user_phone=0;

        if(source.contains("user_address"))
            *(user_address+n)=source.value("user_address").toString();
//        else user_address=0;

        if(source.contains("inspreport_id"))
            *(inspreport_id+n)=source.value("inspreport_id").toString();
//        else inspreport_id=0;

        if(source.contains("inspreport_filepath"))
            *(inspreport_filepath+n)=source.value("inspreport_filepath").toString();
//        else inspreport_filepath=0;

        if(source.contains("inspreport_title"))
            *(inspreport_title+n)=source.value("inspreport_title").toString();
//        else inspreport_title=0;

        if(source.contains("inspreport_date"))
            *(inspreport_date+n)=source.value("inspreport_date").toString();
//        else inspreport_date=0;

        if(source.contains("patient_id"))
            *(patient_id+n)=source.value("patient_id").toString();
//        else patient_id=0;

        if(source.contains("patient_name"))
            *(patient_name+n)=source.value("patient_name").toString();
//        else patient_name=0;

        if(source.contains("patient_gender"))
            *(patient_gender+n)=source.value("patient_gender").toString();
//        else patient_gender=0;

        if(source.contains("patient_phone"))
            *(patient_phone+n)=source.value("patient_phone").toString();
//        else patient_phone=0;

        if(source.contains("appointment_id"))
            *(appointment_id +n)=source.value("appointment_id").toString();
//        else appointment_id =0;

        if(source.contains("appointment_date"))
            *(appointment_date+n)=source.value("appointment_date").toString();
//        else appointment_date=0;

        if(source.contains("appointment_num"))
            *(appointment_num+n)=source.value("appointment_num").toString();
//        else appointment_num=0;

        if(source.contains("appointment_time"))
            *(appointment_time+n)=source.value("appointment_time").toString();
//        else appointment_time=0;

        if(source.contains("notifications_id"))
            *(notifications_id+n)=source.value("notifications_id").toString();
//        else notifications_id=0;

        if(source.contains("notifications_title"))
            *(notifications_title+n)=source.value("notifications_title").toString();
//        else notifications_title=0;

        if(source.contains("notifications_time"))
            *(notifications_time+n)=source.value("notifications_time").toString();
//        else notifications_time=0;

        if(source.contains("notifications_enddate"))
            *(notifications_enddate+n)=source.value("notifications_enddate").toString();
//        else notifications_enddate=0;

        if(source.contains("notifications_content"))
            *(notifications_content+n)=source.value("notifications_content").toString();
//        else notifications_content=0;

        if(source.contains("diagnosis_id"))
            *(diagnosis_id+n)=source.value("diagnosis_id").toString();
//        else diagnosis_id=0;

        if(source.contains("diagnosis_title"))
            *(diagnosis_title+n)=source.value("diagnosis_title").toString();
//        else diagnosis_title=0;

        if(source.contains("diagnosis_filepath"))
            *(diagnosis_filepath+n)=source.value("diagnosis_filepath").toString();
//        else diagnosis_filepath=0;

        if(source.contains("diagnosis_date"))
            *(diagnosis_date+n)=source.value("diagnosis_date").toString();
//        else diagnosis_date=0;

        if(source.contains("prescription_id"))
            *(prescription_id+n)=source.value("prescription_id").toString();
//        else prescription_id=0;

        if(source.contains("prescription_title"))
            *(prescription_title+n)=source.value("prescription_title").toString();
//        else prescription_title=0;

        if(source.contains("prescription_filepath"))
            *(prescription_filepath+n)=source.value("prescription_filepath").toString();
//        else prescription_filepath=0;

        if(source.contains("prescription_date"))
            *(prescription_date+n++)=source.value("prescription_date").toString();
//        else prescription_date=0;

    }
    all_num=n;


}


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

    //最近一年看诊记录
    if(choice_state == 1)
    {
        //显示page
        ui->sw_main->setCurrentIndex(2*choice_state-1);
        //初始化日期
        ui->date_1->setDisplayFormat("yyyy/MM/dd");
        ui->date_1->setDate(QDate::currentDate());
        ui->date_1->setMinimumDate(QDate::currentDate().addYears(-1));
        ui->date_1->setMaximumDate(QDate::currentDate());
        ui->date_1->setCalendarPopup(true);
//        search_1();
    }
    //开始看诊
    if(choice_state == 2)
    {
        //显示page
        ui->sw_main->setCurrentIndex(2*choice_state-1);
        //初始化日期
        ui->date_3->setDisplayFormat("yyyy/MM/dd");
        ui->date_3->setDate(QDate::currentDate());
        ui->date_3->setReadOnly(true);
        QTime currentTime = QTime::currentTime();
        if(currentTime>QTime(8,0,0) && currentTime<QTime(12,0,0) )
        {
            ui->label_time_3->setText("上午");
        }
        else if(currentTime>QTime(13,0,0) && currentTime<QTime(17,0,0) )
        {
            ui->label_time_3->setText("下午");
        }
        else if(currentTime>QTime(18,0,0) && currentTime<QTime(22,0,0) )
        {
            ui->label_time_3->setText("晚上");
        }
        else
        {
            ui->label_time_3->setText("非工作时间");
        }
        search_3();
    }
    //我的预约
    if(choice_state == 3)
    {
        //显示page
        ui->sw_main->setCurrentIndex(4);
        //初始化日期
        ui->date_4->show();
        ui->label_date_text_4->show();
        ui->date_4->setDisplayFormat("yyyy/MM/dd");
        ui->date_4->setDate(QDate::currentDate());
        ui->date_4->setReadOnly(false);
        ui->date_4->setCalendarPopup(true);

        ui->label_date_text_4->setText("预约日期");

        search_4();
    }

//    //医患沟通患者一览
//    if(choice_state == 4)
//    {
//        //显示page
//        ui->sw_main->setCurrentIndex(5);
//        //初始化日期
//        ui->date_5->hide();
//        ui->label_date_5->hide();

//        search_5();
//    }
    //zhihu
    if(choice_state == 5)
    {
        //显示page
        ui->sw_main->setCurrentIndex(2*choice_state-1);

        search_9();
    }

}

void Widget::on_btn_main_item_2_clicked()
{

    //更早诊断记录
    if(choice_state == 1)
    {
        ui->sw_main->setCurrentIndex(2*choice_state-1);
        //初始化日期
        ui->date_1->setDisplayFormat("yyyy/MM/dd");
        ui->date_1->setDate(QDate::currentDate().addYears(-1));
        ui->date_1->setMinimumDate(QDate::currentDate().addYears(-100));
        ui->date_1->setMaximumDate(QDate::currentDate().addYears(-1));
        ui->date_1->setCalendarPopup(true);
        search_1();
        return;
    }



    //沟通历史
    else if(choice_state == 4)
    {
        ui->sw_main->setCurrentIndex(2*choice_state);

        search_8();
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

    btn_hide();
    ui->btn_main_item_1->setText("近一月");
    ui->btn_main_item_2->setText("更早");
    ui->btn_main_item_1->show();
    ui->btn_main_item_2->show();
    on_btn_main_item_1_clicked();
}

void Widget::on_btn_menu_item_2_clicked()
{
    choice_state=2;
    btn_hide();
    ui->btn_main_item_1->setText("开始看诊");
    ui->btn_main_item_1->show();
    on_btn_main_item_1_clicked();
}

void Widget::on_btn_menu_item_3_clicked()
{
    choice_state=3;
//    ui->sw_main->setCurrentIndex(5);
    btn_hide();
    ui->btn_main_item_1->setText("我的预约");
//    ui->btn_main_item_2->setText("本周可预约医生");
    ui->btn_main_item_1->show();
//    ui->btn_main_item_2->show();
    on_btn_main_item_1_clicked();
}

void Widget::on_btn_menu_item_4_clicked()
{
    choice_state=4;
    ui->sw_main->setCurrentIndex(8);
    btn_hide();
//    ui->btn_main_item_1->setText("患者列表");
    ui->btn_main_item_2->setText("沟通列表");
//    ui->btn_main_item_1->show();
    ui->btn_main_item_2->show();
    on_btn_main_item_2_clicked();

}

void Widget::on_btn_menu_item_5_clicked()
{
    choice_state=5;
//    ui->sw_main->setCurrentIndex(9);
    btn_hide();
    ui->btn_main_item_1->setText("zhihu");
//    ui->btn_main_item_2->setText("评估历史");
    ui->btn_main_item_1->show();
//    ui->btn_main_item_2->show();
    on_btn_main_item_1_clicked();
}

void Widget::on_btn_menu_item_6_clicked()
{
    choice_state=6;
    ui->sw_main->setCurrentIndex(11);
    btn_hide();
    ui->btn_main_item_1->setText("研发人员");
    ui->btn_main_item_2->setText("意见反馈");
    ui->btn_main_item_3->setText("联系我们");
    ui->btn_main_item_1->show();
    ui->btn_main_item_2->show();
    ui->btn_main_item_3->show();
}

void Widget::page_hide_1()
{
    ui->btn_page_1_1->hide();
    ui->btn_page_2_1->hide();
    ui->btn_page_3_1->hide();
    ui->btn_page_4_1->hide();
}

void Widget::delete_1()
{
    //清空QlistWidget
    int n=ui->listWidget_1->count();//获取item的总数
//    删去所有item
    for(int i=0;i<n;i++)
    {
        QListWidgetItem *item = ui->listWidget_1->takeItem(0);
        delete item;
    }
}

void Widget::putin_1()
{

    page_hide_1();
    //填写页数
    ui->btn_page_now_1->setText(QString::number(page_now));
    ui->btn_page_now_1->setEnabled(false);
    if(page_now>3)
    {
        ui->btn_page_2_1->setText("...");
        ui->btn_page_2_1->show();
        ui->btn_page_2_1->setEnabled(false);
        ui->btn_page_1_1->setText("1");
        ui->btn_page_1_1->show();
    }
    else if(page_now==3)
    {
        ui->btn_page_2_1->setText("2");
        ui->btn_page_2_1->show();
        ui->btn_page_1_1->setText("1");
        ui->btn_page_1_1->show();
    }
    else if(page_now==2)
    {
        ui->btn_page_2_1->setText("1");
        ui->btn_page_2_1->show();
    }
    if(page_max-page_now>2)
    {
        ui->btn_page_3_1->setText("...");
        ui->btn_page_3_1->setEnabled(false);
        ui->btn_page_3_1->show();
        ui->btn_page_4_1->setText(QString::number(page_max));
        ui->btn_page_4_1->show();
    }
    else if(page_max-page_now==2)
    {
        ui->btn_page_3_1->setText(QString::number(page_max-1));
        ui->btn_page_3_1->show();
        ui->btn_page_4_1->setText(QString::number(page_max));
        ui->btn_page_4_1->show();
    }
    else if(page_max-page_now==1)
    {
        ui->btn_page_3_1->setText(QString::number(page_max));
        ui->btn_page_3_1->show();
    }

    //创建item
    little_history *w = new little_history;
    QListWidgetItem* pItem = new QListWidgetItem;
    //填入数据
    w->set_label_user_name( *(patient_name +page_now-1) );
    w->set_label_date( *(diagnosis_date +page_now-1) );
    w->set_label_user_gender( *(patient_gender +page_now-1) );
    w->set_label_phone( *(patient_phone +page_now-1) );
    if(three_which==1)
    {
        w->set_label_which("诊断报告");
        //将诊断报告添加到富文本编辑器
    }
    else if(three_which==2)
    {
        w->set_label_which("处方");
        //将处方添加到富文本编辑器
    }
    else if(three_which==3)
    {
        w->set_label_which("医嘱");
        //将医嘱添加到富文本编辑器
    }

    //设置item大小
    pItem->setSizeHint(QSize(ui->listWidget_1->width(),ui->listWidget_1->height() ));
    //添加进QlistWidget
    ui->listWidget_1->addItem(pItem);
    ui->listWidget_1->setItemWidget(pItem, w);
    //不可被选中
    pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
}

void Widget::search_1()
{
    QString sql="";
    //通过 患者 日期 医生id 查询 ：患者 日期 科室 医生 诊断报告/处方/医嘱
    if(three_which==1)
    {
        sql=R"(
        SELECT
            patient.name AS patient_name,
            inspreport.date AS inspreport_date,
            office.name AS office_name,
            doctor.name AS doctor_name,
            inspreport.filepath AS inspreport_filepath
        FROM
            patient , inspreport , doctor , office
        WHERE
            patient.name = ')" + ui->combo_patient_1->currentText()  + R"( ' AND
            inspreport.date = ')" + ui->date_1->date().toString("yyMMdd")  + R"(' AND
            doctor.id = ')" + USER_ID  + R"(';
        )";

    }
    else if(three_which==2)
    {
        sql=R"(
        SELECT
            patient.name AS patient_name,
            prescription.date AS prescription_date,
            office.name AS office_name,
            doctor.name AS doctor_name,
            prescription.filepath AS prescription_filepath
        FROM
            patient , prescription , doctor , office
        WHERE
            patient.name = ')" + ui->combo_patient_1->currentText()  + R"( ' AND
            prescription.date = ')" + ui->date_1->date().toString("yyMMdd")  + R"(' AND
            doctor.id = ')" + USER_ID  + R"(';
        )";
    }
    else if(three_which==3)
    {
        sql=R"(
        SELECT
            patient.name AS patient_name,
            diagnosis.date AS diagnosis_date,
            office.name AS office_name,
            doctor.name AS doctor_name,
            diagnosis.filepath AS diagnosis_filepath
        FROM
            patient , diagnosis , doctor , office
        WHERE
            patient.name = ')" + ui->combo_patient_1->currentText()  + R"( ' AND
            diagnosis.date = ')" + ui->date_1->date().toString("yyMMdd")  + R"(' AND
            doctor.id = ')" + USER_ID  + R"(';
        )";
    }

    NetLoader::get_sql(sql , USER_ID , 0 , API_KEY , client );

    int data_num=all_num;
    page_max=data_num;
    page_now=1;

    //填写总数据量
    ui->label_data_num_text_1->setText("共有"+QString::number(data_num)+"项数据");
    //删除数据
    delete_1();
    //填入数据
    if(all_num!=0)
        putin_1();//缺少参数



}

void Widget::on_btn_report_1_clicked()
{
    three_which=1;
    search_1();

}

void Widget::on_btn_prescription_1_clicked()
{
    three_which=2;
    search_1();
}

void Widget::on_btn_diagnosis_1_clicked()
{
    three_which=3;
    search_1();
}

void Widget::on_btn_page_left_1_clicked()
{
    if(page_now!=1)
    {
        page_now--;
        delete_1();
        putin_1();
    }
}

void Widget::on_btn_page_right_1_clicked()
{
    if(page_now!=page_max)
    {
        page_now++;
        delete_1();
        putin_1();
    }
}

void Widget::on_btn_page_1_1_clicked()
{
    page_now=1;
    delete_1();
    putin_1();
}

void Widget::on_btn_page_2_1_clicked()
{
    page_now--;
    delete_1();
    putin_1();

}

void Widget::on_btn_page_3_1_clicked()
{
    page_now++;
    delete_1();
    putin_1();
}

void Widget::on_btn_page_4_1_clicked()
{
    page_now=page_max;
    delete_1();
    putin_1();//缺少参数
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
    //创建item
    nowDiagnose *w = new nowDiagnose;
    QListWidgetItem* pItem = new QListWidgetItem;
    //填入数据
    w->set_label_user_name( *(patient_name)  );
    w->set_label_user_gender( *(patient_gender) );
    w->set_label_age( "18" );
    w->set_label_id(*(patient_id));
    w->doctor_id=doctor_id;
    w->patient_id = patient_id;
    w->date = ui->date_3->date().toString();

    //设置item大小
    pItem->setSizeHint(QSize(ui->listWidget_3->width(),ui->listWidget_3->height() ));
    //添加进QlistWidget
    ui->listWidget_3->addItem(pItem);
    ui->listWidget_3->setItemWidget(pItem, w);
    //不可被选中
    pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
}

void Widget::search_3()
{
    if(ui->label_time_3->text()=="非工作时间")
    {
        return ;
    }
    //get data()
    //通过 日期date 医生id 查询： 病人姓名 性别 年龄 预约叫号 id
    QString sql= R"(
    SELECT
        patient.name AS patient_name,
        patient.gender AS patient_gender,
        patient.id AS patient_id,
        appointment.num AS appointment_num
    FROM
        patient , appointment , doctor
    WHERE
        appointment.date = ')" + ui->date_3->date().toString("yyMMdd")  + R"(' AND
        appointment.doctor_id = ' )" + USER_ID  + R"( ' AND
        appointment.time = ')" + ui->label_time_3->text()  + R"(';
    )";


    NetLoader::get_sql(sql , USER_ID , 0 , API_KEY , client );

    int data_num=all_num;
    page_max=data_num;
    page_now=1;

    //填写总数据量
    ui->label_data_num_text_3->setText("共有"+QString::number(data_num)+"项数据");
    //删除数据
    delete_3();
    //填入数据

    putin_3();//缺少参数

}

void Widget::on_btn_page_right_3_clicked()
{
    if(page_now!=page_max)
    {
        search_3();
    }
}

void Widget::page_hide_4()
{
    ui->btn_page_1_4->hide();
    ui->btn_page_2_4->hide();
    ui->btn_page_3_4->hide();
    ui->btn_page_4_4->hide();
}

void Widget::delete_4()
{
    //清空QlistWidget
    int n=ui->listWidget_4->count();//获取item的总数
//    删去所有item
    for(int i=0;i<n;i++)
    {
        QListWidgetItem *item = ui->listWidget_4->takeItem(0);
        delete item;
    }
}

void Widget::putin_4()
{
    page_hide_4();
    //填写页数
    ui->btn_page_now_4->setText(QString::number(page_now));
    ui->btn_page_now_4->setEnabled(false);
    if(page_now>3)
    {
        ui->btn_page_2_4->setText("...");
        ui->btn_page_2_4->show();
        ui->btn_page_2_4->setEnabled(false);
        ui->btn_page_1_4->setText("1");
        ui->btn_page_1_4->show();
    }
    else if(page_now==3)
    {
        ui->btn_page_2_4->setText("2");
        ui->btn_page_2_4->show();
        ui->btn_page_1_4->setText("1");
        ui->btn_page_1_4->show();
    }
    else if(page_now==2)
    {
        ui->btn_page_2_4->setText("1");
        ui->btn_page_2_4->show();
    }
    if(page_max-page_now>2)
    {
        ui->btn_page_3_4->setText("...");
        ui->btn_page_3_4->setEnabled(false);
        ui->btn_page_3_4->show();
        ui->btn_page_4_4->setText(QString::number(page_max));
        ui->btn_page_4_4->show();
    }
    else if(page_max-page_now==2)
    {
        ui->btn_page_3_4->setText(QString::number(page_max-1));
        ui->btn_page_3_4->show();
        ui->btn_page_4_4->setText(QString::number(page_max));
        ui->btn_page_4_4->show();
    }
    else if(page_max-page_now==1)
    {
        ui->btn_page_3_4->setText(QString::number(page_max));
        ui->btn_page_3_4->show();
    }

    //创建item
    myAppointment *w = new myAppointment;
    QListWidgetItem* pItem = new QListWidgetItem;
    //填入数据
    w->set_label_user_name(  *(patient_name+page_now-1) );
    w->set_label_user_age( "28" );
    w->set_label_user_gender( *(patient_name+page_now-1) );
    w->set_label_time( *(appointment_time+page_now-1) );

    //设置item大小
    pItem->setSizeHint(QSize(ui->listWidget_4->width()/3-10,ui->listWidget_4->height()/3 ));
    //添加进QlistWidget
    ui->listWidget_4->addItem(pItem);
    ui->listWidget_4->setItemWidget(pItem, w);
    //不可被选中
    pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
}

void Widget::search_4()
{
    //通过 日期 时间 医生id 查询：姓名 性别 年龄 预约时间
    QString sql= R"(
    SELECT
        patient.name AS patient_name,
        patient.gender AS patient_gender,
        appointment.time AS appointment_time
    FROM
        patient , appointment , doctor
    WHERE
        appointment.date = ')" + ui->date_4->date().toString("yyMMdd")  + R"(' AND
        appointment.doctor_id = ' )" + USER_ID  + R"( ' AND
        appointment.time = ')" + ui->combo_time_4->currentText()  + R"(';
    )";


    NetLoader::get_sql(sql , USER_ID , 0 , API_KEY , client );

    int data_num=all_num;
    page_max=data_num/9+1;
    page_now=1;

    //填写总数据量
    ui->label_data_num_text_4->setText("共有"+QString::number(data_num)+"项数据");
    //删除数据
    delete_4();
    //填入数据
    if(all_num>9)
    {
        for(int i=0;i<9;i++)
        {
            putin_4();//缺少参数
        }
    }
    else
    {
        for(int i=0;i<all_num;i++)
        {
            putin_4();//缺少参数
        }
    }

}

void Widget::on_btn_confirm_4_clicked()
{
    search_4();//参数未填充

}

void Widget::on_btn_page_left_4_clicked()
{
    if(page_now!=1)
    {
        page_now--;
        delete_4();
        for(int i=0;i<9;i++)
        {
            putin_4();//缺少参数
        }
    }
}

void Widget::on_btn_page_right_4_clicked()
{
    if(page_now!=page_max)
    {
        page_now++;
        delete_4();
        for(int i=0;i<9;i++)
        {
            putin_4();//缺少参数
        }
    }
}

void Widget::on_btn_page_1_4_clicked()
{
    page_now=1;
    delete_4();
    for(int i=0;i<9;i++)
    {
        putin_4();//缺少参数
    }
}

void Widget::on_btn_page_2_4_clicked()
{
    page_now--;
    delete_4();
    for(int i=0;i<9;i++)
    {
        putin_4();//缺少参数
    }

}

void Widget::on_btn_page_3_4_clicked()
{
    page_now++;
    delete_4();
    for(int i=0;i<9;i++)
    {
        putin_4();//缺少参数
    }
}

void Widget::on_btn_page_4_4_clicked()
{
    page_now=page_max;
    delete_4();
    for(int i=0;i<9;i++)
    {
        putin_4();//缺少参数
    }
}

void Widget::page_hide_5()
{
    ui->btn_page_1_5->hide();
    ui->btn_page_2_5->hide();
    ui->btn_page_3_5->hide();
    ui->btn_page_4_5->hide();
}

void Widget::delete_5()
{
    //清空QlistWidget
    int n=ui->listWidget_5->count();//获取item的总数
//    删去所有item
    for(int i=0;i<n;i++)
    {
        QListWidgetItem *item = ui->listWidget_5->takeItem(0);
        delete item;
    }
}

void Widget::putin_5()
{
    //通过 医生序号doc_id[] 当前页数 page_now
    //获得 姓名doc_name[] 性别doc_gender[] 科室doc_apartment[]
    //填写QlistWidget

    //假定数据
    QString doc_name="abcdefghijskdscsdfacs";

    page_hide_5();
    //填写页数
    ui->btn_page_now_5->setText(QString::number(page_now));
    ui->btn_page_now_5->setEnabled(false);
    if(page_now>3)
    {
        ui->btn_page_2_5->setText("...");
        ui->btn_page_2_5->show();
        ui->btn_page_2_5->setEnabled(false);
        ui->btn_page_1_5->setText("1");
        ui->btn_page_1_5->show();
    }
    else if(page_now==3)
    {
        ui->btn_page_2_5->setText("2");
        ui->btn_page_2_5->show();
        ui->btn_page_1_5->setText("1");
        ui->btn_page_1_5->show();
    }
    else if(page_now==2)
    {
        ui->btn_page_2_5->setText("1");
        ui->btn_page_2_5->show();
    }
    if(page_max-page_now>2)
    {
        ui->btn_page_3_5->setText("...");
        ui->btn_page_3_5->setEnabled(false);
        ui->btn_page_3_5->show();
        ui->btn_page_4_5->setText(QString::number(page_max));
        ui->btn_page_4_5->show();
    }
    else if(page_max-page_now==2)
    {
        ui->btn_page_3_5->setText(QString::number(page_max-1));
        ui->btn_page_3_5->show();
        ui->btn_page_4_5->setText(QString::number(page_max));
        ui->btn_page_4_5->show();
    }
    else if(page_max-page_now==1)
    {
        ui->btn_page_3_5->setText(QString::number(page_max));
        ui->btn_page_3_5->show();
    }

    //创建item
    myAppointment *w = new myAppointment;

    QListWidgetItem* pItem = new QListWidgetItem;
    //填入数据
    w->set_label_user_name("zzt");
    w->set_label_user_age("16");
    w->set_label_user_gender("男");
    w->set_label_time("上午");


//    pItem->setBackground(QColor("green"));
    //设置item大小
    pItem->setSizeHint(QSize(ui->listWidget_5->width()/3-10,ui->listWidget_5->height()/3 ));
    //添加进QlistWidget
    ui->listWidget_5->addItem(pItem);
    ui->listWidget_5->setItemWidget(pItem, w);
    //不可被选中
    pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
}

void Widget::search_5()
{
    //get data()
    //通过 科室apartment 日期date 姓名searched_name 性别doc_gender
    //得到 数据总量data_num 总页数page_num 医生序号doc_id[] 当前页数page_now
    int data_num=9456;
    page_max=data_num/9+1;
    page_now=1;
//    int doc_id[6]={1,2,3,4,5,6};

    //填写总数据量
    ui->label_data_num_text_5->setText("共有"+QString::number(data_num)+"项数据");
    //删除数据
    delete_5();
    //填入数据
    for(int i=0;i<9;i++)
    {
        putin_5();//缺少参数
    }



}

void Widget::on_btn_confirm_5_clicked()
{
//    获取需要查询的 科室apartment 日期date 姓名doc_name 性别gender
    QString apartment = ui->combo_depart_5->currentText();
    QDate date = ui->date_5->date();
    QString doc_name = ui->lineEdit_docname_5->text();
    QString gender =  ui->combo_gender_5->currentText();

//    查询
    search_5();//参数未填充

}

void Widget::on_btn_page_left_5_clicked()
{
    if(page_now!=1)
    {
        page_now--;
        delete_5();
        for(int i=0;i<9;i++)
        {
            putin_5();//缺少参数
        }
    }
}

void Widget::on_btn_page_right_5_clicked()
{
    if(page_now!=page_max)
    {
        page_now++;
        delete_5();
        for(int i=0;i<9;i++)
        {
            putin_5();//缺少参数
        }
    }
}

void Widget::on_btn_page_1_5_clicked()
{
    page_now=1;
    delete_5();
    for(int i=0;i<9;i++)
    {
        putin_5();//缺少参数
    }
}

void Widget::on_btn_page_2_5_clicked()
{
    page_now--;
    delete_5();
    for(int i=0;i<9;i++)
    {
        putin_5();//缺少参数
    }

}

void Widget::on_btn_page_3_5_clicked()
{
    page_now++;
    delete_5();
    for(int i=0;i<9;i++)
    {
        putin_5();//缺少参数
    }
}

void Widget::on_btn_page_4_5_clicked()
{
    page_now=page_max;
    delete_5();
    for(int i=0;i<9;i++)
    {
        putin_5();//缺少参数
    }
}


void Widget::onItemClicked_8(QListWidgetItem *item)
{
    // 当用户点击项时，弹出消息框显示点击的项的文本
    QMessageBox::information(this, "Item Clicked", "You clicked: " + item->text());

    //需补充
    //切换当前聊天对象

}

void Widget::delete_8()
{
    //清空QlistWidget
    int n=ui->listWidget_8->count();//获取item的总数
//    删去所有item
    for(int i=0;i<n;i++)
    {
        QListWidgetItem *item = ui->listWidget_8->takeItem(0);
        delete item;
    }
}

void Widget::putin_8()
{
    //通过 医生序号doc_id[]
    //获得 姓名doc_name[] 性别doc_gender[] 科室doc_apartment[]
    //填写QlistWidget

    //假定数据
    QString doc_name="abcdefghijskdscsdfacs";


    //创建item
    QListWidgetItem* pItem = new QListWidgetItem(QIcon(":/icons/money.png"), "Text with icon");

    //设置item大小
    pItem->setSizeHint(QSize(ui->listWidget_8->width(),ui->listWidget_8->height()/6 ));

    //添加进QlistWidget
    ui->listWidget_8->addItem(pItem);
}

void Widget::search_8()
{
    //get data()
    //通过 姓名searched_name
    //得到 数据总量data_num 总页数page_num 医生序号doc_id[] 当前页数page_now
    int doc_id[6]={1,2,3,4,5,6};
    int data_num=9;

    //删除数据
    delete_8();
    //填入数据
    for(int i=0;i<data_num;i++)
    {
        putin_8();//缺少参数
    }



}

void Widget::on_btn_confirm_8_clicked()
{
//    获取需要查询的  姓名doc_name
    QString doc_name = ui->lineEdit_search_8->text();

//    查询
    search_8();//参数未填充

}


void Widget::delete_9()
{
    //清空QlistWidget
    int n=ui->listWidget_9->count();//获取item的总数
//    删去所有item
    for(int i=0;i<n;i++)
    {
        QListWidgetItem *item = ui->listWidget_9->takeItem(0);
        delete item;
    }
}

void Widget::putin_9()
{
    //通过 医生序号doc_id[] 当前页数 page_now
    //获得 姓名doc_name[] 性别doc_gender[] 科室doc_apartment[]
    //填写QlistWidget

    //假定数据
    QString doc_name="abcdefghijskdscsdfacs";


    //创建item
//    myAppointment *w = new myAppointment;
    little_zhihu *w = new little_zhihu;

    QListWidgetItem* pItem = new QListWidgetItem;

    //填入数据
    w->set_label_user_name("zzt");
    w->set_label_user_context("12345677890asdfghjkk");
    w->set_label_answernum("98");

//    pItem->setBackground(QColor("green"));
    //设置item大小
    pItem->setSizeHint(QSize(ui->listWidget_9->width(),ui->listWidget_5->height()/5 ));
    //添加进QlistWidget
    ui->listWidget_9->addItem(pItem);
    ui->listWidget_9->setItemWidget(pItem, w);
    //不可被选中
    pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
}

void Widget::search_9()
{
    //get data()
    //通过 科室apartment 日期date 姓名searched_name 性别doc_gender
    //得到 数据总量data_num 总页数page_num 医生序号doc_id[] 当前页数page_now
    int data_num=99;

    int doc_id[6]={1,2,3,4,5,6};

    //填写总数据量
//    ui->label_data_num_text_9->setText("共有"+QString::number(data_num)+"项数据");
    //删除数据
    delete_9();
    //填入数据
    for(int i=0;i<data_num;i++)
    {
        putin_9();//缺少参数
    }



}

void Widget::on_btn_confirm_9_clicked()
{
//    获取需要查询的 科室apartment 日期date 姓名doc_name 性别gender
    QString search = ui->lineEdit_search_9->text();

//    查询
    search_9();//参数未填充

}






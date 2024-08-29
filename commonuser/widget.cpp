#include "widget.h"
#include "ui_widget.h"
#include "newappointment.h"
#include "myappointment.h"
#include "little_doctor.h"
#include "little_history.h"
#include "chat_box.h"
#include "little_zhihu.h"
#include "../shared/include/netclient.h"
#include "../shared/include/netloader.h"
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
QString* tiezi_id =0,* tiezi_text=0 , *tiezi_date =0 , *tiezi_num=0;
QString* huifu_id =0,* huifu_text=0 , *huifu_time =0;

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
    qDebug()<<"client:::::";
    //client = NetClient::getInstance();



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
    void setToolTip(const QString &);
    ui->btn_mine->setToolTip("个人信息和添加就诊人");
    ui->btn_home->setToolTip("返回主页");
    ui->btn_littleshow->setToolTip("最小化窗口");
    ui->btn_logout->setToolTip("退出应用或者最小化到托盘");

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

void Widget::getMessage()
{
    on_btn_main_item_2_clicked();
}


void Widget::handleJsonReceived(const QJsonObject &mainsource)
{
    qDebug()<<"888" << mainsource;

    if(mainsource.size()<=0)return;//如果source为空直接结束
    QJsonArray array=mainsource.value("array").toArray();
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
            *(prescription_date+n)=source.value("prescription_date").toString();
//        else prescription_date=0;

        if(source.contains("tiezi_id"))
            *(tiezi_id+n)=source.value("tiezi_id").toString();
//        else prescripdate=0;

        if(source.contains("tiezi_text"))
            *(tiezi_text+n)=source.value("tiezi_text").toString();
//        else prescription_date=0;

        if(source.contains("tiezi_date"))
            *(tiezi_date+n)=source.value("tiezi_date").toString();
//        else prescription_date=0;

        if(source.contains("tiezi_num"))
            *(tiezi_num+n)=source.value("tiezi_num").toString();
//        else prescription_date=0;

        if(source.contains("huifu_id"))
            *(huifu_id+n)=source.value("huifu_id").toString();
//        else prescription_date=0;

        if(source.contains("huifu_time"))
            *(huifu_time+n)=source.value("huifu_time").toString();
//        else prescription_date=0;

        if(source.contains("huifu_text"))
            *(huifu_text+n)=source.value("huifu_text").toString();
//        else prescription_date=0;

        n++;
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

    //最近一年病史
    if(choice_state == 1)
    {
        //显示page
        ui->sw_main->setCurrentIndex(1);
        //初始化日期
        ui->date_1->setDisplayFormat("yyyy-MM-dd");
        ui->date_1->setDate(QDate::currentDate());
        ui->date_1->setMinimumDate(QDate::currentDate().addYears(-1));
        ui->date_1->setMaximumDate(QDate::currentDate());
        ui->date_1->setCalendarPopup(true);
//        search_1();
    }
    //预约挂号
    if(choice_state == 2)
    {
        //显示page
        ui->sw_main->setCurrentIndex(3);
        //初始化日期
        ui->date_3->setDisplayFormat("yyyy-MM-dd");
        ui->date_3->setDate(QDate::currentDate());
        ui->date_3->setMinimumDate(QDate::currentDate());
        ui->date_3->setMaximumDate(QDate::currentDate().addDays(10));
        ui->date_3->setCalendarPopup(true);

        search_3();
    }
    //当日在班医生
    if(choice_state == 3)
    {
        //显示page
        ui->sw_main->setCurrentIndex(2*choice_state-1);
        //初始化日期
        ui->date_5->show();
        ui->label_date_5->show();
        ui->date_5->setDisplayFormat("yyyy-MM-dd");
        ui->date_5->setDate(QDate::currentDate());
        ui->date_5->setReadOnly(true);
        ui->date_5->setCalendarPopup(true);

        ui->label_date_5->setText("当前日期");

        search_5();
    }

    //医患沟通医生一览
    if(choice_state == 4)
    {
        //显示page
        ui->sw_main->setCurrentIndex(5);
        //初始化日期
        ui->date_5->hide();
        ui->label_date_5->hide();

        search_5();
    }

    //zhihu???
    if(choice_state == 5)
    {
        //显示page
        ui->sw_main->setCurrentIndex(2*choice_state-1);
        search_9();
    }
    else if(choice_state == 6){
        ui->sw_main->setCurrentIndex(11);
    }
}

void Widget::on_btn_main_item_2_clicked()
{

    //更早病史
    if(choice_state == 1)
    {
        ui->sw_main->setCurrentIndex(1);
        //初始化日期
        ui->date_1->setDisplayFormat("yyyy-MM-dd");
        ui->date_1->setDate(QDate::currentDate().addYears(-1));
        ui->date_1->setMinimumDate(QDate::currentDate().addYears(-20));
        ui->date_1->setMaximumDate(QDate::currentDate().addYears(-1));
        ui->date_1->setCalendarPopup(true);
//        search_1();
//        return;
    }

    //我的预约
    else if(choice_state == 2)
    {
        ui->sw_main->setCurrentIndex(4);
        //初始化日期
        ui->date_4->setDisplayFormat("yyyy-MM-dd");
        ui->date_4->setDate(QDate::currentDate());
        ui->date_4->setCalendarPopup(true);

        search_4();

    }
    //本周可预约医生
    else if(choice_state == 3)
    {
        ui->sw_main->setCurrentIndex(2*choice_state-1);
        //初始化日期
        ui->date_5->show();
        ui->label_date_5->show();
        ui->date_5->setDisplayFormat("yyyy-MM-dd");
        ui->date_5->setDate(QDate::currentDate());
        ui->date_5->setMinimumDate(QDate::currentDate());
        ui->date_5->setMaximumDate(QDate::currentDate().addDays(7));
        ui->date_5->setReadOnly(false);
        ui->date_5->setCalendarPopup(true);
        ui->label_date_5->setText("预约日期");
        search_5();
    }

    //沟通历史
    else if(choice_state == 4)
    {
        ui->sw_main->setCurrentIndex(2*choice_state);

        search_8();
    }

    //zhihu提问
    else if(choice_state == 5)
    {
        ui->sw_main->setCurrentIndex(2*choice_state);

//        search_10();
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
    ui->btn_main_item_1->setText("最近一年");
    ui->btn_main_item_2->setText("更早");
    ui->btn_main_item_1->show();
    ui->btn_main_item_2->show();
    on_btn_main_item_1_clicked();
}

void Widget::on_btn_menu_item_2_clicked()
{
    choice_state=2;
    btn_hide();
    ui->btn_main_item_1->setText("预约挂号");
    ui->btn_main_item_2->setText("我的预约");
    ui->btn_main_item_1->show();
    ui->btn_main_item_2->show();
    on_btn_main_item_1_clicked();
}

void Widget::on_btn_menu_item_3_clicked()
{
    choice_state=3;
    btn_hide();
    ui->btn_main_item_1->setText("当日在班医生");
    ui->btn_main_item_2->setText("本周可预约医生");
    ui->btn_main_item_1->show();
    ui->btn_main_item_2->show();
    on_btn_main_item_1_clicked();
}

void Widget::on_btn_menu_item_4_clicked()
{
    choice_state=4;
    btn_hide();
    ui->btn_main_item_1->setText("医生列表");
    ui->btn_main_item_2->setText("询问历史");
    ui->btn_main_item_1->show();
    ui->btn_main_item_2->show();
    on_btn_main_item_1_clicked();
}

void Widget::on_btn_menu_item_5_clicked()
{
    choice_state=5;
    ui->sw_main->setCurrentIndex(9);
    btn_hide();
    ui->btn_main_item_1->setText("主页");
    ui->btn_main_item_2->setText("提问");
    ui->btn_main_item_1->show();
    ui->btn_main_item_2->show();
}

void Widget::on_btn_menu_item_6_clicked()
{
    choice_state=6;
    ui->sw_main->setCurrentIndex(11);
    btn_hide();
    ui->btn_main_item_1->setText("健康评估");
//    ui->btn_main_item_2->setText("评估历史");
    ui->btn_main_item_1->show();
//    ui->btn_main_item_2->show();
}

void Widget::on_btn_menu_item_7_clicked()
{
    choice_state=7;
    ui->sw_main->setCurrentIndex(13);
    btn_hide();
    ui->btn_main_item_1->setText("研发人员");
    ui->btn_main_item_2->setText("意见反馈");
    ui->btn_main_item_3->setText("联系我们");
    ui->btn_main_item_1->show();
    ui->btn_main_item_2->show();
    ui->btn_main_item_3->show();
}

void Widget::on_combo_patient_1_currentIndexChanged(const QString &arg1)
{
    set_doctors_1();
}

void Widget::on_combo_depart_1_currentIndexChanged(const QString &arg1)
{
    set_doctors_1();
}

void Widget::on_date_1_userDateChanged(const QDate &date)
{
    set_doctors_1();
}

void Widget::set_doctors_1()
{
    //通过 患者 日期 科室 查询 ：医生
//    QString sql= R"(
//    SELECT
//        d.name AS doctor_name
//    FROM
//        patient pa
//    JOIN
//        diagnosis di ON pa.id = di.patient_id
//    JOIN
//        doctor d ON di.doctor_id = d.id
//    JOIN
//        office o ON d.office_id = o.id
//    WHERE
//        pa.name like %')" + ui->combo_patient_1->currentText() + R"('% AND
//        di.date = ')" + ui->date_1->date().toString() + R"(' AND
//        o.name = ')" + ui->combo_depart_1->currentText() + R"(';
//    )";
    QString sql ="SELECT doctor.name AS doctor_name FROM prescription, doctor, patient, office WHERE patient.name ='"+ui->combo_patient_1->currentText()+"' AND prescription.date = '"+ui->date_1->date().toString("yyyy-MM-dd")+"' AND office.name = '"+ui->combo_depart_1->currentText()+"';";

    NetClient &client = NetClient::getInstance();
    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );

    //填入医生信息
    for(int i=0;i<all_num;i++)
    {
        ui->combo_docname_1->addItem( *( doctor_name + all_num - 1 ) );
    }

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
    w->set_label_doc_name( *(doctor_name +page_now-1) );
    w->set_label_apartment( *(office_name +page_now-1) );
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
    //通过 患者 日期 科室 医生 查询 ：患者 日期 科室 医生 诊断报告/处方/医嘱
    if(three_which==1)
    {
//        sql = "";
        sql= " SELECT  patient.name AS patient_name,  inspreport.date AS inspreport_date,  office.name AS office_name,  doctor.name AS doctor_name, inspreport.filepath AS inspreport_filepath FROM patient , inspreport , doctor , office WHERE patient.name = '" + ui->combo_patient_1->currentText() + "' AND inspreport.date = '" + ui->date_1->date().toString("yyyy-MM-dd") + "' AND office.name = '" + ui->combo_depart_1->currentText() + "' AND  doctor.name = '" + ui->combo_docname_1->currentText() + "'; ";
//        QString sql ="SELECT doctor.name AS doctor_name FROM prescription, doctor, patient, office WHERE patient.name like %'"+ui->combo_patient_1->currentText()+"'% AND prescription.date = '"+ui->date_1->date().toString("yyMMdd")+"' AND office.name = '"+ui->combo_depart_1->currentText()+"';";



    }
    else if(three_which==2)
    {
        sql= R"(
        SELECT
            patient.name AS patient_name,
            prescription.date AS prescription_date,
            office.name AS office_name,
            doctor.name AS doctor_name,
            prescription.filepath AS prescription_filepath
        FROM
            patient , prescription , doctor , office
        WHERE
            patient.name = ')" + ui->combo_patient_1->currentText() + R"(' AND
            prescription.date = ')" + ui->date_1->date().toString("yyyy-MM-dd") + R"(' AND
            office.name = ')" + ui->combo_depart_1->currentText() + R"(' AND
            doctor.name = ')" + ui->combo_docname_1->currentText() + R"(';
        )";
    }
    else if(three_which==3)
    {
        sql= R"(
        SELECT
            patient.name AS patient_name,
            diagnosis.date AS diagnosis_date,
            office.name AS office_name,
            doctor.name AS doctor_name,
            diagnosis.filepath AS diagnosis_filepath
        FROM
            patient , diagnosis , doctor , office
        WHERE
            patient.name = ')" + ui->combo_patient_1->currentText() + R"(' AND
            diagnosis.date = ')" + ui->date_1->date().toString("yyyy-MM-dd") + R"(' AND
            office.name = ')" + ui->combo_depart_1->currentText() + R"(' AND
            doctor.name = ')" + ui->combo_docname_1->currentText() + R"(';
        )";
    }

//    qDebug()<<"666";
    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );
//    qDebug()<<"777";

    int data_num=all_num;
    page_max=data_num;
    page_now=1;

    //填写总数据量
    ui->label_data_num_text_1->setText("共有"+QString::number(data_num)+"项数据");
    //删除数据
    delete_1();
    //填入数据
    if(data_num!=0)
    {
        putin_1();
    }


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
    putin_1();
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

void Widget::putin_3(int i)
{

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

    // qDebug()<<*(doctor_name+page_now*9-9+i);
    // qDebug()<< *(doctor_gender+page_now*9-9+i) ;

    //填入数据
    w->set_label_doc_name( *(doctor_name+page_now*9-9+i) );
    w->set_label_gender( *(doctor_gender+page_now*9-9+i) );
    w->set_label_apartment( *(office_name+page_now*9-9+i) );
    w->set_label_describe( *(doctor_describe+page_now*9-9+i) );
    w->adate_now = ui->date_3->date().toString("yyyy-MM-dd");
    w->doctor_id = doctor_id+page_now*9-9+i;
    w->patient_name = patient_name+page_now*9-9+i;
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
    //通过 科室 日期 医生姓名 医生性别 查询： 医生姓名 性别 科室 简介
    QString sql= R"(
    SELECT
        doctor.name AS doctor_name,
        doctor.gender AS doctor_gender,
        office.name AS office_name,
        doctor.describe AS doctor_describe
        doctor.id AS doctor_id
        patient.name AS patient_name
    FROM
        doctor ,office , patient
    WHERE
        office.name like '%)" + ui->combo_depart_3->currentText() + R"(%' AND
        doctor.name like '%)" + ui->lineEdit_docname_3->text() + R"(%' AND
        doctor.gender = ')" + ui->combo_gender_3->currentText() + R"(';
    )";

    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );

    int data_num=all_num;
    page_max=data_num/9+1;
    page_now=1;

    //填写总数据量
    ui->label_data_num_text_3->setText("共有"+QString::number(data_num)+"项数据");
    //删除数据
    delete_3();
    //填入数据
    if(data_num>9)
    {
        for(int i=0;i<9;i++)
        {
            putin_3(i);//缺少参数
        }
    }
    else
    {
        for(int i=0;i<data_num;i++)
        {
            putin_3(i);//缺少参数
        }
    }


}

void Widget::on_btn_confirm_3_clicked()
{
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
            putin_3(i);//缺少参数
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
            putin_3(i);//缺少参数
        }
    }
}

void Widget::on_btn_page_1_3_clicked()
{
    page_now=1;
    delete_3();
    for(int i=0;i<9;i++)
    {
        putin_3(i);//缺少参数
    }
}

void Widget::on_btn_page_2_3_clicked()
{
    page_now--;
    delete_3();
    for(int i=0;i<9;i++)
    {
        putin_3(i);//缺少参数
    }

}

void Widget::on_btn_page_3_3_clicked()
{
    page_now++;
    delete_3();
    for(int i=0;i<9;i++)
    {
        putin_3(i);//缺少参数
    }
}

void Widget::on_btn_page_4_3_clicked()
{
    page_now=page_max;
    delete_3();
    for(int i=0;i<9;i++)
    {
        putin_3(i);//缺少参数
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

void Widget::putin_4(int i)
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
//    little_appointment *w = new little_appointment;
    myAppointment *w = new myAppointment;
    QListWidgetItem* pItem = new QListWidgetItem;
    //填入数据
    w->set_label_user_name(*(patient_name+page_now*9-9+i));
    w->set_label_date(*(appointment_date+page_now*9-9+i));
    w->set_label_time(*(appointment_time+page_now*9-9+i));
    w->set_label_doc_name(  *(doctor_name+page_now*9-9+i)  );
    w->set_label_apartment(*(office_name+page_now*9-9+i));
    w->set_label_id(*(appointment_id+page_now*9-9+i));

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

    //通过 患者姓名 预约日期 医生 医生性别 部门 查询： 患者姓名 日期 时间 医生 部门 预约序号
    QString sql= R"(
    SELECT
        patient.name AS patient_name,
        appointment.date AS appointment_date,
        appointment.num AS appointment_num,
        appointment.time AS appointment_time,
        doctor.name AS doctor_name,
        office.name AS office_name
    FROM
        patient ,appointment, office , doctor
    WHERE
        patient.name like %')" + ui->combo_user_4->currentText() + R"('% AND
        appointment.date like %')" + ui->date_4->date().toString("yyMMdd") + R"('% AND
        doctor.name like %')" + ui->lineEdit_docname_4->text() + R"('% AND
        doctor.gender like %')" + ui->combo_gender_4->currentText() + R"('% AND
        office.name = ')" + ui->combo_depart_4->currentText() + R"(';
    )";

    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );

    int data_num=all_num;
    page_max=data_num/9+1;
    page_now=1;

    //填写总数据量
    ui->label_data_num_text_4->setText("共有"+QString::number(data_num)+"项数据");
    //删除数据
    delete_4();
    //填入数据
    if(data_num>9)
    {
        for(int i=0;i<9;i++)
        {
            putin_4(i);//缺少参数
        }
    }
    else
    {
        for(int i=0;i<data_num;i++)
        {
            putin_4(i);//缺少参数
        }
    }



}

void Widget::on_btn_confirm_4_clicked()
{
//    查询
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
            putin_4(i);//缺少参数
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
            putin_4(i);//缺少参数
        }
    }
}

void Widget::on_btn_page_1_4_clicked()
{
    page_now=1;
    delete_4();
    for(int i=0;i<9;i++)
    {
        putin_4(i);//缺少参数
    }
}

void Widget::on_btn_page_2_4_clicked()
{
    page_now--;
    delete_4();
    for(int i=0;i<9;i++)
    {
        putin_4(i);//缺少参数
    }

}

void Widget::on_btn_page_3_4_clicked()
{
    page_now++;
    delete_4();
    for(int i=0;i<9;i++)
    {
        putin_4(i);//缺少参数
    }
}

void Widget::on_btn_page_4_4_clicked()
{
    page_now=page_max;
    delete_4();
    for(int i=0;i<9;i++)
    {
        putin_4(i);//缺少参数
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

void Widget::putin_5(int i)
{


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
    little_doctor *w = new little_doctor;
    QListWidgetItem* pItem = new QListWidgetItem;
    //填入数据
    w->set_label_name(  *(doctor_name+page_now*9-9+i)  );
    w->set_label_gender( *(doctor_gender+page_now*9-9+i) );
    w->set_label_apartment( *(office_name+page_now*9-9+i) );
    w->set_label_introduce( *(doctor_describe+page_now*9-9+i) );
    w->doc_id=doctor_id;
    if(choice_state==3)
    {
        w->set_btn_hide();
    }
    else if(choice_state==4)
    {
        w->set_btn_unhide();
        w->set_btn_text("咨询");
    }

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
    //通过 科室 日期 医生姓名 医生性别 查询： 医生姓名 医生性别 科室 简介 id
    QString sql = R"(
    SELECT
        doctor.name AS doctor_name,
        doctor.gender AS doctor_gender,
        office.name AS office_name,
        doctor.describe AS doctor_describe,
        doctor.id AS doctor_id
    FROM
        doctor , office
    WHERE
        office.name = ')" + ui->combo_depart_5->currentText() + R"(' AND
        doctor.name like %')" + ui->lineEdit_docname_5->text() + R"('% AND
        doctor.gender = ')" + ui->combo_gender_5->currentText() + R"(';
    )";

    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );

    int data_num=all_num;
    page_max=data_num/9+1;
    page_now=1;

    //填写总数据量
    ui->label_data_num_text_5->setText("共有"+QString::number(data_num)+"项数据");
    //删除数据
    delete_5();
    //填入数据
    if(data_num>9)
    {
        for(int i=0;i<9;i++)
        {
            putin_5(i);//缺少参数
        }
    }
    else
    {
        for(int i=0;i<data_num;i++)
        {
            putin_5(i);//缺少参数
        }
    }



}

void Widget::on_btn_confirm_5_clicked()
{
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
            putin_5(i);//缺少参数
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
            putin_5(i);//缺少参数
        }
    }
}

void Widget::on_btn_page_1_5_clicked()
{
    page_now=1;
    delete_5();
    for(int i=0;i<9;i++)
    {
        putin_5(i);//缺少参数
    }
}

void Widget::on_btn_page_2_5_clicked()
{
    page_now--;
    delete_5();
    for(int i=0;i<9;i++)
    {
        putin_5(i);//缺少参数
    }

}

void Widget::on_btn_page_3_5_clicked()
{
    page_now++;
    delete_5();
    for(int i=0;i<9;i++)
    {
        putin_5(i);//缺少参数
    }
}

void Widget::on_btn_page_4_5_clicked()
{
    page_now=page_max;
    delete_5();
    for(int i=0;i<9;i++)
    {
        putin_5(i);//缺少参数
    }
}

void Widget::onItemClicked_8(QListWidgetItem *item)
{
    // 当用户点击项时，弹出消息框显示点击的项的文本
//    QMessageBox::information(this, "Item Clicked", "You clicked: " + item->text());

    QString sql= R"(
    SELECT
        doctor.id AS doctor_id
    FROM
        doctor
    WHERE
        doctor.name like %')" + item->text() + R"('% ;
    )";

    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );


    ui->label_docname_8->setText(item->text());
    ui->widget_chat_box_8->set_receiver_id(*doctor_id);
    ui->widget_chat_box_8->set_sender_id(USER_ID);
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
    //创建item
    QListWidgetItem* pItem = new QListWidgetItem(QIcon(":/icons/money.png"), "Text with icon");

    //设置item大小
    pItem->setSizeHint(QSize(ui->listWidget_8->width(),ui->listWidget_8->height()/6 ));

    //添加进QlistWidget
    ui->listWidget_8->addItem(pItem);
}

void Widget::search_8()
{
    QString sql = "select receiver_id from chat_history where sender_id ='"+USER_ID+"'; ";

    DatabaseManager &dbm = DatabaseManager::getInstance();
    QSqlQuery query(dbm.getDatabase());
    query.exec(sql);

    //删除数据
    delete_8();

    int in=0;
    while (query.next())
    {
        QString sql= R"(
        SELECT
            doctor.name AS doctor_name,
        FROM
            doctor
        WHERE
            doctor.id like %')" +  query.value(1).toString()  + R"('%;
        )";

        NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );


        if(ui->lineEdit_search_8->text()==""||ui->lineEdit_search_8->text()==*(doctor_name+in))
        {
            //创建item
            QListWidgetItem* pItem = new QListWidgetItem(QIcon(":/icons/money.png"), *(doctor_name+in));

            //设置item大小
            pItem->setSizeHint(QSize(ui->listWidget_8->width(),ui->listWidget_8->height()/6 ));

            //添加进QlistWidget
            ui->listWidget_8->addItem(pItem);
        }

    }

}

void Widget::on_btn_confirm_8_clicked()
{
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

    QString sql= R"(
    SELECT
        huifu.text AS huifu_text,
        doctor.name AS doctor_name,
        huifu.time AS huifu_time
    FROM
        user , tiezi , doctor , huifu
    WHERE
        tiezi.id = '%)"+ *(tiezi_id+page_now) +R"(%'
    )";

    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );

    //创建item
    little_zhihu *w = new little_zhihu;

    QListWidgetItem* pItem = new QListWidgetItem;

    //填入数据
    w->set_label_user_name(*(user_name+page_now-1));
    w->set_label_user_context(*(tiezi_text+page_now-1));
    w->set_label_answernum(*(tiezi_num+page_now-1));
    w->tiezi_id = *(tiezi_id+page_now-1);
    w->allnum=all_num;
    w->now=page_now;
    w->huifutext=huifu_text;
    w->huifutime=huifu_time;
    w->doctorname=doctor_name;
//    w->tiezi_id=tiezi_id;

//    pItem->setBackground(QColor("green"));
    //设置item大小
    pItem->setSizeHint(QSize(ui->listWidget_9->width(),ui->listWidget_9->height()/5 ));
    //添加进QlistWidget
    ui->listWidget_9->addItem(pItem);
    ui->listWidget_9->setItemWidget(pItem, w);
    //不可被选中
    pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
}

void Widget::search_9()
{

    QString sql= R"(
    SELECT
        tiezi.text AS tizi_text,
        tiezi.date AS tiezi_date,
        tiezi.id AS tiezi_id,
        tiezi.num AS tiezi_num,
        user.name AS user_name
    FROM
        user , tiezi
    WHERE
        tiezi.text like '%)"+ ui->lineEdit_search_9->text() +R"(%'
    )";

//    qDebug()<<"666";
    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );

    int data_num=all_num;

    //填写总数据量
//    ui->label_data_num_text_9->setText("共有"+QString::number(data_num)+"项数据");
    //删除数据
    delete_9();
    if(all_num>50)
    {
        //填入数据
        for(int i=0;i<50;i++)
        {
            putin_9();//缺少参数
        }
    }
    else if(all_num>0)
    {
        //填入数据
        for(int i=0;i<data_num;i++)
        {
            putin_9();//缺少参数
        }
    }



}

void Widget::on_btn_confirm_9_clicked()
{
    search_9();//参数未填充
}





void Widget::on_btn_ques_10_clicked()
{
    QString sql = " INSERT INTO tiezi (text, date , num , user_id ) VALUES ( '"+ui->textEdit_10->toPlainText()+"' , '"+ QDate::currentDate().toString("yyyy-MM-dd") +"', 0, '"+ USER_ID +"'); ";
//    QString sql= R"(
//    SELECT
//        tiezi.text AS tizi_text,
//        tiezi.date AS tiezi_date,
//        tiezi.id AS tiezi_id,
//        tiezi.num AS tiezi_num,
//        user.name AS user_name
//    FROM
//        user , tiezi
//    WHERE
//        tiezi.text like '%)"+ ui->lineEdit_search_9->text() +R"(%'
//    )";

//    qDebug()<<"666";
    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );

    ui->textEdit_10->setText("提交成功");

}


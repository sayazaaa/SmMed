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
#include <QVector>

int choice_state=0;
int page_now=0;
int page_max=0;
int three_which=0;


QVector<QString> sql_query;

QVector<QString> doctor_id ,doctor_password , doctor_salt ,doctor_name,doctor_gender,doctor_zc ,doctor_describe, doctor_workingtime;
QVector<QString> office_name,office_id;
QVector<QString> user_id,user_password ,user_salt ,user_age ,user_name ,user_gender,user_phone ,user_address;
QVector<QString> inspreport_id,inspreport_filepath,inspreport_title,inspreport_date;
QVector<QString> patient_id ,patient_name ,patient_gender,patient_phone ;
QVector<QString> appointment_id ,appointment_date ,appointment_num,appointment_time;
QVector<QString> notifications_id , notifications_title, notifications_time, notifications_enddate,notifications_content;
QVector<QString> diagnosis_id ,diagnosis_title,diagnosis_filepath,diagnosis_date;
QVector<QString> prescription_id , prescription_title,prescription_filepath ,prescription_date;
QVector<QString> tiezi_id ,tiezi_text,tiezi_date ,tiezi_num;
QVector<QString> huifu_id , huifu_text,huifu_time ;

int all_num=0;
int search_state=0;
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
//    qDebug()<<"888" << mainsource;
    for(int i=0;i<1;i++){

       doctor_id.clear();
       doctor_password.clear();
       doctor_salt.clear();
       doctor_name.clear();

       doctor_gender.clear();

       doctor_describe.clear();

       doctor_workingtime.clear();

       doctor_zc.clear();

       office_name.clear();

       office_id.clear();

       user_id.clear();

       user_password.clear();

       user_salt.clear();

       user_age.clear();

       user_name.clear();

       user_gender.clear();

       user_phone.clear();

       user_address.clear();

       inspreport_id.clear();

       inspreport_filepath.clear();

       inspreport_title.clear();

       inspreport_date.clear();

       patient_id.clear();

       patient_name.clear();

       patient_gender.clear();

       patient_phone.clear();

       appointment_id .clear();

       appointment_date.clear();

       appointment_num.clear();

       appointment_time.clear();

       notifications_id.clear();

       notifications_title.clear();

       notifications_time.clear();

       notifications_enddate.clear();

       notifications_content.clear();

       diagnosis_id.clear();

       diagnosis_title.clear();

       diagnosis_filepath.clear();

       diagnosis_date.clear();

       prescription_id.clear();

       prescription_title.clear();

       prescription_filepath.clear();

       prescription_date.clear();

       tiezi_id.clear();

       tiezi_text.clear();

       tiezi_date.clear();

       tiezi_num.clear();

       huifu_id.clear();

       huifu_time.clear();

       huifu_text.clear();
    }


    int n=0;
    if(mainsource.size()>0)//如果source为空直接结束
    {
    QJsonArray array=mainsource.value("array").toArray();

    for(auto item:array){

//        qDebug()<<"665";
        QJsonObject source = item.toObject();
        qDebug()<<"source"<<source;
        if(source.contains("doctor_id"))//如果source中有"name"值则提取
            doctor_id.push_back(source.value("doctor_id").toString());
        else doctor_id.clear();
        // qDebug()<<"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

        if(source.contains("doctor_password"))
            doctor_password.push_back(source.value("doctor_password").toString());
        else doctor_password.clear();
        // qDebug()<<"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
        if(source.contains("doctor_salt"))
            doctor_salt.push_back(source.value("doctor_salt").toString());
       else doctor_salt.clear();

        if(source.contains("doctor_name"))
            doctor_name.push_back(source.value("doctor_name").toString());
       else doctor_name.clear();

        if(source.contains("doctor_gender"))
            doctor_gender.push_back(source.value("doctor_gender").toString());
       else doctor_gender.clear();

        if(source.contains("doctor_describe"))
            doctor_describe.push_back(source.value("doctor_describe").toString());
       else doctor_describe.clear();

        if(source.contains("doctor_workingtime"))
            doctor_workingtime.push_back(source.value("doctor_workingtime").toString());
       else doctor_workingtime.clear();

        if(source.contains("doctor_zc"))
            doctor_zc.push_back(source.value("doctor_zc").toString());
       else doctor_zc.clear();

        if(source.contains("office_name"))
            office_name.push_back(source.value("office_name").toString());
       else office_name.clear();

        if(source.contains("office_id"))
            office_id.push_back(source.value("office_id").toString());
       else office_id.clear();

        if(source.contains("user_id"))
            user_id.push_back(source.value("user_id").toString());
       else user_id.clear();

        if(source.contains("user_password"))
            user_password.push_back(source.value("user_password").toString());
       else user_password.clear();

        if(source.contains("user_salt"))
            user_salt.push_back(source.value("user_salt").toString());
       else user_salt.clear();

        if(source.contains("user_age"))
            user_age.push_back(source.value("user_age").toString());
       else user_age.clear();

        if(source.contains("user_name"))
            user_name.push_back(source.value("user_name").toString());
       else user_name.clear();

        if(source.contains("user_gender"))
            user_gender.push_back(source.value("user_gender").toString());
       else user_gender.clear();

        if(source.contains("user_phone"))
            user_phone.push_back(source.value("user_phone").toString());
       else user_phone.clear();

        if(source.contains("user_address"))
            user_address.push_back(source.value("user_address").toString());
       else user_address.clear();

        if(source.contains("inspreport_id"))
            inspreport_id.push_back(source.value("inspreport_id").toString());
       else inspreport_id.clear();

        if(source.contains("inspreport_filepath"))
            inspreport_filepath.push_back(source.value("inspreport_filepath").toString());
       else inspreport_filepath.clear();

        if(source.contains("inspreport_title"))
            inspreport_title.push_back(source.value("inspreport_title").toString());
       else inspreport_title.clear();

        if(source.contains("inspreport_date"))
            inspreport_date.push_back(source.value("inspreport_date").toString());
       else inspreport_date.clear();

        if(source.contains("patient_id"))
            patient_id.push_back(source.value("patient_id").toString());
       else patient_id.clear();

        if(source.contains("patient_name"))
            patient_name.push_back(source.value("patient_name").toString());
       else patient_name.clear();

        if(source.contains("patient_gender"))
            patient_gender.push_back(source.value("patient_gender").toString());
       else patient_gender.clear();

        if(source.contains("patient_phone"))
            patient_phone.push_back(source.value("patient_phone").toString());
       else patient_phone.clear();

        if(source.contains("appointment_id"))
            appointment_id .push_back(source.value("appointment_id").toString());
       else appointment_id .clear();

        if(source.contains("appointment_date"))
            appointment_date.push_back(source.value("appointment_date").toString());
       else appointment_date.clear();

        if(source.contains("appointment_num"))
            appointment_num.push_back(source.value("appointment_num").toString());
       else appointment_num.clear();

        if(source.contains("appointment_time"))
            appointment_time.push_back(source.value("appointment_time").toString());
        else appointment_time.clear();

        if(source.contains("notifications_id"))
            notifications_id.push_back(source.value("notifications_id").toString());
        else notifications_id.clear();

        if(source.contains("notifications_title"))
            notifications_title.push_back(source.value("notifications_title").toString());
        else notifications_title.clear();

        if(source.contains("notifications_time"))
            notifications_time.push_back(source.value("notifications_time").toString());
       else notifications_time.clear();

        if(source.contains("notifications_enddate"))
            notifications_enddate.push_back(source.value("notifications_enddate").toString());
       else notifications_enddate.clear();

        if(source.contains("notifications_content"))
            notifications_content.push_back(source.value("notifications_content").toString());
       else notifications_content.clear();

        if(source.contains("diagnosis_id"))
            diagnosis_id.push_back(source.value("diagnosis_id").toString());
       else diagnosis_id.clear();

        if(source.contains("diagnosis_title"))
            diagnosis_title.push_back(source.value("diagnosis_title").toString());
       else diagnosis_title.clear();

        if(source.contains("diagnosis_filepath"))
            diagnosis_filepath.push_back(source.value("diagnosis_filepath").toString());
       else diagnosis_filepath.clear();

        if(source.contains("diagnosis_date"))
            diagnosis_date.push_back(source.value("diagnosis_date").toString());
       else diagnosis_date.clear();

        if(source.contains("prescription_id"))
            prescription_id.push_back(source.value("prescription_id").toString());
       else prescription_id.clear();

        if(source.contains("prescription_title"))
            prescription_title.push_back(source.value("prescription_title").toString());
       else prescription_title.clear();

        if(source.contains("prescription_filepath"))
            prescription_filepath.push_back(source.value("prescription_filepath").toString());
       else prescription_filepath.clear();

        if(source.contains("prescription_date"))
            prescription_date.push_back(source.value("prescription_date").toString());
       else prescription_date.clear();

        if(source.contains("tiezi_id"))
            tiezi_id.push_back(source.value("tiezi_id").toString());
       else tiezi_id.clear();

        if(source.contains("tiezi_text"))
            tiezi_text.push_back(source.value("tiezi_text").toString());
       else tiezi_text.clear();

        if(source.contains("tiezi_date"))
            tiezi_date.push_back(source.value("tiezi_date").toString());
       else tiezi_date.clear();

        if(source.contains("tiezi_num"))
            tiezi_num.push_back(source.value("tiezi_num").toString());
       else tiezi_num.clear();

        if(source.contains("huifu_id"))
            huifu_id.push_back(source.value("huifu_id").toString());
       else huifu_id.clear();

        if(source.contains("huifu_time"))
            huifu_time.push_back(source.value("huifu_time").toString());
       else huifu_time.clear();

        if(source.contains("huifu_text"))
            huifu_text.push_back(source.value("huifu_text").toString());
       else huifu_text.clear();
        qDebug()<<"endsource";

        n++;
    }
    }


    all_num=n;
    page_now=1;


    if(search_state==101)
    {
        ui->combo_patient_1->clear();
        for(int i=0;i<all_num;i++)
        {
            putin_101();
        }
    }
    else if(search_state==102)
    {
        ui->combo_docname_1->clear();
        for(int i=0;i<all_num;i++)
        {
            putin_102();
        }
    }
    else if(search_state==1)
    {
        page_max=all_num;
        page_now=1;

        //填写总数据量
        ui->label_data_num_text_1->setText("共有"+QString::number(all_num)+"项数据");
        //删除数据
        delete_1();
        //填入数据
        if(all_num>0)
        {
            putin_1();
        }
    }
    else if(search_state==3)
    {
        if(all_num==0) page_max=0;
        else   page_max=(all_num-1)/9+1;
        page_now=1;
        //填写总数据量
        ui->label_data_num_text_3->setText("共有"+QString::number(all_num)+"项数据");

        //删除数据
        delete_3();
        //填入数据
        if(all_num>9)
        {
            for(int i=0;i<9;i++)
            {
                putin_3(i);
            }
        }
        else
        {
            for(int i=0;i<all_num;i++)
            {
                putin_3(i);
            }
        }
    }
    else if(search_state==4)
    {
        if(all_num==0) page_max=0;
        else   page_max=(all_num-1)/9+1;
        page_now=1;
        //填写总数据量
        ui->label_data_num_text_4->setText("共有"+QString::number(all_num)+"项数据");

        //删除数据
        delete_4();
        //填入数据
        if(all_num>9)
        {
            for(int i=0;i<9;i++)
            {
                putin_4(i);
            }
        }
        else
        {
            for(int i=0;i<all_num;i++)
            {
                putin_4(i);
            }
        }

    }
    else if(search_state==401)
    {
        ui->combo_user_4->clear();
        for(int i=0;i<all_num;i++)
        {
            putin_401();
        }
        search_4();
    }
    else if(search_state==5)
    {
        if(all_num==0) page_max=0;
        else   page_max=(all_num-1)/9+1;
        qDebug()<<all_num;
        qDebug()<<page_max;
        page_now=1;
        //填写总数据量
        ui->label_data_num_text_5->setText("共有"+QString::number(all_num)+"项数据");
//        qDebug()<<"eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee";
        //删除数据
        delete_5();
        qDebug()<<"9999999999999999999999999999999999999";
        //填入数据
        if(all_num>9)
        {
//            qDebug()<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
            for(int i=0;i<9;i++)
            {
                putin_5(i);
            }
        }
        else
        {
            qDebug()<<"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
            for(int i=0;i<all_num;i++)
            {
                putin_5(i);
            }
        }

        qDebug()<<"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

    }
    else if(search_state==801)
    {
        if(all_num>0)
            putin_801();
    }
    else if(search_state==802)
    {
        if(all_num>0)
            putin_802();
    }
    else if(search_state==888)
    {

        ui->widget_chat_box_8->set_receiver_id(doctor_id[0]);
        ui->widget_chat_box_8->set_sender_id(USER_ID);
    }

    else if(search_state==9)
    {

        page_max=all_num;
        page_now=1;

        //删除数据
        delete_9();
        //填入数据
        if(all_num>20)
        {
            for(int i=0;i<20;i++)
            {
                putin_9();
            }
        }
        else
        {
            for(int i=0;i<all_num;i++)
            {
                putin_9();
            }
        }
    }
    else if(search_state==555)
    {
        if(all_num>0)
        {
            putin_mine();
        }
    }

    search_state=0;




    // qDebug()<<"00000000000000000000000000"<<all_num;
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
        search_101();
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
//        search_3();
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
        search_101();
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

        search_401();

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

//void Widget::on_btn_mine_clicked(bool checked)
//{
    
//}

void Widget::on_btn_mine_clicked()
{
    search_mine();
}

void Widget::putin_mine()
{
    information *me=new information;
    if(user_name.empty()==false)
        me->set_name(user_name[0]);
    if(user_age.empty()==false)
        me->set_age(user_age[0]);
    if(user_gender.empty()==false)
        me->set_gender(user_gender[0]);
    if(user_address.empty()==false)
        me->set_address(user_address[0]);
    if(user_phone.empty()==false)
        me->set_phone(user_phone[0]);

    me->show();
}

void Widget::search_mine()
{
    search_state=555;
    QString sql= R"(
    SELECT
        user.name AS user_name,
        user.gender AS user_gender,
        user.id AS user_id,
        user.age AS user_age,
        user.phone AS user_phone,
        user.address AS user_address
    FROM
        user
    WHERE
        user.id = ')"+ USER_ID +R"('
    )";
    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );
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

    btn_hide();
    ui->btn_main_item_1->setText("主页");
    ui->btn_main_item_2->setText("提问");
    ui->btn_main_item_1->show();
    ui->btn_main_item_2->show();
    on_btn_main_item_1_clicked();
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
//    search_102();
}

void Widget::on_combo_depart_1_currentIndexChanged(const QString &arg1)
{
//    search_102();
}

void Widget::on_date_1_userDateChanged(const QDate &date)
{
//    search_102();
}

void Widget::putin_102()
{
     ui->combo_docname_1->addItem( doctor_name [ page_now - 1 ] );
}
//填入doctor
void Widget::search_102()
{
    search_state=102;

    QString sql ="SELECT doctor.name AS doctor_name"
                 " FROM appointment, doctor, patient, office "
                 "WHERE "
                 "appointment.patient_id=patient.id AND appointment.doctor_id = doctor.id AND doctor.office_id = office.id AND"
                 " appointment.date = '"+ui->date_1->date().toString("yyyy-MM-dd")+"' AND office.name = '"+ui->combo_depart_1->currentText()+"';";

    NetClient &client = NetClient::getInstance();
    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );

}

void Widget::putin_101()
{
     ui->combo_patient_1->addItem( patient_name [ page_now - 1 ] );
}

//填入患者
void Widget::search_101()
{
    search_state=101;
    QString sql= R"(
    SELECT
        patient.name AS patient_name
    FROM
        patient , user
    WHERE
        user.id = patient.user_id AND
        user.id = ')" + USER_ID + R"(';
    )";
    NetClient &client = NetClient::getInstance();
    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );

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
    w->set_label_user_name( patient_name [page_now-1] );
    w->set_label_date( diagnosis_date [page_now-1] );
    w->set_label_doc_name( doctor_name [page_now-1] );
    w->set_label_apartment( office_name [page_now-1] );
    if(three_which==1)
    {
        w->set_label_which("诊断报告");
        //将诊断报告添加到富文本编辑器
         NetLoader::get_file(inspreport_filepath[page_now-1],API_KEY,client);
    }
    else if(three_which==2)
    {
        w->set_label_which("处方");
        NetLoader::get_file(prescription_filepath[page_now-1],API_KEY,client);
        //将处方添加到富文本编辑器
    }
    else if(three_which==3)
    {
        w->set_label_which("医嘱");
        NetLoader::get_file(diagnosis_filepath[page_now-1],API_KEY,client);
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
        sql= " SELECT  patient.name AS patient_name,"
             "  inspreport.date AS inspreport_date,  "
             "office.name AS office_name,  "
             "doctor.name AS doctor_name, "
             "inspreport.filepath AS inspreport_filepath FROM patient , "
             "inspreport , doctor , office "
             "WHERE "
              "patient.id = inspreport.patient_id AND doctor.id = inspreport.doctor_id AND doctor.office_id = office.id AND "
             "patient.name = '" + ui->combo_patient_1->currentText() + "' AND inspreport.date = '" + ui->date_1->date().toString("yyyy-MM-dd") + "' AND office.name = '" + ui->combo_depart_1->currentText() + "' AND  doctor.name = '" + ui->combo_docname_1->currentText() + "'; ";
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
            patient.id = prescription.patient_id AND prescription.doctor_id = doctor.id AND doctor.office_id = office.id AND
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
             patient.id = diagnosis.patient_id  AND
            doctor.id = diagnosis.doctor_id  AND
            doctor.office_id = office.id AND
            patient.name = ')" + ui->combo_patient_1->currentText() + R"(' AND
            diagnosis.date = ')" + ui->date_1->date().toString("yyyy-MM-dd") + R"(' AND
            office.name = ')" + ui->combo_depart_1->currentText() + R"(' AND
            doctor.name = ')" + ui->combo_docname_1->currentText() + R"(';
        )";
    }

    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );

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
    ui->listWidget_3->clear();

//    //清空QlistWidget
//    int n=ui->listWidget_3->count();//获取item的总数
//    删去所有item
//    for(int i=0;i<n;i++)
//    {
//        QListWidgetItem *item = ui->listWidget_3->takeItem(0);
//        delete item;
//        item=0;
//    }
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

//    qDebug()<<"666666666666666";
    // qDebug()<< *(doctor_gender+page_now*9-9+i) ;

    //填入数据
    w->set_label_doc_name( doctor_name[page_now*9-9+i] );
    w->set_label_gender( doctor_gender[page_now*9-9+i] );
    w->set_label_apartment( office_name[page_now*9-9+i] );
    w->set_label_describe( doctor_describe[page_now*9-9+i] );
    w->adate_now = ui->date_3->date().toString("yyyy-MM-dd");
    w->doctor_id = doctor_id[page_now*9-9+i];
    // w->patient_name = patient_name+page_now*9-9+i;
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
    search_state=3;
    QString sql="";
    //通过 科室 日期 医生姓名 医生性别 查询： 医生姓名 性别 科室 简介
    if(ui->lineEdit_docname_3->text()=="")
    {
        sql= R"(
        SELECT
            doctor.name AS doctor_name,
            doctor.gender AS doctor_gender,
            office.name AS office_name,
            doctor.describe AS doctor_describe,
            doctor.id AS doctor_id
        FROM
            doctor ,office
        WHERE
            doctor.office_id = office.id AND
            office.name = ')" + ui->combo_depart_3->currentText() + R"(' AND
            doctor.gender = ')" + ui->combo_gender_3->currentText() + R"(';
        )";
    }
    else
    {
        sql= R"(
        SELECT
            doctor.name AS doctor_name,
            doctor.gender AS doctor_gender,
            office.name AS office_name,
            doctor.describe AS doctor_describe,
            doctor.id AS doctor_id
        FROM
            doctor ,office
        WHERE
            doctor.office_id = office.id AND
            office.name = ')" + ui->combo_depart_3->currentText() + R"(' AND
            doctor.name = ')" + ui->lineEdit_docname_3->text() + R"(' AND
            doctor.gender = ')" + ui->combo_gender_3->currentText() + R"(';
        )";
    }
    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );

}

void Widget::on_btn_confirm_3_clicked()
{
    search_3();
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

        if(page_now<page_max)
        {
            for(int i=0;i<9;i++)
            {
                putin_3(i);//缺少参数
            }
        }
        else
        {
            for(int i=0;i<all_num-9*(page_max-1);i++)
            {
                putin_3(i);
            }
        }

    }
}

void Widget::on_btn_page_1_3_clicked()
{
    page_now=1;
    delete_3();
    if(page_now<page_max)
    {
        for(int i=0;i<9;i++)
        {
            putin_3(i);//缺少参数
        }
    }
    else
    {
        for(int i=0;i<all_num-9*(page_max-1);i++)
        {
            putin_3(i);
        }
    }
}

void Widget::on_btn_page_2_3_clicked()
{
    page_now--;
    delete_3();
    if(page_now<page_max)
    {
        for(int i=0;i<9;i++)
        {
            putin_3(i);//缺少参数
        }
    }
    else
    {
        for(int i=0;i<all_num-9*(page_max-1);i++)
        {
            putin_3(i);
        }
    }

}

void Widget::on_btn_page_3_3_clicked()
{
    page_now++;
    delete_3();
    if(page_now<page_max)
    {
        for(int i=0;i<9;i++)
        {
            putin_3(i);//缺少参数
        }
    }
    else
    {
        for(int i=0;i<all_num-9*(page_max-1);i++)
        {
            putin_3(i);
        }
    }
}

void Widget::on_btn_page_4_3_clicked()
{
    page_now=page_max;
    if(page_now<page_max)
    {
        for(int i=0;i<9;i++)
        {
            putin_3(i);//缺少参数
        }
    }
    else
    {
        for(int i=0;i<all_num-9*(page_max-1);i++)
        {
            putin_3(i);
        }
    }
}


void Widget::putin_401()
{
     ui->combo_user_4->addItem( patient_name [ page_now - 1 ] );
}

//填入患者
void Widget::search_401()
{
    search_state=401;
    QString sql= R"(
    SELECT
        patient.name AS patient_name
    FROM
        patient , user
    WHERE
        user.id = patient.user_id AND
        user.id = ')" + USER_ID + R"(';
    )";
    NetClient &client = NetClient::getInstance();
    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );

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
    myAppointment *w = new myAppointment;
    QListWidgetItem* pItem = new QListWidgetItem;
    //填入数据
    w->set_label_user_name(patient_name[page_now*9-9+i]);
    w->set_label_date(appointment_date[page_now*9-9+i]);
    w->set_label_time(appointment_time[page_now*9-9+i]);
    w->set_label_doc_name(  doctor_name[page_now*9-9+i]  );
    w->set_label_apartment(office_name[page_now*9-9+i]);
    w->set_label_id(appointment_id[page_now*9-9+i]);

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
    search_state=4;
    QString sql="";
    //通过 患者姓名 预约日期 医生 医生性别 部门 查询： 患者姓名 日期 时间 医生 部门 预约序号
    if(ui->lineEdit_docname_4->text()=="")
    {
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
            patient.id=appointment.patient_id AND   appointment.doctor_id = doctor.id AND office.id = doctor.office_id AND
            patient.name =')" + ui->combo_user_4->currentText() + R"(' AND
            appointment.date =')" + ui->date_4->date().toString("yyMMdd") + R"(' AND
            doctor.gender =')" + ui->combo_gender_4->currentText() + R"(' AND
            office.name = ')" + ui->combo_depart_4->currentText() + R"(';
        )";
    }
    else
    {
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
            patient.id=appointment.patient_id AND   appointment.doctor_id = doctor.id AND office.id = doctor.office_id AND
            patient.name =')" + ui->combo_user_4->currentText() + R"(' AND
            appointment.date =')" + ui->date_4->date().toString("yyMMdd") + R"(' AND
            doctor.name =')" + ui->lineEdit_docname_4->text() + R"(' AND
            doctor.gender =')" + ui->combo_gender_4->currentText() + R"(' AND
            office.name = ')" + ui->combo_depart_4->currentText() + R"(';
        )";
    }
    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );
}

void Widget::on_btn_confirm_4_clicked()
{
    search_4();
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
        if(page_now<page_max)
        {
            for(int i=0;i<9;i++)
            {
                putin_4(i);//缺少参数
            }
        }
        else
        {
            for(int i=0;i<all_num-9*(page_max-1);i++)
            {
                putin_4(i);
            }
        }
    }
}

void Widget::on_btn_page_1_4_clicked()
{
    page_now=1;
    delete_4();
    if(page_now<page_max)
    {
        for(int i=0;i<9;i++)
        {
            putin_4(i);//缺少参数
        }
    }
    else
    {
        for(int i=0;i<all_num-9*(page_max-1);i++)
        {
            putin_4(i);
        }
    }
}

void Widget::on_btn_page_2_4_clicked()
{
    page_now--;
    delete_4();
    if(page_now<page_max)
    {
        for(int i=0;i<9;i++)
        {
            putin_4(i);//缺少参数
        }
    }
    else
    {
        for(int i=0;i<all_num-9*(page_max-1);i++)
        {
            putin_4(i);
        }
    }

}

void Widget::on_btn_page_3_4_clicked()
{
    page_now++;
    delete_4();
    if(page_now<page_max)
    {
        for(int i=0;i<9;i++)
        {
            putin_4(i);//缺少参数
        }
    }
    else
    {
        for(int i=0;i<all_num-9*(page_max-1);i++)
        {
            putin_4(i);
        }
    }
}

void Widget::on_btn_page_4_4_clicked()
{
    page_now=page_max;
    delete_4();
    if(page_now<page_max)
    {
        for(int i=0;i<9;i++)
        {
            putin_4(i);//缺少参数
        }
    }
    else
    {
        for(int i=0;i<all_num-9*(page_max-1);i++)
        {
            putin_4(i);
        }
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
//    qDebug()<<"before";
    w->set_label_name(  doctor_name[page_now*9-9+i]  );
    w->set_label_gender( doctor_gender[page_now*9-9+i] );
    w->set_label_apartment( office_name[page_now*9-9+i] );
    w->set_label_introduce( doctor_describe[page_now*9-9+i] );
    w->doc_id=doctor_id[page_now*9-9+i];
//    qDebug()<<"middddddddddddddddddd";
    w->dw=this;
//    qDebug()<<"afterrrrrrrrrrrrrrrrrr";
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
    search_state=5;
    QString sql = "";
    if(ui->lineEdit_docname_5->text()=="")
    {
        //通过 科室 日期 医生姓名 医生性别 查询： 医生姓名 医生性别 科室 简介 id
        sql = R"(
        SELECT
            doctor.name AS doctor_name,
            doctor.gender AS doctor_gender,
            office.name AS office_name,
            doctor.describe AS doctor_describe,
            doctor.id AS doctor_id
        FROM
            doctor , office
        WHERE
            doctor.office_id = office.id AND
            office.name = ')" + ui->combo_depart_5->currentText() + R"(' AND
            doctor.gender = ')" + ui->combo_gender_5->currentText() + R"(';
        )";
    }
    else
    {
        sql = R"(
        SELECT
            doctor.name AS doctor_name,
            doctor.gender AS doctor_gender,
            office.name AS office_name,
            doctor.describe AS doctor_describe,
            doctor.id AS doctor_id
        FROM
            doctor , office
        WHERE
            doctor.office_id = office.id AND
            office.name = ')" + ui->combo_depart_5->currentText() + R"(' AND
            doctor.name = ')" + ui->lineEdit_docname_5->text() + R"(' AND
            doctor.gender = ')" + ui->combo_gender_5->currentText() + R"(';
        )";
    }
    //通过 科室 日期 医生姓名 医生性别 查询： 医生姓名 医生性别 科室 简介 id


    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );




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
        if(page_now<page_max)
        {
            for(int i=0;i<9;i++)
            {
                putin_5(i);//缺少参数
            }
        }
        else
        {
            for(int i=0;i<all_num-9*(page_max-1);i++)
            {
                putin_5(i);
            }
        }

    }
}

void Widget::on_btn_page_1_5_clicked()
{
    page_now=1;
    delete_5();
    if(page_now<page_max)
    {
        for(int i=0;i<9;i++)
        {
            putin_5(i);//缺少参数
        }
    }
    else
    {
        for(int i=0;i<all_num-9*(page_max-1);i++)
        {
            putin_5(i);
        }
    }
}

void Widget::on_btn_page_2_5_clicked()
{
    page_now--;
    delete_5();
    if(page_now<page_max)
    {
        for(int i=0;i<9;i++)
        {
            putin_5(i);//缺少参数
        }
    }
    else
    {
        for(int i=0;i<all_num-9*(page_max-1);i++)
        {
            putin_5(i);
        }
    }

}

void Widget::on_btn_page_3_5_clicked()
{
    page_now++;
    delete_5();
    if(page_now<page_max)
    {
        for(int i=0;i<9;i++)
        {
            putin_5(i);//缺少参数
        }
    }
    else
    {
        for(int i=0;i<all_num-9*(page_max-1);i++)
        {
            putin_5(i);
        }
    }
}

void Widget::on_btn_page_4_5_clicked()
{
    page_now=page_max;
    delete_5();
    if(page_now<page_max)
    {
        for(int i=0;i<9;i++)
        {
            putin_5(i);//缺少参数
        }
    }
    else
    {
        for(int i=0;i<all_num-9*(page_max-1);i++)
        {
            putin_5(i);
        }
    }
}

void Widget::onItemClicked_8(QListWidgetItem *item)
{
    // 当用户点击项时，弹出消息框显示点击的项的文本
//    QMessageBox::information(this, "Item Clicked", "You clicked: " + item->text());
    search_state=888;
    QString sql= R"(
    SELECT
        doctor.id AS doctor_id
    FROM
        doctor
    WHERE
        doctor.name =')" + item->text() + R"(' ;
    )";

    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );

    ui->label_docname_8->setText(item->text());

}

void Widget::delete_8()
{
//    清空QlistWidget
    int n=ui->listWidget_8->count();//获取item的总数
    qDebug()<<n<<"------------------------------------";
//    删去所有item
    for(int i=0;i<n;i++)
    {
        QListWidgetItem *item = ui->listWidget_8->takeItem(0);
        delete item;
    }
}

void Widget::search_8()
{
    search_state=8;
    QString sql= "select receiver_id from chat_history where sender_id ='"+USER_ID+"'; ";

    DatabaseManager &dbm = DatabaseManager::getInstance();
    QSqlQuery query(dbm.getDatabase());
    query.exec(sql);

    sql_query.clear();
    //删除数据
    delete_8();
//    qDebug()<<"123456";
    while (query.next())
    {
        QString qi= query.value(0).toString();
//        QThread::sleep(1);
//        sql_query.push_back(qi);
        search_801(qi);
//        search_801(query.value(0).toString());
    }
//    if(sql_query.empty()==false)
//        search_801();

}

void Widget::on_btn_confirm_8_clicked()
{
    //    查询
    search_8();//参数未填充
}

void Widget::putin_801()
{

    if(ui->lineEdit_search_8->text()==""||ui->lineEdit_search_8->text()==doctor_name[0])
    {
        //创建item
        QListWidgetItem* pItem = new QListWidgetItem(QIcon(":/icons/money.png"), doctor_name[0]);

        //设置item大小
        pItem->setSizeHint(QSize(ui->listWidget_8->width(),ui->listWidget_8->height()/6 ));

        //添加进QlistWidget
        ui->listWidget_8->addItem(pItem);
//        delete pItem;
        ui->listWidget_8->update();
    }
//        //创建item
//        QListWidgetItem* pItem1 = new QListWidgetItem(QIcon(":/icons/money.png"), doctor_name[0]);

//        //设置item大小
//        pItem1->setSizeHint(QSize(ui->listWidget_8->width(),ui->listWidget_8->height()/6 ));

//        //添加进QlistWidget
//        ui->listWidget_8->addItem(pItem1);

//    sql_query.pop_front();
//    if(sql_query.empty()==false)
//        search_801();
}

void Widget::search_801(QString qi)
{
    search_state=801;
    QString sql= R"(
    SELECT
        name AS doctor_name
    FROM
        doctor
    WHERE
        id = ')" +  qi  + R"(';
    )";

    NetLoader::get_sql(sql , USER_ID , 0 , API_KEY , client );
}

void Widget::putin_802()
{
    ui->label_docname_8->setText(doctor_name[0]);
    ui->widget_chat_box_8->set_receiver_id(doctor_id[0]);
    ui->widget_chat_box_8->set_sender_id(USER_ID);
}

void Widget::search_802(QString qi)
{
    search_state=802;
    QString sql= R"(
    SELECT
        doctor.id AS doctor_id,
        doctor.name AS doctor_name
    FROM
        doctor
    WHERE
        doctor.name = ')" + qi + R"(' ;
    )";

    NetLoader::get_sql(sql , USER_ID , 0 , API_KEY , client );

}
/*
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
        user.id = tiezi.user_id AND
        huifu.tiezi_id = tiezi.id AND
        huifu.doctor_id = huifu.doctor_id AND
        tiezi.id = )"+ tiezi_id[page_now] +R"(
    )";

    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );

    //创建item
    little_zhihu *w = new little_zhihu;

    QListWidgetItem* pItem = new QListWidgetItem;

    //填入数据
    w->set_label_user_name(user_name[page_now-1]);
    w->set_label_user_context(tiezi_text[page_now-1]);
    w->set_label_answernum(tiezi_num[page_now-1]);
    w->tiezi_id = tiezi_id[page_now-1];
    w->allnum=all_num;
    w->now=page_now;
    w->huifutext=huifu_text[page_now-1];
    w->huifutime=huifu_time[page_now-1];
    w->doctorname=doctor_name[page_now-1];
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
        tiezi.text AS tiezi_text,
        tiezi.date AS tiezi_date,
        tiezi.id AS tiezi_id,
        tiezi.num AS tiezi_num,
        user.name AS user_name
    FROM
        user , tiezi
    WHERE
        user.id = tiezi.user_id AND
        tiezi.text = ')"+ ui->lineEdit_search_9->text() +R"('
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
    search_9();//参数未填
}*/


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
    //创建item
    little_zhihu *w = new little_zhihu;
    QListWidgetItem* pItem = new QListWidgetItem;

    //填入数据
    w->set_label_user_name(user_name[page_now-1]);
    w->set_label_user_context(tiezi_text[page_now-1]);
    w->set_label_answernum(tiezi_num[page_now-1]);
    w->tiezi_id = tiezi_id[page_now-1];
    //设置item大小
    pItem->setSizeHint(QSize(ui->listWidget_9->width(),ui->listWidget_9->height()/5 ));
    //添加进QlistWidget
    ui->listWidget_9->addItem(pItem);
    ui->listWidget_9->setItemWidget(pItem, w);
    //不可被选中
    pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
    page_now++;
}

void Widget::search_9()
{
    search_state=9;
    QString sql="";
    if(ui->lineEdit_search_9->text()=="")
    {
        sql= R"(
        SELECT
            tiezi.text AS tiezi_text,
            tiezi.date AS tiezi_date,
            tiezi.id AS tiezi_id,
            tiezi.num AS tiezi_num,
            user.name AS user_name
        FROM
            user , tiezi
        WHERE
            user.id = tiezi.user_id
        )";
    }
    else
    {
        sql= R"(
        SELECT
            tiezi.text AS tiezi_text,
            tiezi.date AS tiezi_date,
            tiezi.id AS tiezi_id,
            tiezi.num AS tiezi_num,
            user.name AS user_name
        FROM
            user , tiezi
        WHERE
            user.id = tiezi.user_id AND
            tiezi.text = ')"+ ui->lineEdit_search_9->text() +R"('
        )";
    }

    NetLoader::get_sql(sql , USER_ID , 0 , API_KEY , client );
}

void Widget::on_btn_confirm_9_clicked()
{
    search_9();
}





void Widget::on_btn_ques_10_clicked()
{
    QString sql = " INSERT INTO tiezi (text, date , num , user_id ) VALUES ( '"+ui->textEdit_10->toPlainText()+"' , '"+ QDate::currentDate().toString("yyyy-MM-dd") +"', 0, '"+ USER_ID +"'); ";

    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );

    ui->textEdit_10->setText("提交成功");

}


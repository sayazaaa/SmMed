#include "widget.h"
#include "ui_widget.h"
#include "newappointment.h"
#include "little_doctor.h"
#include "little_history.h"
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

QVector<QString> v;

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

int page_state=-1;
QString  USER_ID="root";
QString apikey="429080af-532a-48a0-868b-42159fd4319e";
NetClient &client = NetClient::getInstance();
//NetClient &client = NetClient::getInstance();
int daydata[7]={0};
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

    ui->sw_main->setCurrentIndex(0);
    void setToolTip(const QString &);
    ui->btn_mine->setToolTip("近期预约就诊情况");
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
}


void Widget::handleJsonReceived(const QJsonObject &mainsource)
{
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


    if(mainsource.size()<=0)return;//如果source为空直接结束
    QJsonArray array=mainsource.value("array").toArray();
    int n=0;
    for(auto item:array){


        QJsonObject source = item.toObject();
        qDebug()<<"777"<<source;
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
        qDebug()<<"111111111111111";
        n++;
    }
    all_num=n;
    if(choice_state == 100){
        for(int i=0;i<all_num;i++)
        {
            ui->combo_docname_1->addItem( doctor_name [ all_num - i]  );
        }

    }else if(choice_state == 101){
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
    }else if(choice_state == 401){
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
    }else if(choice_state == 301){
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
    }else if(choice_state == 201){
        int data_num=all_num;
        page_max=data_num/9+1;
        page_now=1;

        //填写总数据量
        ui->label_data_num_text_2->setText("共有"+QString::number(data_num)+"项数据");
        //删除数据
        delete_2();
        //填入数据
        if(data_num>9)
        {
            for(int i=0;i<9;i++)
            {
                putin_2(i);//缺少参数
            }
        }
        else
        {
            for(int i=0;i<data_num;i++)
            {
                putin_2(i);//缺少参数
            }
        }
    }else if(choice_state == 0){
        daydata[choice_state++] =all_num;
        QString sql ="SELECT appointment.patient_id AS patient_id "
                     "FROM appointment "
                     "WHERE "
                     "appointment.date ='"+QDateTime::currentDateTime().addDays(-1).toString("yyyy-MM-dd")+"';";
        NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );
    }else if(choice_state == 1){
        daydata[choice_state++] =all_num;
        qDebug()<<"                          ssssssssssssssssssssssss     ";
        QString sql ="SELECT appointment.patient_id AS patient_id "
                     "FROM appointment "
                     "WHERE "
                     "appointment.date ='"+(QDateTime::currentDateTime().addDays(-2)).toString("yyyy-MM-dd")+"';";
        NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );
    }else if(choice_state == 2){
        daydata[choice_state++] =all_num;
        QString sql ="SELECT appointment.patient_id AS patient_id "
                     "FROM appointment "
                     "WHERE "
                     "appointment.date ='"+(QDateTime::currentDateTime().addDays(-3)).toString("yyyy-MM-dd")+"';";
        NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );
    }else if(choice_state == 3){
        daydata[choice_state++] =all_num;
        QString sql ="SELECT appointment.patient_id AS patient_id "
                     "FROM appointment "
                     "WHERE "
                     "appointment.date ='"+(QDateTime::currentDateTime().addDays(-4)).toString("yyyy-MM-dd")+"';";
        NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );
    }else if(choice_state == 4){
        daydata[choice_state++] =all_num;
        QString sql ="SELECT appointment.patient_id AS patient_id "
                     "FROM appointment "
                     "WHERE "
                     "appointment.date ='"+(QDateTime::currentDateTime().addDays(-5)).toString("yyyy-MM-dd")+"';";
        NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );
    }else if(choice_state == 5){
        daydata[choice_state++] =all_num;
        QString sql ="SELECT appointment.patient_id AS patient_id "
                     "FROM appointment "
                     "WHERE "
                     "appointment.date ='"+(QDateTime::currentDateTime().addDays(-6)).toString("yyyy-MM-dd")+"';";
        NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );
    }else if(choice_state == 6){
        daydata[choice_state++] =all_num;
        chart_create *a = new chart_create();
        a->set(7,daydata);
        a->create();
        a->show();
    }

    //
}

void chart_create::set(int day, int* item_group)
{
    days=day;
    item=item_group;
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

void Widget::on_btn_logout_clicked()
{
    close();
}

void Widget::on_btn_littleshow_clicked()
{
    showMinimized();
}


void Widget::on_btn_mine_clicked()
{
    QString sql ="SELECT appointment.patient_id AS patient_id "
                 "FROM appointment "
                 "WHERE "
                 "appointment.date ='"+QDateTime::currentDateTime().toString("yyyy-MM-dd")+"';";

    choice_state=000;
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
}



void Widget::on_btn_menu_item_1_clicked()
{
    ui->sw_main->setCurrentIndex(1);
}

void Widget::on_btn_menu_item_2_clicked()
{
    ui->sw_main->setCurrentIndex(2);
    QString sql= R"(
    SELECT
        user.id       AS user_id,
        user.name     AS user_name,
        user.gender   AS user_gender,
        user.phone   AS  user_phone,
        user.password AS user_password,
        user.address  AS user_address
    FROM
        user;
    )";

    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );
    choice_state=201;
}

void Widget::on_btn_menu_item_3_clicked()
{
    ui->sw_main->setCurrentIndex(3);
    QString sql= R"(
    SELECT
        doctor.name AS doctor_name,
        doctor.gender AS doctor_gender,
        office.name AS office_name,
        doctor.describe AS doctor_describe,
        doctor.id AS doctor_id,
        doctor.password AS doctor_password
    FROM
        doctor ,office
    WHERE
        doctor.office_id = office.id;
    )";

    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );
    choice_state=301;
}

void Widget::on_btn_menu_item_4_clicked()
{
    ui->sw_main->setCurrentIndex(4);
    QString sql= R"(
    SELECT
        patient.name AS patient_name,
        patient.id AS patient_id,
        patient.gender AS patient_gender,
        patient.phone AS  patient_phone
    FROM
        patient;
    )";

    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );
    choice_state=401;

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
//        pa.name = ')" + ui->combo_patient_1->currentText() + R"(' AND
//        di.date = ')" + ui->date_1->date().toString() + R"(' AND
//        o.name = ')" + ui->combo_depart_1->currentText() + R"(';
//    )";

    QString sql;
    sql.sprintf(
            "SELECT doctor.name AS doctor_name FROM prescription, doctor, patient, office WHERE prescription.doctor_id = doctor.id AND prescription.patient_id = patient.id AND doctor.office_id = office.id %s %s",
            ((ui->label_patient_1->text() == "")?"":("AND patient.name = '"+ui->label_patient_1->text().toStdString()+"'")).c_str(),
            ((ui->date_1->date().toString("yyyy-MM-dd")=="")?"":("AND patient.name = '"+ui->date_1->date().toString("yyyy-MM-dd").toStdString()+"'")).c_str()
        );

    choice_state=100;
    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );

    //填入医生信息

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

        sql.sprintf(
                "SELECT patient.name AS patient_name,  inspreport.date AS inspreport_date,  office.name AS office_name,  doctor.name AS doctor_nameinspreport.filepath AS inspreport_filepath FROM patient , inspreport , doctor , office WHERE patient.id = inspreport.patient_id AND doctor.id = inspreport.doctor_id AND doctor.office_id = office.id %s %s %s %s",
                ((ui->label_patient_1->text() == "")?"":("AND patient.name = '"+ui->label_patient_1->text().toStdString()+"'")).c_str(),
                ((ui->date_1->date().toString("yyyy-MM-dd")=="")?"":("AND inspreport.date = '"+ui->date_1->date().toString("yyyy-MM-dd").toStdString()+"'")).c_str(),
                ((ui->combo_depart_1->currentText()=="")?"":("AND office.name = '"+ui->combo_depart_1->currentText().toStdString()+"'")).c_str(),
                 ((ui->combo_docname_1->currentText()=="")?"":("AND doctor.name ='"+ui->combo_docname_1->currentText().toStdString()  +"'")).c_str()
            );


    }
    else if(three_which==2)
    {
        sql.sprintf(
                "SELECT patient.name AS patient_name,prescription.date AS prescription_date, office.name AS office.name,doctor.name AS doctor_name, prescription.filepath AS prescription_filepath"
                " FROM patient, prescription , doctor , office WHERE patient.id = prescription.patient_id AND doctor.id = prescription.doctor_id AND doctor.office_id = office.id %s %s %s %s",
                    ((ui->label_patient_1->text() == "")?"":("AND patient.name = '"+ui->label_patient_1->text().toStdString()+"'")).c_str(),
                    ((ui->date_1->date().toString("yyyy-MM-dd")=="")?"":("AND inspreport.date = '"+ui->date_1->date().toString("yyyy-MM-dd").toStdString()+"'")).c_str(),
                    ((ui->combo_depart_1->currentText()=="")?"":("AND office.name = '"+ui->combo_depart_1->currentText().toStdString()+"'")).c_str(),
                     ((ui->combo_docname_1->currentText()=="")?"":("AND doctor.name ='"+ui->combo_docname_1->currentText().toStdString()  +"'")).c_str()
            );
    }
    else if(three_which==3)
    {
        sql.sprintf(
                "SELECT patient.name AS patient_name,diagnosis.date AS diagnosis_date, office.name AS office.name,doctor.name AS doctor_name, diagnosis.filepath AS diagnosis_filepath FROM patient, diagnosis , doctor , office WHERE patient.id = prescription.patient_id AND doctor.id = prescription.doctor_id AND doctor.office_id = office.id %s %s %s %s",
                    ((ui->label_patient_1->text() == "")?"":("AND patient.name = '"+ui->label_patient_1->text().toStdString()+"'")).c_str(),
                    ((ui->date_1->date().toString("yyyy-MM-dd")=="")?"":("AND inspreport.date = '"+ui->date_1->date().toString("yyyy-MM-dd").toStdString()+"'")).c_str(),
                    ((ui->combo_depart_1->currentText()=="")?"":("AND office.name = '"+ui->combo_depart_1->currentText().toStdString()+"'")).c_str(),
                     ((ui->combo_docname_1->currentText()=="")?"":("AND doctor.name ='"+ui->combo_docname_1->currentText().toStdString()  +"'")).c_str()
            );
    }

//    qDebug()<<"666";
    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );
//    qDebug()<<"777";
    choice_state=101;



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
    little_doctor *w = new little_doctor;
    QListWidgetItem* pItem = new QListWidgetItem;

    //填入数据
    w->set_label_name( doctor_name[page_now*9+i-9] );
    w->set_label_gender( doctor_gender[page_now*9-9+i] );
    w->set_label_apartment( office_name[page_now*9-9+i] );
    w->set_label_introduce( doctor_describe[page_now*9-9+i] );
    w->set_label_id( doctor_id[page_now*9-9+i]);
    w->set_label_password(doctor_password[page_now*9-9+i]);
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
    QString sql;
    sql.sprintf(
            "SELECT doctor.name AS doctor_name,doctor.gender AS doctor_gender,office.name AS office_name,doctor.describe AS doctor_describe,doctor.id AS doctor_id,doctor.password AS doctor_password FROM doctor ,office WHERE doctor.office_id = office.id %s %s %s",
            ((ui->combo_depart_3->currentText() == "")?"":("AND office.name = '"+ui->combo_depart_3->currentText().toStdString()+"'")).c_str(),
            ((ui->lineEdit_docname_3->text()=="")?"":("AND doctor.name = '"+ui->lineEdit_docname_3->text().toStdString()+"'")).c_str(),
            ((ui->combo_gender_3->currentText()=="全部")?"":("AND doctor.gender = '"+ui->combo_gender_3->currentText().toStdString()+"'")).c_str()
        );

    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );
    choice_state=301;



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
    patient_editor *w = new patient_editor;
    QListWidgetItem* pItem = new QListWidgetItem;
    //填入数据
    w->set_gender(patient_gender[page_now*9-9+i]);
    w->set_id(patient_id[page_now*9-9+i]);
    w->set_name(patient_name[page_now*9-9+i]);
    w->set_phone(patient_phone[page_now*9-9+i]);

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
    QString sql;
    sql.sprintf(
        "SELECT patient.name AS patient_name,patient.id AS patient_id,patient.gender AS patient_gender,patient.phone AS  patient_phone FROM patient WHERE 1 %s %s %s",
        ((ui->combo_gender_4->currentText() == "全部")?"":("AND patient.gender = '"+ui->combo_gender_4->currentText().toStdString()+"'")).c_str(),
        ((ui->lineEdit_docname_4->text()=="")?"":("AND patient.name = '"+ui->lineEdit_docname_4->text().toStdString()+"'")).c_str(),
        ((ui->lineEdit_phone_4->text()=="")?"":("AND patient.name = '"+ui->lineEdit_phone_4->text().toStdString()+"'")).c_str()
    );

    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );
    choice_state=401;




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

void Widget::page_hide_2()
{
    ui->btn_page_1_2->hide();
    ui->btn_page_2_2->hide();
    ui->btn_page_3_2->hide();
    ui->btn_page_4_2->hide();
}

void Widget::delete_2()
{
    //清空QlistWidget
    int n=ui->listWidget_2->count();//获取item的总数
//    删去所有item
    for(int i=0;i<n;i++)
    {
        QListWidgetItem *item = ui->listWidget_2->takeItem(0);
        delete item;
    }
}

void Widget::putin_2(int i)
{
    page_hide_2();
    //填写页数
    ui->btn_page_now_2->setText(QString::number(page_now));
    ui->btn_page_now_2->setEnabled(false);
    if(page_now>3)
    {
        ui->btn_page_2_2->setText("...");
        ui->btn_page_2_2->show();
        ui->btn_page_2_2->setEnabled(false);
        ui->btn_page_1_2->setText("1");
        ui->btn_page_1_2->show();
    }
    else if(page_now==3)
    {
        ui->btn_page_2_2->setText("2");
        ui->btn_page_2_2->show();
        ui->btn_page_1_2->setText("1");
        ui->btn_page_1_2->show();
    }
    else if(page_now==2)
    {
        ui->btn_page_2_2->setText("1");
        ui->btn_page_2_2->show();
    }
    if(page_max-page_now>2)
    {
        ui->btn_page_3_2->setText("...");
        ui->btn_page_3_2->setEnabled(false);
        ui->btn_page_3_2->show();
        ui->btn_page_4_2->setText(QString::number(page_max));
        ui->btn_page_4_2->show();
    }
    else if(page_max-page_now==2)
    {
        ui->btn_page_3_2->setText(QString::number(page_max-1));
        ui->btn_page_3_2->show();
        ui->btn_page_4_2->setText(QString::number(page_max));
        ui->btn_page_4_2->show();
    }
    else if(page_max-page_now==1)
    {
        ui->btn_page_3_2->setText(QString::number(page_max));
        ui->btn_page_3_2->show();
    }

    //创建item
//    little_appointment *w = new little_appointment;
    information *w = new information;
    QListWidgetItem* pItem = new QListWidgetItem;
    //填入数据
    w->set_name(user_name[page_now*9+i-9]);
    w->set_address(user_address[page_now*9-9+i]);
    w->set_gender(user_gender[page_now*9-9+i]);
    w->set_id(user_id[page_now*9-9+i]);
    w->set_password(user_password[page_now*9-9+i]);
    w->set_phone(user_phone[page_now*9+i-9]);

    //设置item大小
    pItem->setSizeHint(QSize(ui->listWidget_2->width()/3-10,ui->listWidget_2->height()/3 ));
    //添加进QlistWidget
    ui->listWidget_2->addItem(pItem);
    ui->listWidget_2->setItemWidget(pItem, w);
    //不可被选中
    pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
}

void Widget::search_2()
{

    //通过 患者姓名 预约日期 医生 医生性别 部门 查询： 患者姓名 日期 时间 医生 部门 预约序号
    QString sql;
    sql.sprintf(
            "SELECT user.id AS user_id,user.name AS user_name,user.gender AS user_gender,user.phone AS  user_phone,user.password AS user_password,user.address AS user_address FROM user WHERE 1 %s ",
            ((ui->lineEdit_docname_2->text() == "")?"":("AND user.id = '"+ui->lineEdit_docname_2->text().toStdString()+"'")).c_str()
            );

    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );
    choice_state=201;




}

void Widget::on_btn_confirm_2_clicked()
{
//    查询
    search_2();//参数未填充

}

void Widget::on_btn_page_left_2_clicked()
{
    if(page_now!=1)
    {
        page_now--;
        delete_4();
        for(int i=0;i<9;i++)
        {
            putin_2(i);//缺少参数
        }
    }
}

void Widget::on_btn_page_right_2_clicked()
{
    if(page_now!=page_max)
    {
        page_now++;
        delete_2();
        for(int i=0;i<9;i++)
        {
            putin_2(i);//缺少参数
        }
    }
}

void Widget::on_btn_page_1_2_clicked()
{
    page_now=1;
    delete_2();
    for(int i=0;i<9;i++)
    {
        putin_2(i);//缺少参数
    }
}

void Widget::on_btn_page_2_2_clicked()
{
    page_now--;
    delete_2();
    for(int i=0;i<9;i++)
    {
        putin_2(i);//缺少参数
    }

}

void Widget::on_btn_page_3_2_clicked()
{
    page_now++;
    delete_2();
    for(int i=0;i<9;i++)
    {
        putin_2(i);//缺少参数
    }
}

void Widget::on_btn_page_4_2_clicked()
{
    page_now=page_max;
    delete_2();
    for(int i=0;i<9;i++)
    {
        putin_2(i);//缺少参数
    }
}

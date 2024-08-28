#include "widget.h"
#include "ui_widget.h"
#include "newappointment.h"
#include <QGraphicsDropShadowEffect>
#include <QString>
#include <QDebug>
#include "../shared/include/netclient.h"
#include "../shared/include/netloader.h"
#include "../shared/include/apikey.h"
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
//NetClient &client = NetClient::getInstance();

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

    ui->sw_main->setCurrentIndex(4);
    connect(&client, &NetClient::received_json, this, &Widget::handleJsonReceived);

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
            *(huifu_text+n++)=source.value("huifu_text").toString();
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
    //通过 医生序号doc_id[] 当前页数 page_now
    //获得 姓名doc_name[] 性别doc_gender[] 科室doc_apartment[]
    //填写QlistWidget

    //假定数据
    QString doc_name="abcdefghijskdscsdfacs";

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
    little_appointment *w = new little_appointment;
    QListWidgetItem* pItem = new QListWidgetItem;
    //填入数据
    w->set_name("用户");
    w->set_apartment(*(user_id+page_now*9-9+i));
    w->set_label_doc_name(  doc_name.mid(2,3)  );
    w->set_label_gender(*(user_gender+page_now*9-9+i));
    w->set_label_apartment(+page_now*9-9+i);

//    pItem->setBackground(QColor("green"));
    //设置item大小
    pItem->setSizeHint(QSize(ui->listWidget_1->width()/3-10,ui->listWidget_1->height()/3 ));
    //添加进QlistWidget
    ui->listWidget_1->addItem(pItem);
    ui->listWidget_1->setItemWidget(pItem, w);
    //不可被选中
    pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
}

void Widget::search_1()
{
    //通过 患者 日期 科室 查询 ：医生
    QString sql= R"(
    SELECT
        d.name AS doctor_name
    FROM
        patient pa
    JOIN
        diagnosis di ON pa.id = di.patient_id
    JOIN
        doctor d ON di.doctor_id = d.id
    JOIN
        office o ON d.office_id = o.id
    WHERE
        pa.name = ')" + ui->combo_patient_1->currentText() + R"(' AND
        di.date = ')" + ui->date_1->date().toString() + R"(' AND
        o.name = ')" + ui->combo_depart_1->currentText() + R"(';
    )";
    QString sql ="SELECT doctor.name AS doctor_name FROM prescription, doctor, patient, office WHERE patient.name ='"+ui->combo_patient_1->currentText()+"' AND prescription.date = '"+ui->date_1->date().toString("yyMMdd")+"' AND office.name = '"+ui->combo_depart_1->currentText()+"';";


    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );

    int data_num=all_num;
    page_max=data_num/9+1;
    page_now=1;

    //填写总数据量
    ui->label_data_num_text_7->setText("共有"+QString::number(data_num)+"项数据");
    //删除数据
    delete_1();
    //填入数据
    for(int i=0;i<9;i++)
    {
        putin_1();//缺少参数
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


void Widget::putin_2()
{
    //通过 医生序号doc_id[] 当前页数 page_now
    //获得 姓名doc_name[] 性别doc_gender[] 科室doc_apartment[]
    //填写QlistWidget

    //假定数据
    QString doc_name="abcdefghijskdscsdfacs";

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
    little_appointment *w = new little_appointment;
    QListWidgetItem* pItem = new QListWidgetItem;
    //填入数据
    w->set_name("患者");
    w->set_apartment("年龄");
    w->set_label_doc_name(  doc_name.mid(2,3)  );
    w->set_label_gender("male");
    w->set_label_apartment("18");

//    pItem->setBackground(QColor("green"));
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
    //get data()
    //通过 科室apartment 日期date 姓名searched_name 性别doc_gender
    //得到 数据总量data_num 总页数page_num 医生序号doc_id[] 当前页数page_now
    int data_num=9456;
    page_max=data_num/9+1;
    page_now=1;
    int doc_id[6]={1,2,3,4,5,6};

    //填写总数据量
    ui->label_data_num_text_2->setText("共有"+QString::number(data_num)+"项数据");
    //删除数据
    delete_2();
    //填入数据
    for(int i=0;i<9;i++)
    {
        putin_2();//缺少参数
    }
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
    ui->label_data_num_text_4->setText("共有"+QString::number(data_num)+"项数据");
    //删除数据
    delete_3();
    //填入数据
    for(int i=0;i<9;i++)
    {
        putin_3();//缺少参数
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
    //通过 医生序号doc_id[] 当前页数 page_now
    //获得 姓名doc_name[] 性别doc_gender[] 科室doc_apartment[]
    //填写QlistWidget

    //假定数据
    QString doc_name="abcdefghijskdscsdfacs";

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
    little_appointment *w = new little_appointment;
    QListWidgetItem* pItem = new QListWidgetItem;
    //填入数据
    w->set_apartment("类型");
    w->set_label_doc_name(  doc_name.mid(2,3)  );
    w->set_label_gender("male");
    w->set_label_apartment("医嘱");

//    pItem->setBackground(QColor("green"));
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
    //get data()
    //通过 科室apartment 日期date 姓名searched_name 性别doc_gender
    //得到 数据总量data_num 总页数page_num 医生序号doc_id[] 当前页数page_now
    int data_num=9456;
    page_max=data_num/9+1;
    page_now=1;
    int doc_id[6]={1,2,3,4,5,6};

    //填写总数据量
    ui->label_data_num_text_4->setText("共有"+QString::number(data_num)+"项数据");
    //删除数据
    delete_4();
    //填入数据
    for(int i=0;i<9;i++)
    {
        putin_4();//缺少参数
    }
}


void Widget::on_btn_logout_clicked()
{
    close();
}

void Widget::on_btn_littleshow_clicked()
{
    showMinimized();
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
    ui->sw_main->setCurrentIndex(4);
}


void Widget::on_btn_menu_item_1_clicked()
{
    ui->sw_main->setCurrentIndex(0);
    search_1();
}

void Widget::on_btn_menu_item_2_clicked()
{
    ui->sw_main->setCurrentIndex(1);
    search_2();
}

void Widget::on_btn_menu_item_3_clicked()
{
    ui->sw_main->setCurrentIndex(2);
    search_3();
}

void Widget::on_btn_menu_item_4_clicked()
{
    ui->sw_main->setCurrentIndex(3);
    ui->date->setDisplayFormat("yyyy/MM/dd");
    ui->date->setDate(QDate::currentDate());
    ui->date->setMinimumDate(QDate::currentDate());
    ui->date->setMaximumDate(QDate::currentDate().addDays(10));
    ui->date->setCalendarPopup(true);
    search_4();
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


void Widget::on_btn_confirm_1_clicked()
{

}


void Widget::on_btn_page_left_1_clicked()
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


void Widget::on_btn_page_1_1_clicked()
{
    page_now=1;
    delete_3();
    for(int i=0;i<9;i++)
    {
        putin_3();//缺少参数
    }
}


void Widget::on_btn_page_2_1_clicked()
{
    page_now--;
    delete_3();
    for(int i=0;i<9;i++)
    {
        putin_3();//缺少参数
    }
}





void Widget::on_btn_page_3_1_clicked()
{
    page_now++;
    delete_3();
    for(int i=0;i<9;i++)
    {
        putin_3();//缺少参数
    }
}


void Widget::on_btn_page_4_1_clicked()
{
    page_now=page_max;
    delete_3();
    for(int i=0;i<9;i++)
    {
        putin_3();//缺少参数
    }
}


void Widget::on_btn_page_right_1_clicked()
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


void Widget::on_btn_confirm_2_clicked()
{

}


void Widget::on_btn_page_left_2_clicked()
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


void Widget::on_btn_page_1_2_clicked()
{
    page_now=1;
    delete_3();
    for(int i=0;i<9;i++)
    {
        putin_3();//缺少参数
    }
}


void Widget::on_btn_page_2_2_clicked()
{
    page_now--;
    delete_3();
    for(int i=0;i<9;i++)
    {
        putin_3();//缺少参数
    }
}


void Widget::on_btn_page_3_2_clicked()
{
    page_now++;
    delete_3();
    for(int i=0;i<9;i++)
    {
        putin_3();//缺少参数
    }
}


void Widget::on_btn_page_4_2_clicked()
{
    page_now=page_max;
    delete_3();
    for(int i=0;i<9;i++)
    {
        putin_3();//缺少参数
    }
}


void Widget::on_btn_page_right_2_clicked()
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


void Widget::on_btn_page_left_4_clicked()
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


void Widget::on_btn_page_1_4_clicked()
{
    page_now=1;
    delete_3();
    for(int i=0;i<9;i++)
    {
        putin_3();//缺少参数
    }
}


void Widget::on_btn_page_2_4_clicked()
{
    page_now--;
    delete_3();
    for(int i=0;i<9;i++)
    {
        putin_3();//缺少参数
    }
}


void Widget::on_btn_page_3_4_clicked()
{
    page_now++;
    delete_3();
    for(int i=0;i<9;i++)
    {
        putin_3();//缺少参数
    }
}


void Widget::on_btn_page_4_4_clicked()
{
    page_now=page_max;
    delete_3();
    for(int i=0;i<9;i++)
    {
        putin_3();//缺少参数
    }
}


void Widget::on_btn_page_right_4_clicked()
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


void Widget::on_btn_confirm_3_clicked()
{

}


void Widget::on_pushButton_3_clicked()
{

}


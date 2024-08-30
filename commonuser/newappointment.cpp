#include "newappointment.h"
#include "ui_newappointment.h"
#include <QDate>
#include "apikey.h"
#include "netloader.h"
#include "netclient.h"


QVector<QString> user_id_na;
QVector<QString> patient_id_na ,patient_name_na ;
int all_num_na=0;


newAppointment::newAppointment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newAppointment)
{
    ui->setupUi(this);

    NetClient &client = NetClient::getInstance();
    connect(&client, &NetClient::received_json, this, &newAppointment::handleJsonReceived);
    search_101();

}

newAppointment::~newAppointment()
{
    delete ui;
}

void newAppointment::handleJsonReceived(const QJsonObject &mainsource)
{
//    qDebug()<<"888" << mainsource;
    int n=0;
    if(mainsource.size()>0)//如果source为空直接结束
    {
    QJsonArray array=mainsource.value("array").toArray();
//    int n=0;
    for(auto item:array){
        QJsonObject source = item.toObject();
        if(source.contains("user_id_na"))
            user_id_na.push_back(source.value("user_id_na").toString());
        else user_id_na.clear();

        if(source.contains("patient_id_na"))
            patient_id_na.push_back(source.value("patient_id_na").toString());
        else patient_id_na.clear();

        if(source.contains("patient_name_na"))
            patient_name_na.push_back(source.value("patient_name_na").toString());
        else patient_name_na.clear();
        n++;
    }


    }
    all_num_na=n;
    qDebug()<<"12345678987654323456543345654345654345445654545454545454";
    ui->combo_user->clear();
    for(int i=0;i<all_num_na;i++)
    {
        putin_101();
    }

}

void newAppointment::on_Btn_cancel_clicked()
{
    close();
}

void newAppointment::putin_101()
{
    for(int i=0;i<all_num_na;i++)
    {
        ui->combo_user->addItem( patient_name_na [i] );
    }

}

//填入患者
void newAppointment::search_101()
{
    QString sql= R"(
    SELECT
        patient.name AS patient_name_na,
        patient.id AS patient_name_na
    FROM
        patient , user
    WHERE
        user.id = patient.user_id AND
        user.id = ')" + USER_ID + R"(';
    )";
    NetClient &client = NetClient::getInstance();
    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );

}



void newAppointment::on_Btn_yes_clicked()
{

    //从ui中获取数据
    //通过 医生 科室 医生性别 日期 时间 就诊人 添加： 到appointment
    if(ui->combo_user->currentText()=="")
    {
        QMessageBox::information(this, QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("未选择就诊人！"));
        return;
    }
    QString sql="    INSERT INTO appointment (user_id,patient_id,doctor_id,date,time) VALUES ( '"+ USER_ID +"','"+ patient_id_na[ui->combo_user->currentIndex()] +"','"+ doctor_id +"','"+ ui->label_date->text() +"','"+ ui->combo_time->currentText() +"'  );";

    NetClient &client = NetClient::getInstance();
    //将数据发送到数据库
    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );

    close();
}
void newAppointment::set_name(const QString &text)
{
    ui->label_doc_name->setText(text);

}
void newAppointment::set_gender(const QString &text)
{
    ui->label_doc_gender->setText(text);

}
void newAppointment::set_office(const QString &text)
{
    ui->label_doc_apartment->setText(text);

}
void newAppointment::set_date(const QString &text)
{
    ui->label_date->setText(text);
}

void newAppointment::set_patient(const QString &text)
{
    ui->combo_user->addItem(text);

}

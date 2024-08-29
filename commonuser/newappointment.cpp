#include "newappointment.h"
#include "ui_newappointment.h"
#include <QDate>
#include "apikey.h"
#include "netloader.h"
#include "netclient.h"

newAppointment::newAppointment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newAppointment)
{
    ui->setupUi(this);

}

newAppointment::~newAppointment()
{
    delete ui;
}

void newAppointment::on_Btn_cancel_clicked()
{
    close();
}

void newAppointment::on_Btn_yes_clicked()
{

    // QString apikey="";
    // NetClient client ;

    //从ui中获取数据
    //通过 医生 科室 医生性别 日期 时间 就诊人 添加： 到appointment
    QString sql="    INSERT INTO appointment (patient_id,doctor_id,date,time) VALUES ( '"+ USER_ID +"','"+ doctor_id +"','"+ ui->label_date->text() +"','"+ ui->combo_time->currentText() +"'  ));";

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
void newAppointment::on_Btn_add_user_clicked()
{
    //添加就诊人

}


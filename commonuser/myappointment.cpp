#include "myappointment.h"
#include "ui_myappointment.h"
#include <QMessageBox>
#include "apikey.h"
#include"netclient.h"
#include "netloader.h"

myAppointment::myAppointment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myAppointment)
{
    ui->setupUi(this);
}

myAppointment::~myAppointment()
{
    delete ui;
}

void myAppointment::set_label_user_name(const QString &text)
{
    ui->label_user->setText(text);
}
void myAppointment::set_label_date(const QString &text)
{
    ui->label_date->setText(text);
}
void myAppointment::set_label_time(const QString &text)
{
    ui->label_time->setText(text);
}
void myAppointment::set_label_doc_name(const QString &text)
{
    ui->label_docname->setText(text);
}
void myAppointment::set_label_apartment(const QString &text)
{
    ui->label_depart->setText(text);
}
void myAppointment::set_label_id(const QString &text)
{
    ui->label_id->setText(text);
}

void myAppointment::on_btn_cancel_clicked()
{
    QMessageBox::StandardButton box;
    box = QMessageBox::question(this, "提示", "确实要删除吗?", QMessageBox::Yes|QMessageBox::No);
    if(box==QMessageBox::No)
       return;
    else
    {
        QString sql = R"(

            DELETE appointment
            FROM appointment
            JOIN doctor ON appointment.doctor_id = doctor.id
            JOIN patient ON appointment.patient_id =patient.id
            WHERE doctor.name= ')" + ui->label_docname->text() + R"(' AND
            WHERE appointment.date = ')" + ui->label_date->text() + R"(' AND
            WHERE patient.user_id= ')" + USER_ID + R"(';
        )";
        NetClient &client = NetClient::getInstance();
        NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );

    }

}


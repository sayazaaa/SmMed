#include "myappointment.h"
#include "ui_myappointment.h"

myAppointment::myAppointment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myAppointment)
{
    ui->setupUi(this);
    ui->btn_cancel->hide();
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

#include "myappointment.h"
#include "ui_myappointment.h"

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

void myAppointment:: set_label_user_name(const QString &text)
{
    ui->label_user->setText(text);
}
void myAppointment::set_label_user_gender(const QString &text)
{
    ui->label_gender->setText(text);
}
void myAppointment::set_label_user_age(const QString &text)
{
    ui->label_age->setText(text);
}
void myAppointment::set_label_time(const QString &text)
{
    ui->label_time->setText(text);
}

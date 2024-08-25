#include "newappointment.h"
#include "ui_newappointment.h"
#include <QDate>

newAppointment::newAppointment(QWidget *parent,const QString &name,const QString &gender,const QString &apartment,const QDate &date) :
    QWidget(parent),
    ui(new Ui::newAppointment)
{
    ui->setupUi(this);

    ui->label_doc_name->setText(name);
    ui->label_doc_gender->setText(gender);
    ui->label_doc_apartment->setText(apartment);
    ui->label_date->setText(date.toString());
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
    //从ui中获取数据

    //将数据发送到数据库
    close();
}


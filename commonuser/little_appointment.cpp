#include "little_appointment.h"
#include "ui_little_appointment.h"
#include "newappointment.h"
#include "netloader.h"
#include "netclient.h"
#include "widget.h"

//QString apikey="";
//NetClient client;

little_appointment::little_appointment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::little_appointment)
{
    ui->setupUi(this);

}

little_appointment::~little_appointment()
{
    delete ui;
}

void little_appointment::set_label_doc_name(const QString &text)
{
    ui->label_doc_name->setText(text);

}

void little_appointment::set_label_gender(const QString &text)
{
    ui->label_gender->setText(text);
}

void little_appointment::set_label_apartment(const QString &text)
{
    ui->label_apartment->setText(text);
}

void little_appointment::set_label_describe(const QString &text)
{
    ui->label_describe->setText(text);
}

void little_appointment::on_btn_yes_clicked()
{
    newAppointment *nA=new newAppointment();
    nA->set_name(ui->label_doc_name->text());
    nA->set_gender(ui->label_gender->text());
    nA->set_office(ui->label_apartment->text());
    nA->set_date(adate_now);
    nA->user_id = user_id;


//    将就诊人姓名填入nA的combo
    for(int i=0;patient_name+i!=nullptr;i++)
    {
        nA->set_patient(*(patient_name+i));
    }


    nA->show();
}


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


void little_appointment::set_apartment(const QString &text)
{
    ui->label_apartment_text->setText(text);
}

void little_appointment::set_name(const QString &text)
{
    ui->label_doc_name_text->setText(text);
}

void little_appointment::set_gender(const QString &text)
{
    ui->label_gender_text->setText(text);
}

void little_appointment::set_btn_yes(const QString &text)
{
    ui->btn_yes->setText(text);
}

void little_appointment::btn_more_hide()
{
//    ui->btn_more->hide();
}

void little_appointment::set_state()
{
    state=1;
}


void little_appointment::on_btn_yes_clicked()
{
    if(!state){
        newAppointment *nA=new newAppointment();
        nA->set_name(ui->label_doc_name->text());
        nA->set_gender(ui->label_gender->text());
        nA->set_office(ui->label_apartment->text());
        nA->set_date(adate_now);
        nA->doctor_id = doctor_id;


    //    将就诊人姓名填入nA的combo
        for(int i=0;i<patient_name.length();i++)
        {
            nA->set_patient(patient_name[i]);
        }


        nA->show();
    }else{
        patient_editor * n = new patient_editor();
        n->show();
    }



}


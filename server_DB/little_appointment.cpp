#include "little_appointment.h"
#include "ui_little_appointment.h"
#include "newappointment.h"

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

//    ui->label_doc_name->setScaledContents(true);
//    ui->label_doc_name_text->setScaledContents(true);

}

void little_appointment::set_label_gender(const QString &text)
{
    ui->label_gender->setText(text);

//    ui->label_gender->setScaledContents(true);
//    ui->label_gender_text->setScaledContents(true);
}

void little_appointment::set_label_apartment(const QString &text)
{
    ui->label_apartment->setText(text);

//    ui->label_apartment->setScaledContents(true);
//    ui->label_apartment_text->setScaledContents(true);
}
void little_appointment::set_apartment(const QString &text)
{
    ui->label_apartment_text->setText(text);
}
void little_appointment::set_gender(const QString &text)
{
    ui->label_gender_text->setText(text);
}
void little_appointment::set_name(const QString &text)
{
     ui->label_doc_name_text->setText(text);
}

void little_appointment::on_btn_yes_clicked()
{
    newAppointment *nA=new newAppointment;

    nA->show();
}


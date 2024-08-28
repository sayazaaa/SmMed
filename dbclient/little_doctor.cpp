#include "little_doctor.h"
#include "ui_little_doctor.h"

little_doctor::little_doctor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::little_doctor)
{
    ui->setupUi(this);
    connect(this,SIGNAL(sendMessage()),&w,SLOT(getMessage()));
}

little_doctor::~little_doctor()
{
    delete ui;
}

void little_doctor::set_label_id(const QString &text)
{
    ui->label_id->setText(text);
}
void little_doctor::set_label_password(const QString &text)
{
    ui->label_password->setText(text);
}
void little_doctor::set_label_salt(const QString &text)
{
    ui->label_salt->setText(text);
}

void little_doctor::set_label_name(const QString &text)
{
    ui->label_name->setText(text);
}
void little_doctor::set_label_gender(const QString &text)
{
    ui->label_gender->setText(text);
}
void little_doctor::set_label_apartment(const QString &text)
{
    ui->label_depart->setText(text);
}
void little_doctor::set_label_introduce(const QString &text)
{
    ui->label_introduce->setText(text);
}





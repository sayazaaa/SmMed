#include "little_doctor.h"
#include "ui_little_doctor.h"

little_doctor::little_doctor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::little_doctor)
{
    ui->setupUi(this);
}

little_doctor::~little_doctor()
{
    delete ui;
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
void little_doctor::set_btn_hide()
{
    ui->btn_ask->hide();
}
void little_doctor:: set_btn_unhide()
{
    ui->btn_ask->show();
}
void little_doctor::set_btn_text(const QString &text)
{
    ui->btn_ask->setText(text);
}

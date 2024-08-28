#include "little_user.h"
#include "ui_little_user.h"

little_user::little_user(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::little_user)
{
    ui->setupUi(this);
    connect(this,SIGNAL(sendMessage()),&w,SLOT(getMessage()));
}

little_user::~little_user()
{
    delete ui;
}


void little_user::set_label_id(const QString &text)
{
    ui->label_id->setText(text);
}
void little_user::set_label_password(const QString &text)
{
    ui->label_password->setText(text);
}
void little_user::set_label_salt(const QString &text)
{
    ui->label_salt->setText(text);
}

void little_user::set_label_name(const QString &text)
{
    ui->label_name->setText(text);
}
void little_user::set_label_gender(const QString &text)
{
    ui->label_gender->setText(text);
}
void little_user::set_label_age(const QString &text)
{
    ui->label_age->setText(text);
}
void little_user::set_label_phone(const QString &text)
{
    ui->phone->setText(text);
}
void little_user::set_label_address(const QString &text)
{
    ui->label_address->setText(text);
}



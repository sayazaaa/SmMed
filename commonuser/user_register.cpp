#include "user_register.h"
#include "ui_user_register.h"

user_register::user_register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user_register)
{
    ui->setupUi(this);
}

user_register::~user_register()
{
    delete ui;
}

void user_register::on_close_clicked()
{
    this->close();
}


void user_register::on_register_confirm_clicked()
{

}


#include "login.h"
#include "ui_login.h"
#include<QMessageBox>
int doctor_check=0;
login::login(QWidget *parent) :
    QDialog(parent),

    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}


void login::on_pushButton_clicked()
{
    if(ui->username->text() == "admin" && ui->password->text() == "114514"){
        this->close();
        Widget *w=new Widget;
        w->show();
    }else{
        QMessageBox::warning(this,tr("登录失败"),tr("账号或密码错误，请检查后重试"),QMessageBox::Ok);
        ui->password->clear();
        ui->username->setFocus();//如果登录失败就标红账号并清空密码要求重试
    }
}




void login::on_password_textEdited(const QString &arg1)
{
        ui->password->setEchoMode(QLineEdit::Password);
}



void login::on_checkBox_stateChanged(int arg1)
{
    doctor_check=1-doctor_check;
}


void login::on_pushButton_2_clicked()
{
    information *me=new information;
    me->show();
}


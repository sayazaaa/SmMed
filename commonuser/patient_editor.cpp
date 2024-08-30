#include "patient_editor.h"
#include "ui_patient_editor.h"
#include"netloader.h"
#include"netclient.h"
#include"apikey.h"


patient_editor::patient_editor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::patient_editor)
{
    ui->setupUi(this);
}

patient_editor::~patient_editor()
{
    delete ui;
}

void patient_editor::set_id(const QString &text){
    ui->id->setText(text);
}

void patient_editor::set_name(const QString &text)
{
    ui->name->setText(text);
}

void patient_editor::set_gender(const QString &text)
{
    ui->gender->setText(text);
}

void patient_editor::set_phone(const QString &text)
{
    ui->phone->setText(text);
}

void patient_editor::on_confirm_clicked()
{
//    insert into stuinfo(sid,sname,saddress,sclass,ssex) values (1,'码仙1','火星',1001,'男');
    QString sql= "INSERT INTO patient( user_id, id,name, gender , phone) values ( '"+ USER_ID +"','"+ui->id->text()+"','"+ ui->name->text() +"','"+ ui->gender->text() +"','"+ ui->phone->text() +"'); ";

    NetClient &client=NetClient::getInstance();
    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );


}


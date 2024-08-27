#include "nowdiagnose.h"
#include "ui_nowdiagnose.h"

nowDiagnose::nowDiagnose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nowDiagnose)
{
    ui->setupUi(this);

}

nowDiagnose::~nowDiagnose()
{
    delete ui;
}

void nowDiagnose:: set_label_user_name(const QString &text)
{
    ui->label_user_name->setText(text);
}
void nowDiagnose::set_label_user_gender(const QString &text)
{
    ui->label_gender->setText(text);
}
void nowDiagnose::set_label_age(const QString &text)
{
    ui->label_age->setText(text);
}
void nowDiagnose::set_label_id(const QString &text)
{
    ui->label_id->setText(text);
}
void nowDiagnose::on_btn_call_clicked()
{
    ui->btn_call->setText("已叫号");
    ui->btn_call->setDisabled(true);
}


void nowDiagnose::on_btn_start_clicked()
{
    ui->btn_start->setText("正在诊断...");
    ui->btn_start->setDisabled(true);
}


void nowDiagnose::on_btn_push_clicked()
{
    //提交


    ui->btn_push->setText("已提交");
    ui->btn_start->setText("已结束诊断");
    ui->btn_push->setDisabled(true);
}


#include "information.h"
#include "ui_information.h"
#include <QGraphicsDropShadowEffect>
#include<QMessageBox>

#include"netclient.h"
#include"netloader.h"
#include"apikey.h"

information::information(QWidget *parent) :
    FramelessWidget(parent),
    ui(new Ui::information)
{
    ui->setupUi(this);
    this->initUi();
}

information::~information()
{
    delete ui;
}

void information::set_name(const QString &text)
{
    ui->name->setText(text);
}
void information::set_gender(const QString &text)
{
    ui->gender->setCurrentText(text);
}
void information::set_office(const QString &text)
{
    ui->comboBox_office->setCurrentText(text);
}
void information::set_zc(const QString &text)
{
    ui->zc->setText(text);
}
void information::set_describe(const QString &text)
{
    ui->describe->setText(text);
}


void information::on_confirm_clicked()
{


    QString sql= "UPDATE doctor SET name = '"+ ui->name->text() +"',gender = '"+ ui->gender->currentText() +"',zc = '"+ ui->zc->text() +"',describe = '"+ ui->describe->toPlainText() +"',office_id='"+ ui->comboBox_office->currentIndex()+1 +"' WHERE id = '" + USER_ID + "'; ";

    NetClient &client=NetClient::getInstance();
    NetLoader::get_sql(sql , USER_ID ,0 , API_KEY , client );
}


void information::on_close_clicked()
{
    this->close();
}


void information::on_smallize_clicked()
{
    showMinimized();
}

void information::initUi()
{

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setColor(QColor("#444444"));
    shadow->setBlurRadius(16);
    ui->inf->setGraphicsEffect(shadow);
//    ui->inf_lay->setMargin(12);
    this->setAttribute(Qt::WA_Hover);

}

void information::on_close_btn_clicked()
{
    this->close();
}


void information::on_id_editingFinished()
{

}


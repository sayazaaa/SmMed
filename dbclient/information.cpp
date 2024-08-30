#include "information.h"
#include "ui_information.h"
#include <QGraphicsDropShadowEffect>
#include<QMessageBox>
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



void information::initUi()
{

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setColor(QColor("#444444"));
    shadow->setBlurRadius(16);
    ui->inf->setGraphicsEffect(shadow);
    this->setAttribute(Qt::WA_Hover);

}


void information::set_name(QString const& text)
{
    ui->name->setText(text);
}
void information::set_id(QString const& text)
{
    ui->id->setText(text);
}
void information::set_gender(const QString & text)
{
    ui->gender->setText(text);
}
void information::set_password(const QString & text){
    ui->password->setText(text);
}
void information::set_address(const QString & text)
{
    ui->address->setText(text);
}
void information::set_phone(const QString & text)
{
    ui->phone->setText(text);
}




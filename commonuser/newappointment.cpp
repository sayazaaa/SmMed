#include "newappointment.h"
#include "ui_newappointment.h"

newAppointment::newAppointment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newAppointment)
{
    ui->setupUi(this);
}

newAppointment::~newAppointment()
{
    delete ui;
}




void newAppointment::on_Btn_cancel_clicked()
{

}


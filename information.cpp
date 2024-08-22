#include "information.h"
#include "ui_information.h"
#include <QGraphicsDropShadowEffect>
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

void information::on_confirm_clicked()
{
    this->close();
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
    ui->inf_lay->setMargin(12);
    this->setAttribute(Qt::WA_Hover);

}

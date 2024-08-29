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

void information::on_confirm_clicked()
{
    QString idNumber=ui->id->text();
    bool ok;
    QRegExp validLastChar("[0-9]|X");
    //检查身份证号码长度
    if(idNumber.length() != 18)
    {
        QMessageBox::warning(this,tr("身份证非法"),tr("身份证长度非法，请检查后重试"),QMessageBox::Ok);
        ui->id->setFocus();
    }
    else if(!idNumber.left(17).toLongLong(&ok)){
        QMessageBox::warning(this,tr("身份证非法"),tr("身份证前十七位只能是数字，请检查后重试"),QMessageBox::Ok);
        ui->id->setFocus();
    }
    else if (!validLastChar.exactMatch(idNumber.right(1)))
    {
        QMessageBox::warning(this,tr("身份证非法"),tr("最后一位可以是字母X大写或者数字，请检查后重试"),QMessageBox::Ok);
        ui->id->setFocus();
    }
    else
    {
        //获取出生年月日
        int year = idNumber.mid(6, 4).toInt();
        int month = idNumber.mid(10, 2).toInt();
        int day = idNumber.mid(12, 2).toInt();
        // 获取当前日期
        QDateTime currentDate = QDateTime::currentDateTime();
        int currentYear = currentDate.date().year();
        int currentMonth = currentDate.date().month();
        int currentDay = currentDate.date().day();

        // 计算年龄
        int age = currentYear - year;

        // 如果还没过生日，减一岁
        if (currentMonth < month || (currentMonth == month && currentDay < day))
        {
            age--;
        }

        ui->age->setText(QString::number(age));
    }

    QString sql= "UPDATE doctor SET name = '"+ ui->name->text() +"',gender='"+ ui->gender->currentText() +"' WHERE id = '" + USER_ID + "'; ";

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
    ui->inf_lay->setMargin(12);
    this->setAttribute(Qt::WA_Hover);

}

void information::on_close_btn_clicked()
{
    this->close();
}


void information::on_id_editingFinished()
{

}


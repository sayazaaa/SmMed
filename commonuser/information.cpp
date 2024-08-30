#include "information.h"
#include "ui_information.h"
#include <QGraphicsDropShadowEffect>
#include<QMessageBox>
#include"netloader.h"
#include"apikey.h"
#include"netclient.h"
#include "patient_editor.h"

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
//    QString idNumber=ui->id->text();
//    bool ok;
//    QRegExp validLastChar("[0-9]|X");
//    QChar genderChar = idNumber[16]; // 第17位字符
//    int genderInt = genderChar.digitValue(); // 将 QChar 转换成 int
//    //检查身份证号码长度
//    if(idNumber.length() != 18)
//    {
//        QMessageBox::warning(this,tr("身份证非法"),tr("身份证长度非法，请检查后重试"),QMessageBox::Ok);
//        ui->id->setFocus();
//    }
//    else if(!idNumber.left(17).toLongLong(&ok)){
//        QMessageBox::warning(this,tr("身份证非法"),tr("身份证前十七位只能是数字，请检查后重试"),QMessageBox::Ok);
//        ui->id->setFocus();
//    }
//    else if (!validLastChar.exactMatch(idNumber.right(1)))
//    {
//        QMessageBox::warning(this,tr("身份证非法"),tr("最后一位可以是字母X大写或者数字，请检查后重试"),QMessageBox::Ok);
//        ui->id->setFocus();
//    }else if((genderInt%2 == 0 && ui->gender->currentText() == "男")||(genderInt%2 == 1 && ui->gender->currentText() == "女")){
//        QMessageBox::warning(this,tr("身份证非法"),tr("性别和身份证号无法对应，请检查后重试"),QMessageBox::Ok);
//        ui->id->setFocus();
//    }else{
//        //获取出生年月日
//        int year = idNumber.mid(6, 4).toInt();
//        int month = idNumber.mid(10, 2).toInt();
//        int day = idNumber.mid(12, 2).toInt();
//        // 获取当前日期
//        QDateTime currentDate = QDateTime::currentDateTime();
//        int currentYear = currentDate.date().year();
//        int currentMonth = currentDate.date().month();
//        int currentDay = currentDate.date().day();

//        // 计算年龄
//        int age = currentYear - year;

//        // 如果还没过生日，减一岁
//        if (currentMonth < month || (currentMonth == month && currentDay < day))
//        {
//            age--;
//        }
//        ui->age->setText(QString::number(age));


//    }


    QString sql= "UPDATE user SET name = '"+ ui->name->text() +"',gender='"+ ui->gender->currentText() +"',phone='"+ ui->phone->text() +"',address='"+ ui->address->text() +"',age='"+ ui->age->text() +"' WHERE id = '" + USER_ID + "'; ";

    NetClient &client=NetClient::getInstance();
    NetLoader::get_sql(sql , USER_ID , 1 , API_KEY , client );



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


void information::on_pushButton_clicked()
{
    patient_editor *pe = new patient_editor;
    pe->show();
}


void information::set_name(QString const& text)
{
    ui->name->setText(text);
}
void information::set_age(QString const& text)
{
    ui->age->setText(text);
}
void information::set_gender(const QString & text)
{
    ui->gender->setCurrentText(text);
}

void information::set_address(const QString & text)
{
    ui->address->setText(text);
}
void information::set_phone(const QString & text)
{
    ui->phone->setText(text);
}


#include "nowdiagnose.h"
#include "ui_nowdiagnose.h"
#include "netloader.h"
#include "netclient.h"

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



void nowDiagnose::on_btn_push_1_clicked()
{
   
    // RichTextEdit *textEdit = ui->thewidget;
    // QString path = QDir::cleanPath(QApplication::applicationDirPath() + QDir::separator() + "file" + QDir::separator())
    // QFile file(path + "/report.txt");
    // if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    // {
    //     qDebug() << "Could not open file for writing";
    //     return;
    // }
    // QTextStream out(&file);
    // out << "dsadasdsa";
    // file.close();TODO




    // // QString apikey;
    // NetClient &client = NetClient::getInstance();
    // //通过 日期 患者姓名 医生id 富文本编辑器 增加：诊断报告
    // QString sql="INSERT INTO inspreport (doctor_id , patient_id , date)  VALUES( '"+ USER_ID +"','"+ *patient_id +"','"+ date +" )";
    // NetLoader::get_sql(sql , USER_ID , 0 , API_KEY , client );
    ui->btn_push_1->setText("已提交诊断报告");
    ui->btn_push_1->setDisabled(true);
}


void nowDiagnose::on_btn_push_2_clicked()
{
    QString apikey;
    NetClient client;
    //通过 日期 患者姓名 医生id 富文本编辑器 增加：处方
    QString sql="INSERT INTO prescription (doctor_id , patient_id , date)  VALUES( '"+ USER_ID +"','"+ *patient_id +"','"+ date +" )";
    NetLoader::get_sql(sql , USER_ID, 0 , API_KEY , client );
    ui->btn_push_1->setText("已提交处方");
    ui->btn_push_1->setDisabled(true);
}


void nowDiagnose::on_btn_push_3_clicked()
{
    QString apikey;
    NetClient client;
    //通过 日期 患者姓名 医生id 富文本编辑器 增加：医嘱
    QString sql="INSERT INTO diagnosis (doctor_id , patient_id , date)  VALUES( '"+ USER_ID +"','"+ *patient_id +"','"+ date +" )";
    NetLoader::get_sql(sql , USER_ID , 0 , API_KEY , client );
    ui->btn_push_1->setText("已提交医嘱");
    ui->btn_push_1->setDisabled(true);
}


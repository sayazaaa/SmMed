#include "little_doctor.h"
#include "ui_little_doctor.h"

little_doctor::little_doctor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::little_doctor)
{
    ui->setupUi(this);
    connect(this,SIGNAL(sendMessage()),&w,SLOT(getMessage()));
}

little_doctor::~little_doctor()
{
    delete ui;
}

void little_doctor::set_label_name(const QString &text)
{
    ui->label_name->setText(text);
}
void little_doctor::set_label_gender(const QString &text)
{
    ui->label_gender->setText(text);
}
void little_doctor::set_label_apartment(const QString &text)
{
    ui->label_depart->setText(text);
}
void little_doctor::set_label_introduce(const QString &text)
{
    ui->label_introduce->setText(text);
}
void little_doctor::set_btn_hide()
{
    ui->btn_ask->hide();
}
void little_doctor:: set_btn_unhide()
{
    ui->btn_ask->show();
}
void little_doctor::set_btn_text(const QString &text)
{
    ui->btn_ask->setText(text);
}

void little_doctor::on_btn_ask_clicked()
{
    //添加到sqlite：
//    "insert into chat_messages(sender_id,receiver_id,message,timestamp) value('"+ USER_ID+"', '"+张三+"','"+1+"','"+3+"');";


    QString sql = "insert into chat_history(sender_id,receiver_id) value('"+ USER_ID+"', '"+*doc_id+"');";

    DatabaseManager &dbm = DatabaseManager::getInstance();
    QSqlQuery query(dbm.getDatabase());
    query.exec(sql);

    //此处为需要发送信号的位置（函数内部）
    emit sendMessage( );

}


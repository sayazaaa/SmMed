#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QDialog(parent),

    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}


void login::on_pushButton_clicked()
{
//    if(ui->username->text() == "admin" && ui->password->text() == "114514"){
//        this->close();
//        Widget *w=new Widget;
//        w->show();
//    }else{
//        QMessageBox::warning(this,tr("登录失败"),tr("账号或密码错误，请检查后重试"),QMessageBox::Ok);
//        ui->password->clear();
//        ui->username->setFocus();//如果登录失败就标红账号并清空密码要求重试
// 

    QString username = ui->username->text();
    QString password = ui->password->text();
    if(username == "" || password == "") {
        QMessageBox::warning(this, "Warning", "用户名或密码不能为空");
        return;
    }
    if(username.length() < 4) {
        QMessageBox::warning(this, "Warning", "用户名长度不能小于4");
        return;
    }
    if(password.length() < 4) {
        QMessageBox::warning(this, "Warning", "密码长度不能小于4");
        return;
    }
    if(username.length() > 24) {
        QMessageBox::warning(this, "Warning", "用户名长度不能超过24");
        return;
    }
    if(password.length() > 24) {
        QMessageBox::warning(this, "Warning", "密码长度不能超过24");
        return;
    }
    NetClient &client = NetClient::getInstance();
    std::unique_ptr<Botan::HashFunction> hashFunction(Botan::HashFunction::create("SHA-256"));
    hashFunction->update(password.toStdString());
    Botan::secure_vector<uint8_t> hashValue = hashFunction->final();
    std::string hexHash = Botan::hex_encode(hashValue);
    disconnect(&NetClient::getInstance(), &NetClient::received_json, this, &login::handle_reply_json);
    connect(&NetClient::getInstance(), &NetClient::received_json, this, &login::handle_reply_json);
    NetLoader::post_login(username, QString(hexHash.c_str()),1, client);

}

void login::on_password_textEdited(const QString &arg1)
{
        ui->password->setEchoMode(QLineEdit::Password);
}

void login::on_pushButton_2_clicked()
{
    user_register *me=new user_register;
    me->show();
}

void login::handle_reply_json(const QJsonObject &json)
{
    qDebug() << "handle reply json apikey:" << json["apikey"].toString();
    if(json["apikey"].toString() != "") {
        API_KEY = json["apikey"].toString();
    }

    disconnect(&NetClient::getInstance(), &NetClient::received_json, this, &login::handle_reply_json);
    this->close();
    Widget *w=new Widget;
    w->show();
}


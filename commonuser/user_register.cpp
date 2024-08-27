#include "user_register.h"
#include "ui_user_register.h"

#include <QDebug>

user_register::user_register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user_register)
{
    ui->setupUi(this);
    setWindowTitle("注册");
    ui->password->setEchoMode(QLineEdit::Password);
    ui->password_confirm->setEchoMode(QLineEdit::Password);
    
}

user_register::~user_register()
{
    delete ui;
}

void user_register::on_close_clicked()
{
    this->close();
}


void user_register::on_register_confirm_clicked()
{
    QString username = ui->username->text();
    QString password = ui->password->text();
    QString password_confirm = ui->password_confirm->text();
    if(username == "" || password == "" || password_confirm == "") {
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
    if(password != password_confirm) {
        QMessageBox::warning(this, "Warning", "两次密码不一致");
        return;
    }
    send_register_request(username, password);

}

void user_register::send_register_request(const QString &username, const QString &password) {
    NetClient &client = NetClient::getInstance();
    HttpServer::User user;
    qDebug() << "username:" << username;
    qDebug() << "password:" << password;
    user.setId(username);
    std::unique_ptr<Botan::HashFunction> hashFunction(Botan::HashFunction::create("SHA-256"));
    hashFunction->update(password.toStdString());
    Botan::secure_vector<uint8_t> hashValue = hashFunction->final();
    std::string hexHash = Botan::hex_encode(hashValue);
    user.setPassword(QString(hexHash.c_str()));
    qDebug() << user.getId() << "  " << user.getPassword();
    disconnect(&client, &NetClient::received_json, this, &user_register::handle_reply_json);
    connect(&client, &NetClient::received_json, this, &user_register::handle_reply_json);
    NetLoader::post_create_user(user, client);
}

void user_register::handle_reply_json(const QJsonObject& json) {
    qDebug() << "handle reply json apikey:" << json["apikey"].toString();
    if (json.isEmpty())
    {
        send_register_request(ui->username->text(), ui->password->text());
    }
    
    if(json["apikey"].toString() != "") {
        API_KEY = json["apikey"].toString();
        USER_ID = ui->username->text();
    }
    disconnect(&NetClient::getInstance(), &NetClient::received_json, this, &user_register::handle_reply_json);
    this->close();
}


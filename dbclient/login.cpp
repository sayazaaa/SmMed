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

//    this->close();
//    Widget *w=new Widget;
//    w->show();

// 



    QString username = ui->username->text();
    QString password = ui->password->text();
    NetClient &client = NetClient::getInstance();
    std::unique_ptr<Botan::HashFunction> hashFunction(Botan::HashFunction::create("SHA-256"));
    hashFunction->update(password.toStdString());
    Botan::secure_vector<uint8_t> hashValue = hashFunction->final();
    std::string hexHash = Botan::hex_encode(hashValue);
    disconnect(&NetClient::getInstance(), &NetClient::received_json, this, &login::handle_reply_json);
    connect(&NetClient::getInstance(), &NetClient::received_json, this, &login::handle_reply_json);
    QString apikey = "429080af-532a-48a0-868b-42159fd4319e";
    NetLoader::post_login(username,"unusued",apikey,client);

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
        USER_ID = ui->username->text();
        NetClient::getInstance().send_socket_apikey_request(API_KEY);
    }

    disconnect(&NetClient::getInstance(), &NetClient::received_json, this, &login::handle_reply_json);
    this->close();
    Widget *w=new Widget;
    w->show();
}


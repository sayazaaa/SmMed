#include "login.h"
#include "ui_login.h"
int doctor_check = 0;
login::login(QWidget* parent) :
    QDialog(parent),

    ui(new Ui::login) {
    ui->setupUi(this);
}

login::~login() {
    delete ui;
}


void login::on_pushButton_clicked() {
    QString username = ui->username->text();
    QString password = ui->password->text();
    if (username == "" || password == "") {
        QMessageBox::warning(this, "Warning", "用户名或密码不能为空");
        return;
    }
    if (username.length() < 4) {
        QMessageBox::warning(this, "Warning", "用户名长度不能小于4");
        return;
    }
    if (password.length() < 4) {
        QMessageBox::warning(this, "Warning", "密码长度不能小于4");
        return;
    }
    if (username.length() > 24) {
        QMessageBox::warning(this, "Warning", "用户名长度不能超过24");
        return;
    }
    if (password.length() > 24) {
        QMessageBox::warning(this, "Warning", "密码长度不能超过24");
        return;
    }
    NetClient& client = NetClient::getInstance();
    std::unique_ptr<Botan::HashFunction> hashFunction(Botan::HashFunction::create("SHA-256"));
    hashFunction->update(password.toStdString());
    Botan::secure_vector<uint8_t> hashValue = hashFunction->final();
    std::string hexHash = Botan::hex_encode(hashValue);
    disconnect(&NetClient::getInstance(), &NetClient::received_json, this, &login::handle_reply_json);
    connect(&NetClient::getInstance(), &NetClient::received_json, this, &login::handle_reply_json);
    NetLoader::post_login(username, QString(hexHash.c_str()), 0, client);
}

void login::on_password_textEdited(const QString& arg1) {
    ui->password->setEchoMode(QLineEdit::Password);
}

void login::on_pushButton_2_clicked() {
    user_register* me = new user_register;
    me->show();
}

void login::handle_reply_json(const QJsonObject& json) {
    qDebug() << "handle reply json apikey:" << json["apikey"].toString();

    if (json["apikey"].toString() != "") {
        API_KEY = json["apikey"].toString();
        USER_ID = ui->username->text();
        NetClient::getInstance().send_socket_apikey_request(API_KEY);

        // //test TODO
        // QString path = QDir::cleanPath(QApplication::applicationDirPath() + QDir::separator());
        // QFile f(path + "/report.txt");
        // if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) {
        //     qDebug() << "Could not open file for writing: " << f.fileName() << ", error: " << f.errorString() << "path" << path;            return;
        // }
        // QTextStream out(&f);
        // out << "dsadasdsa";
        // f.close();
        // if (f.waitForBytesWritten(500)) {
        //     qDebug() << "write success";
        //     NetLoader::post_file(path + "/report.txt", "report.txt", "saya", "222222200408082222", "diagnose", API_KEY, "1", NetClient::getInstance());
        // }
    }

    disconnect(&NetClient::getInstance(), &NetClient::received_json, this, &login::handle_reply_json);
    this->close();
    Widget* w = new Widget;
    w->show();
}


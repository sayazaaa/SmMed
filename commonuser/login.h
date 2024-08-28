#ifndef LOGIN_H
#define LOGIN_H
#include "widget.h"
#include <QDialog>
#include"information.h"
#include "user_register.h"
#include<QMessageBox>
#include "apikey.h"

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:

    void on_pushButton_clicked();


    void on_password_textEdited(const QString &arg1);


    void on_pushButton_2_clicked();

    void handle_reply_json(const QJsonObject& json);

private:
    Ui::login *ui;

};

#endif // LOGIN_H

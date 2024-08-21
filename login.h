#ifndef LOGIN_H
#define LOGIN_H
#include "widget.h"
#include <QDialog>


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


    void on_checkBox_stateChanged(int arg1);

private:
    Ui::login *ui;
};

#endif // LOGIN_H

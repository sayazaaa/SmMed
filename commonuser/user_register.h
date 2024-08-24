#ifndef USER_REGISTER_H
#define USER_REGISTER_H

#include <QDialog>

#include "sharedglobal.h"
#include "netclient.h"
#include "netloader.h"

namespace Ui {
class user_register;
}

class user_register : public QDialog
{
    Q_OBJECT

public:
    explicit user_register(QWidget *parent = nullptr);
    ~user_register();

private slots:
    void on_close_clicked();

    void on_register_confirm_clicked();

private:
    Ui::user_register *ui;
};

#endif // USER_REGISTER_H

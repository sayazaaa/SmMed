#ifndef USER_REGISTER_H
#define USER_REGISTER_H

#include <QDialog>
#include <QMessageBox>
#include <botan-2/botan/hash.h>
#include <botan-2/botan/hex.h>

#include "sharedglobal.h"
#include "netclient.h"
#include "netloader.h"
#include "apikey.h"

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

    void handle_reply_json(const QJsonObject& json);

private:
    Ui::user_register *ui;
    void send_register_request(const QString &username, const QString &password);
    

};

#endif // USER_REGISTER_H

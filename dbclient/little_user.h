#ifndef LITTLE_USER_H
#define LITTLE_USER_H

#include <QWidget>
#include "widget.h"
#include "DBManager.h"
#include <QtSql>
#include "apikey.h"

namespace Ui {
class little_user;
}

class little_user : public QWidget
{
    Q_OBJECT

public:

    QString *doc_id;
    Widget w;
    void set_label_id(const QString &text);
    void set_label_password(const QString &text);
    void set_label_salt(const QString &text);
//    void set_label_introduce(const QString &text);
    void set_label_name(const QString &text);
    void set_label_gender(const QString &text);
    void set_label_age(const QString &text);
    void set_label_phone(const QString &text);
    void set_label_address(const QString &text);

    explicit little_user(QWidget *parent = nullptr);
    ~little_user();

private:
    Ui::little_user *ui;
};

#endif // LITTLE_USER_H

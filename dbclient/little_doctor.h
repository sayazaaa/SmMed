#ifndef LITTLE_DOCTOR_H
#define LITTLE_DOCTOR_H

#include <QWidget>
#include "widget.h"
#include "DBManager.h"
#include <QtSql>
#include "apikey.h"

namespace Ui {
class little_doctor;
}

class little_doctor : public QWidget
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
    void set_label_apartment(const QString &text);
    void set_label_introduce(const QString &text);

    explicit little_doctor(QWidget *parent = nullptr);
    ~little_doctor();

signals:
    void sendMessage( );


private:
    Ui::little_doctor *ui;
};

#endif // LITTLE_DOCTOR_H

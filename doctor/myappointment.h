#ifndef MYAPPOINTMENT_H
#define MYAPPOINTMENT_H

#include <QWidget>

namespace Ui {
class myAppointment;
}

class myAppointment : public QWidget
{
    Q_OBJECT

public:
    void set_label_user_name(const QString &text);
    void set_label_user_gender(const QString &text);
    void set_label_user_age(const QString &text);
//    void set_label_date(const QString &text);
    void set_label_time(const QString &text);
//    void set_label_doc_name(const QString &text);
//    void set_label_apartment(const QString &text);
//    void set_label_id(const QString &text);
    explicit myAppointment(QWidget *parent = nullptr);
    ~myAppointment();

private:
    Ui::myAppointment *ui;
};

#endif // MYAPPOINTMENT_H

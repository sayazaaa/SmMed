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
    void set_label_date(const QString &text);
    void set_label_time(const QString &text);
    void set_label_doc_name(const QString &text);
    void set_label_apartment(const QString &text);
    void set_label_id(const QString &text);
    explicit myAppointment(QWidget *parent = nullptr);
    ~myAppointment();

private slots:
    void on_btn_cancel_clicked();

private:
    Ui::myAppointment *ui;
};

#endif // MYAPPOINTMENT_H

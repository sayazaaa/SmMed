#ifndef LITTLE_APPOINTMENT_H
#define LITTLE_APPOINTMENT_H

#include <QWidget>

namespace Ui {
class little_appointment;
}

class little_appointment : public QWidget
{
    Q_OBJECT

public:
    QString *user_id = 0;
    QString *patient_name = 0;
    QString adate_now="";
    void set_label_doc_name(const QString &text);
    void set_label_gender(const QString &text);
    void set_label_apartment(const QString &text);
    void set_label_describe(const QString &text);
    explicit little_appointment(QWidget *parent = nullptr);
    ~little_appointment();

private slots:
    void on_btn_yes_clicked();

private:
    Ui::little_appointment *ui;
};

#endif // LITTLE_APPOINTMENT_H

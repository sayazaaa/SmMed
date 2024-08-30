#ifndef NEWAPPOINTMENT_H
#define NEWAPPOINTMENT_H

#include <QWidget>
#include <QDate>

namespace Ui {
class newAppointment;
}

class newAppointment : public QWidget
{
    Q_OBJECT

public:

    QString doctor_id;
    void set_name(const QString &text);
    void set_gender(const QString &text);
    void set_office(const QString &text);
    void set_date(const QString &text);
    void set_patient(const QString &text);

    explicit newAppointment(QWidget *parent = nullptr);
    ~newAppointment();

private slots:

    void on_Btn_cancel_clicked();

    void on_Btn_yes_clicked();

private:
    Ui::newAppointment *ui;
};

#endif // NEWAPPOINTMENT_H

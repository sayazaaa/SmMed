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

    explicit newAppointment(QWidget *parent = nullptr,
                            const QString &name="",
                            const QString &gender="",
                            const QString &apartment="",
                            const QDate &date=QDate::fromString("20240101", "yyyyMMdd"));
    ~newAppointment();

private slots:

    void on_Btn_cancel_clicked();

    void on_Btn_yes_clicked();

private:
    Ui::newAppointment *ui;
};

#endif // NEWAPPOINTMENT_H

#ifndef NEWAPPOINTMENT_H
#define NEWAPPOINTMENT_H

#include <QWidget>

namespace Ui {
class newAppointment;
}

class newAppointment : public QWidget
{
    Q_OBJECT

public:
    explicit newAppointment(QWidget *parent = nullptr);
    ~newAppointment();

private slots:

    void on_Btn_cancel_clicked();

private:
    Ui::newAppointment *ui;
};

#endif // NEWAPPOINTMENT_H

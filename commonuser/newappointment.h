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

    void putin_101();
    //填入患者
    void search_101();

//    void putin_102();
//    //填入患者
//    void search_102();

    QString doctor_id;
    void set_name(const QString &text);
    void set_gender(const QString &text);
    void set_office(const QString &text);
    void set_date(const QString &text);
    void set_patient(const QString &text);

    explicit newAppointment(QWidget *parent = nullptr);
    ~newAppointment();

public slots:
    void handleJsonReceived(const QJsonObject &mainsource);  // 槽函数


private slots:

    void on_Btn_cancel_clicked();

    void on_Btn_yes_clicked();

private:
    Ui::newAppointment *ui;
};

#endif // NEWAPPOINTMENT_H

#ifndef LITTLE_APPOINTMENT_H
#define LITTLE_APPOINTMENT_H

#include <QWidget>
#include "patient_editor.h"

namespace Ui {
class little_appointment;
}

class little_appointment : public QWidget
{
    Q_OBJECT

public:
    QString doctor_id ;
    QVector<QString> patient_name ;
    QString adate_now="";
    void set_label_doc_name(const QString &text);
    void set_label_gender(const QString &text);
    void set_label_apartment(const QString &text);
    void set_label_describe(const QString &text);
    void set_apartment(const QString &text);
    void set_name(const QString &text);
    void set_gender(const QString &text);
    void set_btn_yes(const QString &text);
    void btn_more_hide();
    void set_state();
    explicit little_appointment(QWidget *parent = nullptr);
    ~little_appointment();

private slots:
    void on_btn_yes_clicked();

private:
    Ui::little_appointment *ui;
    int state=0;
};

#endif // LITTLE_APPOINTMENT_H

#ifndef NOWDIAGNOSE_H
#define NOWDIAGNOSE_H

#include <QWidget>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDateTime>
#include <QApplication>
#include <QTextDocument>
#include <QTime>
#include <QTimer>

namespace Ui {
class nowDiagnose;
}

class nowDiagnose : public QWidget
{
    Q_OBJECT

public:
    QString *doctor_id;
    QString *patient_id;
    QString date;
    void set_label_user_name(const QString &text);
    void set_label_user_gender(const QString &text);
    void set_label_age(const QString &text);
    void set_label_id(const QString &text);
    void set_appointment_id(const QString &text);

    explicit nowDiagnose(QWidget *parent = nullptr);
    ~nowDiagnose();

private slots:
    void on_btn_call_clicked();

    void on_btn_start_clicked();

//    void on_btn_push_clicked();

    void on_btn_push_1_clicked();

    void on_btn_push_2_clicked();

    void on_btn_push_3_clicked();

private:
    Ui::nowDiagnose *ui;
    QString appointment_id;
};

#endif // NOWDIAGNOSE_H

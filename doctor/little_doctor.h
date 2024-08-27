#ifndef LITTLE_DOCTOR_H
#define LITTLE_DOCTOR_H

#include <QWidget>

namespace Ui {
class little_doctor;
}

class little_doctor : public QWidget
{
    Q_OBJECT

public:
    void set_label_name(const QString &text);
    void set_label_gender(const QString &text);
    void set_label_apartment(const QString &text);
    void set_label_introduce(const QString &text);
    void set_btn_hide();
    void set_btn_unhide();
    void set_btn_text(const QString &text);
    explicit little_doctor(QWidget *parent = nullptr);
    ~little_doctor();

private:
    Ui::little_doctor *ui;
};

#endif // LITTLE_DOCTOR_H

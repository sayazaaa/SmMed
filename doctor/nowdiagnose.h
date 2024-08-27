#ifndef NOWDIAGNOSE_H
#define NOWDIAGNOSE_H

#include <QWidget>

namespace Ui {
class nowDiagnose;
}

class nowDiagnose : public QWidget
{
    Q_OBJECT

public:

    void set_label_user_name(const QString &text);
    void set_label_user_gender(const QString &text);
    void set_label_age(const QString &text);
    void set_label_id(const QString &text);

    explicit nowDiagnose(QWidget *parent = nullptr);
    ~nowDiagnose();

private slots:
    void on_btn_call_clicked();

    void on_btn_start_clicked();

    void on_btn_push_clicked();

private:
    Ui::nowDiagnose *ui;
};

#endif // NOWDIAGNOSE_H

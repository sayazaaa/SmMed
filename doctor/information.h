#ifndef INFORMATION_H
#define INFORMATION_H

#include "framelesswidget.h"
#include <QDateTime>

namespace Ui {
class information;
}

class information : public FramelessWidget
{
    Q_OBJECT

public:

    void set_name(const QString &text);
    void set_gender(const QString &text);
    void set_office(const QString &text);
    void set_zc(const QString &text);
    void set_describe(const QString &text);




    explicit information(QWidget *parent = nullptr);
    ~information();

private slots:
    void on_confirm_clicked();

    void on_close_clicked();

    void on_smallize_clicked();

    void on_close_btn_clicked();

    void on_id_editingFinished();

private:
    Ui::information *ui;
    void initUi();          //Ui界面初始化函数
};

#endif // INFORMATION_H

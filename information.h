#ifndef INFORMATION_H
#define INFORMATION_H

#include "framelesswidget.h"

namespace Ui {
class information;
}

class information : public FramelessWidget
{
    Q_OBJECT

public:
    explicit information(QWidget *parent = nullptr);
    ~information();

private slots:
    void on_confirm_clicked();

    void on_close_clicked();

    void on_smallize_clicked();

private:
    Ui::information *ui;
    void initUi();          //Ui界面初始化函数
};

#endif // INFORMATION_H

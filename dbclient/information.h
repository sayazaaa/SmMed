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
    explicit information(QWidget *parent = nullptr);
    ~information();
    void set_name(const QString & text);
    void set_id(const QString & text);
    void set_gender(const QString & text);
    void set_password(const QString & text);
    void set_address(const QString & text);
    void set_phone(const QString & text);

private slots:

private:
    Ui::information *ui;
    void initUi();          //Ui界面初始化函数
};

#endif // INFORMATION_H

#ifndef LITTLE_ZHIHU_H
#define LITTLE_ZHIHU_H

#include <QWidget>
#include "detailzhihu.h"

namespace Ui {
class little_zhihu;
}

class little_zhihu : public QWidget
{
    Q_OBJECT

public:

    int allnum=0;
    int now=0;
    QString *huifutext;
    QString *huifutime;
    QString *doctorname;
    QString tiezi_id;
    void set_label_user_name(const QString &text);
    void set_label_user_context(const QString &text);
    void set_label_answernum(const  QString &text);

    explicit little_zhihu(QWidget *parent = nullptr);
    ~little_zhihu();

private slots:
    void on_btn_more_clicked();

private:
    Ui::little_zhihu *ui;
};

#endif // LITTLE_ZHIHU_H

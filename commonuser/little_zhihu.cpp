#include "little_zhihu.h"
#include "ui_little_zhihu.h"
#include "detailzhihu.h"

little_zhihu::little_zhihu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::little_zhihu)
{
    ui->setupUi(this);
}

little_zhihu::~little_zhihu()
{
    delete ui;
}

void little_zhihu:: set_label_user_name(const QString &text)
{
    ui->label_username->setText(text);
}
void little_zhihu::set_label_user_context(const QString &text)
{
    ui->label_context->setText(text);
}
void little_zhihu::set_label_answernum(const  QString &text)
{
    ui->label_answernum->setText(text);
}

void little_zhihu:: on_btn_more_clicked()
{
    detailZhihu *dZ = new detailZhihu(this,tiezi_id);
    dZ->setquestion(ui->label_context->text());
    dZ->tiez_id=tiezi_id;
//    dZ->search_901();
//    dZ->detailZhihu;
//    dZ->show();
    dZ->show();
}


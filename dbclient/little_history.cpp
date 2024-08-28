#include "little_history.h"
#include "ui_little_history.h"

little_history::little_history(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::little_history)
{
    ui->setupUi(this);


}

little_history::~little_history()
{
    delete ui;
}

void little_history::set_label_user_name(const QString &text)
{
    ui->label_user->setText(text);
}
void little_history::set_label_date(const QString &text)
{
    ui->label_date->setText(text);
}
void little_history::set_label_which(const QString &text)
{
    ui->label_which->setText(text);
}
void little_history::set_label_doc_name(const QString &text)
{
    ui->label_docname->setText(text);
}

void little_history::set_label_apartment(const QString &text)
{
    ui->label_depart->setText(text);
}

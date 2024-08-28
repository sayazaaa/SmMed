#include "patient_editor.h"
#include "ui_patient_editor.h"

patient_editor::patient_editor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::patient_editor)
{
    ui->setupUi(this);
}

patient_editor::~patient_editor()
{
    delete ui;
}

void patient_editor::set_age(int p){
    ui->age->setText(QString::number(p));
}

void patient_editor::set_name(const QString &text)
{
    ui->name->setText(text);
}

void patient_editor::set_gender(const QString &text)
{
    ui->gender->setText(text);
}

void patient_editor::set_phone(const QString &text)
{
    ui->phone->setText(text);
}

#include "TableToolbarPopup.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

TableToolBarPopup::TableToolBarPopup(QWidget *parent)
    : QWidget(parent), rowsEdit(new QLineEdit), columnsEdit(new QLineEdit),
      okButton(new QPushButton("确定")), cancelButton(new QPushButton("取消"))
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *rowsLayout = new QHBoxLayout;
    rowsLayout->addWidget(new QLabel("行数:"));
    rowsLayout->addWidget(rowsEdit);
    mainLayout->addLayout(rowsLayout);

    QHBoxLayout *columnsLayout = new QHBoxLayout;
    columnsLayout->addWidget(new QLabel("列数:"));
    columnsLayout->addWidget(columnsEdit);
    mainLayout->addLayout(columnsLayout);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(okButton);
    buttonsLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonsLayout);

    connect(okButton, &QPushButton::clicked, this, &TableToolBarPopup::accepted);
    connect(cancelButton, &QPushButton::clicked, this, &TableToolBarPopup::rejected);
}

int TableToolBarPopup::rows() const
{
    return rowsEdit->text().toInt();
}

int TableToolBarPopup::columns() const
{
    return columnsEdit->text().toInt();
}
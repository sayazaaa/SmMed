#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建 RichTextEdit
    textEdit = new RichTextEdit(this);
    setCentralWidget(textEdit);

}

MainWindow::~MainWindow()
{
    delete ui;
}



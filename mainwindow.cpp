#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkRequest>
#include <QUrl>
#include<QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onPushButtonClicked);
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onNetworkReply);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onPushButtonClicked()
{
    QString url = ui->lineEdit->text();
    QNetworkRequest request = QNetworkRequest(QUrl(url));
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute,true);
    qDebug() << "Sending request to:" << url;
    networkManager->get(request);
}

void MainWindow::onNetworkReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QString response = reply->readAll();
        ui->label->setText(response);
    } else {
        ui->label->setText("Error: " + reply->errorString());
    }
    reply->deleteLater();
}
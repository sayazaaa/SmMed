#ifndef HEALTHTEST_H
#define HEALTHTEST_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include<QMessageBox>

namespace Ui {
class HealthTest;
}

class HealthTest : public QWidget
{
    Q_OBJECT

public:
    explicit HealthTest(QWidget *parent = nullptr);
    ~HealthTest();

private slots:
    void on_pushButton_clicked();

private:
    Ui::HealthTest *ui;
};

#endif // HEALTHTEST_H

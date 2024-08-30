#ifndef CHART_CREATE_H
#define CHART_CREATE_H

#include <QWidget>
#include <QtCharts>
#include<QDateTime>


using namespace QtCharts;

namespace Ui {
class chart_create;
}

class chart_create : public QWidget
{
    Q_OBJECT

public:
    explicit chart_create(QWidget *parent = nullptr);
    ~chart_create();
    void set(int day, int* item_group);
    void create();

private:
    void createQSplineSeries();
    Ui::chart_create *ui;

    QChart* chart ;
    QLineSeries *series;
    int days;//时间跨度
    int* item;

};

#endif // CHART_CREATE_H

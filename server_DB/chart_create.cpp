#include "chart_create.h"
#include "ui_chart_create.h"
double test[7]={0,0,0,0,1,0,0};
chart_create::chart_create(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chart_create)
{
    ui->setupUi(this);
    this->set(7,test);
    QChart *chart = new QChart();
    QLineSeries *series = new QLineSeries();
    QDateTime curDateTIme = QDateTime::currentDateTime();

    // 设置 X 轴
    QDateTimeAxis *AxisX = new QDateTimeAxis();
    AxisX->setTitleText("日期");
    AxisX->setGridLineVisible(false);
    AxisX->setFormat("MM.dd");
    AxisX->setLabelsAngle(0);
    AxisX->setTickCount(days);

    // 设置日期范围
    QDateTime startDate = curDateTIme.addSecs(-60 * 60 * 24 * (days-1)); // 1 天前
    QDateTime endDate = curDateTIme;
    AxisX->setRange(startDate, endDate);

    // 设置 Y 轴
    QValueAxis *AxisY = new QValueAxis();
    AxisY->setTitleText("预约人数");
    AxisY->setGridLineVisible(false);

    // 添加数据系列和轴到图表
    chart->addSeries(series);
    chart->addAxis(AxisX, Qt::AlignBottom);
    chart->addAxis(AxisY, Qt::AlignLeft);
    series->attachAxis(AxisY);
    series->attachAxis(AxisX);

    // 循环添加数据点
    for (unsigned short index = 0; index < days; ++index)
    {
        QDateTime temp_AddTimePos = startDate.addSecs(index * 60 * 60 * 24); // 每天一个数据点
        series->append(temp_AddTimePos.toMSecsSinceEpoch(), *(item + index));
    }

    // 设置其他属性
    chart->setTheme(QtCharts::QChart::ChartThemeBlueCerulean);
    chart->setTitle("近期患者预约情况");
    chart->legend()->hide();

    // 将图表设置到视图中
    ui->my_chart->setChart(chart);
    ui->my_chart->resize(900, 400);
    ui->my_chart->setRenderHint(QPainter::Antialiasing);
    this->resize(1200, 600);


}
void chart_create::set(int day, double* item_group)
{
    days=day;
    item=item_group;
}
chart_create::~chart_create()
{
    delete ui;
}

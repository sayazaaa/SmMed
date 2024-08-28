#include "widget.h"
#include <QApplication>
#include <QFile>
#include <QFont>
#include <chart_create.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //加载样式表
    QFile file(":/css/index.css");
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        qApp->setStyleSheet(qss);
        file.close();
    }

    //全局字体
    QFont font("Arial", 10);
    a.setFont(font);
//    chart_create *p=new chart_create();
//    p->show();
    Widget *l=new Widget;
    l->show();
    return a.exec();
}

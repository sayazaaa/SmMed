#include "widget.h"
#include "login.h"
#include <QApplication>
#include <QFile>
#include <QFont>

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

    login *l=new login;
    l->show();




//    chat_box *c=new chat_box("aaaa","cccc");
//    c->show();
    return a.exec();
}
